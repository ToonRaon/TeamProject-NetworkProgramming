#pragma comment(lib, "ws2_32")
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <process.h>
#include <Windows.h>
#include <time.h>
#include <string.h>

#define MAP_HEIGHT 20
#define MAP_WIDTH 34
#define MAX_PLAYABLE_COUNT 4 //�ִ� �÷��� ���� �ο�
#define BUF_SIZE 1024

#define COLOR_WHITE 7
#define COLOR_RED 4

int map_input[MAP_HEIGHT][MAP_WIDTH] = {
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,1,
	1,0,1,0,1,0,1,1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,0,0,0,0,0,0,1,0,1,1,
	1,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,
	1,0,1,1,1,0,1,1,0,1,0,1,1,1,0,1,1,1,0,1,1,0,1,0,1,1,0,1,0,0,1,0,0,1,
	1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,1,1,0,0,0,1,0,1,1,1,1,1,1,1,0,0,0,0,1,
	1,0,1,1,0,1,1,0,1,1,1,0,0,0,0,1,0,1,0,1,1,0,0,1,0,0,1,0,0,0,1,1,1,1,
	1,0,0,0,0,1,1,0,1,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,1,
	1,1,0,1,0,1,1,1,1,1,1,0,1,0,0,1,0,1,1,1,0,1,1,1,1,0,1,0,1,0,1,1,0,1,
	1,1,1,1,0,1,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,1,
	1,0,0,1,0,0,0,0,1,0,1,0,1,1,0,0,0,1,1,0,1,1,1,0,1,1,0,0,1,1,1,1,0,1,
	1,0,1,1,0,1,1,0,1,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,1,0,0,0,1,0,1,
	1,0,0,0,0,1,0,0,1,0,0,0,1,1,0,1,1,1,1,1,1,0,1,1,0,0,0,1,0,1,0,1,0,1,
	1,0,1,1,1,0,0,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,0,0,1,
	1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,1,1,1,1,0,1,0,0,0,1,0,1,
	1,0,0,1,0,1,1,0,1,0,1,1,1,0,1,1,0,1,0,1,0,1,0,0,1,0,0,0,1,1,1,1,0,1,
	1,0,1,1,0,1,1,0,1,0,1,0,1,0,1,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,1,
	1,0,1,0,0,1,0,0,0,1,1,0,0,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,0,1,
	1,0,0,0,0,0,0,1,0,0,0,0,1,1,1,0,1,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

char map[MAP_HEIGHT][MAP_WIDTH * 2 + 1] = {
	"�����������������������������������",
	"�ᡡ�������������������ᡡ����������������������������ᡡ��ᡡ����",
	"�ᡡ�ᡡ�ᡡ��ᡡ�����ᡡ�ᡡ�ᡡ�����ᡡ�����������ᡡ���",
	"�ᡡ�ᡡ�ᡡ�������ᡡ�������������ᡡ�ᡡ���ᡡ���ᡡ�ᡡ���ᡡ����",
	"�ᡡ���ᡡ��ᡡ�ᡡ���ᡡ���ᡡ��ᡡ�ᡡ��ᡡ�ᡡ���ᡡ����",
	"�ᡡ�ᡡ���������������ᡡ�ᡡ��ᡡ�����ᡡ�������ᡡ��������",
	"�ᡡ��ᡡ��ᡡ���ᡡ�������ᡡ�ᡡ��ᡡ���ᡡ���ᡡ���������",
	"�ᡡ��������ᡡ�ᡡ�����ᡡ��ᡡ�������������������ᡡ�ᡡ�ᡡ����",
	"��ᡡ�ᡡ������ᡡ�ᡡ���ᡡ���ᡡ����ᡡ�ᡡ�ᡡ��ᡡ��",
	"����ᡡ��ᡡ�����ᡡ�������ᡡ�����������ᡡ�����ᡡ�ᡡ��������",
	"�ᡡ���ᡡ�������ᡡ�ᡡ��ᡡ������ᡡ���ᡡ��ᡡ������ᡡ��",
	"�ᡡ��ᡡ��ᡡ�ᡡ�ᡡ�������ᡡ�����ᡡ��������ᡡ�ᡡ�����ᡡ��",
	"�ᡡ�������ᡡ���ᡡ������ᡡ������ᡡ��ᡡ�����ᡡ�ᡡ�ᡡ��",
	"�ᡡ���ᡡ�������ᡡ�ᡡ�����������������ᡡ���ᡡ�ᡡ�ᡡ������",
	"�ᡡ�ᡡ�ᡡ�ᡡ���������������ᡡ�ᡡ�ᡡ�����ᡡ�ᡡ�����ᡡ��",
	"�ᡡ���ᡡ��ᡡ�ᡡ���ᡡ��ᡡ�ᡡ�ᡡ�ᡡ���ᡡ��������ᡡ��",
	"�ᡡ��ᡡ��ᡡ�ᡡ�ᡡ�ᡡ�ᡡ�������ᡡ�������ᡡ�ᡡ������������",
	"�ᡡ�ᡡ���ᡡ������ᡡ�����ᡡ�ᡡ�����ᡡ�ᡡ�ᡡ����ᡡ��",
	"�ᡡ�����������ᡡ���������ᡡ�ᡡ�����ᡡ���������ᡡ�ᡡ��������",
	"�����������������������������������",
};

struct charactor {
	char icon[2]; //�߰���: ��, ������: ��
	int x; //���� ȭ�� ���� x��ǥ
	int y; //���� ȭ�� ���� y��ǥ
	int next_x; //�������� ���۵�, ���� �̵��ؾ��� x��ǥ
	int next_y; //�������� ���۵�, ���� �̵��ؾ��� y��ǥ
	int powerMode; //�Ŀ� �縴 �Ծ�����
};

struct charactor* charactorArr[MAX_PLAYABLE_COUNT]; //������ ������ �÷��̾ ������
struct charactor* powerPelletArr[4]; //�Ŀ� �縴 ��ġ ����

SOCKET hSocket;

int chaserSpeed = 70; //������ �ӵ�. moveSpeed �и��ʸ�ŭ Sleep�� �� ĳ���Ͱ� 1ĭ �����̴� �� �ݺ��մϴ�. (���ڰ� �������� �ӵ��� ����)
int runnerSpeed = 100; //������ �ӵ�. moveSpeed �и��ʸ�ŭ Sleep�� �� ĳ���Ͱ� 1ĭ �����̴� �� �ݺ��մϴ�. (���ڰ� �������� �ӵ��� ����)
int clockCount = 0;
int clockCountIncreaseAmount = 1; //�ݵ�� chaserSpeed�� runnerSpeed�� �����������.

int seqNum;
int dir; //��,��,��,�� ���� 8,2,4,6 (���� Ű�е�)

int survivorCount = MAX_PLAYABLE_COUNT - 1;
int leftTime = 10000;

bool isGameOver = false;

CRITICAL_SECTION cs;



void ErrorHandling(const char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

void setTextColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

unsigned int __stdcall KeyboardHandlerThread(void* args) {
	if (seqNum >= MAX_PLAYABLE_COUNT) { //5��° �̻� ���Ӻ��ʹ� ���游
		return 0;
	}

	while (1) {
		if (isGameOver) {
			break;
		}

		int key = _getch();

		if (key == 224) { //����Ű �ƽ�Ű �ڵ� ��: 224, 72 ��: 224, 80 ��: 224, 75 ��: 224, 77
			key = _getch();
			switch (key) {
			case 72: //��
				dir = 8;
				break;
			case 75: //����
				dir = 4;
				break;
			case 77: //������
				dir = 6;
				break;
			case 80: //�Ʒ�
				dir = 2;
				break;
			}
		}
	}

	return 0;
}

unsigned int __stdcall RecvCoordThread(void* args) {
	char buf[BUF_SIZE];
	char buf2[BUF_SIZE];
	char buf3[BUF_SIZE];

	while (1) {
		recv(hSocket, buf, sizeof(buf), 0); //seqNum
		recv(hSocket, buf2, sizeof(buf2), 0); //x ��ǥ
		recv(hSocket, buf3, sizeof(buf3), 0); //y ��ǥ

		struct charactor* ch = charactorArr[atoi(buf)];
		ch->next_x = atoi(buf2);
		ch->next_y = atoi(buf3);
	}

	return 0;
}

void sendInt2Server(int k) {
	char buf[BUF_SIZE];
	sprintf(buf, "%d", k);
	send(hSocket, buf, sizeof(buf), 0);
}

//2���� char �迭�� ����Ѵ�. r�� ��, c�� ��
void printArray(char **arr, int r, int c) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; i < c; j++) {
			printf("%c", arr[r][c]);
		}
		puts("");
	}
	puts("");
}

