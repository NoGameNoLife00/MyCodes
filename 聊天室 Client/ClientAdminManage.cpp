#include "ClientAdminManage.h"


int SetUserOffLine(char *pUserName)
{
	int nRet = SUCCESS;
	DataHead head;
	head.sign = DEFAULT_SIGN;
	head.cmd = CMD_SET_USER_OFFLINE;
	head.response = RES_NULL;
	head.dataLen = USER_NAME_LEN;

	nRet = SendHead(g_connectSocket, &head);
	if (nRet == SUCCESS)
	{
		nRet = SendData(g_connectSocket, pUserName, USER_NAME_LEN);
	}

	return nRet;
}

int SetUserLevel(char *pUserName, int userLevel)
{
	int nRet = SUCCESS;
	DataHead head;
	UserData userData;
	head.sign = DEFAULT_SIGN;
	head.cmd = CMD_SET_USER_LEVEL;
	head.response = RES_NULL;
	head.dataLen = USER_NAME_LEN;

	nRet = SendHead(g_connectSocket, &head);
	if (nRet == SUCCESS)
	{
		userData.userLevel = userLevel;
		strcpy_s(userData.userName, USER_NAME_LEN, pUserName);
		strcpy_s(userData.userPwd, USER_PWD_LEN, "");

		nRet = SendData(g_connectSocket, (char*)&userData, sizeof(UserData));
	}

	return nRet;
}

