#include "HappyEliminate.h"

HappyEliminate::HappyEliminate(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	QObject::connect(ui.btn_start, SIGNAL(clicked()), this, SLOT(on_btn_start_clicked()), Qt::UniqueConnection);  //���� ��ʼ �������ź�
	QObject::connect(ui.btn_auto, SIGNAL(clicked()), this, SLOT(on_btn_auto_clicked()), Qt::UniqueConnection);

    Init();
}

void HappyEliminate::Init()
{
    myform = new Gameform();  // ��Map��ͼ����ռ�
	connect(myform, SIGNAL(SignalSendMapdataone(int, int)), this, SLOT(doProcess(int, int)));  //���������������ź�����
	connect(myform, SIGNAL(SignalSendMapdatatwo(int, int)), this, SLOT(doRelease(int, int)));  //��������ͷ�������ź�����
    ui.gridLayout->addWidget(myform); //��ui����ʾ��ͼҳ��

	Score = 0;
}

//���̳�ʼ������������
void HappyEliminate::setMapInit()
{
	srand((unsigned)time(0));
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 14; j++) {
			Map[i][j] = rand() % 7;
		}
	}
	myform->setMapStatus(Map);
}
void HappyEliminate::doProcess(int i1,int j1)
{
	qDebug() << "��ҵ����" << i1 << "," << j1;
	Pro_x = i1; Pro_y = j1;  //��������긳ֵ
}
void HappyEliminate::doRelease(int i2, int j2)
{
	if (checkend()) {
		qDebug() << "����ͷţ�" << i2 << "," << j2;
		Rel_x = i2; Rel_y = j2; //����ͷ����긳ֵ

		std::swap(Map[Pro_x][Pro_y], Map[Rel_x][Rel_y]);
		myform->setMapStatus(Map);

		if ((abs(Rel_x - Pro_x) == 1 && Rel_y == Pro_y) || (abs(Rel_y - Pro_y) == 1 && Rel_x == Pro_x)) {
			Sleep(500);
			if (updateCheck())
			{
				Eliminate();
				while (updateCheck())
				{
					Eliminate();
				}
				ui.LCDnum->display(Score);
			}
			else { std::swap(Map[Rel_x][Rel_y], Map[Pro_x][Pro_y]); }
		}
		else { std::swap(Map[Rel_x][Rel_y], Map[Pro_x][Pro_y]); }
		this->update();
		myform->setMapStatus(Map);
	}
	else {
		int Restart = QMessageBox::question(NULL, "��Ϸ����", "���¿�ʼ", QMessageBox::Yes | QMessageBox::No);
		if (Restart == QMessageBox::Yes) {
			Score = 0;
			ui.LCDnum->display(Score);
			memset(Map, -1, sizeof(int) * 9 * 14);
			myform->setMapStatus(Map);
		}
		else
			this->close();
	}
}

//����Ƿ��з�������������ͨ��bfs������bfs��Ǽ�Խ���⣬bfs�㷨���������BFS�㷨
bool HappyEliminate::updateCheck()
{
	bool isUpdate = false;
	memset(bfsVis, 0, sizeof(bfsVis));
	
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 14; j++) {
			if (bfsVis[i][j] == 0) {
				bool mark = false;
				if (bfs(i,j)) { 
					mark = true;       
					isUpdate = true;
				}

				if (mark) {
					mapCody();  //�ֳ�һ���µ�ͼ�;ɵ�ͼ��������ʾ��ʧЧ��
					Bfs(i, j);
				}
			}
		}
	}
	return isUpdate;
}
bool HappyEliminate::bfsCheck(int x, int y, int squre)
{
	if (x < 0 || x >= 9 || y < 0 || y >= 14)return false;
	if (bfsVis[x][y] != 0 || Map[x][y] != squre)return false;
	return true;
}
bool HappyEliminate::bfs(int x, int y)
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
		//qDebug() << "COUNT:" << COUNT;
		COUNT++;
		if (COUNT >= 4) return true;
		B.pop(); // ����
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
void HappyEliminate::Bfs(int x, int y)
{
	int ans = 0;
	std::queue<node> S;  //����һ������
	node now, next;
	now.x = x, now.y = y; //���ɳ�ʼ���

	bfsVis[x][y] = 1;
	int squre = Map[x][y];
	Map[x][y] = Gameform::Empty;

	S.push(now); //�����м����ʼ���
	while (!S.empty()) {
		now = S.front();
		ans++;
		S.pop(); // ����
		for (int i = 0; i < 4; i++) {
			next = now;
			next.x += xx[i], next.y += yy[i];  // Ѱ��[x,y]���������ҵ�����   int xx[4] = { 0, 0, 1, -1 };int yy[4] = { 1, -1, 0, 0 };�����������
			if (bfsCheck(next.x, next.y, squre) == 0)continue; // ��������������������

			bfsVis[next.x][next.y] = 1;
			Map[next.x][next.y] = Gameform::Empty;

			S.push(next);  //���β��������
		}
	}
	Score += ans;
	displayUpdate();
}

