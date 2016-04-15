#ifndef WIN32_LEAN_AND_MEAN 
#define WIN32_LEAN_AND_MEAN
#endif #include <windows.h> 

#include <WS2tcpip.h>
#include <IPHlpApi.h>
#include <stdio.h> 
#include <stdlib.h>
#include <process.h>
#include "Config.h"
#include "ServerUserManage.h"
#include "ServerMassage.h"
#include "ServerNotice.h"
#include "ServerAdminManage.h"

#define MAX_THREAD_COUNTS 20 

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
	DataHead head;
	sockaddr_in currAddr;
	bool isLogin = false;
	SOCKET clientSocket = INVALID_SOCKET;
	SOCKET *pListenSocket = (SOCKET*)pSocket;
	PUserOnlineNode currOnlineUser = NULL;
	int addrLen = sizeof(currAddr);
	currOnlineUser = (PUserOnlineNode)malloc(sizeof(UserOnlineNode));
	if (currOnlineUser == NULL)
	{
		printf("Malloc failed!\n");
		return ERROR_MALLOC;
	}

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

		while (!g_isExit && nRet == SUCCESS)
		{
			nRet = RecvHead(clientSocket, &head);
			if (nRet != SUCCESS)
			{
				break;
			}

			if (!isLogin) // 用户未登陆
			{
				switch (head.cmd)
				{
					case CMD_REGIEST:
						nRet = Register(clientSocket);
						break;
					case CMD_LOGIN:
						nRet = Login(clientSocket, currOnlineUser, &isLogin);
						break;
					default:
						nRet = ERROR_OTHER;
						break;
				}
			}
			else         // 用户已登陆
			{
				switch (head.cmd)
				{
				case CMD_LOGOUT:
					nRet = Logout(&clientSocket, currOnlineUser, &isLogin);
					break;
				case CMD_GROUPCHAT:
					nRet = GroupMassage(currOnlineUser, &head);
					break;
				case CMD_PRIVATECHAT:
					nRet = PrivateMassage(currOnlineUser, &head);
					break;
				case CMD_SET_USER_NAME:
					nRet = SetUserName(currOnlineUser);
					break;
				case  CMD_SET_USER_PWD:
					nRet = SetUserPwd(currOnlineUser);
					break;
				case CMD_GET_ALL_USER:
					nRet = SendAllUserList(currOnlineUser);
					break;
				case CMD_GET_ONLINE_USER:
					nRet = SendOnlineUserList(currOnlineUser);
					break;
				case CMD_GET_CURRENT_USER:
					nRet = SendCurrentUser(currOnlineUser);
					break;
				case CMD_SET_USER_OFFLINE:
					nRet = SetUserOffLine(currOnlineUser);
					break;
				case CMD_SET_USER_LEVEL:
					nRet = SetUserLevel(currOnlineUser);
					break;
				default:
					break;
				}
			}
		}
		// 发送异常，用户退出登陆
		if (nRet != SUCCESS)
		{
			Logout(&clientSocket, currOnlineUser, &isLogin);
		}
		closesocket(clientSocket);
	}

	free(currOnlineUser);
	currOnlineUser = NULL;
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

		printf("服务启动成功，退出请输入（E）: \n");
		while ((ch = getchar()) != NULL)
		{
			ch = tolower(ch);
			if (ch = 'e')
			{
				g_isExit = true;
				break;
			}
		}

		WaitForMultipleObjects(MAX_THREAD_COUNTS, aThread, true, 500);
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