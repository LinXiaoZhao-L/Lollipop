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

    // ������������ Online#name#OnlineEnd
    QString msg = QString("Online#%1#OnlineEnd").arg(Player);
    MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

    QSqlQuery query;
    query.exec(QString("update GamePlayer set IsLine='������' where Player='%1'").arg(User));
    query.exec(QString("select * from GamePlayer where Player = '%1'").arg(User)); // ��ѯ��ǰ�˺���Ϣ
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

        // 1.�յ���ս������Ϣ eg:fight#FromName#ToName#fightEnd
        if (msg.contains("fight#")) {
            QStringList list = msg.split("#");QString FromName = list.at(1);

            int Accpet = QMessageBox::question(this, tr("Hey,Man"), tr("ȷ�����ܶ�ս��"), QMessageBox::Yes, QMessageBox::No);
            if (Accpet == QMessageBox::Yes) {
                QSqlQuery query;
                query.exec(QString("update GamePlayer set IsLine='PVPing' where Player='%1'").arg(Player));

                // ���ͽ��ܶ�ս��Ϣ eg:Accpet#FightFromName#FightToName#AccpetEnd
                QString msg = QString("Accpet#%1#%2#AccpetEnd").arg(FromName).arg(Player);
                MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

                PVPform->show(); emit StartGame(Player, FromName, 1); // ���Ǳ���ս��
            }
        }
        // 2.�յ����ܶ�ս��Ϣ eg:Accpet#FightFromName#FightToName#Accpet
        else if (msg.contains("Accpet#")) {
            QStringList list = msg.split("#"); QString ToName = list.at(2);

            QSqlQuery query;
            query.exec(QString("update GamePlayer set IsLine='PVPing' where Player='%1'").arg(Player));
            QMessageBox::about(this, tr("Hey,Man"), tr("�Է�������ս\n��������Ծ�"));

            PVPform->show(); emit StartGame(Player, ToName, 0); // ������ս��
        }
    }
}
void PlayerForm::closeEvent(QCloseEvent*)
{
    // ֪ͨ���������� Offline#name#OfflineEnd
    QString msg = QString("Offline#%1#OfflineEnd").arg(Player);
    MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

    QSqlQuery query;
    query.exec(QString("update GamePlayer set IsLine='������' where Player='%1'").arg(Player));
}

void PlayerForm::on_PVP_clicked()
{
    int curRow = ui.SHOW->currentIndex().row();   // ��ȡ��ǰ�����λ���к�
    QModelIndex index = ui.SHOW->currentIndex();  // ��ȡ��ǰ�����λ������
    QString TaName = index.sibling(curRow, 0).data().toString();    // ��ȡ��ǰ�����λ�õĵ�ǰ�е�һ��Ԫ��
    if (curRow == -1) {
        QMessageBox::about(this, tr("��sir"), tr("��δѡ�����"));
    }
    else if (TaName == Player) {
        QMessageBox::about(this, tr("��sir"), tr("���� �� �� �� ����"));
    }
    else {
        QMessageBox::about(this, tr("OK,fine"), tr("���ͳɹ�\n�ȴ��Է����ܻ��߲�����(�޻���)"));

        // ���Ͷ�ս������Ϣ eg:fight#MyName#TaName#fightEnd
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
    query.exec(QString("update GamePlayer set IsLine='������' where Player='%1'").arg(Player));

    QString msg = QString("Offline#%1#OfflineEnd").arg(Player);
    MySocket->writeDatagram(msg.toUtf8(), QHostAddress(ServerIP), ServerPort);

    count++;emit ShowMain(QString::number(count));
    this->hide();
}
void PlayerForm::on_Refresh_clicked()
{
    // ��ǰ�������
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("select Player,GameCount,BotDefeat,TopScore,Isline from GamePlayer where IsLine!='������'");
    ui.SHOW->setModel(model);
    ui.SHOW->setAlternatingRowColors(true);
    ui.SHOW->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // ����Ӧ�п�
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