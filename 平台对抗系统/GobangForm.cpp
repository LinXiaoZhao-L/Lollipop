#include "GobangForm.h"

GobangForm::GobangForm(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.btn_start, SIGNAL(clicked()), this, SLOT(on_btn_start_clicked()), Qt::UniqueConnection);
	QObject::connect(ui.btn_regret, SIGNAL(clicked()), this, SLOT(on_btn_regret_clicked()), Qt::UniqueConnection);
	QObject::connect(ui.btn_peace, SIGNAL(clicked()), this, SLOT(on_btn_peace_clicked()), Qt::UniqueConnection);
	QObject::connect(ui.btn_giveup, SIGNAL(clicked()), this, SLOT(on_btn_giveup_clicked()), Qt::UniqueConnection);

	Init();
}
GobangForm::~GobangForm()
{
}

void GobangForm::Init()
{
	count = 0;
	currentRole = Chess::Empty;
	RoleInit("../平台对抗系统/image/black.png", "../平台对抗系统/image/white.png");

	//申请棋盘类空间
	myform = new Chess();
	connect(myform, SIGNAL(SignalSendChessdata(int, int)), this, SLOT(doProcess(int, int)));
	ui.grid_chess->addWidget(myform);
}
void GobangForm::receive(QString Player)
{
	Name = Player;
	isPushBotton(false);
	this->setWindowTitle(Name + " vs THE bot");
}

// 棋盘初始化、发送坐标
void GobangForm::setChessInit()
{
	RoleInit("../平台对抗系统/image/black.png", "../平台对抗系统/image/white.png");
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			ChessData[i][j] = Chess::Empty;
		}
	}
	// 若AI先手，默认在[8，8]处落黑子
	if (currentPK == PKtype::defensive) ChessData[7][7] = Chess::black;
	myform->setChessStatus(ChessData);
}
void GobangForm::doProcess(int i, int j)
{
	memcpy(HistoryData, ChessData, sizeof(int) * 15 * 15);
	if (currentRole != Chess::Forbidden) {
		if (ChessData[i][j] == Chess::Empty) {
			ChessData[i][j] = currentRole;
			myform->setChessStatus(ChessData);
			if (!GobangWIN(currentRole, 0)) {
				Rolechange();Sleep(500);

				playwithAI(i, j, currentRole);
				if (GobangWIN(currentRole, 1))goto win;
				Rolechange();
			}
			else {
			win:
				currentRole = Chess::Forbidden;
				currentPK = STOP;
				setChessInit();
			}
		}
	}
}

// 黑白子落子显示、切换落子显示、轮换落子
void GobangForm::RoleInit(const QString blackfilename, const QString whitefilename)
{
	ui.label_black->setPixmap(QPixmap(blackfilename));
	ui.label_black->setScaledContents(true);
	ui.label_white->setPixmap(QPixmap(whitefilename));
	ui.label_white->setScaledContents(true);
}
void GobangForm::setRole(Chess::ChessType Role)
{
	currentRole = Role;
	if (Role == Chess::black) 
		RoleInit("../平台对抗系统/image/black.png", "../平台对抗系统/image/blank.png");
	else 
		RoleInit("../平台对抗系统/image/blank.png", "../平台对抗系统/image/white.png");
}
void GobangForm::Rolechange()
{
	if (currentRole == Chess::black) 
		currentRole = Chess::white;
	else 
		currentRole = Chess::black;
	setRole(currentRole);
}

// THE bot 落子函数
void GobangForm::playwithAI(int& x, int& y, Chess::ChessType Role)
{
	FindbestScore(x,y,Role);
	myform->setChessStatus(ChessData);
}

