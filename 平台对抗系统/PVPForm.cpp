#include "PVPForm.h"

PVPForm::PVPForm(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    QObject::connect(ui.btn_start, SIGNAL(clicked()), this, SLOT(on_btn_start_clicked()), Qt::UniqueConnection);
    QObject::connect(ui.btn_regret, SIGNAL(clicked()), this, SLOT(on_btn_regret_clicked()), Qt::UniqueConnection);
    QObject::connect(ui.btn_peace, SIGNAL(clicked()), this, SLOT(on_btn_peace_clicked()), Qt::UniqueConnection);
    QObject::connect(ui.btn_giveup, SIGNAL(clicked()), this, SLOT(on_btn_giveup_clicked()), Qt::UniqueConnection);
    QObject::connect(ui.btn_Send, SIGNAL(clicked()), this, SLOT(on_btn_Send_clicked()), Qt::UniqueConnection);
    QObject::connect(ui.btn_Empty, SIGNAL(clicked()), this, SLOT(on_btn_Empty_clicked()), Qt::UniqueConnection);

    Init();
}
PVPForm::~PVPForm()
{
}

void PVPForm::Receive(QString Me, QString Ta,int Gage)
{
    isDown = false;
    MyName = Me; TaName = Ta;

    // 挑战方禁用“开始”按钮;被挑战方选择颜色与使用“开始”按钮
    if (Gage == 0) {
        ui.btn_start->setEnabled(false); 
        ui.Rblack->setEnabled(false);
        ui.Rwhite->setEnabled(false);
    }

    // 通知服务器进入对局 eg:Join#name#in#JoinEnd
    QString msg = QString("Join#%1#in#JoinEnd").arg(MyName);
    MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);
}
void PVPForm::Init()
{
    isDown = false;
    ServerPort = 9000;
    ServerIP = "10.87.252.11";
    isPushButton(false); ui.btn_regret->setEnabled(false);

    // 建立Socket连接
    MySocket = new QUdpSocket(this);
    connect(MySocket, SIGNAL(readyRead()), this, SLOT(doProcessReadyRead()));
    connect(MySocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(doProcessError(QAbstractSocket::SocketError)));

    // 申请棋盘类空间,并显示棋盘
    myform = new Chess();
    connect(myform, SIGNAL(SignalSendChessdata(int, int)), this, SLOT(doProcess(int, int)));
    
    ui.gridLayout->addWidget(myform); currentRole = Chess::Forbidden;
    RoleInit("../平台对抗系统/image/black.png", "../平台对抗系统/image/white.png");
}

// 棋盘初始化、落子
void PVPForm::setChessInit()
{
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            ChessData[i][j] = Chess::Empty;
        }
    }
    myform->setChessStatus(ChessData);
}
void PVPForm::doProcess(int i, int j)
{
    if (isDown && (currentRole != Chess::Forbidden)) {
        if (ChessData[i][j] == Chess::Empty) {
            // 记录上一轮棋盘信息,落子
            memcpy(HistoryData, ChessData, sizeof(int) * 15 * 15);
            ChessData[i][j] = currentRole; myform->setChessStatus(ChessData);
            isDown = false; ui.btn_regret->setEnabled(true);

            QSqlQuery q;
            // 五子连珠,胜利
            if (checkwin(currentRole, ChessData)) {
                QString Msg = QString("GAME：%1 获得本局胜利!").arg(MyName); 
                ui.tEdit_Msg->append(Msg);
                ui.tEdit_Msg->append("<<< 本局游戏结束 >>>");

                // 通知对方更新界面 eg:data#from#to#x#y#role#dataEnd
                QString msg = QString("data#%1#%2#%3#%4#%5#dataEnd").arg(MyName).arg(TaName).arg(i).arg(j).arg(currentRole);
                MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

                // 发送胜利信息 eg:game#from#to#Win#gameEnd
                msg = QString("game#%1#%2#Win#gameEnd").arg(MyName).arg(TaName);
                MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

                currentRole = Chess::Forbidden;//不准下棋
            }
            // 棋盘已满,平局
            else if (checkpeace()) {
                ui.tEdit_Msg->append("GAME：本局双方战平");
                ui.tEdit_Msg->append("<<< 本局游戏结束 >>>");

                QString msg = QString("data#%1#%2#%3#%4#%5#dataEnd").arg(MyName).arg(TaName).arg(i).arg(j).arg(currentRole);
                MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

                // 发送平局信息 eg:game#from#to#Peace#gameEnd
                msg = QString("game#%1#%2#Peace#gameEnd").arg(MyName).arg(TaName);
                MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

                currentRole = Chess::Forbidden;
            }
            // 正常落子
            else {
                QString msg = QString("data#%1#%2#%3#%4#%5#dataEnd").arg(MyName).arg(TaName).arg(i).arg(j).arg(currentRole);
                MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);
            }
            // 切换落子方
            Rolechange(); setRole(currentRole);
        }
    }
}

