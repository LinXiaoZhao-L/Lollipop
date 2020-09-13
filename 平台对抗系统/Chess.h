#pragma once
#pragma execution_character_set("utf-8")

#include <QWidget>
#include "ui_PVPForm.h"
#include <QPainter>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QDebug>

#define GridCount 17

class Chess : public QWidget
{
	Q_OBJECT

public:
	Chess(QWidget* parent = Q_NULLPTR);

	//棋子类型
	enum ChessType
	{
		Empty = 0,
		white,
		black,
		Forbidden
	};

	// 格子的宽高，画线起始点
	int gridWidth, gridHeight, startX, startY;
	int chessdata[15][15];

	//改变棋盘的显示值
	void setChessStatus(void* p);

protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent*);
	void mousePressEvent(QMouseEvent*);

private:
	void InitChess();

signals:
	void SignalSendChessdata(int i, int j);//发送点击的坐标
};