// 重新开始与退出游戏，判断五子连珠、判断平局
bool GobangForm::GobangWIN(Chess::ChessType Role, int player)
{
	if (checkwin(Role, ChessData) == 1) {
		isPushBotton(false);
		currentRole = Chess::Forbidden;
		currentPK = STOP;

		if (player == 0) {
			int Restart = QMessageBox::question(this, "tql", "赢多几次？\nYOU WIN THE bot!",QMessageBox::Yes | QMessageBox::No);
			if (Restart == QMessageBox::No) {
				setChessInit();
				this->close();
			}
		}
		else {
			QSqlQuery query; QString Content = "再来亿把？\nTHE bot WIN YOU!";
			query.exec(QString("update GamePlayer set BotDefeat=BotDefeat+1 where Player='%1'").arg(Name));
			int Restart = QMessageBox::question(this, "Sorry,Sorry", Content, QMessageBox::Yes | QMessageBox::No);
			if (Restart == QMessageBox::No) {
				setChessInit();
				this->close();
			}
		}
		return true;
	}
	else if (checkpeace()) {
		isPushBotton(false);
		currentRole = Chess::Forbidden;
		currentPK = STOP;

		QString Content = "再来亿把？\nYOU AND THE bot 55开";
		int Restart = QMessageBox::question(this, "Sorry,Sorry", Content, QMessageBox::Yes | QMessageBox::No);
		if (Restart == QMessageBox::No) {
			setChessInit();
			this->close();
		}
		return true;
	}
	return false;
}
int GobangForm::checkwin(int color, void* myform)
{
	typedef int(*p)[15];
	p chessData = p(myform);
	for (int i = 0; i < 15; i++) {              // 遍历数组查找五子连珠
		for (int j = 0; j < 15; j++) {

			//和右边4子连成5个
			if (i < 11
				&& chessData[i][j] == color
				&& chessData[i + 1][j] == color
				&& chessData[i + 2][j] == color
				&& chessData[i + 3][j] == color
				&& chessData[i + 4][j] == color)
			{
				return 1;
			}
			//和下边4子连成5个
			if (j < 11
				&& chessData[i][j] == color
				&& chessData[i][j + 1] == color
				&& chessData[i][j + 2] == color
				&& chessData[i][j + 3] == color
				&& chessData[i][j + 4] == color)
			{
				return 1;
			}
			//和左下4子连成5个
			if (i > 3 && j < 11
				&& chessData[i][j] == color
				&& chessData[i - 1][j + 1] == color
				&& chessData[i - 2][j + 2] == color
				&& chessData[i - 3][j + 3] == color
				&& chessData[i - 4][j + 4] == color)
			{
				return 1;
			}
			//和右下4子连成5个
			if (i < 11 && j < 11
				&& chessData[i][j] == color
				&& chessData[i + 1][j + 1] == color
				&& chessData[i + 2][j + 2] == color
				&& chessData[i + 3][j + 3] == color
				&& chessData[i + 4][j + 4] == color)
			{
				return 1;
			}
		}
	}
	return 0;
}
bool GobangForm::checkpeace()
{
	int Count = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (ChessData[i][j] == Chess::Empty)
				Count++;
		}
	}
	return (Count == 0);
}

// 游戏开始(选择先后手)、悔棋(未实现)、求和、认负
void GobangForm::isPushBotton(bool TF)
{
	ui.btn_regret->setEnabled(TF);
	ui.btn_giveup->setEnabled(TF);
	ui.btn_peace->setEnabled(TF);
	if (TF) 
		ui.btn_start->setEnabled(false);
	else 
		ui.btn_start->setEnabled(true);
}
void GobangForm::on_btn_start_clicked()
{
	int ret = QMessageBox::question(this, "Hey,Man", "Yes?先手(黑子)\nNo?后手(白子)", QMessageBox::Yes | QMessageBox::No);
	if (ret == QMessageBox::Yes) {
		currentPK = PKtype::offensive;
		setRole(Chess::black);
	}
	else {
		currentPK = PKtype::defensive;
		setRole(Chess::white);
	}
	isPushBotton(true); 
	setChessInit();
	memcpy(HistoryData, ChessData, sizeof(int) * 15 * 15);
}
void GobangForm::on_btn_regret_clicked()
{
	int ret = QMessageBox::question(this, "哥", "你真的要悔棋吗", QMessageBox::Yes | QMessageBox::No);
	if (ret == QMessageBox::Yes) {
		memcpy(ChessData, HistoryData, sizeof(int) * 15 * 15);
		myform->setChessStatus(ChessData);
	}
}
void GobangForm::on_btn_peace_clicked()
{
	isPushBotton(false);
	currentRole = Chess::Forbidden;
	currentPK = STOP; setChessInit();

	int Restart = QMessageBox::question(this, "Sorry,Sorry", "再来亿把？\nYOU AND THE bot 55开", QMessageBox::Yes | QMessageBox::No);
	if (Restart == QMessageBox::No)
		this->close();
}
void GobangForm::on_btn_giveup_clicked()
{
	isPushBotton(false);
	currentRole = Chess::Forbidden;
	currentPK = STOP; setChessInit();

	QSqlQuery query;
	query.exec(QString("update GamePlayer set BotDefeat=BotDefeat+1 where Player='%1'").arg(Name));
	int Restart = QMessageBox::question(this, "Sorry,Sorry", "再来亿把？\nTHE bot WIN YOU!",QMessageBox::Yes | QMessageBox::No);
	if (Restart == QMessageBox::No)
		this->close();
}

