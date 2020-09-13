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

    // ��ս�����á���ʼ����ť;����ս��ѡ����ɫ��ʹ�á���ʼ����ť
    if (Gage == 0) {
        ui.btn_start->setEnabled(false); 
        ui.Rblack->setEnabled(false);
        ui.Rwhite->setEnabled(false);
    }

    // ֪ͨ����������Ծ� eg:Join#name#in#JoinEnd
    QString msg = QString("Join#%1#in#JoinEnd").arg(MyName);
    MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);
}
void PVPForm::Init()
{
    isDown = false;
    ServerPort = 9000;
    ServerIP = "10.87.252.11";
    isPushButton(false); ui.btn_regret->setEnabled(false);

    // ����Socket����
    MySocket = new QUdpSocket(this);
    connect(MySocket, SIGNAL(readyRead()), this, SLOT(doProcessReadyRead()));
    connect(MySocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(doProcessError(QAbstractSocket::SocketError)));

    // ����������ռ�,����ʾ����
    myform = new Chess();
    connect(myform, SIGNAL(SignalSendChessdata(int, int)), this, SLOT(doProcess(int, int)));
    
    ui.gridLayout->addWidget(myform); currentRole = Chess::Forbidden;
    RoleInit("../ƽ̨�Կ�ϵͳ/image/black.png", "../ƽ̨�Կ�ϵͳ/image/white.png");
}

// ���̳�ʼ��������
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
            // ��¼��һ��������Ϣ,����
            memcpy(HistoryData, ChessData, sizeof(int) * 15 * 15);
            ChessData[i][j] = currentRole; myform->setChessStatus(ChessData);
            isDown = false; ui.btn_regret->setEnabled(true);

            QSqlQuery q;
            // ��������,ʤ��
            if (checkwin(currentRole, ChessData)) {
                QString Msg = QString("GAME��%1 ��ñ���ʤ��!").arg(MyName); 
                ui.tEdit_Msg->append(Msg);
                ui.tEdit_Msg->append("<<< ������Ϸ���� >>>");

                // ֪ͨ�Է����½��� eg:data#from#to#x#y#role#dataEnd
                QString msg = QString("data#%1#%2#%3#%4#%5#dataEnd").arg(MyName).arg(TaName).arg(i).arg(j).arg(currentRole);
                MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

                // ����ʤ����Ϣ eg:game#from#to#Win#gameEnd
                msg = QString("game#%1#%2#Win#gameEnd").arg(MyName).arg(TaName);
                MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

                currentRole = Chess::Forbidden;//��׼����
            }
            // ��������,ƽ��
            else if (checkpeace()) {
                ui.tEdit_Msg->append("GAME������˫��սƽ");
                ui.tEdit_Msg->append("<<< ������Ϸ���� >>>");

                QString msg = QString("data#%1#%2#%3#%4#%5#dataEnd").arg(MyName).arg(TaName).arg(i).arg(j).arg(currentRole);
                MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

                // ����ƽ����Ϣ eg:game#from#to#Peace#gameEnd
                msg = QString("game#%1#%2#Peace#gameEnd").arg(MyName).arg(TaName);
                MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

                currentRole = Chess::Forbidden;
            }
            // ��������
            else {
                QString msg = QString("data#%1#%2#%3#%4#%5#dataEnd").arg(MyName).arg(TaName).arg(i).arg(j).arg(currentRole);
                MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);
            }
            // �л����ӷ�
            Rolechange(); setRole(currentRole);
        }
    }
}

