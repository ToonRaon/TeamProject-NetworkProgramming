#pragma comment(lib, "ws2_32")

#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MAP_HEIGHT 20
#define MAP_WIDTH 50

int map_input[MAP_HEIGHT][MAP_WIDTH] = {
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,1,
	1,0,1,0,1,0,1,1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,0,0,0,0,0,0,1,0,1,1,
	1,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,
	1,0,1,1,1,0,1,1,0,1,0,1,1,1,0,1,1,1,0,1,1,0,1,0,1,1,0,1,0,0,1,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
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
		printf("%s", map[i]);
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
	//int r = y;
	//int c = x / 2;

	//if (map_input[r][c] == 1) {
	//	return true;
	//}

	//return false;

	return false;
}

//벽이면 true return
bool move(int x, int y) {
	if (isWall(x, y)) { //벽이면 바로 return true
		return true;
	}

	gotoxy(x, y);
	return false;
}

void move(int dir) {
	bool b = false;

	COORD cur = getxy();
	int curX = cur.X;
	int curY = cur.Y;

	printf("　");
	switch (dir) {
	case 4: //좌
		b = move(curX - 2, curY);
		break;
	case 6: //우
		b = move(curX + 2, curY);
		break;
	case 8: //상
		b = move(curX, curY - 1);
		break;
	case 2: //하
		b = move(curX, curY + 1);
		break;
	}
	if (b == true) {
		return;
	}
	printf("◎");

	cur = getxy();
	curX = cur.X;
	curY = cur.Y;
	move(curX - 2, curY); //printf하면 오른쪽으로 커서 밀려서 다시 원래대로
}

void init() {
	printMap();

	removeCursor();
}

void keyboardHandler() {
	while (1) {
		int key = getch();

		if (key == 224) { //방향키 아스키 코드 ↑: 224, 72 ↓: 224, 80 ←: 224, 75 →: 224, 77
			key = getch();
			switch (key) {
			case 72: //위
				move(8);
				break;
			case 75: //왼쪽
				move(4);
				break;
			case 77: //오른쪽
				move(6);
				break;
			case 80: //아래
				move(2);
				break;
			}
		}
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