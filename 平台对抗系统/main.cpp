#include "Register.h"
#include <QtWidgets/QApplication>

bool OpenDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    QString dsn = QString::fromLocal8Bit("QtDSN");
    db.setDatabaseName(QString("DRIVER={SQL SERVER};"
        "SERVER=%1;"   //服务器名称 
        "DATABASE=%2;" //数据库名 
        "UID=%3;"      //登录名 
        "PWD=%4;"      //登录密码 
    ).arg("10.87.252.11")
        .arg("平台对抗系统")
        .arg("sa")
        .arg("245619")
    );
    if (!db.open()){
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            db.lastError().databaseText(), QMessageBox::Cancel);
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Register w;
    w.setWindowTitle("登录界面");
    w.show();

    /*打开数据库*/
    OpenDatabase();
    return a.exec();
}
