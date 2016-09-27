#include "ServerNotice.h"
#include "stdio.h"

int SendOnlineUserList(PUserOnlineNode pCurrUser)
{
	int nRet = SUCCESS;
	DataHead head;
	PUserData pUserData;
	PUserOnlineNode pOnlineNode = g_pUserOnlineBegin;
	head.sign = DEFAULT_SIGN;
	head.cmd = CMD_SEND_ONLINE_USER;
	head.response = RES_NULL;
	head.dataLen = sizeof(UserData);
	pUserData = (PUserData)malloc(sizeof(UserData));
	if (pUserData == NULL)
	{
		printf("Malloc Falied!\n");
		return ERROR_MALLOC;
	}

	while (pOnlineNode)
	{
		nRet = SendHead(pCurrUser->userSocket, &head);
		if (nRet == SUCCESS)
		{
			pUserData->userLevel = pOnlineNode->userData->userLevel;
			strcpy_s(pUserData->userName, USER_NAME_LEN, pOnlineNode->userData->userName);
			strcpy_s(pUserData->userPwd, USER_PWD_LEN, "");
			nRet = SendData(pCurrUser->userSocket, (char*)pUserData, sizeof(UserData));
		}
		pOnlineNode = pOnlineNode->pNext;
	}
	printf("%s 获取在线用户列表", pCurrUser->userData->userName);
	free(pUserData);
	pUserData = NULL;
	return nRet;
}

int SendAllUserList(PUserOnlineNode pCurrUser)
{
	int nRet = SUCCESS;
	DataHead head;
	PUserData pUserData;
	PUserDataNode pUserDataNode = g_pUserDataBegin;
	head.sign = DEFAULT_SIGN;
	head.cmd = CMD_SEND_USER;
	head.response = RES_NULL;
	head.dataLen = sizeof(UserData);
	pUserData = (PUserData)malloc(sizeof(UserData));
	if (pUserData == NULL)
	{
		printf("Malloc Falied!\n");
		return ERROR_MALLOC;
	}

	while (pUserDataNode)
	{
		nRet = SendHead(pCurrUser->userSocket, &head);
		if (nRet == SUCCESS)
		{
			pUserData->userLevel = pUserDataNode->userData->userLevel;
			strcpy_s(pUserData->userName, USER_NAME_LEN, pUserDataNode->userData->userName);
			strcpy_s(pUserData->userPwd, USER_PWD_LEN, "");
			nRet = SendData(pCurrUser->userSocket, (char*)pUserData, sizeof(UserData));
		}
		pUserDataNode = pUserDataNode->pNext;
	}

	printf("%s 获取全部用户列表", pCurrUser->userData->userName);
	free(pUserData);
	pUserData = NULL;
	return nRet;
}

int SendCurrentUser(PUserOnlineNode pCurrUser)
{
	int nRet = SUCCESS;
	DataHead head;
	PUserData pUserData;
	head.sign = DEFAULT_SIGN;
	head.cmd = CMD_SEND_CURRENT_USER;
	head.response = RES_NULL;
	head.dataLen = sizeof(UserData);
	pUserData = (PUserData)malloc(sizeof(UserData));
	if (pUserData == NULL)
	{
		printf("Malloc Falied!\n");
		return ERROR_MALLOC;
	}

	nRet = SendHead(pCurrUser->userSocket, &head);
	if (nRet == SUCCESS)
	{
		pUserData->userLevel = pCurrUser->userData->userLevel;
		strcpy_s(pUserData->userName, USER_NAME_LEN, pCurrUser->userData->userName);
		strcpy_s(pUserData->userPwd, USER_PWD_LEN, pCurrUser->userData->userPwd);
		nRet = SendData(pCurrUser->userSocket, (char *)pCurrUser->userData, sizeof(UserData));
	}
	return nRet;
}