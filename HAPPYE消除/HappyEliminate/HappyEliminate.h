#pragma once
#pragma execution_character_set("utf-8")
#include <QtWidgets/QMainWindow>
#include "ui_HappyEliminate.h"
#include "Gameform.h"
#include <ctime>
#include <queue>
#include <iostream>
#include <QDebug>
#include <QTime>
#include <QLCDNumber>
#include <QMessageBox>

class HappyEliminate : public QMainWindow
{
    Q_OBJECT

public:
    HappyEliminate(QWidget *parent = Q_NULLPTR);

    struct node {
        int x, y;
    };

protected:
    void setMapInit();

    int Map[9][14], Map_2[9][14], dropNumber[9][14], bfsVis[9][14] , isbfs[9][14];
    int Score;
    int xx[4] = { 0, 0, 1, -1 };
    int yy[4] = { 1, -1, 0, 0 };
    int Pro_x, Pro_y, Rel_x, Rel_y;

    void mapCody();

    void dropNumberCount();
    void squreDrop();
    void reflashMap();
    void displayUpdate();

    bool updateCheck();
    bool bfsCheck(int x, int y, int squre);
    bool bfs(int x, int y);
    void Bfs(int x, int y);

    void Eliminate();
    bool checkend();

    void Sleep(int msec);

private slots:
    void doProcess(int i1, int j1);
    void doRelease(int i2, int j2);

    void on_btn_start_clicked();
    void on_btn_auto_clicked();

private:
    Ui::HappyEliminateClass ui;

    Gameform* myform;
    void Init();
};
