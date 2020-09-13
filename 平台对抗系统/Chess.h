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

	//��������
	enum ChessType
	{
		Empty = 0,
		white,
		black,
		Forbidden
	};

	// ���ӵĿ�ߣ�������ʼ��
	int gridWidth, gridHeight, startX, startY;
	int chessdata[15][15];

	//�ı����̵���ʾֵ
	void setChessStatus(void* p);

protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent*);
	void mousePressEvent(QMouseEvent*);

private:
	void InitChess();

signals:
	void SignalSendChessdata(int i, int j);//���͵��������
};