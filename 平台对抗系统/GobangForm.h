#pragma once
#pragma execution_character_set("utf-8")

#include <QWidget>
#include "ui_GobangForm.h"

#include <QtSql/QSqlQuery>
#include <QPainter>
#include "Chess.h"
#include <QDebug>
#include <QMessagebox>
#include <QTime> 
#include <ctime> 

class GobangForm : public QWidget
{
	Q_OBJECT

public:
	GobangForm(QWidget *parent = Q_NULLPTR);
	~GobangForm();

	enum PKtype { offensive, defensive,STOP }; // 先手和后手

protected:
	Chess::ChessType currentRole;
	PKtype currentPK;

	void paintEvent(QPaintEvent*);
	void closeEvent(QCloseEvent*);

	int Score[15][15];
	int Player_score[15][15], AI_score[15][15];
	int ChessData[15][15],HistoryData[15][15];

	void Rolechange();
	void setChessInit();
	void setRole(Chess::ChessType Role);
	void ChessScore(Chess::ChessType Role);
	bool GobangWIN(Chess::ChessType Role, int player);
	void FindbestScore(int& x, int& y, Chess::ChessType Role);
	void RoleInit(const QString whitefilename, const QString blackfilename);
	void Sleep(int msec);
	void isPushBotton(bool TF);

private slots:
	void on_btn_start_clicked();
	void on_btn_regret_clicked();
	void on_btn_peace_clicked();
	void on_btn_giveup_clicked();

	void doProcess(int i, int j);
	void receive(QString);

private:
	Ui::GobangForm ui;
	QString Name;
	int count;

	void Init();
	Chess* myform;
	
	int checkwin(int color, void* myform);
	void playwithAI(int& x, int& y, Chess::ChessType Role);
	bool checkpeace();
};