// 进行游戏
void PVPForm::on_btn_start_clicked()
{
    // 当前可落子,"悔棋"不可用
    isDown = true; ui.btn_regret->setEnabled(false);
    QSqlQuery query;
    
    // 选子,开启落子显示
    if (ui.Rwhite->isChecked()) {
        currentRole = Chess::white; // 当前落子方为白
        setRole(currentRole);
        setChessInit();
        isPushButton(true);

        ui.White_Name->setText(MyName);
        ui.Black_Name->setText(TaName);
        ui.tEdit_Msg->append("<<< 游戏开始 >>>");

        // 发送棋盘初始化信息 eg:init#from#to#role#initEnd
        QString msg = QString("init#%1#%2#%3#initEnd").arg(MyName).arg(TaName).arg(currentRole);
        MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

        // 更新战绩
        query.prepare("INSERT INTO GameRecord (Gno,Winner,Black,White,StartTime,EndTime) "
            "VALUES (?, ?, ?, ?, getdate(), getdate())");
        query.bindValue(0, "G00000");query.bindValue(1, ""); 
        query.bindValue(2, TaName); query.bindValue(3, MyName);
        query.exec();
    }
    else if (ui.Rblack->isChecked()) {
        currentRole = Chess::black; // 当前落子方为黑
        setRole(currentRole);
        setChessInit();
        isPushButton(true);        

        ui.White_Name->setText(TaName);
        ui.Black_Name->setText(MyName);
        ui.tEdit_Msg->append("<<< 游戏开始 >>>");

        QString msg = QString("init#%1#%2#%3#initEnd").arg(MyName).arg(TaName).arg(currentRole);
        MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

        query.prepare("INSERT INTO GameRecord (Gno,Winner,Black,White,StartTime,EndTime) "
            "VALUES (?, ?, ?, ?, getdate(), getdate())");
        query.bindValue(0, "G00000");query.bindValue(1, ""); 
        query.bindValue(2, MyName); query.bindValue(3, TaName);
        query.exec();
    }
    else {
        QMessageBox::warning(this, tr("FBI WARNING"), tr("请选择黑子白子"));
    }
}
void PVPForm::doProcessReadyRead()
{
    QByteArray ba; QHostAddress addr; quint16 port;
    while (MySocket->hasPendingDatagrams()) {
        ba.clear(); addr.clear(); port = 0;
        ba.resize(MySocket->pendingDatagramSize());
        MySocket->readDatagram(ba.data(), ba.length(), &addr, &port);
        QString msg = QString(ba);

        // 1.收到棋盘初始化信息 eg:init#role#initEnd
        if (msg.contains("init#")) {
            QStringList list = msg.split("#");
            if (QString(list.at(1)).toInt() == Chess::white) {
                currentRole = Chess::white;
                ui.White_Name->setText(TaName);
                ui.Black_Name->setText(MyName);
            }
            else if (QString(list.at(1)).toInt() == Chess::black) {
                currentRole = Chess::black;
                ui.White_Name->setText(MyName);
                ui.Black_Name->setText(TaName);
            }
            setChessInit();
            isPushButton(true);
            setRole(currentRole);
            ui.tEdit_Msg->append("<<< 游戏开始 >>>");
        }
        // 2.收到下棋数据信息 eg:data#from#to#x#y#role#dataEnd
        else if (msg.contains("data#")) {
            QStringList list = msg.split("#");
            int x = QString(list.at(3)).toInt();
            int y = QString(list.at(4)).toInt();
            int role = QString(list.at(5)).toInt();

            // 记录上一轮棋盘数据,更新棋盘
            memcpy(HistoryData, ChessData, sizeof(int) * 14 * 14);
            ChessData[x][y] = (Chess::ChessType)role;
            myform->setChessStatus(ChessData);

            // 当前可落子,不可悔棋
            Rolechange(); setRole(currentRole);
            ui.btn_regret->setEnabled(false);
            isDown = true; 
        }
        // 3.收到对局信息 eg:game#from#to#msg#gameEnd
        else if (msg.contains("game#")){
            QStringList list = msg.split("#"); QSqlQuery q;

            // 对方悔棋
            if (list.at(3) == "isRegret") {
                int Accpet = QMessageBox::question(this, tr("佬"), tr("确定接受悔棋？"),QMessageBox::Yes, QMessageBox::No);
                if (Accpet == QMessageBox::Yes) {
                    // 还原上一轮棋局
                    memcpy(ChessData, HistoryData, sizeof(int) * 15 * 15);
                    myform->setChessStatus(ChessData); this->update();
                    msg = QString("GAME: %1 进行悔棋").arg(TaName);
                    ui.tEdit_Msg->append(msg);

                    // 当前不可落子,不可悔棋
                    Rolechange(); setRole(currentRole);
                    isDown = false; ui.btn_regret->setEnabled(false);

                    // 发送确认悔棋信息 eg:game#from#to#Regret#gameEnd
                    msg = QString("game#%1#%2#Regret#gameEnd").arg(MyName).arg(TaName);
                    MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);
                }
            }
            // 确认悔棋
            else if (list.at(3) == "Regret") {
                // 还原上一轮棋局
                memcpy(ChessData, HistoryData, sizeof(int) * 15 * 15);
                myform->setChessStatus(ChessData); this->update();
                msg = QString("GAME: %1 进行悔棋").arg("你");
                ui.tEdit_Msg->append(msg);

                // 当前可落子,不可悔棋
                Rolechange(); setRole(currentRole);
                isDown = true; ui.btn_regret->setEnabled(false);
            }
            // 对方认负
            else if (list.at(3) == "Lose") {
                // 更新战绩
                q.exec(QString("update GamePlayer set Win=Win+1 where Player='%1'").arg(MyName));
                q.exec(QString("update GamePlayer set Lose=Lose+1 where Player='%1'").arg(TaName));
                q.exec(QString("update GameRecord set Result='%1',EndTime=getdate() where Gno='G00000'").arg(MyName));
                
                msg = QString("GAME: %1 获得本局胜利!\n<<< 本局游戏结束 >>>").arg(MyName);ui.tEdit_Msg->append(msg);
                ReStart();// 重新开始
            }
            // 对方胜利
            else if (list.at(3) == "Win") {
                q.exec(QString("update GamePlayer set Lose=Lose+1 where Player='%1'").arg(MyName));
                q.exec(QString("update GamePlayer set Win=Win+1 where Player='%1'").arg(TaName));
                q.exec(QString("update GameRecord set Result='%1',EndTime=getdate() where Gno='G00000'").arg(TaName));

                msg = QString("GAME: %1 获得本局胜利!\n<<< 本局游戏结束 >>>").arg(TaName);ui.tEdit_Msg->append(msg);
                ReStart();
            }
            // 平局收场
            else if (list.at(3) == "Peace"){
                // 更新战绩
                q.exec(QString("update GamePlayer set Draw=Draw+1 where Player='%1'").arg(MyName));
                q.exec(QString("update GamePlayer set Draw=Draw+1 where Player='%1'").arg(TaName));
                q.exec(QString("update GameRecord set Result='%1',EndTime=getdate() where Gno='G00000'").arg("平局"));

                ui.tEdit_Msg->append("GAME: 本局双方战平\n<<< 本局游戏结束 >>>");
                ReStart();
            }
            // 对方求和
            else if (list.at(3) == "isPeace") {
                int Accpet = QMessageBox::question(this, tr("佬"), tr("确定接受求和？"),QMessageBox::Yes, QMessageBox::No);
                if (Accpet == QMessageBox::Yes) {
                    // 发送平局信息 eg:game#from#to#Peace#gameEnd
                    msg = QString("game#%1#%2#Peace#gameEnd").arg(MyName).arg(TaName);
                    MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

                    ui.tEdit_Msg->append("GAME: 本局双方战平\n<<< 本局游戏结束 >>>");
                    ReStart();
                }
            }
            //// 重新开始请求
            //else if (list.at(3) == "Restart") {
            //    ui.tEdit_Msg->append(TaName + "：再来！");

            //    int ret = QMessageBox::question(this, "啊哈", "Yes?再爽亿把\nNo?溜了溜了",QMessageBox::Yes | QMessageBox::No);
            //    if (ret == QMessageBox::Yes) {
            //        setChessInit();
            //        isPushButton(false);
            //        ui.btn_regret->setEnabled(false);
            //        ui.tEdit_Msg->append(MyName + "：打,打个够！");
            //        RoleInit("../平台对抗系统/image/black.png", "../平台对抗系统/image/white.png");

            //        msg = QString("Msg#%1#%2#%3#MsgEnd").arg(MyName).arg(TaName).arg("打，打个够！");
            //        MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);
            //    }
            //    else {
            //        // 通知对方自己不打了
            //        msg = QString("Msg#%1#%2#%3#MsgEnd").arg(MyName).arg(TaName).arg("来个锤子！");
            //        MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);
            //    }
            //}
            // 对方退出
            else if (list.at(3) == "Exit") {
                isPushButton(true);
                ui.btn_peace->setEnabled(false);
                ui.btn_regret->setEnabled(false);
                ui.btn_giveup->setEnabled(false);

                if (currentRole != Chess::Forbidden) {
                    QString Result = QString("%1逃跑").arg(TaName);
                    q.exec(QString("update GamePlayer set Win=Win+1 where Player='%1'").arg(MyName));
                    q.exec(QString("update GamePlayer set Lose=Lose+1 where Player='%1'").arg(TaName));
                    q.exec(QString("update GameRecord set Result='%1',EndTime=getdate() where Gno='G00000'").arg(Result));
                
                    ui.tEdit_Msg->append(TaName + " 离开了对局，TA...跑了！\n<<< EndGame >>>");
                }
                else {
                    ui.tEdit_Msg->append(TaName + " 乏了");
                    ui.tEdit_Msg->append(TaName + " 已退出当前对局");
                    ui.tEdit_Msg->append("<<< EndGame >>>");
                }
            }
        }
        // 4.收到聊天信息 eg:Msg#from#to#content#MsgEnd
        else if (msg.contains("Msg#")) {
            QStringList list = msg.split("#");
            QString Content = list.at(3);
            msg = QString("%1：%2").arg(TaName).arg(Content);
            ui.tEdit_Msg->append(msg);
        }
    }
    UpdateRecord(MyName); UpdateRecord(TaName); // 更新战绩
}
void PVPForm::doProcessError(QAbstractSocket::SocketError err) 
{
    qDebug() << err;
}
void PVPForm::closeEvent(QCloseEvent*)
{
    isDown = false;
    isPushButton(false);
    ui.White_Name->setText("");
    ui.Black_Name->setText("");
    ui.btn_regret->setEnabled(false);
    RoleInit("../平台对抗系统/image/black.png", "../平台对抗系统/image/white.png");

    QSqlQuery query;
    query.exec(QString("update GamePlayer set IsLine='在线上' where Player='%1'").arg(MyName));

    // 向对手发送退出信息
    QString msg = QString("game#%1#%2#%3#gameEnd").arg(MyName).arg(TaName).arg("Exit");
    MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);
    // 向服务器发送退出信息
    msg = QString("Join#%1#out#JoinEnd").arg(MyName);
    MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);
}

