#include "Chess.h"

Chess::Chess(QWidget* parent)
    : QWidget(parent)
{
    InitChess();
}

//������������,��굥������
void Chess::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.drawPixmap(this->rect(), QPixmap("../ƽ̨�Կ�ϵͳ/image/bg.jpg")); //���̱���

    //���û���
    QPen pen_1;
    pen_1.setColor(Qt::black);
    pen_1.setStyle(Qt::SolidLine);
    pen_1.setWidth(2);
    painter.setPen(pen_1);

    //������
    for (int i = 0; i <= 15; i++) {
        painter.drawLine(startX, startY + i * gridHeight, 16 * gridWidth, startY + i * gridHeight);
        painter.drawLine(startX + i * gridWidth, startY, startX + i * gridWidth, 16 * gridHeight);
    }

    //������
    QString chessfilename;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (chessdata[i][j] == white) {
                chessfilename = "../ƽ̨�Կ�ϵͳ/image/white1.png";
            }
            else if (chessdata[i][j] == black) {
                chessfilename = "../ƽ̨�Կ�ϵͳ/image/black1.png";
            }
            else {
                chessfilename.clear();continue;
            }
            painter.drawPixmap(startX + i * gridWidth, startY + j * gridHeight, gridWidth, gridHeight, QPixmap(chessfilename));
        }
    }
}
void Chess::resizeEvent(QResizeEvent* event)
{
    gridWidth = event->size().width() / GridCount;
    gridHeight = event->size().height() / GridCount;
    startX = gridWidth;
    startY = gridHeight;
}
void Chess::mousePressEvent(QMouseEvent* event)
{
    //������¼�����������[x,y]
    int x = event->x();
    int y = event->y();

    if (x >= startX && (x <= startX + 15 * gridWidth)) {
        if (y >= startY && (y <= startY + 15 * gridHeight)) {

            //ת������Ϊ��������[i,j]
            int i = 0, j = 0;
            i = (x - startX) / gridWidth;
            j = (y - startY) / gridHeight;

            this->update();
            SignalSendChessdata(i, j);
        }
    }
}

//��ʼ�����̺������ź�����
void Chess::InitChess()
{
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            chessdata[i][j] = Empty;
        }
    }
}
void Chess::setChessStatus(void* p)
{
    memcpy(chessdata, p, sizeof(int) * 15 * 15);
    this->update();
}