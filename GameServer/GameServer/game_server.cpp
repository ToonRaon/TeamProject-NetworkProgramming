#pragma comment(lib, "ws2_32")
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUF_SIZE 1024
#define MAX_PLAYABLE_COUNT 4 //최대 플레이 가능 인원

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

struct coord {
	int x;
	int y;
};
struct coord  coordArr[MAX_PLAYABLE_COUNT];



void ErrorHandling(const char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

bool isWall(int x, int y) {
	int r = y;
	int c = x / 2;

	if (map_input[r][c] == 1) {
		return true;
	}

	return false;
}

//0 ~ bound - 1 사이 정수를 랜덤으로 반환
int getRand(int bound) {
	srand(time(NULL));

	return (rand() % bound);
}

//캐릭터들의 처음 위치 세팅
void setInitPosition() {
	//랜덤으로 하니까 너무 오래 걸림
	//for (int i = 0; i < MAX_PLAYABLE_COUNT; i++) { // 마지막 1명만 추적자
	//	struct coord crd;

	//	while (1) {
	//		crd.x = 2 * getRand(MAP_WIDTH);
	//		crd.y = getRand(MAP_HEIGHT);

	//		//뽑은 x, y좌표가 벽이거나 이미 다른 캐릭터가 있는 자리면 다시 뽑음
	//		if (isWall(crd.x, crd.y)) {
	//			continue;
	//		}
	//		bool isOverlaped = false;
	//		for (int j = 0; j < i; j++) {
	//			if (coordArr[j].x == crd.x && coordArr[j].y == crd.y) {
	//				isOverlaped = true;
	//			}
	//		}
	//		if (isOverlaped) {
	//			continue;
	//		}

	//		break;
	//	}

	//	coordArr[i] = crd;
	//}

	//그냥 정해진 곳에 스폰
	coordArr[0].x = 6;
	coordArr[0].y = 1;

	coordArr[1].x = 22;
	coordArr[1].y = 9;

	coordArr[2].x = 42;
	coordArr[2].y = 6;

	coordArr[3].x = 36;
	coordArr[3].y = 11;
}

void startGameServer() {
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAdr, clntAdr;
	TIMEVAL timeout;
	fd_set reads, cpyReads;
	int connectedClientCount = 0;

	int adrSz;
	int strLen, fdNum, i;
	char buf[BUF_SIZE];
	
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi("123654"));

	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");
	if (listen(hServSock, MAX_PLAYABLE_COUNT) == SOCKET_ERROR) //입장 제한 4명
		ErrorHandling("listen() error");

	FD_ZERO(&reads);//select 함수의 관찰 대상이 되는 디스크립터들을 0으로 초기화
	//hServSock은 리스닝 소켓이므로 연결요청이 오는지 확인하기 위해
	FD_SET(hServSock, &reads);//hServSock을 관찰대상으로 등록

	while (1)
	{
		//select 함수의 호출이 끝나면 변화가 발생한 디스크립터를 제외한 나머지는 0으로
		//따라서 디스크립터 정보들을 복사
		cpyReads = reads;
		timeout.tv_sec = 5;
		timeout.tv_usec = 5000;

		//select함수 error 처리
		//윈도우에서는 관찰대상이 
		if ((fdNum = select(0, &cpyReads, 0, 0, &timeout)) == SOCKET_ERROR)
			break;
		//readset 즉 어떤 디스크립터(배열 내에)에도 변화가 없음을 의미
		//따라서 타임아웃 재설정하고 재호출하기 위해 continue 
		if (fdNum == 0)
			continue;
		//파일 스크립터 내에 상태가 변경되었을 경우
		//(연결 요청 또는 데이터 수신)
		for (i = 0; i < reads.fd_count; i++)
		{
			if (FD_ISSET(reads.fd_array[i], &cpyReads))
			{
				if (reads.fd_array[i] == hServSock)     // connection request!
				{
					adrSz = sizeof(clntAdr);
					hClntSock =
						accept(hServSock, (SOCKADDR*)&clntAdr, &adrSz);
					FD_SET(hClntSock, &reads);
					printf("connected client: %d \n", hClntSock);

					//connectedClientCount를 string으로 변환 후 클라에게 send == 즉 시퀀스 번호를 넘겨준다
					char string_connectedClientCount[16];
					sprintf(string_connectedClientCount, "%d", connectedClientCount++);
					send(hClntSock, string_connectedClientCount, sizeof(string_connectedClientCount), 0); //클라이언트에게 클라이언트의 시퀀스 번호를 보내준다.

					//각 캐릭터들 위치 전송
					for (int j = 0; j < MAX_PLAYABLE_COUNT; j++) {
						sprintf(string_connectedClientCount, "%d %d", coordArr[j].x, coordArr[j].y);
						send(hClntSock, string_connectedClientCount, sizeof(string_connectedClientCount), 0);
					}
				}
				else    // read message!
				{
					strLen = recv(reads.fd_array[i], buf, BUF_SIZE, 0); //seqNum 저장

					if (strLen == -1)    // close request!
					{
						FD_CLR(reads.fd_array[i], &reads);
						closesocket(cpyReads.fd_array[i]);
						printf("closed client: %d \n", cpyReads.fd_array[i]);
					}
					else
					{
						char buf2[BUF_SIZE]; //x 저장
						char buf3[BUF_SIZE]; //y 저장
						int strLen2 = recv(reads.fd_array[i], buf2, BUF_SIZE, 0); //방금 시퀀스 번호 메세지 날린 클라에게서 다시 한 번 x y 좌표를 받는다
						int strLen3 = recv(reads.fd_array[i], buf3, BUF_SIZE, 0); //방금 시퀀스 번호 메세지 날린 클라에게서 다시 한 번 x y 좌표를 받는다

						for (int j = 0; j < reads.fd_count; j++) { //모든 클라이언트들에게 방금 받은 시퀀스 번호와 x y 좌표 전송
							send(reads.fd_array[j], buf, strLen, 0); //시리얼 번호 send
							send(reads.fd_array[j], buf2, strLen2, 0); //x send
							send(reads.fd_array[j], buf3, strLen3, 0); //y send
						}
					}
				}
			}
		}
	}
	closesocket(hServSock);
	WSACleanup();

}

int main() {
	setInitPosition();

	printf("Start Server\n");
	startGameServer();

	return 0;
}