// ������Ϸ
void PVPForm::on_btn_start_clicked()
{
    // ��ǰ������,"����"������
    isDown = true; ui.btn_regret->setEnabled(false);
    QSqlQuery query;
    
    // ѡ��,����������ʾ
    if (ui.Rwhite->isChecked()) {
        currentRole = Chess::white; // ��ǰ���ӷ�Ϊ��
        setRole(currentRole);
        setChessInit();
        isPushButton(true);

        ui.White_Name->setText(MyName);
        ui.Black_Name->setText(TaName);
        ui.tEdit_Msg->append("<<< ��Ϸ��ʼ >>>");

        // �������̳�ʼ����Ϣ eg:init#from#to#role#initEnd
        QString msg = QString("init#%1#%2#%3#initEnd").arg(MyName).arg(TaName).arg(currentRole);
        MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

        // ����ս��
        query.prepare("INSERT INTO GameRecord (Gno,Winner,Black,White,StartTime,EndTime) "
            "VALUES (?, ?, ?, ?, getdate(), getdate())");
        query.bindValue(0, "G00000");query.bindValue(1, ""); 
        query.bindValue(2, TaName); query.bindValue(3, MyName);
        query.exec();
    }
    else if (ui.Rblack->isChecked()) {
        currentRole = Chess::black; // ��ǰ���ӷ�Ϊ��
        setRole(currentRole);
        setChessInit();
        isPushButton(true);        

        ui.White_Name->setText(TaName);
        ui.Black_Name->setText(MyName);
        ui.tEdit_Msg->append("<<< ��Ϸ��ʼ >>>");

        QString msg = QString("init#%1#%2#%3#initEnd").arg(MyName).arg(TaName).arg(currentRole);
        MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

        query.prepare("INSERT INTO GameRecord (Gno,Winner,Black,White,StartTime,EndTime) "
            "VALUES (?, ?, ?, ?, getdate(), getdate())");
        query.bindValue(0, "G00000");query.bindValue(1, ""); 
        query.bindValue(2, MyName); query.bindValue(3, TaName);
        query.exec();
    }
    else {
        QMessageBox::warning(this, tr("FBI WARNING"), tr("��ѡ����Ӱ���"));
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

        // 1.�յ����̳�ʼ����Ϣ eg:init#role#initEnd
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
            ui.tEdit_Msg->append("<<< ��Ϸ��ʼ >>>");
        }
        // 2.�յ�����������Ϣ eg:data#from#to#x#y#role#dataEnd
        else if (msg.contains("data#")) {
            QStringList list = msg.split("#");
            int x = QString(list.at(3)).toInt();
            int y = QString(list.at(4)).toInt();
            int role = QString(list.at(5)).toInt();

            // ��¼��һ����������,��������
            memcpy(HistoryData, ChessData, sizeof(int) * 14 * 14);
            ChessData[x][y] = (Chess::ChessType)role;
            myform->setChessStatus(ChessData);

            // ��ǰ������,���ɻ���
            Rolechange(); setRole(currentRole);
            ui.btn_regret->setEnabled(false);
            isDown = true; 
        }
        // 3.�յ��Ծ���Ϣ eg:game#from#to#msg#gameEnd
        else if (msg.contains("game#")){
            QStringList list = msg.split("#"); QSqlQuery q;

            // �Է�����
            if (list.at(3) == "isRegret") {
                int Accpet = QMessageBox::question(this, tr("��"), tr("ȷ�����ܻ��壿"),QMessageBox::Yes, QMessageBox::No);
                if (Accpet == QMessageBox::Yes) {
                    // ��ԭ��һ�����
                    memcpy(ChessData, HistoryData, sizeof(int) * 15 * 15);
                    myform->setChessStatus(ChessData); this->update();
                    msg = QString("GAME: %1 ���л���").arg(TaName);
                    ui.tEdit_Msg->append(msg);

                    // ��ǰ��������,���ɻ���
                    Rolechange(); setRole(currentRole);
                    isDown = false; ui.btn_regret->setEnabled(false);

                    // ����ȷ�ϻ�����Ϣ eg:game#from#to#Regret#gameEnd
                    msg = QString("game#%1#%2#Regret#gameEnd").arg(MyName).arg(TaName);
                    MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);
                }
            }
            // ȷ�ϻ���
            else if (list.at(3) == "Regret") {
                // ��ԭ��һ�����
                memcpy(ChessData, HistoryData, sizeof(int) * 15 * 15);
                myform->setChessStatus(ChessData); this->update();
                msg = QString("GAME: %1 ���л���").arg("��");
                ui.tEdit_Msg->append(msg);

                // ��ǰ������,���ɻ���
                Rolechange(); setRole(currentRole);
                isDown = true; ui.btn_regret->setEnabled(false);
            }
            // �Է��ϸ�
            else if (list.at(3) == "Lose") {
                // ����ս��
                q.exec(QString("update GamePlayer set Win=Win+1 where Player='%1'").arg(MyName));
                q.exec(QString("update GamePlayer set Lose=Lose+1 where Player='%1'").arg(TaName));
                q.exec(QString("update GameRecord set Result='%1',EndTime=getdate() where Gno='G00000'").arg(MyName));
                
                msg = QString("GAME: %1 ��ñ���ʤ��!\n<<< ������Ϸ���� >>>").arg(MyName);ui.tEdit_Msg->append(msg);
                ReStart();// ���¿�ʼ
            }
            // �Է�ʤ��
            else if (list.at(3) == "Win") {
                q.exec(QString("update GamePlayer set Lose=Lose+1 where Player='%1'").arg(MyName));
                q.exec(QString("update GamePlayer set Win=Win+1 where Player='%1'").arg(TaName));
                q.exec(QString("update GameRecord set Result='%1',EndTime=getdate() where Gno='G00000'").arg(TaName));

                msg = QString("GAME: %1 ��ñ���ʤ��!\n<<< ������Ϸ���� >>>").arg(TaName);ui.tEdit_Msg->append(msg);
                ReStart();
            }
            // ƽ���ճ�
            else if (list.at(3) == "Peace"){
                // ����ս��
                q.exec(QString("update GamePlayer set Draw=Draw+1 where Player='%1'").arg(MyName));
                q.exec(QString("update GamePlayer set Draw=Draw+1 where Player='%1'").arg(TaName));
                q.exec(QString("update GameRecord set Result='%1',EndTime=getdate() where Gno='G00000'").arg("ƽ��"));

                ui.tEdit_Msg->append("GAME: ����˫��սƽ\n<<< ������Ϸ���� >>>");
                ReStart();
            }
            // �Է����
            else if (list.at(3) == "isPeace") {
                int Accpet = QMessageBox::question(this, tr("��"), tr("ȷ��������ͣ�"),QMessageBox::Yes, QMessageBox::No);
                if (Accpet == QMessageBox::Yes) {
                    // ����ƽ����Ϣ eg:game#from#to#Peace#gameEnd
                    msg = QString("game#%1#%2#Peace#gameEnd").arg(MyName).arg(TaName);
                    MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

                    ui.tEdit_Msg->append("GAME: ����˫��սƽ\n<<< ������Ϸ���� >>>");
                    ReStart();
                }
            }
            //// ���¿�ʼ����
            //else if (list.at(3) == "Restart") {
            //    ui.tEdit_Msg->append(TaName + "��������");

            //    int ret = QMessageBox::question(this, "����", "Yes?��ˬ�ڰ�\nNo?��������",QMessageBox::Yes | QMessageBox::No);
            //    if (ret == QMessageBox::Yes) {
            //        setChessInit();
            //        isPushButton(false);
            //        ui.btn_regret->setEnabled(false);
            //        ui.tEdit_Msg->append(MyName + "����,�������");
            //        RoleInit("../ƽ̨�Կ�ϵͳ/image/black.png", "../ƽ̨�Կ�ϵͳ/image/white.png");

            //        msg = QString("Msg#%1#%2#%3#MsgEnd").arg(MyName).arg(TaName).arg("�򣬴������");
            //        MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);
            //    }
            //    else {
            //        // ֪ͨ�Է��Լ�������
            //        msg = QString("Msg#%1#%2#%3#MsgEnd").arg(MyName).arg(TaName).arg("�������ӣ�");
            //        MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);
            //    }
            //}
            // �Է��˳�
            else if (list.at(3) == "Exit") {
                isPushButton(true);
                ui.btn_peace->setEnabled(false);
                ui.btn_regret->setEnabled(false);
                ui.btn_giveup->setEnabled(false);

                if (currentRole != Chess::Forbidden) {
                    QString Result = QString("%1����").arg(TaName);
                    q.exec(QString("update GamePlayer set Win=Win+1 where Player='%1'").arg(MyName));
                    q.exec(QString("update GamePlayer set Lose=Lose+1 where Player='%1'").arg(TaName));
                    q.exec(QString("update GameRecord set Result='%1',EndTime=getdate() where Gno='G00000'").arg(Result));
                
                    ui.tEdit_Msg->append(TaName + " �뿪�˶Ծ֣�TA...���ˣ�\n<<< EndGame >>>");
                }
                else {
                    ui.tEdit_Msg->append(TaName + " ����");
                    ui.tEdit_Msg->append(TaName + " ���˳���ǰ�Ծ�");
                    ui.tEdit_Msg->append("<<< EndGame >>>");
                }
            }
        }
        // 4.�յ�������Ϣ eg:Msg#from#to#content#MsgEnd
        else if (msg.contains("Msg#")) {
            QStringList list = msg.split("#");
            QString Content = list.at(3);
            msg = QString("%1��%2").arg(TaName).arg(Content);
            ui.tEdit_Msg->append(msg);
        }
    }
    UpdateRecord(MyName); UpdateRecord(TaName); // ����ս��
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
    RoleInit("../ƽ̨�Կ�ϵͳ/image/black.png", "../ƽ̨�Կ�ϵͳ/image/white.png");

    QSqlQuery query;
    query.exec(QString("update GamePlayer set IsLine='������' where Player='%1'").arg(MyName));

    // ����ַ����˳���Ϣ
    QString msg = QString("game#%1#%2#%3#gameEnd").arg(MyName).arg(TaName).arg("Exit");
    MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);
    // ������������˳���Ϣ
    msg = QString("Join#%1#out#JoinEnd").arg(MyName);
    MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);
}

