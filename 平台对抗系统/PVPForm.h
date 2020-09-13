#pragma once
#pragma execution_character_set("utf-8")
#include <QWidget>
#include "ui_PVPForm.h"
#include "Chess.h"

#include <QtSql/QSqlQuery>

#include <QDebug>
#include <QPainter>
#include <QUdpSocket>
#include <QMessagebox>

class PVPForm : public QWidget
{
	Q_OBJECT

public:
	PVPForm(QWidget *parent = Q_NULLPTR);
	~PVPForm();

	QString ServerIP;
	int ServerPort;

protected:
	void paintEvent(QPaintEvent*);
	void closeEvent(QCloseEvent*);

private slots:	
	void on_btn_Send_clicked();
	void on_btn_Empty_clicked();
	void on_btn_start_clicked();
	void on_btn_peace_clicked();
	void on_btn_regret_clicked();
	void on_btn_giveup_clicked();
	
	void doProcessReadyRead();
	void doProcess(int i, int j);
	void Receive(QString Me, QString Ta, int Gage);
	void doProcessError(QAbstractSocket::SocketError);

private:
	Ui::PVPForm ui;

	Chess* myform;
	QUdpSocket* MySocket;
	QString MyName, TaName;
	Chess::ChessType currentRole;
	
	int ChessData[15][15], HistoryData[15][15];
	bool isDown;

	void Init();
	void ReStart();
	void Rolechange();
	void setChessInit();
	void isPushButton(bool TF);
	void setRole(Chess::ChessType Role);
	void RoleInit(const QString whitefilename, const QString blackfilename);
	void UpdateRecord(QString Player);

	bool checkwin(int color, void* myform);
	bool checkpeace();
};
