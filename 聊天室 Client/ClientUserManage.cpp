#include "ClientUserManage.h"
#include "stdio.h"

bool CheckNameAndPwd(char *pUserName, char *pPassword)
{
	bool isOK = true;
	if (pUserName != NULL)
	{
		for (int i = 0; pUserName[i] != '\0'; i++)
		{
			if (!isalnum(pUserName[i]))
			{
				isOK = false;
				break;
			}
		}
	}

	if (pPassword != NULL)
	{
		for (int i = 0; pPassword[i] != '\0'; i++)
		{
			if (!isalnum(pPassword[i]))
			{
				isOK = false;
				break;
			}
		}
	}

	return isOK;
}

int Register(char *pUserName, char *pPassword)
{
	int nRet = SUCCESS;
	UserData userData;
	DataHead head;
	strcpy_s(userData.userName, USER_NAME_LEN, pUserName);
	strcpy_s(userData.userPwd, USER_NAME_LEN, pPassword);
	userData.userLevel = LEVEL_USER;
	
	head.sign = DEFAULT_SIGN;
	head.cmd = CMD_REGIEST;
	head.response = RES_NULL;
	head.dataLen = sizeof(UserData);

	nRet = SendHead(g_connectSocket, &head);
	if (nRet == SUCCESS)
	{
		nRet = SendData(g_connectSocket, (char*)&userData, sizeof(UserData));
		RecvHead(g_connectSocket, &head);
		if (head.response != RES_SUCCESS)
		{
			printf("Register failed!\n");
			nRet = ERROR_OTHER;
		}
	}

	return nRet;
}

int Login(char *pUserName, char *pUserPwd)
{
	int nRet = SUCCESS;
	UserData userData;
	DataHead head;
	strcpy_s(userData.userName, USER_NAME_LEN, pUserName);
	strcpy_s(userData.userPwd, USER_NAME_LEN, pUserPwd);
	userData.userLevel = -1;

	head.sign = DEFAULT_SIGN;
	head.cmd = CMD_LOGIN;
	head.response = RES_NULL;
	head.dataLen = sizeof(UserData);

	nRet = SendHead(g_connectSocket, &head);
	if (nRet == SUCCESS)
	{
		nRet = SendData(g_connectSocket, (char*)&userData, sizeof(UserData));
		RecvHead(g_connectSocket, &head);
		if (head.response != RES_SUCCESS)
		{
			printf("Login failed!\n");
			nRet = ERROR_OTHER;
		}
	}

	return nRet;
}

int Logout()
{
	int nRet = SUCCESS;
	DataHead head;
	head.sign = DEFAULT_SIGN;
	head.cmd = CMD_LOGOUT;
	head.response = RES_NULL;
	head.dataLen = 0;
	nRet = SendHead(g_connectSocket, &head);
	return nRet;
}

int SetUserName(char *pNewUserName)
{
	int nRet = SUCCESS;
	DataHead head;

	head.sign = DEFAULT_SIGN;
	head.cmd = CMD_SET_USER_NAME;
	head.response = RES_NULL;
	head.dataLen = USER_NAME_LEN;

	nRet = SendHead(g_connectSocket, &head);
	if (nRet == SUCCESS)
	{
		nRet = SendData(g_connectSocket, pNewUserName, USER_NAME_LEN);
	}
	return nRet;
}

int SetUserPwd(char *pNewUserPwd)
{
	int nRet = SUCCESS;
	DataHead head;

	head.sign = DEFAULT_SIGN;
	head.cmd = CMD_SET_USER_PWD;
	head.response = RES_NULL;
	head.dataLen = USER_PWD_LEN;

	nRet = SendHead(g_connectSocket, &head);
	if (nRet == SUCCESS)
	{
		nRet = SendData(g_connectSocket, pNewUserPwd, USER_PWD_LEN);
	}
	return nRet;
}
