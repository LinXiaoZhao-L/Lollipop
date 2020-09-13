#include "Register.h"

Register::Register(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QObject::connect(ui.btn_Close, SIGNAL(clicked()), this, SLOT(on_Close_clicked()), Qt::UniqueConnection);
    QObject::connect(ui.btn_Register, SIGNAL(clicked()), this, SLOT(on_Register_clicked()), Qt::UniqueConnection);
    ui.Edit_PassWord->setEchoMode(QLineEdit::Password); // 隐藏密码

    Init();
}
void Register::Init()
{
    playerForm = new PlayerForm();
    connect(playerForm, SIGNAL(ShowMain(QString)), this, SLOT(doProBack(QString)));
    connect(this, SIGNAL(SendUserNo(QString)), playerForm, SLOT(ReceiveAUser(QString)));
}

/*==========账号登录==========*/
void Register::login()
{
    // 获取账户和密码，并清空输入
    QString account = this->ui.Edit_Account->text(); ui.Edit_Account->clear();
    QString password = this->ui.Edit_PassWord->text(); ui.Edit_PassWord->clear();

    if (account.isEmpty()) { QMessageBox::warning(this, tr("FBI WARNING"), tr("账号/昵称不能为空")); }
    else if (password.isEmpty()) { QMessageBox::warning(this, tr("FBI WARNING"), tr("密码不能为空")); }
    else {
        QSqlTableModel model; QSqlQuery query;
        model.setTable("GamePlayer");
        model.setFilter(tr("Player = '%1' and PlayerPW = '%2'").arg(account).arg(password)); //验证账号密码
        model.select();
        if (model.rowCount() == 1) {
            model.setFilter(tr("Player = '%1' and IsLine = '已离线'").arg(account)); //登录冲突
            model.select();
            if (model.rowCount() == 1) {
                playerForm->show(); emit SendUserNo(account); this->hide();
            }
            else { QMessageBox::warning(this, tr("啊这"), tr("该账号已在线上\n你被盗号了(bushi)")); }
        }
        else {
            model.setFilter(tr("Player = '%1'").arg(account));
            model.select();
            if (model.rowCount() == 1) { QMessageBox::warning(this, tr("啊这"), tr("宁或许输错了密码")); }
            else {
                int ok = QMessageBox::question(this, tr("该账号不存在"), tr("你确定注册新账号吗？"), QMessageBox::Yes, QMessageBox::No);
                if (ok == QMessageBox::Yes) {
                    query.prepare("INSERT INTO GamePlayer (Player,PlayerPW,Win,Draw,Lose,GameCount,BotDefeat,TopScore,IsLine) "
                        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
                    query.bindValue(0, account);
                    query.bindValue(1, password);
                    query.bindValue(2, 0); query.bindValue(3, 0);
                    query.bindValue(4, 0); query.bindValue(5, "0/0/0");
                    query.bindValue(6, 0); query.bindValue(7, 0);
                    query.bindValue(8, "在线上");
                    query.exec();
                    QMessageBox::about(this, tr("Sign in"), tr("注册成功\n即将跳转界面"));
                    playerForm->show(); emit SendUserNo(account); this->hide();
                }
            }
        }
    }
}
/*==========登录按钮==========*/
void Register::on_Register_clicked()
{
    login();
}
/*==========退出按钮==========*/
void Register::on_Close_clicked()
{
    this->close();
}
/*=======接受信号显示界面======*/
void Register::doProBack(QString str)
{
    this->show();
}