//�� ���
void printMap() {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			printf("%s", map_input[i][j] == 1 ? "��" : "��");
		}
		puts("");
	}
	puts("");
}

void removeCursor() {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

//Ŀ�� �̵�
void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//Ŀ�� ��ǥ get
COORD getxy() {
	COORD Cur;
	CONSOLE_SCREEN_BUFFER_INFO a;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &a);
	Cur.X = a.dwCursorPosition.X;
	Cur.Y = a.dwCursorPosition.Y;
	return Cur;
}

bool isWall(int x, int y) {
	int r = y;
	int c = x / 2;

	if (map_input[r][c] == 1) {
		return true;
	}

	return false;
}

void drawIcon(int seq) {
	struct charactor* ch = charactorArr[seq];

	if (ch->next_x < 0 || ch->next_y < 0 || ch->next_x >= 2 * MAP_WIDTH || ch->next_y >= MAP_HEIGHT) { //�� ���� ����� return
		return;
	}

	//���� ��ġ�� �ִ� ������ �����
	gotoxy(ch->x, ch->y);
	//printf("��");
	printf("��");

	//�� ��ġ�� �̵�
	gotoxy(ch->next_x, ch->next_y);
	printf("%s", ch->icon);

	ch->x = ch->next_x;
	ch->y = ch->next_y;
}

