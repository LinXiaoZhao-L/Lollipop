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

	enum MapType   // ö������
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

	// ���ӵĿ�ߣ�������ʼ��
	int gridWidth, gridHeight, startX, startY;
	int Mapdata[9][14];

	//�ı����̵���ʾֵ
	void setMapStatus(void* p);

protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent*);
	void mousePressEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);

private:
	void InitGrid();

signals:
	void SignalSendMapdataone(int i1, int j1);// ���� ���������
	void SignalSendMapdatatwo(int i2, int j2);// ���� �ͷŵ�����
};