// �ڰ���������ʾ���л�������ʾ���ֻ�����
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
        RoleInit("../ƽ̨�Կ�ϵͳ/image/black1.png", "../ƽ̨�Կ�ϵͳ/image/blank.png");
    else 
        RoleInit("../ƽ̨�Կ�ϵͳ/image/blank.png", "../ƽ̨�Կ�ϵͳ/image/white1.png");
}
void PVPForm::Rolechange()
{
    if (currentRole == Chess::black) 
        currentRole = Chess::white;
    else 
        currentRole = Chess::black;
}

// ���¿�ʼ���ж���Ӯƽ����ӱ���
void PVPForm::ReStart() 
{
    setChessInit();
    isPushButton(false);
    ui.btn_regret->setEnabled(false);
    currentRole = Chess::Forbidden;// ��ֹ����
    RoleInit("../ƽ̨�Կ�ϵͳ/image/black.png", "../ƽ̨�Կ�ϵͳ/image/white.png");

    //int ret = QMessageBox::question(this, "����,���ˣ�", "Yes?�����ھ�\nNo?��������", QMessageBox::Yes | QMessageBox::No);
    //if (ret == QMessageBox::Yes) {
    //    ui.tEdit_Msg->append(MyName + "��������");
    //    
    //    // �������¿�ʼ���� eg:game#from#to#Restart#gameEnd
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

    // �������������������
    for (int i = 0; i < 15; i++) {              
        for (int j = 0; j < 15; j++) {

            //���ұ�4������5��
            if (i < 11
                && chessData[i][j] == color
                && chessData[i + 1][j] == color
                && chessData[i + 2][j] == color
                && chessData[i + 3][j] == color
                && chessData[i + 4][j] == color)
            {
                return 1;
            }
            //���±�4������5��
            if (j < 11
                && chessData[i][j] == color
                && chessData[i][j + 1] == color
                && chessData[i][j + 2] == color
                && chessData[i][j + 3] == color
                && chessData[i][j + 4] == color)
            {
                return 1;
            }
            //������4������5��
            if (i > 3 && j < 11
                && chessData[i][j] == color
                && chessData[i - 1][j + 1] == color
                && chessData[i - 2][j + 2] == color
                && chessData[i - 3][j + 3] == color
                && chessData[i - 4][j + 4] == color)
            {
                return 1;
            }
            //������4������5��
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
    painter.drawPixmap(this->rect(), QPixmap("../ƽ̨�Կ�ϵͳ/image/bgStart.png"));
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

    if (Num < 1) {QMessageBox::about(this, tr("��sir"), tr("�㻹û����..."));}
    else {
        int ret = QMessageBox::question(this, "��sir", "�����Ҫ������", QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::Yes) {
            // �������������Ϣ game#from#to#isRegret#gameEnd
            QString msg = QString("game#%1#%2#isRegret#gameEnd").arg(MyName).arg(TaName);
            MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);
        }
    }
}
void PVPForm::on_btn_peace_clicked()
{
    // ���������Ϣ game#from#to#isPeace#gameEnd
    QString msg = QString("game#%1#%2#isPeace#gameEnd").arg(MyName).arg(TaName);
    MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);
}
void PVPForm::on_btn_giveup_clicked()
{
    // �����ϸ���Ϣ game#from#to#Lose#gameEnd
    QString msg = QString("game#%1#%2#Lose#gameEnd").arg(MyName).arg(TaName);
    MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

    QString Msg = QString("GAME: %1 ��ñ���ʤ��").arg(TaName); ui.tEdit_Msg->append(Msg);
    currentRole = Chess::Forbidden;
    ReStart();
}
void PVPForm::on_btn_Send_clicked() 
{
    QString Content = ui.tEdit_Send->toPlainText();
    if (!Content.isEmpty()) {
        // ����������Ϣ Msg#from#to#content#MsgEnd
        QString msg = QString("Msg#%1#%2#%3#MsgEnd").arg(MyName).arg(TaName).arg(Content);
        MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

        ui.tEdit_Msg->append("�㣺" + Content);
        ui.tEdit_Send->clear();
    }
}
void PVPForm::on_btn_Empty_clicked()
{
    int ret = QMessageBox::question(this, "����", "Yes�������\nNo�����Ϣ", QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes)
        ui.tEdit_Send->clear();
    else 
        ui.tEdit_Msg->clear();
}

void PVPForm::UpdateRecord(QString Player)
{
    QSqlQuery query;
    query.exec(QString("select * from GamePlayer where Player = '%1'").arg(Player)); // ��ѯ��ǰ�˺���Ϣ
    if (query.next()) {
        QString Win = query.value(2).toString();
        QString Draw = query.value(3).toString();
        QString Lose = query.value(4).toString();
        QString GameCount = QString("%1/%2/%3").arg(Win).arg(Draw).arg(Lose);
        query.exec(QString("update GamePlayer set GameCount='%1' where Player='%2'").arg(GameCount).arg(Player));
    }
}