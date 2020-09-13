#include "HEChess.h"

HEChess::HEChess(QWidget* parent)
    : QWidget(parent)
{
    InitGrid();
}

//初始化棋盘和棋盘信号数据
void HEChess::InitGrid()
{
    //srand((unsigned)time(0));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 14; j++) {
            Mapdata[i][j] = MapType::Empty;
        }
    }
}
void HEChess::setMapStatus(void* p)
{
    memcpy(Mapdata, p, sizeof(int) * 9 * 14);
    this->update();
}

//画棋盘与棋子,鼠标单击落子
void HEChess::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    //设置画笔
    QPen pen_1;
    pen_1.setColor(Qt::black);
    pen_1.setStyle(Qt::SolidLine);
    pen_1.setWidth(1);
    painter.setPen(pen_1);

    //画棋盘
    for (int i = 0; i <= 14; i++)
        painter.drawLine(startX, startY + i * gridHeight, 10 * gridWidth, startY + i * gridHeight);
    for (int j = 0; j <= 9; j++)
        painter.drawLine(startX + j * gridWidth, startY, startX + j * gridWidth, 15 * gridHeight);

    //画棋子
    QString Shapefilename;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 14; j++) {
            if (Mapdata[i][j] == bblue) {
                Shapefilename = "../平台对抗系统/image1/bblue_cat.png";
            }
            else if (Mapdata[i][j] == blue) {
                Shapefilename = "../平台对抗系统/image1/blue_cat.png";
            }
            else if (Mapdata[i][j] == yellow) {
                Shapefilename = "../平台对抗系统/image1/yellow_cat.png";
            }
            else if (Mapdata[i][j] == black) {
                Shapefilename = "../平台对抗系统/image1/black_cat.png";
            }
            else if (Mapdata[i][j] == cute) {
                Shapefilename = "../平台对抗系统/image1/cute_cat.png";
            }
            else if (Mapdata[i][j] == Empty) {
                Shapefilename = "../平台对抗系统/image1/PI.png";
            }
            else if (Mapdata[i][j] == www) {
                Shapefilename = "../平台对抗系统/image1/www.png";
            }
            else if (Mapdata[i][j] == wb) {
                Shapefilename = "../平台对抗系统/image1/wb.png";
            }
            else {
                Shapefilename.clear();
                continue;
            }
            painter.drawPixmap(startX + i * gridWidth, startY + j * gridHeight, gridWidth, gridHeight, QPixmap(Shapefilename));
        }
    }
}
void HEChess::resizeEvent(QResizeEvent* event)
{
    gridWidth = event->size().width() / 11;
    gridHeight = event->size().height() / 15;
    startX = gridWidth;
    startY = gridHeight;
}
void HEChess::mousePressEvent(QMouseEvent* event)
{
    //鼠标点击事件产生的坐标[x,y]
    int x1 = event->x();
    int y1 = event->y();
    if (x1 >= startX && (x1 <= startX + 9 * gridWidth)) {
        if (y1 >= startY && (y1 <= startY + 14 * gridHeight)) {  //将鼠标点击范围控制在棋盘内
                    //转换坐标为棋盘坐标[i1,j1]
            int i1 = 0, j1 = 0;
            i1 = (x1 - startX) / gridWidth;
            j1 = (y1 - startY) / gridHeight;
            //Mapdata[i][j] = cute;    
            this->update();
            SignalSendMapdataone(i1, j1);
        }
    }

}
void HEChess::mouseReleaseEvent(QMouseEvent* event)
{
    //鼠标释放事件产生的坐标[x,y]
    int x2 = event->x();
    int y2 = event->y();
    if (x2 >= startX && (x2 <= startX + 9 * gridWidth)) {
        if (y2 >= startY && (y2 <= startY + 14 * gridHeight)) {

            //转换坐标为棋盘坐标[i1,j1]
            int i2 = 0, j2 = 0;
            i2 = (x2 - startX) / gridWidth;
            j2 = (y2 - startY) / gridHeight;
            //Mapdata[i][j] = cute;    
            this->update();
            SignalSendMapdatatwo(i2, j2);
        }
    }

}