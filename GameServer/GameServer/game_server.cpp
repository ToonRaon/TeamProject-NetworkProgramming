#pragma comment(lib, "ws2_32")
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUF_SIZE 1024
#define MAX_PLAYABLE_COUNT 4 //�ִ� �÷��� ���� �ο�

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

//0 ~ bound - 1 ���� ������ �������� ��ȯ
int getRand(int bound) {
	srand(time(NULL));

	return (rand() % bound);
}

//ĳ���͵��� ó�� ��ġ ����
void setInitPosition() {
	//�������� �ϴϱ� �ʹ� ���� �ɸ�
	//for (int i = 0; i < MAX_PLAYABLE_COUNT; i++) { // ������ 1�� ������
	//	struct coord crd;

	//	while (1) {
	//		crd.x = 2 * getRand(MAP_WIDTH);
	//		crd.y = getRand(MAP_HEIGHT);

	//		//���� x, y��ǥ�� ���̰ų� �̹� �ٸ� ĳ���Ͱ� �ִ� �ڸ��� �ٽ� ����
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

	//�׳� ������ ���� ����
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
	if (listen(hServSock, MAX_PLAYABLE_COUNT) == SOCKET_ERROR) //���� ���� 4��
		ErrorHandling("listen() error");

	FD_ZERO(&reads);//select �Լ��� ���� ����� �Ǵ� ��ũ���͵��� 0���� �ʱ�ȭ
	//hServSock�� ������ �����̹Ƿ� �����û�� ������ Ȯ���ϱ� ����
	FD_SET(hServSock, &reads);//hServSock�� ����������� ���

	while (1)
	{
		//select �Լ��� ȣ���� ������ ��ȭ�� �߻��� ��ũ���͸� ������ �������� 0����
		//���� ��ũ���� �������� ����
		cpyReads = reads;
		timeout.tv_sec = 5;
		timeout.tv_usec = 5000;

		//select�Լ� error ó��
		//�����쿡���� ��������� 
		if ((fdNum = select(0, &cpyReads, 0, 0, &timeout)) == SOCKET_ERROR)
			break;
		//readset �� � ��ũ����(�迭 ����)���� ��ȭ�� ������ �ǹ�
		//���� Ÿ�Ӿƿ� �缳���ϰ� ��ȣ���ϱ� ���� continue 
		if (fdNum == 0)
			continue;
		//���� ��ũ���� ���� ���°� ����Ǿ��� ���
		//(���� ��û �Ǵ� ������ ����)
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

					//connectedClientCount�� string���� ��ȯ �� Ŭ�󿡰� send == �� ������ ��ȣ�� �Ѱ��ش�
					char string_connectedClientCount[16];
					sprintf(string_connectedClientCount, "%d", connectedClientCount++);
					send(hClntSock, string_connectedClientCount, sizeof(string_connectedClientCount), 0); //Ŭ���̾�Ʈ���� Ŭ���̾�Ʈ�� ������ ��ȣ�� �����ش�.

					//�� ĳ���͵� ��ġ ����
					for (int j = 0; j < MAX_PLAYABLE_COUNT; j++) {
						sprintf(string_connectedClientCount, "%d %d", coordArr[j].x, coordArr[j].y);
						send(hClntSock, string_connectedClientCount, sizeof(string_connectedClientCount), 0);
					}
				}
				else    // read message!
				{
					strLen = recv(reads.fd_array[i], buf, BUF_SIZE, 0); //seqNum ����

					if (strLen == -1)    // close request!
					{
						FD_CLR(reads.fd_array[i], &reads);
						closesocket(cpyReads.fd_array[i]);
						printf("closed client: %d \n", cpyReads.fd_array[i]);
					}
					else
					{
						char buf2[BUF_SIZE]; //x ����
						char buf3[BUF_SIZE]; //y ����
						int strLen2 = recv(reads.fd_array[i], buf2, BUF_SIZE, 0); //��� ������ ��ȣ �޼��� ���� Ŭ�󿡰Լ� �ٽ� �� �� x y ��ǥ�� �޴´�
						int strLen3 = recv(reads.fd_array[i], buf3, BUF_SIZE, 0); //��� ������ ��ȣ �޼��� ���� Ŭ�󿡰Լ� �ٽ� �� �� x y ��ǥ�� �޴´�

						for (int j = 0; j < reads.fd_count; j++) { //��� Ŭ���̾�Ʈ�鿡�� ��� ���� ������ ��ȣ�� x y ��ǥ ����
							send(reads.fd_array[j], buf, strLen, 0); //�ø��� ��ȣ send
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