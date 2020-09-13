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
	RoleInit("../ƽ̨�Կ�ϵͳ/image/black.png", "../ƽ̨�Կ�ϵͳ/image/white.png");

	//����������ռ�
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

// ���̳�ʼ������������
void GobangForm::setChessInit()
{
	RoleInit("../ƽ̨�Կ�ϵͳ/image/black.png", "../ƽ̨�Կ�ϵͳ/image/white.png");
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			ChessData[i][j] = Chess::Empty;
		}
	}
	// ��AI���֣�Ĭ����[8��8]�������
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

// �ڰ���������ʾ���л�������ʾ���ֻ�����
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
		RoleInit("../ƽ̨�Կ�ϵͳ/image/black.png", "../ƽ̨�Կ�ϵͳ/image/blank.png");
	else 
		RoleInit("../ƽ̨�Կ�ϵͳ/image/blank.png", "../ƽ̨�Կ�ϵͳ/image/white.png");
}
void GobangForm::Rolechange()
{
	if (currentRole == Chess::black) 
		currentRole = Chess::white;
	else 
		currentRole = Chess::black;
	setRole(currentRole);
}

// THE bot ���Ӻ���
void GobangForm::playwithAI(int& x, int& y, Chess::ChessType Role)
{
	FindbestScore(x,y,Role);
	myform->setChessStatus(ChessData);
}

