#pragma comment(lib, "ws2_32")

#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <process.h>
#include <Windows.h>

#define MAP_HEIGHT 20
#define MAP_WIDTH 34

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

int dir; //상,하,좌,우 각각 8,2,4,6 (숫자 키패드)
int moveSpeed = 300; //moveSpeed 밀리초만큼 Sleep한 후 캐릭터가 1칸 움직이는 걸 반복합니다. (숫자가 낮을수록 속도가 빠름)


unsigned int __stdcall KeyboardHandlerThread(void* args) {
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

	//좌표를 콘솔창 타이틀에 출력
	//char temp[100];
	//sprintf(temp, "title y: %d, x: %d, r: %d, c: %d", y, x, r, c);
	//system(temp);

	if (map_input[r][c] == 1) {
		return true;
	}

	return false;
}

void move(int dir) {
	COORD cur = getxy();
	int curX = cur.X;
	int curY = cur.Y;
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
	printf("　");
	gotoxy(nextX, nextY);
	printf("◎");

	cur = getxy();
	gotoxy(cur.X - 2, cur.Y); //printf하면 오른쪽으로 커서 밀려서 다시 원래대로
}

void init() {
	printMap();

	removeCursor();
}

void keyboardHandler() {
	HANDLE handlerThread;
	unsigned handlerThreadThreadID;

	handlerThread = (HANDLE)_beginthreadex(NULL, 0, KeyboardHandlerThread, NULL, 0, &handlerThreadThreadID); //이 쓰레드에서 방향키에 따라 dir를 설정

	while (1) {
		move(dir); //dir방향으로 이동
		Sleep(moveSpeed); //moveSpeed 시간만큼 sleep
	}
}

void startGame() {
	init();

	gotoxy(2, 1);
	printf("◎");
	gotoxy(2, 1);

	keyboardHandler();
}

int main() {

	startGame();

	Sleep(3000);
	return 0;
}