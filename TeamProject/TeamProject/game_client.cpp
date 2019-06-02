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

int dir; //��,��,��,�� ���� 8,2,4,6 (���� Ű�е�)
int moveSpeed = 300; //moveSpeed �и��ʸ�ŭ Sleep�� �� ĳ���Ͱ� 1ĭ �����̴� �� �ݺ��մϴ�. (���ڰ� �������� �ӵ��� ����)


unsigned int __stdcall KeyboardHandlerThread(void* args) {
	while (1) {
		int key = getch();

		if (key == 224) { //����Ű �ƽ�Ű �ڵ� ��: 224, 72 ��: 224, 80 ��: 224, 75 ��: 224, 77
			key = getch();
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

	//��ǥ�� �ܼ�â Ÿ��Ʋ�� ���
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
	printf("��");
	gotoxy(nextX, nextY);
	printf("��");

	cur = getxy();
	gotoxy(cur.X - 2, cur.Y); //printf�ϸ� ���������� Ŀ�� �з��� �ٽ� �������
}

void init() {
	printMap();

	removeCursor();
}

void keyboardHandler() {
	HANDLE handlerThread;
	unsigned handlerThreadThreadID;

	handlerThread = (HANDLE)_beginthreadex(NULL, 0, KeyboardHandlerThread, NULL, 0, &handlerThreadThreadID); //�� �����忡�� ����Ű�� ���� dir�� ����

	while (1) {
		move(dir); //dir�������� �̵�
		Sleep(moveSpeed); //moveSpeed �ð���ŭ sleep
	}
}

void startGame() {
	init();

	gotoxy(2, 1);
	printf("��");
	gotoxy(2, 1);

	keyboardHandler();
}

int main() {

	startGame();

	Sleep(3000);
	return 0;
}