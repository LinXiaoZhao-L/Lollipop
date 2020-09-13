#pragma once
#pragma execution_character_set("utf-8")
#include <QWidget>
#include "ui_PlayerForm.h"
#include "PVPForm.h"
#include "GobangForm.h"
#include "HappyEForm.h"

#include <QSql>
#include <QDebug>
#include <QMessageBox>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlTableModel>

#include <QUdpSocket>

class PlayerForm : public QWidget
{
	Q_OBJECT

public:
	PlayerForm(QWidget *parent = Q_NULLPTR);
	~PlayerForm();

	QString Player,ServerIP;
	int ServerPort;

protected:
	void closeEvent(QCloseEvent*);

private slots:
	void on_PVP_clicked(); 
	void on_Rank_clicked();
	void on_PVE_GB_clicked();
	void on_PVE_HE_clicked();
	void on_back_clicked();
	void on_Refresh_clicked();
	void ReceiveAUser(QString User);

	void doProcessReadyRead();

private:
	Ui::PlayerForm ui;
	QUdpSocket* MySocket;
	PVPForm* PVPform;
	GobangForm* PVEGBform;
	HappyEForm* PVEHEform;
	QString PVP, PVEGB, PVEHE, GameCount;
	int count = 0;

	void Init();
	void HomeRank();

signals:
	void ShowMain(QString);
	void StartGame(QString Me, QString Ta,int Gage); // 挑战方:Gage=0;被挑战方:Gage=1
	void StartPVE(QString Player);
};
