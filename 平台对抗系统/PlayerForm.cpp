#include "PlayerForm.h"

PlayerForm::PlayerForm(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    QObject::connect(ui.btn_PVP, SIGNAL(clicked(bool)), this, SLOT(on_PVP_clicked()));
    QObject::connect(ui.btn_Rank, SIGNAL(clicked(bool)), this, SLOT(on_Rank_clicked()));
    QObject::connect(ui.btn_PVE_GB, SIGNAL(clicked(bool)), this, SLOT(on_PVE_GB_clicked()));
    QObject::connect(ui.btn_PVE_HE, SIGNAL(clicked(bool)), this, SLOT(on_PVE_HE_clicked()));
    QObject::connect(ui.btn_SignOut, SIGNAL(clicked(bool)), this, SLOT(on_back_clicked()));
    QObject::connect(ui.btn_Refresh, SIGNAL(clicked(bool)), this, SLOT(on_Refresh_clicked()));

    Init();
}
PlayerForm::~PlayerForm()
{
}

void PlayerForm::Init()
{
    ServerPort = 9000;
    ServerIP = "10.87.252.11";

    PVPform = new PVPForm();
    PVEGBform = new GobangForm();
    PVEHEform = new HappyEForm();
    connect(this, SIGNAL(StartPVE(QString)), PVEGBform, SLOT(receive(QString)));
    connect(this, SIGNAL(StartPVE(QString)), PVEHEform, SLOT(REceive(QString)));
    connect(this, SIGNAL(StartGame(QString, QString, int)), PVPform, SLOT(Receive(QString, QString, int)));

    MySocket = new QUdpSocket(this);
    connect(MySocket, SIGNAL(readyRead()), this, SLOT(doProcessReadyRead()));
}
void PlayerForm::ReceiveAUser(QString User)
{
    Player = User;

    // 发送上线数据 Online#name#OnlineEnd
    QString msg = QString("Online#%1#OnlineEnd").arg(Player);
    MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

    QSqlQuery query;
    query.exec(QString("update GamePlayer set IsLine='在线上' where Player='%1'").arg(User));
    query.exec(QString("select * from GamePlayer where Player = '%1'").arg(User)); // 查询当前账号信息
    if (query.next()) {
        this->setWindowTitle("GamePlayer " + query.value(0).toString());
        PVP = query.value(2).toString();
        PVEGB = query.value(6).toString();
        PVEHE = query.value(7).toString();
        GameCount = query.value(5).toString();
        HomeRank();
    } 
}
void PlayerForm::HomeRank()
{
    QSqlQuery q; int str = 1;

    q.exec(QString("SELECT Player FROM GamePlayer WHERE Win>'%1'").arg(PVP)); 
    while (q.next()) { str++; }
    ui.label_PVP->setText(GameCount + " | " + QString::number(str)); str = 1;

    q.exec(QString("SELECT Player FROM GamePlayer WHERE BotDefeat>'%1'").arg(PVEGB.toInt()));
    while (q.next()) { str++; }
    ui.label_PVE_GB->setText(PVEGB + " | " + QString::number(str)); str = 1;

    q.exec(QString("SELECT Player FROM GamePlayer WHERE TopScore>'%1'").arg(PVEHE.toInt()));
    while (q.next()) { str++; }
    ui.label_PVE_HE->setText(PVEHE + " | " + QString::number(str));
}

void PlayerForm::doProcessReadyRead()
{
    QByteArray ba; QHostAddress addr; quint16 port;
    while (MySocket->hasPendingDatagrams()) {
        ba.clear(); addr.clear(); port = 0;
        ba.resize(MySocket->pendingDatagramSize());
        MySocket->readDatagram(ba.data(), ba.length(), &addr, &port);
        QString msg = QString(ba);

        // 1.收到对战请求信息 eg:fight#FromName#ToName#fightEnd
        if (msg.contains("fight#")) {
            QStringList list = msg.split("#");QString FromName = list.at(1);

            int Accpet = QMessageBox::question(this, tr("Hey,Man"), tr("确定接受对战？"), QMessageBox::Yes, QMessageBox::No);
            if (Accpet == QMessageBox::Yes) {
                QSqlQuery query;
                query.exec(QString("update GamePlayer set IsLine='PVPing' where Player='%1'").arg(Player));

                // 发送接受对战信息 eg:Accpet#FightFromName#FightToName#AccpetEnd
                QString msg = QString("Accpet#%1#%2#AccpetEnd").arg(FromName).arg(Player);
                MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

                PVPform->show(); emit StartGame(Player, FromName, 1); // 我是被挑战方
            }
        }
        // 2.收到接受对战信息 eg:Accpet#FightFromName#FightToName#Accpet
        else if (msg.contains("Accpet#")) {
            QStringList list = msg.split("#"); QString ToName = list.at(2);

            QSqlQuery query;
            query.exec(QString("update GamePlayer set IsLine='PVPing' where Player='%1'").arg(Player));
            QMessageBox::about(this, tr("Hey,Man"), tr("对方接受挑战\n即将进入对局"));

            PVPform->show(); emit StartGame(Player, ToName, 0); // 我是挑战方
        }
    }
}
void PlayerForm::closeEvent(QCloseEvent*)
{
    // 通知服务器下线 Offline#name#OfflineEnd
    QString msg = QString("Offline#%1#OfflineEnd").arg(Player);
    MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

    QSqlQuery query;
    query.exec(QString("update GamePlayer set IsLine='已离线' where Player='%1'").arg(Player));
}

