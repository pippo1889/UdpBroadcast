// UDPDemoSend.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#pragma comment(lib,"Ws2_32.lib")


int _tmain(int argc, _TCHAR* argv[])
{

	WSADATA wsaData = {0};
	if(WSAStartup(MAKEWORD(2,2),&wsaData) != 0)
	{
		printf("WSAStartup failed!");
		return -1;
	}

	SOCKET s= socket(AF_INET, SOCK_DGRAM,0);

	BOOL fBroadcast = TRUE;
	setsockopt(s,SOL_SOCKET,SO_BROADCAST,(char *)&fBroadcast,sizeof (BOOL));

	SOCKADDR_IN recvaddr;
	recvaddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	recvaddr.sin_family = AF_INET;
	recvaddr.sin_port = htons(56679); 

	DWORD dw= 0;
	char tmp[100];
	memset(tmp,0,100);	
	int recvLen = sizeof(recvaddr);
	int ret = 0;
	while(gets(tmp) != NULL)
	{
		if(strcmp(tmp,"q") == 0)
			break;

		ret = sendto(s, tmp, 100, 0, (SOCKADDR *)&recvaddr, recvLen);
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

		}
	}	
	closesocket(s);
	WSACleanup();

	
	return 0;
}

