#ifndef WIN32_LEAN_AND_MEAN 
#define WIN32_LEAN_AND_MEAN
#endif #include <windows.h> 

#include <WS2tcpip.h>
#include <IPHlpApi.h>
#include <stdio.h> 
#include <stdlib.h>
#include <process.h>
#include "Config.h"

#define MAX_THREAD_COUNTS 20 
#define DEFAULT_PORT 27015

PUserDataNode g_pUserDataBegin;
PUserDataNode g_pUserDataEnd;

PUserOnlineNode g_pUserOnlineBegin;
PUserOnlineNode g_pUserOnlineEnd;

HANDLE g_hMutex;
bool g_isExit = false;

// 初始化监听套接字
int InitListenSocket(SOCKET *pListenSocket)
{
	int nRet = 0;
	int iResult;
	sockaddr_in service;

	service.sin_family = AF_INET;
	//service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_addr.s_addr = ADDR_ANY;
	service.sin_port = htons(DEFAULT_PORT);
	*pListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (*pListenSocket != INVALID_SOCKET)
	{
		iResult = bind(*pListenSocket, (SOCKADDR*)&service, sizeof(service));
		if (iResult == SOCKET_ERROR)
		{
			printf("bind failed with error: %d\n", WSAGetLastError());
			nRet = 1;
		}
	}
	else
	{
		printf("socket failed with error: %ld\n", WSAGetLastError());
	}
	return nRet;
}

unsigned __stdcall ClientThread(void *pSocket)
{
	int nRet = 0;
	long userCounts;
	sockaddr_in currAddr;
	SOCKET clientSocket = INVALID_SOCKET;
	SOCKET *pListenSocket = (SOCKET*)pSocket;
	int addrLen = sizeof(currAddr);

	while (!g_isExit)
	{
		// 原子锁
		WaitForSingleObject(g_hMutex, INFINITE);
		clientSocket = accept(*pListenSocket, (sockaddr *)&currAddr, &addrLen);
		ReleaseMutex(g_hMutex);

		if (clientSocket == INVALID_SOCKET)
		{
			printf("accept failed: %d\n", GetLastError());
			nRet = ERROR_ACCEPT;
			continue;
		}


	}

	return nRet;
}

int main()
{
	int iResult;
	WSADATA wsaData;
	SOCKET listeningSocket = INVALID_SOCKET;
	HANDLE aThread[MAX_THREAD_COUNTS];
	char ch;
	// 初始化winsock 
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	// 创建互斥锁
	g_hMutex = CreateMutex(NULL, false, NULL);
	if (g_hMutex == NULL)
	{
		printf("CreateMutex error: %d\n", GetLastError());
		return 1;
	}

	InitConfig();

	InitListenSocket(&listeningSocket);
	iResult = listen(listeningSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
		printf("Listen failed with error: %d\n", WSAGetLastError());
	}
	else
	{
		for (int i = 0; i < MAX_THREAD_COUNTS; i++)
		{
			aThread[i] = (HANDLE)_beginthreadex(NULL, 0, &ClientThread, (void*)&listeningSocket, 0, NULL);
		}

		printf("服务启动成功，退出请输入（E）: ");
		while ((ch = getchar()) != NULL)
		{
			ch = tolower(ch);
			if (ch = 'e')
			{
				g_isExit = true;
				break;
			}
		}

		WaitForMultipleObjects(MAX_THREAD_COUNTS, aThread, true, INFINITE);
		for (int i = 0; i < MAX_THREAD_COUNTS; i++)
		{
			CloseHandle(aThread[i]);
		}
	}

	// 释放资源
	CloseConfig();
	CloseHandle(g_hMutex);
	closesocket(listeningSocket);
	WSACleanup();

	return 0;
}