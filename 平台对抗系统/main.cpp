#include "Register.h"
#include <QtWidgets/QApplication>

bool OpenDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    QString dsn = QString::fromLocal8Bit("QtDSN");
    db.setDatabaseName(QString("DRIVER={SQL SERVER};"
        "SERVER=%1;"   //���������� 
        "DATABASE=%2;" //���ݿ��� 
        "UID=%3;"      //��¼�� 
        "PWD=%4;"      //��¼���� 
    ).arg("10.87.252.11")
        .arg("ƽ̨�Կ�ϵͳ")
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
    w.setWindowTitle("��¼����");
    w.show();

    /*�����ݿ�*/
    OpenDatabase();
    return a.exec();
}
