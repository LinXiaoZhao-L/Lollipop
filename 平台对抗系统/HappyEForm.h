#pragma once
#pragma execution_character_set("utf-8")
#include <QWidget>
#include "ui_HappyEForm.h"

#include "HEChess.h"
#include <ctime>
#include <queue>
#include <iostream>
#include <QDebug>
#include <QTime>
#include <QLCDNumber>
#include <QMessageBox>
#include <QtSql/QSqlQuery>

class HappyEForm : public QWidget
{
	Q_OBJECT

public:
	HappyEForm(QWidget *parent = Q_NULLPTR);
	~HappyEForm();

	struct node {
		int x, y;
	};

protected:
    QString Name;
    int Map[9][14], Map_2[9][14], dropNumber[9][14], bfsVis[9][14], isbfs[9][14];
    int Score,MAXScore;
    int xx[4] = { 0, 0, 1, -1 };
    int yy[4] = { 1, -1, 0, 0 };
    int Pro_x, Pro_y, Rel_x, Rel_y;

    void END();
    void mapCody();   
    void Eliminate();
    void squreDrop();
    void reflashMap();
    void setMapInit();
    void displayUpdate();
    void dropNumberCount();

    bool checkend();
    bool updateCheck();
    bool bfsCheck(int x, int y, int squre);
    bool bfs(int x, int y);
    void Bfs(int x, int y);
    void Sleep(int msec);
    void closeEvent(QCloseEvent*);

private slots:
    void doProcess(int i1, int j1);
    void doRelease(int i2, int j2);
    void REceive(QString);
    void on_btn_start_clicked();
    void on_btn_auto_clicked();

private:
	Ui::HappyEForm ui;

    HEChess* myform;
    void Init();
};