// 黑白子落子显示、切换落子显示、轮换落子
void PVPForm::RoleInit(const QString blackfilename, const QString whitefilename)
{
    ui.label_black->setPixmap(QPixmap(blackfilename));
    ui.label_black->setScaledContents(true);
    ui.label_white->setPixmap(QPixmap(whitefilename));
    ui.label_white->setScaledContents(true);
}
void PVPForm::setRole(Chess::ChessType Role)
{
    if (Role == Chess::black) 
        RoleInit("../平台对抗系统/image/black1.png", "../平台对抗系统/image/blank.png");
    else 
        RoleInit("../平台对抗系统/image/blank.png", "../平台对抗系统/image/white1.png");
}
void PVPForm::Rolechange()
{
    if (currentRole == Chess::black) 
        currentRole = Chess::white;
    else 
        currentRole = Chess::black;
}

// 重新开始、判断输赢平、添加背景
void PVPForm::ReStart() 
{
    setChessInit();
    isPushButton(false);
    ui.btn_regret->setEnabled(false);
    currentRole = Chess::Forbidden;// 禁止落子
    RoleInit("../平台对抗系统/image/black.png", "../平台对抗系统/image/white.png");

    //int ret = QMessageBox::question(this, "啊哈,输了？", "Yes?再来亿局\nNo?溜了溜了", QMessageBox::Yes | QMessageBox::No);
    //if (ret == QMessageBox::Yes) {
    //    ui.tEdit_Msg->append(MyName + "：再来！");
    //    
    //    // 发送重新开始请求 eg:game#from#to#Restart#gameEnd
    //    QString msg = QString("game#%1#%2#%3#gameEnd").arg(MyName).arg(TaName).arg("Restart");
    //    MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);
    //}
}
bool PVPForm::checkpeace()
{
    int Count = 0;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (ChessData[i][j] == Chess::Empty)
                Count++;
        }
    }
    return (Count == 0);
}
bool PVPForm::checkwin(int color, void* myform)
{
    typedef int(*p)[15];
    p chessData = p(myform);

    // 遍历数组查找五子连珠
    for (int i = 0; i < 15; i++) {              
        for (int j = 0; j < 15; j++) {

            //和右边4子连成5个
            if (i < 11
                && chessData[i][j] == color
                && chessData[i + 1][j] == color
                && chessData[i + 2][j] == color
                && chessData[i + 3][j] == color
                && chessData[i + 4][j] == color)
            {
                return 1;
            }
            //和下边4子连成5个
            if (j < 11
                && chessData[i][j] == color
                && chessData[i][j + 1] == color
                && chessData[i][j + 2] == color
                && chessData[i][j + 3] == color
                && chessData[i][j + 4] == color)
            {
                return 1;
            }
            //和左下4子连成5个
            if (i > 3 && j < 11
                && chessData[i][j] == color
                && chessData[i - 1][j + 1] == color
                && chessData[i - 2][j + 2] == color
                && chessData[i - 3][j + 3] == color
                && chessData[i - 4][j + 4] == color)
            {
                return 1;
            }
            //和右下4子连成5个
            if (i < 11 && j < 11
                && chessData[i][j] == color
                && chessData[i + 1][j + 1] == color
                && chessData[i + 2][j + 2] == color
                && chessData[i + 3][j + 3] == color
                && chessData[i + 4][j + 4] == color)
            {
                return 1;
            }
        }
    }
    return 0;
}
void PVPForm::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawPixmap(this->rect(), QPixmap("../平台对抗系统/image/bgStart.png"));
}