struct charactor* createCharactorStruct(const char icon[2], int x, int y) {
	struct charactor* ch = (struct charactor*)malloc(sizeof(struct charactor));
	ch->x = x;
	ch->y = y;
	ch->next_x = x;
	ch->next_y = y;
	strcpy(ch->icon, icon);
	ch->powerMode = false;

	return ch;
}

void chaserWin() {
	system("title �߰��ڰ� �¸��Ͽ����ϴ�!");
}

void isCatchedByChaser() {
	for (int i = 0; i < MAX_PLAYABLE_COUNT - 1; i++) {
		if (charactorArr[i]->x == charactorArr[MAX_PLAYABLE_COUNT - 1]->x && charactorArr[i]->y == charactorArr[MAX_PLAYABLE_COUNT - 1]->y) { //� �����ڰ� �����ڿ��� ������
			charactorArr[i]->x = -1;
			charactorArr[i]->next_x = -1;
			charactorArr[i]->y = -1;
			charactorArr[i]->next_y = -1;

			survivorCount--;

			if (survivorCount == 0) { //���� �����ڰ� ������
				chaserWin();
				isGameOver = true;
			}
		}
	}
}

//Ư�� �ð����� �Ŀ����� ����� ���� ���������ϰ� �� �� ���� �ð� ������ ����
//unsigned int __stdcall PowerPelletThread(void* args) {
//	int counter = 0;
//
//	while (1) {
//		if (counter >= 5000) {
//			break;
//		}
//
//		if (counter % 1000) {
//			strcpy(charactorArr[*(int*)args]->icon, "��");
//		}
//		else {
//			strcpy(charactorArr[*(int*)args]->icon, "��");
//		}
//
//		counter += 500;
//		Sleep(500);
//	}
//
//	return 0;
//}
//
//void isPowerPellet(int seq) {
//	for (int i = 0; i < 4; i++) {
//		if (powerPelletArr[i]->x == charactorArr[seq]->x && powerPelletArr[i]->y == charactorArr[seq]->y) {
//			_beginthreadex(NULL, 0, PowerPelletThread, &seq, 0, NULL);
//		}
//	}
//}

void move(int seq) {
	struct charactor* ch = charactorArr[seq];

	EnterCriticalSection(&cs);

	if (seq == seqNum) { //�� Ŭ���̾�Ʈ�� �ش��ϴ� ĳ���� �ٲ� �� ���������� ������ ǥ��
		setTextColor(COLOR_RED);
	}
	
	drawIcon(seq);

	if (seq == seqNum) {
		setTextColor(COLOR_WHITE);
	}

	LeaveCriticalSection(&cs);
	
	//isPowerPellet(seq);
	isCatchedByChaser();
}