void PlayerForm::on_PVP_clicked()
{
    int curRow = ui.SHOW->currentIndex().row();   // 提取当前鼠标点击位置行号
    QModelIndex index = ui.SHOW->currentIndex();  // 提取当前鼠标点击位置索引
    QString TaName = index.sibling(curRow, 0).data().toString();    // 获取当前鼠标点击位置的当前行第一个元素
    if (curRow == -1) {
        QMessageBox::about(this, tr("阿sir"), tr("宁未选择对手"));
    }
    else if (TaName == Player) {
        QMessageBox::about(this, tr("阿sir"), tr("《我 打 我 自 己》"));
    }
    else {
        QMessageBox::about(this, tr("OK,fine"), tr("发送成功\n等待对方接受或者不接受(无回音)"));

        // 发送对战请求信息 eg:fight#MyName#TaName#fightEnd
        QString msg = QString("fight#%1#%2#fightEnd").arg(Player).arg(TaName);
        MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);
    }
}
void PlayerForm::on_Rank_clicked()
{
    QModelIndex index = ui.SHOW->currentIndex();
    QSqlQueryModel* model = new QSqlQueryModel;
    if (index.column() == 1) {
        model->setQuery("SELECT Player,GameCount,IsLine FROM GamePlayer ORDER BY GameCount DESC");
    }
    else if (index.column() == 2) {
        model->setQuery("SELECT Player,BotDefeat,IsLine FROM GamePlayer ORDER BY BotDefeat DESC");
    }
    else if (index.column() == 3) {
        model->setQuery("SELECT Player,TopScore,IsLine FROM GamePlayer ORDER BY TopScore DESC");
    }
    else {
        model->setQuery("SELECT Player,Win,Draw,Lose,IsLine FROM GamePlayer ORDER BY Win DESC");
    }
    ui.SHOW->setModel(model);
}
void PlayerForm::on_PVE_GB_clicked()
{
    QSqlQuery query;
    query.exec(QString("update GamePlayer set IsLine='PVEing' where Player='%1'").arg(Player));
    PVEGBform->show(); emit StartPVE(Player);
}
void PlayerForm::on_PVE_HE_clicked()
{
    QSqlQuery query;
    query.exec(QString("update GamePlayer set IsLine='PVEing' where Player='%1'").arg(Player));
    PVEHEform->show(); emit StartPVE(Player);
}
void PlayerForm::on_back_clicked()
{
    QSqlQuery query;
    query.exec(QString("update GamePlayer set IsLine='已离线' where Player='%1'").arg(Player));

    QString msg = QString("Offline#%1#OfflineEnd").arg(Player);
    MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

    count++;emit ShowMain(QString::number(count));
    this->hide();
}
void PlayerForm::on_Refresh_clicked()
{
    // 当前在线玩家
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("select Player,GameCount,BotDefeat,TopScore,Isline from GamePlayer where IsLine!='已离线'");
    ui.SHOW->setModel(model);
    ui.SHOW->setAlternatingRowColors(true);
    ui.SHOW->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 自适应列宽
    int row_count = model->rowCount();
    for (int i = 0; i < row_count; i++) ui.SHOW->setRowHeight(i, 20);

    QSqlQuery query;
    query.exec(QString("select * from GamePlayer where Player = '%1'").arg(Player));
    if (query.next()) {
        PVP = query.value(2).toString();
        PVEGB = query.value(6).toString();
        PVEHE = query.value(7).toString();
        GameCount = query.value(5).toString();
        HomeRank();
    }
}