// ���¿�ʼ���˳���Ϸ���ж��������顢�ж�ƽ��
bool GobangForm::GobangWIN(Chess::ChessType Role, int player)
{
	if (checkwin(Role, ChessData) == 1) {
		isPushBotton(false);
		currentRole = Chess::Forbidden;
		currentPK = STOP;

		if (player == 0) {
			int Restart = QMessageBox::question(this, "tql", "Ӯ�༸�Σ�\nYOU WIN THE bot!",QMessageBox::Yes | QMessageBox::No);
			if (Restart == QMessageBox::No) {
				setChessInit();
				this->close();
			}
		}
		else {
			QSqlQuery query; QString Content = "�����ڰѣ�\nTHE bot WIN YOU!";
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

		QString Content = "�����ڰѣ�\nYOU AND THE bot 55��";
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
	for (int i = 0; i < 15; i++) {              // �������������������
		for (int j = 0; j < 15; j++) {

			//���ұ�4������5��
			if (i < 11
				&& chessData[i][j] == color
				&& chessData[i + 1][j] == color
				&& chessData[i + 2][j] == color
				&& chessData[i + 3][j] == color
				&& chessData[i + 4][j] == color)
			{
				return 1;
			}
			//���±�4������5��
			if (j < 11
				&& chessData[i][j] == color
				&& chessData[i][j + 1] == color
				&& chessData[i][j + 2] == color
				&& chessData[i][j + 3] == color
				&& chessData[i][j + 4] == color)
			{
				return 1;
			}
			//������4������5��
			if (i > 3 && j < 11
				&& chessData[i][j] == color
				&& chessData[i - 1][j + 1] == color
				&& chessData[i - 2][j + 2] == color
				&& chessData[i - 3][j + 3] == color
				&& chessData[i - 4][j + 4] == color)
			{
				return 1;
			}
			//������4������5��
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

// ��Ϸ��ʼ(ѡ���Ⱥ���)������(δʵ��)����͡��ϸ�
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
	int ret = QMessageBox::question(this, "Hey,Man", "Yes?����(����)\nNo?����(����)", QMessageBox::Yes | QMessageBox::No);
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
	int ret = QMessageBox::question(this, "��", "�����Ҫ������", QMessageBox::Yes | QMessageBox::No);
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

	int Restart = QMessageBox::question(this, "Sorry,Sorry", "�����ڰѣ�\nYOU AND THE bot 55��", QMessageBox::Yes | QMessageBox::No);
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
	int Restart = QMessageBox::question(this, "Sorry,Sorry", "�����ڰѣ�\nTHE bot WIN YOU!",QMessageBox::Yes | QMessageBox::No);
	if (Restart == QMessageBox::No)
		this->close();
}

// THE bot ���ֺ���
void GobangForm::ChessScore(Chess::ChessType Role)
{
	// ����˫����ɫ(��Ϊ�漰���֣�����ֱ�ӹ̶���ɫ)
	int AI_role, Player_role;
	if (Role == Chess::black) { AI_role = Role; Player_role = Chess::white; }
	else { AI_role = Role; Player_role = Chess::black; }

	memset(Score, 0, sizeof(Score));  //��ʼ����������
	int Player_num = 0, AI_num = 0;   //��һ�AI��������ͳ�Ƹ���
	int empty = 0;  //�յ�ͳ�Ƹ���

	/*
	����
	��ÿһ�����ӽ���ȫ�̵ı�������ĳ��Ϊ�հף���������ܰ˸������ڱ�Եλ���жϱ߽磩
	���ڿհ״����ҷ�����ĳһ�Խ��߷�������һ��������ɫ�����ӣ��հ�λ�õķ������鸳��
	����������������Ƿ���������ͬһ��ɫ�����ӣ���û����������������߼����һ���հ�λ�á�
	�������ƣ�������⡣ÿһ���������ʹ�÷�������õ��ۼӣ��ᵼ��AI�жϵı仯��

	����
	�ڷ��ط�������Ļ����ϣ��Ա�������Ҳ�������Ƶı������ж��Լ������ƣ��Է������鸳�֡�
	*/

	for (int x = 0; x < 15; x++) {
		for (int y = 0; y < 15; y++) {
			if (ChessData[x][y] == Chess::Empty) {

				/*�жϸÿհ����ӵİ˸����� */
				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) {
						if (i != 0 || j != 0) {  // [i,j]=[0,0]���ǿհ�����λ��

							/* ��������Ӽ��� */
							for (int k = 1; k <= 4; k++) {
								if (x + k * i >= 0 && x + k * i < 15 && y + k * j >= 0 && y + k * j < 15  //�߽��ж�
									&& ChessData[x + k * i][y + k * j] == Player_role)
									Player_num++;
								else if (ChessData[x + k * i][y + k * j] == Chess::Empty) { empty++; break; }  //�յ�+1�˳�
								else { break; }
							}
							for (int k = -1; k >= -4; k--) {
								if (x + k * i >= 0 && x + k * i < 15 && y + k * j >= 0 && y + k * j < 15
									&& ChessData[x + k * i][y + k * j] == Player_role)
									Player_num++;
								else if (ChessData[x + k * i][y + k * j] == Chess::Empty) { empty++; break; }  //�յ�+1�˳�
								else { break; }
							}

							/* ������������� */                                 //  ��հ����ӿ��γɵ�����
							if (Player_num == 1) { Score[x][y] += 1; }          //  2������  +   1�� ����
							else if (Player_num == 2) {                         //  3������
								if (empty == 1) { Score[x][y] += 5; }           //  1���յ�  +   5�� ����
								else if (empty == 2) { Score[x][y] += 10; }     //  2���յ�  +  10�� ����/������/������(����)
							}
							else if (Player_num == 3) {                         //  4������
								if (empty == 1) { Score[x][y] += 20; }          //  1���յ�  +  20�� ����/����
								else if (empty == 2) { Score[x][y] += 100; }    //  2���յ�  + 100�� ����
							}
							else if (Player_num >= 4) { Score[x][y] += 10000; }  //  5������  +1000�� ����
																				//  �޷��ж�˫������˫���ġ�����+����������
							empty = 0; //�յ�����

							/* AI����������� */
							for (int k = 1; k <= 4; k++) {
								if (x + k * i >= 0 && x + k * i < 15 && y + k * j >= 0 && y + k * j < 15
									&& ChessData[x + k * i][y + k * j] == AI_role)
									AI_num++;
								else if (ChessData[x + k * i][y + k * j] == Chess::Empty) { empty++; break; }  //�յ�+1�˳�
								else { break; }
							}
							for (int k = -1; k >= -4; k--) {
								if (x + k * i >= 0 && x + k * i < 15 && y + k * j >= 0 && y + k * j < 15
									&& ChessData[x + k * i][y + k * j] == AI_role)
									AI_num++;
								else if (ChessData[x + k * i][y + k * j] == Chess::Empty) { empty++; break; }  //�յ�+1�˳�
								else { break; }
							}

							/* AI������������ */                                  // ��հ����ӿ��γ�����
							if (AI_num == 0) { Score[x][y] += 1; }               // 1������  +    1�� ����
							else if (AI_num == 1) { Score[x][y] += 2; }          // 2������  +    2�� ���
							else if (AI_num == 2) {                              // 3������
								if (empty == 1) { Score[x][y] += 8; }            // 1���յ�  +    8�� ����
								else if (empty == 2) { Score[x][y] += 30; }      // 2���յ�  +   30�� ����/������/������(����)
							}
							else if (AI_num == 3) {                              // 4������
								if (empty == 1) { Score[x][y] += 50; }           // 1���յ�  +   50�� ����/����
								else if (empty == 2) { Score[x][y] += 2000; }    // 2���յ�  + 2000�� ����
							}
							else if (AI_num >= 4) { Score[x][y] += 20000; }      // 5������  +10000�� ����

							Player_num = 0; AI_num = 0; empty = 0; //ȫ�����������´α���
						}
					}
				}
			}
		}
	}
}
void GobangForm::FindbestScore(int& x, int& y, Chess::ChessType Role)
{
	srand((unsigned)time(0)); //����ϵͳʱ�䣬��α������������
	ChessScore(Role); // �������ֺ���

	//��߷֡���ͬ��߷����������
	int Max = 0;
	int best_x[225], best_y[225], best_i = 1, bestx, besty;

	//��ȡ���е�����߷�����
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

	//һ��������ж����߷�����
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (Score[i][j] == Max && i != bestx && j != besty) {
				best_x[best_i] = i;
				best_y[best_i] = j;
				best_i++;
			}
		}
	}

	//�����ڶ����߷֣������������ȡһ����
	if (best_i == 1) { x = best_x[0]; y = best_y[0]; }
	else {
		int r = rand() % best_i;
		x = best_x[r]; y = best_y[r];
	}

	qDebug() << "AI��" << x << "��" << y;
	ChessData[x][y] = Role;  //AI����
	Max = 0; //������߷���ֵ
}

// Something Events
void GobangForm::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.drawPixmap(this->rect(), QPixmap("../ƽ̨�Կ�ϵͳ/image/bg_start.png"));
}
void GobangForm::closeEvent(QCloseEvent*)
{
	setChessInit();
	isPushBotton(false);
	QSqlQuery query;
	query.exec(QString("update GamePlayer set IsLine='������' where Player='%1'").arg(Name));
}
void GobangForm::Sleep(int msec)
{
	QTime dieTime = QTime::currentTime().addMSecs(msec);
	while (QTime::currentTime() < dieTime)
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}