// THE bot 评分函数
void GobangForm::ChessScore(Chess::ChessType Role)
{
	// 设置双方颜色(因为涉及换手，不能直接固定颜色)
	int AI_role, Player_role;
	if (Role == Chess::black) { AI_role = Role; Player_role = Chess::white; }
	else { AI_role = Role; Player_role = Chess::black; }

	memset(Score, 0, sizeof(Score));  //初始化评分数组
	int Player_num = 0, AI_num = 0;   //玩家或AI棋子连成统计个数
	int empty = 0;  //空点统计个数

	/*
	防守
	对每一次落子进行全盘的遍历，若某处为空白，检查其四周八个方向（在边缘位置判断边界）
	若在空白处，且发现在某一对角线方向发现有一个其他颜色的棋子，空白位置的分数数组赋分
	继续往这个方向检测是否还有连续的同一颜色的棋子，若没有则检查其他方向或者检测下一个空白位置。
	依次类推，继续检测。每一遍遍历都会使得分数数组得到累加，会导致AI判断的变化。

	进攻
	在防守分数数组的基础上，对本身棋子也进行类似的遍历，判断自己的形势，对分数数组赋分。
	*/

	for (int x = 0; x < 15; x++) {
		for (int y = 0; y < 15; y++) {
			if (ChessData[x][y] == Chess::Empty) {

				/*判断该空白棋子的八个方向 */
				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) {
						if (i != 0 || j != 0) {  // [i,j]=[0,0]就是空白棋子位置

							/* 对玩家棋子计数 */
							for (int k = 1; k <= 4; k++) {
								if (x + k * i >= 0 && x + k * i < 15 && y + k * j >= 0 && y + k * j < 15  //边界判断
									&& ChessData[x + k * i][y + k * j] == Player_role)
									Player_num++;
								else if (ChessData[x + k * i][y + k * j] == Chess::Empty) { empty++; break; }  //空点+1退出
								else { break; }
							}
							for (int k = -1; k >= -4; k--) {
								if (x + k * i >= 0 && x + k * i < 15 && y + k * j >= 0 && y + k * j < 15
									&& ChessData[x + k * i][y + k * j] == Player_role)
									Player_num++;
								else if (ChessData[x + k * i][y + k * j] == Chess::Empty) { empty++; break; }  //空点+1退出
								else { break; }
							}

							/* 对玩家棋子评分 */                                 //  与空白棋子可形成的阵型
							if (Player_num == 1) { Score[x][y] += 1; }          //  2个棋子  +   1分 单子
							else if (Player_num == 2) {                         //  3个棋子
								if (empty == 1) { Score[x][y] += 5; }           //  1个空点  +   5分 死三
								else if (empty == 2) { Score[x][y] += 10; }     //  2个空点  +  10分 活三/连活三/跳活三(眠四)
							}
							else if (Player_num == 3) {                         //  4个棋子
								if (empty == 1) { Score[x][y] += 20; }          //  1个空点  +  20分 冲四/死四
								else if (empty == 2) { Score[x][y] += 100; }    //  2个空点  + 100分 活四
							}
							else if (Player_num >= 4) { Score[x][y] += 10000; }  //  5个棋子  +1000分 成五
																				//  无法判断双活三、双冲四、活三+冲死等阵型
							empty = 0; //空点清零

							/* AI自我落点评分 */
							for (int k = 1; k <= 4; k++) {
								if (x + k * i >= 0 && x + k * i < 15 && y + k * j >= 0 && y + k * j < 15
									&& ChessData[x + k * i][y + k * j] == AI_role)
									AI_num++;
								else if (ChessData[x + k * i][y + k * j] == Chess::Empty) { empty++; break; }  //空点+1退出
								else { break; }
							}
							for (int k = -1; k >= -4; k--) {
								if (x + k * i >= 0 && x + k * i < 15 && y + k * j >= 0 && y + k * j < 15
									&& ChessData[x + k * i][y + k * j] == AI_role)
									AI_num++;
								else if (ChessData[x + k * i][y + k * j] == Chess::Empty) { empty++; break; }  //空点+1退出
								else { break; }
							}

							/* AI自我棋子评分 */                                  // 与空白棋子可形成阵型
							if (AI_num == 0) { Score[x][y] += 1; }               // 1个棋子  +    1分 单子
							else if (AI_num == 1) { Score[x][y] += 2; }          // 2个棋子  +    2分 活二
							else if (AI_num == 2) {                              // 3个棋子
								if (empty == 1) { Score[x][y] += 8; }            // 1个空点  +    8分 死三
								else if (empty == 2) { Score[x][y] += 30; }      // 2个空点  +   30分 活三/连活三/跳活三(眠四)
							}
							else if (AI_num == 3) {                              // 4个棋子
								if (empty == 1) { Score[x][y] += 50; }           // 1个空点  +   50分 冲四/死四
								else if (empty == 2) { Score[x][y] += 2000; }    // 2个空点  + 2000分 活四
							}
							else if (AI_num >= 4) { Score[x][y] += 20000; }      // 5个棋子  +10000分 成五

							Player_num = 0; AI_num = 0; empty = 0; //全部清零用于下次遍历
						}
					}
				}
			}
		}
	}
}
void GobangForm::FindbestScore(int& x, int& y, Chess::ChessType Role)
{
	srand((unsigned)time(0)); //调节系统时间，将伪随机数彻底随机
	ChessScore(Role); // 引用评分函数

	//最高分、相同最高分坐标的数组
	int Max = 0;
	int best_x[225], best_y[225], best_i = 1, bestx, besty;

	//获取所有点中最高分坐标
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (Score[i][j] > Max) {
				Max = Score[i][j];
				bestx = i;
				besty = j;
			}
		}
	}
	best_x[0] = bestx; best_y[0] = besty;

	//一个局面具有多个最高分坐标
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (Score[i][j] == Max && i != bestx && j != besty) {
				best_x[best_i] = i;
				best_y[best_i] = j;
				best_i++;
			}
		}
	}

	//当存在多个最高分，在数组中随机取一坐标
	if (best_i == 1) { x = best_x[0]; y = best_y[0]; }
	else {
		int r = rand() % best_i;
		x = best_x[r]; y = best_y[r];
	}

	qDebug() << "AI：" << x << "，" << y;
	ChessData[x][y] = Role;  //AI落子
	Max = 0; //重设最高分数值
}

// Something Events
void GobangForm::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.drawPixmap(this->rect(), QPixmap("../平台对抗系统/image/bg_start.png"));
}
void GobangForm::closeEvent(QCloseEvent*)
{
	setChessInit();
	isPushBotton(false);
	QSqlQuery query;
	query.exec(QString("update GamePlayer set IsLine='在线上' where Player='%1'").arg(Name));
}
void GobangForm::Sleep(int msec)
{
	QTime dieTime = QTime::currentTime().addMSecs(msec);
	while (QTime::currentTime() < dieTime)
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}