void PVPForm::isPushButton(bool TF)
{
    ui.btn_peace->setEnabled(TF);
    ui.btn_giveup->setEnabled(TF);
    if (TF) { 
        ui.btn_start->setEnabled(false); 
        ui.Rblack->setEnabled(false);
        ui.Rwhite->setEnabled(false);
    }
    else {
        ui.btn_start->setEnabled(true);
        ui.Rblack->setEnabled(true);
        ui.Rwhite->setEnabled(true);
    }
}
void PVPForm::on_btn_regret_clicked()
{
    int Num = 0; 
    Chess::ChessType Role = (currentRole == Chess::white) ? Chess::black : Chess::white;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (ChessData[i][j] == Role) 
                Num++;
        }
    }

    if (Num < 1) {QMessageBox::about(this, tr("阿sir"), tr("你还没下呢..."));}
    else {
        int ret = QMessageBox::question(this, "阿sir", "你真的要悔棋吗？", QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::Yes) {
            // 发送请求悔棋信息 game#from#to#isRegret#gameEnd
            QString msg = QString("game#%1#%2#isRegret#gameEnd").arg(MyName).arg(TaName);
            MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);
        }
    }
}
void PVPForm::on_btn_peace_clicked()
{
    // 发送求和信息 game#from#to#isPeace#gameEnd
    QString msg = QString("game#%1#%2#isPeace#gameEnd").arg(MyName).arg(TaName);
    MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);
}
void PVPForm::on_btn_giveup_clicked()
{
    // 发送认负信息 game#from#to#Lose#gameEnd
    QString msg = QString("game#%1#%2#Lose#gameEnd").arg(MyName).arg(TaName);
    MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

    QString Msg = QString("GAME: %1 获得本局胜利").arg(TaName); ui.tEdit_Msg->append(Msg);
    currentRole = Chess::Forbidden;
    ReStart();
}
void PVPForm::on_btn_Send_clicked() 
{
    QString Content = ui.tEdit_Send->toPlainText();
    if (!Content.isEmpty()) {
        // 发送聊天信息 Msg#from#to#content#MsgEnd
        QString msg = QString("Msg#%1#%2#%3#MsgEnd").arg(MyName).arg(TaName).arg(Content);
        MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

        ui.tEdit_Msg->append("你：" + Content);
        ui.tEdit_Send->clear();
    }
}
void PVPForm::on_btn_Empty_clicked()
{
    int ret = QMessageBox::question(this, "啊哈", "Yes清空输入\nNo清空消息", QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes)
        ui.tEdit_Send->clear();
    else 
        ui.tEdit_Msg->clear();
}

void PVPForm::UpdateRecord(QString Player)
{
    QSqlQuery query;
    query.exec(QString("select * from GamePlayer where Player = '%1'").arg(Player)); // 查询当前账号信息
    if (query.next()) {
        QString Win = query.value(2).toString();
        QString Draw = query.value(3).toString();
        QString Lose = query.value(4).toString();
        QString GameCount = QString("%1/%2/%3").arg(Win).arg(Draw).arg(Lose);
        query.exec(QString("update GamePlayer set GameCount='%1' where Player='%2'").arg(GameCount).arg(Player));
    }
}