void connect2Server() {
	WSADATA wsaData;

	char buf[BUF_SIZE];
	char buf2[BUF_SIZE];
	int readCnt;
	SOCKADDR_IN servAdr;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hSocket = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAdr.sin_port = htons(atoi("123654"));

	connect(hSocket, (SOCKADDR*)&servAdr, sizeof(servAdr));
	recv(hSocket, buf, sizeof(buf), 0);//�� Ŭ���� ������ ��ȣ �޾ƿ�
	seqNum = atoi(buf); //�޾ƿ� �ø��� ��ȣ�� int�� ��ȯ�Ͽ� seqNum�� ����

	//�� ĳ���͵��� �ʱ� ��ǥ �޾ƿ�
	for (int i = 0; i < MAX_PLAYABLE_COUNT; i++) {
		recv(hSocket, buf, sizeof(buf), 0);

		charactorArr[i]->x = atoi(strtok(buf, " "));
		charactorArr[i]->next_x = charactorArr[i]->x;
		charactorArr[i]->y = atoi(strtok(NULL, " "));
		charactorArr[i]->next_y = charactorArr[i]->y;
	}

	//�Ŀ� �縴 ��ġ �޾ƿ�
	for (int i = 0; i < 4; i++) {
		recv(hSocket, buf, sizeof(buf), 0);

		int x = atoi(strtok(buf, " "));
		int y = atoi(strtok(NULL, " "));
		powerPelletArr[i] = createCharactorStruct("��", x, y);
	}

	//�׽�Ʈ �ڵ�
	sprintf(buf, "title seqNum: %d\n", seqNum);
	system(buf);
}

void initCharactorArr() {
	for (int i = 0; i < MAX_PLAYABLE_COUNT; i++) {
		if (i == MAX_PLAYABLE_COUNT - 1) { //������
			charactorArr[i] = createCharactorStruct("��", -1, -1);
		}
		else { //������
			charactorArr[i] = createCharactorStruct("��", -1, -1);
		}
	}
}

void printPowerPellet() {
	for (int i = 0; i < 4; i++) {
		//drawIcon(powerPelletArr, i);
	}
}

void init() {
	printMap();

	initCharactorArr();

	connect2Server();
	
	//printPowerPellet();

	removeCursor();
}

void moveAllCharactors() {
	for (int i = 0; i < MAX_PLAYABLE_COUNT; i++) {
		move(i);
	}
}

void sendMyNextPosition() {
	if (seqNum >= MAX_PLAYABLE_COUNT) { // 5��° ���Ӻ��ʹ� �׳� ���游
		return;
	}

	struct charactor* ch = charactorArr[seqNum];
	int curX = ch->x;
	int curY = ch->y;
	int nextX = curX;
	int nextY = curY;

	switch (dir) {
	case 4: //��
		nextX = curX - 2;
		break;
	case 6: //��
		nextX = curX + 2;
		break;
	case 8: //��
		nextY = curY - 1;
		break;
	case 2: //��
		nextY = curY + 1;
		break;
	}

	if (isWall(nextX, nextY)) { //�����̷��� ���� ���̸�
		return;
	}

	//������ seqNum x y ����
	sendInt2Server(seqNum);
	sendInt2Server(nextX);
	sendInt2Server(nextY);
}

void showLeftTime() {
	EnterCriticalSection(&cs);

	gotoxy(100, 3);
	printf("%d seconds left", leftTime / 1000);

	LeaveCriticalSection(&cs);
}

void timeover() {
	isGameOver = true;
	system("title �ð� �ʰ��� �����ڰ� �¸��Ͽ����ϴ�!");
}

unsigned int __stdcall LeftTimeThread(void* args) {
	while (1) {
		if (clockCount % 1000 == 0) {
			showLeftTime(); //���� �ð� ���
			leftTime -= 1000;
			if (leftTime <= 0) {
				timeover();
				break;
			}

			Sleep(100);
		}
	}

	return 0;
}

void startGame() {

	init();
	
	InitializeCriticalSection(&cs);

	_beginthreadex(NULL, 0, KeyboardHandlerThread, NULL, 0, NULL); //����Ű �Է¿� ���� �ǽð����� dir ����
	_beginthreadex(NULL, 0, RecvCoordThread, NULL, 0, NULL); //�ǽð����� ĳ���͵��� ��ǥ�� �����κ��� ����
	_beginthreadex(NULL, 0, LeftTimeThread, NULL, 0, NULL); //�ð� ����

	while (1) {
		if ( (seqNum == MAX_PLAYABLE_COUNT - 1 && clockCount % chaserSpeed == 0) || (seqNum != MAX_PLAYABLE_COUNT - 1 && clockCount % runnerSpeed == 0) ) { //�����ڴ� charserSpeed����, �����ڴ� runnerSpeed���� �ڽ��� ��ġ�� �ű� �� �������� ����
			sendMyNextPosition();
		}

		moveAllCharactors();

		Sleep(clockCountIncreaseAmount);
		clockCount = clockCount + clockCountIncreaseAmount;
	}

	DeleteCriticalSection(&cs);
}

int main() {

	startGame();

	closesocket(hSocket);
	WSACleanup();

	Sleep(3000);
	return 0;
}