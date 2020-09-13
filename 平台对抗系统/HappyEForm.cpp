#include "HappyEForm.h"

HappyEForm::HappyEForm(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.btn_start, SIGNAL(clicked()), this, SLOT(on_btn_start_clicked()), Qt::UniqueConnection);
	QObject::connect(ui.btn_auto, SIGNAL(clicked()), this, SLOT(on_btn_auto_clicked()), Qt::UniqueConnection);

	Init();
}
HappyEForm::~HappyEForm()
{
}

void HappyEForm::Init()
{
	myform = new HEChess();  // 给Map地图分配空间
	connect(myform, SIGNAL(SignalSendMapdataone(int, int)), this, SLOT(doProcess(int, int)));  //发生鼠标点击坐标的信号连接
	connect(myform, SIGNAL(SignalSendMapdatatwo(int, int)), this, SLOT(doRelease(int, int)));  //发生鼠标释放坐标的信号连接
	ui.gridLayout->addWidget(myform); //在ui上显示地图页面

	Score = 0;
}
void HappyEForm::REceive(QString Player)
{
	Name = Player;
	this->setWindowTitle("消消乐使者 " + Name);

	QSqlQuery query;
	query.exec(QString("select * from GamePlayer where Player = '%1'").arg(Player)); // 查询当前账号信息
	if (query.next()) {
		MAXScore = query.value(6).toInt();
	}
}

//棋盘初始化、发送坐标
void HappyEForm::setMapInit()
{
	srand((unsigned)time(0));
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 14; j++) {
			Map[i][j] = rand() % 7;
		}
	}
	myform->setMapStatus(Map);
}
void HappyEForm::doProcess(int i1, int j1)
{
	qDebug() << "玩家点击：" << i1 << "," << j1;
	Pro_x = i1; Pro_y = j1;  //鼠标点击坐标赋值
}
void HappyEForm::doRelease(int i2, int j2)
{
	qDebug() << "玩家释放：" << i2 << "," << j2;
	Rel_x = i2; Rel_y = j2; //鼠标释放坐标赋值

	// 尝试交换形状
	std::swap(Map[Pro_x][Pro_y], Map[Rel_x][Rel_y]);
	myform->setMapStatus(Map);

	if ((abs(Rel_x - Pro_x) == 1 && Rel_y == Pro_y) || (abs(Rel_y - Pro_y) == 1 && Rel_x == Pro_x)) {
		Sleep(500);
		if (updateCheck()) {
			Eliminate();
			while (updateCheck()) {
				Eliminate();
			}
			Sleep(500);
			if (!checkend()) {
				END(); goto End;
			}
			ui.LCDnum->display(Score);
		}
		else { std::swap(Map[Rel_x][Rel_y], Map[Pro_x][Pro_y]); }
	}
	else { std::swap(Map[Rel_x][Rel_y], Map[Pro_x][Pro_y]); }
	myform->setMapStatus(Map);
End:
	this->update();
}

//检测是否有符合消除条件，通过bfs消除、bfs标记及越界检测，bfs算法检测消除，BFS算法
bool HappyEForm::updateCheck()
{
	bool isUpdate = false;
	memset(bfsVis, 0, sizeof(bfsVis));

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 14; j++) {
			if (bfsVis[i][j] == 0) {
				bool mark = false;
				if (bfs(i, j)) {
					mark = true;
					isUpdate = true;
				}
				if (mark) {
					mapCody();  //分成一个新地图和旧地图，用来显示消失效果
					Bfs(i, j);
				}
			}
		}
	}
	return isUpdate;
}
bool HappyEForm::bfsCheck(int x, int y, int squre)
{
	if (x < 0 || x >= 9 || y < 0 || y >= 14)return false;
	if (bfsVis[x][y] != 0 || Map[x][y] != squre)return false;
	return true;
}
bool HappyEForm::bfs(int x, int y)
{
	memset(isbfs, 0, sizeof(isbfs));
	int COUNT = 0;
	std::queue<node> B;
	node now, next;
	now.x = x, now.y = y;
	isbfs[x][y] = 1;

	int squre = Map[x][y];
	B.push(now);
	while (!B.empty()) {
		now = B.front();
		COUNT++;
		if (COUNT >= 4) return true;
		B.pop(); // 出队
		for (int i = 0; i < 4; i++) {
			next = now;
			next.x += xx[i], next.y += yy[i];
			if (bfsCheck(next.x, next.y, squre) == 0 || isbfs[next.x][next.y] == 1)continue;
			isbfs[next.x][next.y] = 1;
			B.push(next);
		}
	}
	return false;
}
void HappyEForm::Bfs(int x, int y)
{
	int ans = 0;
	std::queue<node> S;  //创建一个队列
	node now, next;
	now.x = x, now.y = y; //生成初始结点

	bfsVis[x][y] = 1;
	int squre = Map[x][y];
	Map[x][y] = HEChess::Empty;

	S.push(now); //队列中加入初始结点
	while (!S.empty()) {
		now = S.front();
		ans++;
		S.pop(); // 出队
		for (int i = 0; i < 4; i++) {
			next = now;
			next.x += xx[i], next.y += yy[i];  // 寻找[x,y]的上下左右的坐标   int xx[4] = { 0, 0, 1, -1 };int yy[4] = { 1, -1, 0, 0 };方向调整函数
			if (bfsCheck(next.x, next.y, squre) == 0)continue; // 不满足消除条件则跳过

			bfsVis[next.x][next.y] = 1;
			Map[next.x][next.y] = HEChess::Empty;

			S.push(next);  //依次插入坐标点
		}
	}
	Score += ans;
	displayUpdate();
}

