#include "Register.h"

Register::Register(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QObject::connect(ui.btn_Close, SIGNAL(clicked()), this, SLOT(on_Close_clicked()), Qt::UniqueConnection);
    QObject::connect(ui.btn_Register, SIGNAL(clicked()), this, SLOT(on_Register_clicked()), Qt::UniqueConnection);
    ui.Edit_PassWord->setEchoMode(QLineEdit::Password); // ��������

    Init();
}
void Register::Init()
{
    playerForm = new PlayerForm();
    connect(playerForm, SIGNAL(ShowMain(QString)), this, SLOT(doProBack(QString)));
    connect(this, SIGNAL(SendUserNo(QString)), playerForm, SLOT(ReceiveAUser(QString)));
}

/*==========�˺ŵ�¼==========*/
void Register::login()
{
    // ��ȡ�˻������룬���������
    QString account = this->ui.Edit_Account->text(); ui.Edit_Account->clear();
    QString password = this->ui.Edit_PassWord->text(); ui.Edit_PassWord->clear();

    if (account.isEmpty()) { QMessageBox::warning(this, tr("FBI WARNING"), tr("�˺�/�ǳƲ���Ϊ��")); }
    else if (password.isEmpty()) { QMessageBox::warning(this, tr("FBI WARNING"), tr("���벻��Ϊ��")); }
    else {
        QSqlTableModel model; QSqlQuery query;
        model.setTable("GamePlayer");
        model.setFilter(tr("Player = '%1' and PlayerPW = '%2'").arg(account).arg(password)); //��֤�˺�����
        model.select();
        if (model.rowCount() == 1) {
            model.setFilter(tr("Player = '%1' and IsLine = '������'").arg(account)); //��¼��ͻ
            model.select();
            if (model.rowCount() == 1) {
                playerForm->show(); emit SendUserNo(account); this->hide();
            }
            else { QMessageBox::warning(this, tr("����"), tr("���˺���������\n�㱻������(bushi)")); }
        }
        else {
            model.setFilter(tr("Player = '%1'").arg(account));
            model.select();
            if (model.rowCount() == 1) { QMessageBox::warning(this, tr("����"), tr("���������������")); }
            else {
                int ok = QMessageBox::question(this, tr("���˺Ų�����"), tr("��ȷ��ע�����˺���"), QMessageBox::Yes, QMessageBox::No);
                if (ok == QMessageBox::Yes) {
                    query.prepare("INSERT INTO GamePlayer (Player,PlayerPW,Win,Draw,Lose,GameCount,BotDefeat,TopScore,IsLine) "
                        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
                    query.bindValue(0, account);
                    query.bindValue(1, password);
                    query.bindValue(2, 0); query.bindValue(3, 0);
                    query.bindValue(4, 0); query.bindValue(5, "0/0/0");
                    query.bindValue(6, 0); query.bindValue(7, 0);
                    query.bindValue(8, "������");
                    query.exec();
                    QMessageBox::about(this, tr("Sign in"), tr("ע��ɹ�\n������ת����"));
                    playerForm->show(); emit SendUserNo(account); this->hide();
                }
            }
        }
    }
}
/*==========��¼��ť==========*/
void Register::on_Register_clicked()
{
    login();
}
/*==========�˳���ť==========*/
void Register::on_Close_clicked()
{
    this->close();
}
/*=======�����ź���ʾ����======*/
void Register::doProBack(QString str)
{
    this->show();
}