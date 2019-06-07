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
#define MAX_PLAYABLE_COUNT 4 //최대 플레이 가능 인원
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
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
	"■　　　　　　　　　　■　　　　　　　　　　　　　　■■　■■　　■",
	"■　■　■　■■　■■■■■　■　■　■■■■■　　　　　　■　■■",
	"■　■　■　　　　■　　　　　　　■　■　　■　　■　■　　■　　■",
	"■　■■■　■■　■　■■■　■■■　■■　■　■■　■　　■　　■",
	"■　■　　　　　　　　■　■　■■　　　■　■■■■■■■　　　　■",
	"■　■■　■■　■■■　　　　■　■　■■　　■　　■　　　■■■■",
	"■　　　　■■　■　　　■　■■　　　　　　　　　　■　■　■　　■",
	"■■　■　■■■■■■　■　　■　■■■　■■■■　■　■　■■　■",
	"■■■■　■■　　　■　　　　■　　　　　　■　　　■　■　　　　■",
	"■　　■　　　　■　■　■■　　　■■　■■■　■■　　■■■■　■",
	"■　■■　■■　■　■　　　　■　　　■　　　　■■　■　　　■　■",
	"■　　　　■　　■　　　■■　■■■■■■　■■　　　■　■　■　■",
	"■　■■■　　　■■■　■　　　　　　　　　■　　■　■　■　　　■",
	"■　■　■　■　　　　　　　　■　■　■　■■■■■　■　　　■　■",
	"■　　■　■■　■　■■■　■■　■　■　■　　■　　　■■■■　■",
	"■　■■　■■　■　■　■　■　　　　■　　　　■　■　　　　　　■",
	"■　■　　■　　　■■　　　■　■　■■■■■　■　■　■■■■　■",
	"■　　　　　　■　　　　■■■　■　　　■　　　　　■　■　　　　■",
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
};

struct charactor {
	char icon[2]; //추격자: Ω, 도망자: ●
	int x; //현재 화면 상의 x좌표
	int y; //현재 화면 상의 y좌표
	int next_x; //서버에서 전송된, 이제 이동해야할 x좌표
	int next_y; //서버에서 전송된, 이제 이동해야할 y좌표
};

struct charactor* charactorArr[MAX_PLAYABLE_COUNT]; //무조건 마지막 플레이어가 추적자

SOCKET hSocket;

int chaserSpeed = 250; //추적자 속도. moveSpeed 밀리초만큼 Sleep한 후 캐릭터가 1칸 움직이는 걸 반복합니다. (숫자가 낮을수록 속도가 빠름)
int runnerSpeed = 300; //도망자 속도. moveSpeed 밀리초만큼 Sleep한 후 캐릭터가 1칸 움직이는 걸 반복합니다. (숫자가 낮을수록 속도가 빠름)
int clockCount = 0;
int clockCountIncreaseAmount = 50; //반드시 chaserSpeed와 runnerSpeed의 공약수여야함.

int seqNum;
int dir; //상,하,좌,우 각각 8,2,4,6 (숫자 키패드)

int survivorCount = MAX_PLAYABLE_COUNT - 1;


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
	if (seqNum >= MAX_PLAYABLE_COUNT) { //5번째 이상 접속부터는 구경만
		return 0;
	}

	while (1) {
		int key = getch();

		if (key == 224) { //방향키 아스키 코드 ↑: 224, 72 ↓: 224, 80 ←: 224, 75 →: 224, 77
			key = getch();
			switch (key) {
			case 72: //위
				dir = 8;
				break;
			case 75: //왼쪽
				dir = 4;
				break;
			case 77: //오른쪽
				dir = 6;
				break;
			case 80: //아래
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
		recv(hSocket, buf2, sizeof(buf2), 0); //x 좌표
		recv(hSocket, buf3, sizeof(buf3), 0); //y 좌표

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

//2차원 char 배열을 출력한다. r은 행, c는 열
void printArray(char **arr, int r, int c) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; i < c; j++) {
			printf("%c", arr[r][c]);
		}
		puts("");
	}
	puts("");
}

//맵 출력
void printMap() {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			printf("%s", map_input[i][j] == 1 ? "■" : "　");
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

//커서 이동
void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//커서 좌표 get
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

	if (ch->next_x < 0 || ch->next_y < 0 || ch->next_x >= 2 * MAP_WIDTH || ch->next_y >= MAP_HEIGHT) { //맵 범위 벗어나면 return
		return;
	}

	//원래 위치에 있던 아이콘 지우고
	gotoxy(ch->x, ch->y);
	printf("　");

	//새 위치로 이동
	gotoxy(ch->next_x, ch->next_y);
	printf("%s", ch->icon);

	ch->x = ch->next_x;
	ch->y = ch->next_y;
}

