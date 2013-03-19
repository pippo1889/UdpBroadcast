// UDPDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#pragma comment(lib,"Ws2_32.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	//int c;
	//int a;
	//a = getchar();
	//while(a!= '\n')
	//{
	//	printf ("%c",a);
	//	a = getchar();
	//}

	//char ip[50];
	//char port[50];
	//printf ("请输入IP地址:");
	//gets_s(ip, 50);
	//printf ("请输入请输入端口地址:");
	//gets_s(port, 50);

	WSADATA wsaData = {0};
	if(WSAStartup(MAKEWORD(2,2),&wsaData) != 0)
	{
		printf("WSAStartup failed!");
		return -1;
	}

	SOCKET s= socket(AF_INET, SOCK_DGRAM,0);

	SOCKADDR_IN addr;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(56679); 

	if(bind(s, (SOCKADDR *)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		printf("bind failed!");
	}

	SOCKADDR_IN from;
	char tmp[100];
	int fromLen = sizeof(from);


	DWORD dw= 0;
	int ret = recvfrom(s, tmp, 100, 0, (SOCKADDR *)&from, &fromLen);
	while(true)
	{
		if(ret == SOCKET_ERROR)
		{
			dw = WSAGetLastError();
			break;
		}
		else if(ret == 0)
		{
			break;
		}
		else if( ret > 0)
		{
			printf("收到数据:%s\r\n", tmp);
			if(strcmp(tmp,"quit") == 0)
				break;
		}
		ret = recvfrom(s, tmp, 100, 0, (SOCKADDR *)&from, &fromLen);
	}

	closesocket(s);
	WSACleanup();

	return 0;

} 

