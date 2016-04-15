#ifndef WIN32_LEAN_AND_MEAN 
#define WIN32_LEAN_AND_MEAN 
#endif #include <windows.h> 

#include <WinSock2.h> 
#include <WS2tcpip.h> 
#include <IPHlpApi.h> 
#include <stdio.h> 
#include <string.h>
#include <process.h>
#include <conio.h>
#include <stdlib.h>
#include "BaseData.h"
#include "ClientUserManage.h"
#include "ClientMassage.h"
#include "ClientNotice.h"
#include "ClientAdminManage.h"

#define DEFAULT_BUFLEN 1024
#define MASSAGE_BUFLEN 512 
#define IP_LEN 20

SOCKET g_connectSocket = INVALID_SOCKET;
UserData g_myUser;
bool g_isLogin = false;

int CreateConnectSocket(char *serverName, SOCKET *pConnectSocket)
{
	int nRet = SUCCESS;
	int iResult;
	sockaddr_in clientService;
	// 确定服务器地址和端口 
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr(serverName);
	clientService.sin_port = htons(DEFAULT_PORT);

	// 创建套接字连接到服务器
	*pConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (*pConnectSocket == INVALID_SOCKET)
	{
		printf("Error at socket(): %ld\n", WSAGetLastError());
		nRet = ERROR_OTHER;
	}
	// 创建成功,连接服务器
	if (nRet == 0)
	{
		iResult = connect(*pConnectSocket, (SOCKADDR *)&clientService, sizeof(clientService));
		if (iResult == SOCKET_ERROR)
		{
			printf("Error at cnnect(): %d\n", iResult);
			nRet = ERROR_OTHER;
		}
	}

	return nRet;
}

unsigned __stdcall RecvMsgThread(void *pSocket)
{
	int iResult;
	char *recvbuf;
	DataHead dataHead;
	SOCKET *connectSocket = (SOCKET*)pSocket;
	
	do
	{
		// 获取数据头
		iResult = RecvHead(*connectSocket, &dataHead);
		if (iResult == SOCKET_ERROR)
		{
			printf("recv failed! Error code: %d\n", GetLastError());
			break;
		}

		if (dataHead.response == RES_SUCCESS)
		{
			switch (dataHead.cmd)
			{
			case CMD_PRIVATECHAT:
				printf("私聊消息发送成功!\n");
				break;
			case CMD_LOGOUT:
				printf("您已经退出登陆!\n");
				g_isLogin = false;
				break;
			case CMD_SET_USER_NAME:
				printf("设置用户名成功\n");
				break;
			case  CMD_SET_USER_PWD:
				printf("设置用户密码成功\n");
				break;
			case CMD_SET_USER_OFFLINE:
				printf("强制用户离线成功\n");
				break;
			case  CMD_SET_USER_LEVEL:
				printf("设置用户权限成功\n");
				break;
			default:
				break;
			}
		}
		else if (dataHead.response == RES_FAULT)
		{
			switch (dataHead.cmd)
			{
			case CMD_PRIVATECHAT:
				printf("私聊消息发送失败!\n");
				break;
			case CMD_SET_USER_NAME:
				printf("设置用户名失败\n");
				break;
			case  CMD_SET_USER_PWD:
				printf("设置用户密码失败\n");
				break;
			default:
				break;
			}
		}
		else
		{

			recvbuf = (char *)malloc(dataHead.dataLen);
			if (recvbuf == NULL)
			{
				iResult = ERROR_MALLOC;
				printf("malloc failed!");
				continue;
			}

			iResult = RecvData(*connectSocket, recvbuf, dataHead.dataLen);
			if (iResult != SUCCESS)
			{
				break;
			}

			// 判断数据类型，解析数据内容并输出
			switch (dataHead.cmd)
			{

			case CMD_GROUPCHAT:
				PrintGroupMassage(recvbuf);
				break;
			case CMD_PRIVATECHAT:
				PrintPrivateMassage(recvbuf);
				break;
			case CMD_SEND_ONLINE_USER:
				PrintOnlineUser(recvbuf);
				break;
			case CMD_SEND_USER:
				PrintUser(recvbuf);
				break;
			case CMD_SEND_CURRENT_USER:
				SetCurrentUserData(recvbuf);
				PrintOnlineUser(recvbuf);
				break;
			default:
				break;
			}
			free(recvbuf);
			recvbuf = NULL;
		}

	} while (g_isLogin);

	return iResult;
}