void chaserWin() {
	system("title 추격자가 승리하였습니다!");
}

void isCatchedByChaser() {
	for (int i = 0; i < MAX_PLAYABLE_COUNT - 1; i++) {
		if (charactorArr[i]->x == charactorArr[MAX_PLAYABLE_COUNT - 1]->x && charactorArr[i]->y == charactorArr[MAX_PLAYABLE_COUNT - 1]->y) { //어떤 도망자가 추적자에게 잡히면
			charactorArr[i]->x = -1;
			charactorArr[i]->next_x = -1;
			charactorArr[i]->y = -1;
			charactorArr[i]->next_y = -1;

			survivorCount--;

			if (survivorCount == 0) { //남은 생존자가 없으면
				chaserWin();
			}
		}
	}
}

void move(int seq) {
	struct charactor* ch = charactorArr[seq];

	if (seq == seqNum) { //내 클라이언트에 해당하는 캐릭터 바꿀 땐 빨간색으로 아이콘 표시
		setTextColor(COLOR_RED);
	}
	
	drawIcon(seq);

	if (seq == seqNum) {
		setTextColor(COLOR_WHITE);
	}

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
	recv(hSocket, buf, sizeof(buf), 0);//이 클라의 시퀀스 번호 받아옴
	seqNum = atoi(buf); //받아온 시리얼 번호를 int로 변환하여 seqNum에 저장

	//각 캐릭터들의 초기 좌표 받아옴
	for (int i = 0; i < MAX_PLAYABLE_COUNT; i++) {
		recv(hSocket, buf, sizeof(buf), 0);
		charactorArr[i]->x = atoi(strtok(buf, " "));
		charactorArr[i]->next_x = charactorArr[i]->x;
		charactorArr[i]->y = atoi(strtok(NULL, " "));
		charactorArr[i]->next_y = charactorArr[i]->y;
	}

	//테스트 코드
	sprintf(buf, "title seqNum: %d\n", seqNum);
	system(buf);
}

struct charactor* createCharactorStruct(const char icon[2], int x, int y) {
	struct charactor* ch = (struct charactor*)malloc(sizeof(struct charactor));
	ch->x = x;
	ch->y = y;
	ch->next_x = x;
	ch->next_y = y;
	strcpy(ch->icon, icon);

	return ch;
}

void initCharactorArr() {
	for (int i = 0; i < MAX_PLAYABLE_COUNT; i++) {
		if (i == MAX_PLAYABLE_COUNT - 1) { //추적자
			charactorArr[i] = createCharactorStruct("Ω", -1, -1);
		}
		else { //도망자
			charactorArr[i] = createCharactorStruct("●", -1, -1);
		}
	}
}

void init() {
	printMap();

	initCharactorArr();

	connect2Server();
	
	removeCursor();
}

void moveAllCharactors() {
	for (int i = 0; i < MAX_PLAYABLE_COUNT; i++) {
		move(i);
	}
}

void sendMyNextPosition() {
	if (seqNum >= MAX_PLAYABLE_COUNT) { // 5번째 접속부터는 그냥 구경만
		return;
	}

	struct charactor* ch = charactorArr[seqNum];
	int curX = ch->x;
	int curY = ch->y;
	int nextX = curX;
	int nextY = curY;

	switch (dir) {
	case 4: //좌
		nextX = curX - 2;
		break;
	case 6: //우
		nextX = curX + 2;
		break;
	case 8: //상
		nextY = curY - 1;
		break;
	case 2: //하
		nextY = curY + 1;
		break;
	}

	if (isWall(nextX, nextY)) { //움직이려는 곳이 벽이면
		return;
	}

	//서버에 seqNum x y 전송
	sendInt2Server(seqNum);
	sendInt2Server(nextX);
	sendInt2Server(nextY);
}

void startGame() {
	init();

	_beginthreadex(NULL, 0, KeyboardHandlerThread, NULL, 0, NULL); //방향키 입력에 따라서 실시간으로 dir 설정
	_beginthreadex(NULL, 0, RecvCoordThread, NULL, 0, NULL); //실시간으로 캐릭터들의 좌표를 서버로부터 수신

	while (1) {
		if ( (seqNum == MAX_PLAYABLE_COUNT - 1 && clockCount % chaserSpeed == 0) || (seqNum != MAX_PLAYABLE_COUNT - 1 && clockCount % runnerSpeed == 0) ) { //추적자는 charserSpeed마다, 도망자는 runnerSpeed마다 자신의 위치를 옮긴 후 서버에게 보냄
			sendMyNextPosition();
		}

		moveAllCharactors();

		Sleep(clockCountIncreaseAmount);
		clockCount = clockCount + clockCountIncreaseAmount;
	}
}

int main() {

	startGame();

	closesocket(hSocket);
	WSACleanup();

	Sleep(3000);
	return 0;
}