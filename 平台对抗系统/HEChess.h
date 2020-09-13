#pragma once
#pragma execution_character_set("utf-8")

#include <QWidget>
#include "ui_HappyEForm.h"
#include <QPainter>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QDebug>
#include <ctime> 

class HEChess : public QWidget
{
	Q_OBJECT

public:
	HEChess(QWidget* parent = Q_NULLPTR);

	enum MapType   // 枚举类型
	{
		Empty = -1,
		bblue,
		blue,
		yellow,
		black,
		cute,
		www,
		wb
	};

	// 格子的宽高，画线起始点
	int gridWidth, gridHeight, startX, startY;
	int Mapdata[9][14];

	//改变棋盘的显示值
	void setMapStatus(void* p);

protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent*);
	void mousePressEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);

private:
	void InitGrid();

signals:
	void SignalSendMapdataone(int i1, int j1);// 发送 点击的坐标
	void SignalSendMapdatatwo(int i2, int j2);// 发送 释放的坐标
};