//����߶�ͳ��
void HappyEliminate::dropNumberCount()
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 14; j++) {
			if (Map[i][j] == Gameform::Empty) {
				dropNumber[i][j] = 0;  //��������Ϊ��ʱ����ʼ�����������ж�Ӧ�ĵ�Ϊ0��������һ��ѭ��
				continue;
			}

			// �õ㲻Ϊ��ʱ

			int sum = 0;
			for (int z = j + 1; z < 14; z++) {
				if (Map[i][z] == Gameform::Empty)sum++;  // ���㵱ǰ�������µ����пյ�������  ������߶�
			}
			dropNumber[i][j] = sum;  //�������鸳ֵ
		}
	}
}
//��������߶ȸ��µ�ͼ
void HappyEliminate::squreDrop()
{
	for (int j = 14 - 1; j >= 0; j--) {  //��������
		for (int i = 0; i < 9; i++) {
			int temp = dropNumber[i][j];  // ��ֵÿ�����������߶�
			if (temp != 0) {
				Map[i][j + temp] = Map[i][j]; //��״���߶�����
				Map[i][j] = Gameform::Empty;  //�õ���
			}
		}
	}
}
//�����ĵ�ͼ��Ԫ�����
void HappyEliminate::reflashMap()
{
	srand((unsigned)time(0));
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 14; j++) {
			if (Map[i][j] == Gameform::Empty) {
				Map[i][j] = rand() % 7; //����ͼ�Ͽյ�λ���������
			}
		}
	}
}
//��ʧЧ��
void HappyEliminate::displayUpdate()
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
//��������
void HappyEliminate::mapCody()
{
	memcpy(Map_2, Map, sizeof(int) * 9 * 14); //��ͼ����
}
//���µ�ͼ 
void HappyEliminate::Eliminate()
{
	dropNumberCount();
	squreDrop();
	reflashMap();
	this->update();  //���½���
	myform->setMapStatus(Map);  // ������ӳ�䵽Gameform�ĵ�ͼ��
}
//������
bool HappyEliminate::checkend()
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

//���水ť����
void HappyEliminate::on_btn_start_clicked()
{
	setMapInit();  //��ʼ����ͼ
	while (updateCheck())
	{
		Eliminate();
	}
	ui.LCDnum->display(Score);
}
void HappyEliminate::on_btn_auto_clicked()
{
c2:
	for (int y = 13; y >=0; y--) {
		for (int x = 8; x >= 0; x--) {
			std::swap(Map[x][y], Map[x - 1][y]);
			if (updateCheck()) {
				Eliminate();
				while (updateCheck())
				{
					Eliminate();
				}
				
				ui.LCDnum->display(Score);
				goto c2;
			}
			else { std::swap(Map[x - 1][y], Map[x][y]); }

			std::swap(Map[x][y], Map[x][y - 1]);
			if (updateCheck()) {
				Eliminate();
				while (updateCheck())
				{
					Eliminate();
				}
				
				ui.LCDnum->display(Score);
				goto c2;
			}
			else { std::swap(Map[x][y - 1], Map[x][y]); }
		}
	}
}

//˯��ʱ��
void HappyEliminate::Sleep(int msec)
{
	QTime dieTime = QTime::currentTime().addMSecs(msec);
	while (QTime::currentTime() < dieTime)
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}