void Run()
{
	int nRet = SUCCESS;
	HANDLE hThread;
	char msgBuf[MASSAGE_BUFLEN];
	char userName[USER_NAME_LEN];
	char userPwd[USER_PWD_LEN];
	int option;
	printf("|--------------------------聊天室菜单：-------------------------------|\n");
	printf("| 1.发送群消息   2.发送私聊消息 3.获取当前在线用户 4.获取所有用户     |\n");
	printf("| 5.设置用户名   6.设置登陆密码                                       |\n");
	printf("| 7.强制用户离开(ADMIN)  8.设置用户级别(SUPER ADMIN)  9.退出登陆      |\n");
	printf("|---------------------------------------------------------------------|\n");
	// 创建接受信息的线程
	hThread = (HANDLE)_beginthreadex(NULL, 0, &RecvMsgThread, (void*)&g_connectSocket, 0, NULL);
	CloseHandle(hThread);
	GetCurrentUserData();
	while (g_isLogin)
	{
		printf("请输入指令：\n");
		scanf("%d", &option);
		while (getchar() != '\n')
		{
			continue;
		}

		if (!g_isLogin)
		{
			break;
		}
		switch (option)
		{
		case 1:
			printf("请输入您要发送的消息：\n");
			gets(msgBuf);
			nRet = SendGroupMassage(msgBuf);
			break;
		case 2:
			printf("请输入你要发送的用户名：\n");
			gets(userName);
			printf("请输入您要发送的消息：\n");
			gets(msgBuf);
			nRet = SendPrivateMassage(userName, msgBuf);
			break;
		case 3:
			nRet = GetOnlineUserList();
			break;
		case 4:
			nRet = GetAllUserList();
			break;
		case 5:
			printf("请输入新的用户名：\n");
			gets(userName);
			nRet = SetUserName(userName);
			break;
		case 6:
			printf("请输入新的用户密码：\n");
			gets(userPwd);
			nRet = SetUserPwd(userPwd);
			break;
		case 7:
			if (g_myUser.userLevel >= LEVEL_AMMIN)
			{
				printf("请输入您要强制离开的用户名：\n");
				gets(userName);
				nRet = SetUserOffLine(userName);
			}
			else
			{
				printf("您的用户权限不够！\n");
			}
			break;
		case 8:
			if (g_myUser.userLevel == LEVEL_SUPER_ADMIN)
			{
				printf("请输入你要设置的用户名：\n");
				gets(userName);
				printf("请输入你要给予的权限（1.普通用户  2.管理员）：\n");
				scanf("%d", &option);
				switch (option)
				{
				case 1:
					nRet = SetUserLevel(userName, LEVEL_USER);
					break;
				case 2:
					nRet = SetUserLevel(userName, LEVEL_AMMIN);
					break;
				default:
					printf("您输入的指令不正确\n");
					break;
				}

			}
			else
			{
				printf("您的用户权限不够！\n");
			}
			break;
		case 9:
			Logout();
			g_isLogin = false;
			break;
		default:
			printf("请输入正确的指令！\n");
			break;
		}
	}
}

int main(int argc, char*argv[])
{
	int iResult;
	WSADATA wsaData;
	char userName[USER_NAME_LEN];
	char userPwd[USER_PWD_LEN];
	char msgBuf[MASSAGE_BUFLEN];
	char ServerName[IP_LEN] = "127.0.0.1";
	int option;
	bool isExit = false;
	//printf("请输入服务器ip: ");
	//gets(ServerName);

	// 初始化winsock 
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	iResult = CreateConnectSocket(ServerName, &g_connectSocket);
	if (iResult != SUCCESS)
	{
		printf("服务器地址不正确！\n");
	}
	else
	{
		while (!isExit)
		{
			printf("注册请输入：1\t登陆请输入: 2\t退出程序请输入: 3\n");
			scanf("%d", &option);
			while (getchar() != '\n')
			{
				continue;
			}

			switch (option)
			{
			case 1:
				printf("请输入用户名(长度不超过20，不能包含特殊符号)：\n");
				gets(userName);
				printf("请输入用户秘密（由字母或数字组成）：\n");
				gets(userPwd);

				if (!CheckNameAndPwd(userName, userPwd))
				{
					printf("您输入的注册信息不合法！\n");
					break;
				}
				iResult = Register(userName, userPwd);
				if (iResult == SUCCESS)
				{
					printf("注册成功！\n");
				}
				else
				{
					printf("注册失败，可能您的用户名已经存在!\n");
				}
				break;
			case 2:
				printf("请输入用户名(长度不超过20，不能包含特殊符号)：\n");
				gets(userName);
				printf("请输入用户秘密（由字母或数字组成）：\n");
				gets(userPwd);
				if (!CheckNameAndPwd(userName, userPwd))
				{
					printf("您输入的登陆信息不合法！\n");
					break;
				}
				iResult = Login(userName, userPwd);
				if (iResult != SUCCESS)
				{
					printf("登陆失败");
					break;
				}

				printf("登陆成功！\n");
				strcpy_s(g_myUser.userName, USER_NAME_LEN, userName);
				strcpy_s(g_myUser.userPwd, USER_PWD_LEN, userPwd);
				g_isLogin = true;
				Run();

				break;
			case 3:
				printf("程序退出！\n");
				isExit = true;
				break;
			default:
				printf("请输入正确的命令!\n");
				break;
			}
		}
	}

	closesocket(g_connectSocket);
	WSACleanup();
	getchar();
	return 0;
}