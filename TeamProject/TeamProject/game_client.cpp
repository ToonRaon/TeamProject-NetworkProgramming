#pragma comment(lib, "ws2_32")

#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>

#define MAP_HEIGHT 20
#define MAP_WIDTH 50

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

void init() {
	printMap();
}

void startGame() {
	init();
}

int main() {

	startGame();

	return 0;
}