void HappyEForm::dropNumberCount() // 下落高度统计
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 14; j++) {
			if (Map[i][j] == HEChess::Empty) {
				dropNumber[i][j] = 0;  //当该坐标为空时，初始化下落数组中对应的点为0，进行下一个循环
				continue;
			}

			// 该点不为空时

			int sum = 0;
			for (int z = j + 1; z < 14; z++) {
				if (Map[i][z] == HEChess::Empty)sum++;  // 计算当前坐标往下的所有空的坐标数  即下落高度
			}
			dropNumber[i][j] = sum;  //下落数组赋值
		}
	}
}
void HappyEForm::squreDrop() // 根据下落高度更新地图
{
	for (int j = 14 - 1; j >= 0; j--) {  //从下往上
		for (int i = 0; i < 9; i++) {
			int temp = dropNumber[i][j];  // 赋值每个坐标的下落高度
			if (temp != 0) {
				Map[i][j + temp] = Map[i][j]; //形状按高度下落
				Map[i][j] = HEChess::Empty;  //该点变空
			}
		}
	}
}
void HappyEForm::reflashMap() // 下落后的地图新元素添加
{
	srand((unsigned)time(0));
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 14; j++) {
			if (Map[i][j] == HEChess::Empty) {
				Map[i][j] = rand() % 7; //将地图上空的位置随机生成
			}
		}
	}
}
void HappyEForm::displayUpdate() // 消失效果
{
	myform->setMapStatus(Map);
	Sleep(500);
	myform->setMapStatus(Map_2);
	Sleep(500);
	myform->setMapStatus(Map);
	Sleep(500);
	myform->setMapStatus(Map_2);
	Sleep(500);
	myform->setMapStatus(Map);
}
void HappyEForm::mapCody() // 复制棋盘
{
	memcpy(Map_2, Map, sizeof(int) * 9 * 14); //地图复制
}
void HappyEForm::Eliminate() // 更新地图
{
	dropNumberCount();
	squreDrop();
	reflashMap();
	this->update();  //更新界面
	myform->setMapStatus(Map);  // 将数据映射到Gameform的地图中
}
bool HappyEForm::checkend() // 检测游戏结束
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 14; j++) {
			if (bfs(i, j)) return true;
		}
	}
	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 14; y++) {
			if (x + 1 < 9) {
				std::swap(Map[x][y], Map[x + 1][y]);
				if (bfs(x, y) || bfs(x + 1, y)) {
					std::swap(Map[x + 1][y], Map[x][y]);
					return true;
				}
				std::swap(Map[x + 1][y], Map[x][y]);
			}
			if (y + 1 < 14) {
				std::swap(Map[x][y], Map[x][y + 1]);
				if (bfs(x, y) || bfs(x, y + 1)) {
					std::swap(Map[x][y + 1], Map[x][y]);
					return true;
				}
				std::swap(Map[x][y + 1], Map[x][y]);
			}
		}
	}
	return false;
}
void HappyEForm::END() 
{
	if (!checkend()) {
		if (Score > MAXScore) {
			MAXScore = Score;
			QSqlQuery q;
			q.exec(QString("update GamePlayer set TopScore=%1 where Player='%2'").arg(MAXScore).arg(Name));
		}
		Score = 0; ui.LCDnum->display(Score);
		int Restart = QMessageBox::question(this, "游戏结束", "再来亿盘？", QMessageBox::Yes | QMessageBox::No);
		memset(Map, -1, sizeof(int) * 9 * 14); myform->setMapStatus(Map);
		if (Restart == QMessageBox::No) {
			this->close();
		}
	}
}

void HappyEForm::on_btn_start_clicked() // 界面按钮功能
{
	setMapInit();  //初始化地图
	while (updateCheck()){
		Eliminate();
	}
	END();
	ui.LCDnum->display(Score);
}
void HappyEForm::on_btn_auto_clicked()
{
c2:
	for (int y = 13; y >= 0; y--) {
		for (int x = 8; x >= 0; x--) {
			std::swap(Map[x][y], Map[x - 1][y]);
			if (updateCheck()) {
				Eliminate();
				while (updateCheck()) {
					Eliminate();
				}
				ui.LCDnum->display(Score);
				if (!checkend()) {
					END();
					goto end;
				}
				goto c2;
			}
			else { std::swap(Map[x - 1][y], Map[x][y]); }

			std::swap(Map[x][y], Map[x][y - 1]);
			if (updateCheck()) {
				Eliminate();
				while (updateCheck()) {
					Eliminate();
				}
				ui.LCDnum->display(Score);
				if (!checkend()) {
					END();goto end;
				}
				goto c2;
			}
			else { std::swap(Map[x][y - 1], Map[x][y]); }
		}
	}
end:
	this->update();
}


void HappyEForm::Sleep(int msec) // 睡眠时间
{
	QTime dieTime = QTime::currentTime().addMSecs(msec);
	while (QTime::currentTime() < dieTime)
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
void HappyEForm::closeEvent(QCloseEvent*)
{
	QSqlQuery query;
	query.exec(QString("update GamePlayer set IsLine='在线上' where Player='%1'").arg(Name));
}