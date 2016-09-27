#include "ServerAdminManage.h"
#include "ServerUserManage.h"
#include "ServerNotice.h"

int SetUserOffLine(PUserOnlineNode pCurrUser)
{
	int nRet = SUCCESS;
	char userName[USER_NAME_LEN];
	bool isLogin = true;
	PUserOnlineNode pOnlineNode = g_pUserOnlineBegin;
	DataHead head;
	head.sign = DEFAULT_SIGN;
	head.cmd = CMD_SET_USER_OFFLINE;
	head.response = RES_FAULT;
	head.dataLen = 0;

	nRet = RecvData(pCurrUser->userSocket, userName, USER_NAME_LEN);
	if (nRet == SUCCESS && pCurrUser->userData->userLevel >= LEVEL_AMMIN)
	{
		while (pOnlineNode)
		{
			if (strcmp(userName, pOnlineNode->userData->userName) == 0)
			{
				Logout(&pOnlineNode->userSocket, pOnlineNode, &isLogin);
				head.response = RES_SUCCESS;
				break;
			}
			pOnlineNode = pOnlineNode->pNext;
		}
	}

	nRet = SendHead(pCurrUser->userSocket, &head);
	return nRet;
}

int SetUserLevel(PUserOnlineNode pCurrUser)
{
	int nRet = SUCCESS;
	PUserDataNode pUserNode = g_pUserDataBegin;
	UserData userData;
	DataHead resHead;
	resHead.sign = DEFAULT_SIGN;
	resHead.cmd = CMD_SET_USER_LEVEL;
	resHead.response = RES_FAULT;
	resHead.dataLen = 0;

	nRet = RecvData(pCurrUser->userSocket, (char*)&userData, sizeof(UserData));
	if (nRet == SUCCESS && pCurrUser->userData->userLevel == LEVEL_SUPER_ADMIN)
	{
		while (pUserNode)
		{
			if (strcmp(userData.userName, pUserNode->userData->userName) == 0)
			{
				pUserNode->userData->userLevel = userData.userLevel;
				resHead.response = RES_SUCCESS;
				SaveConfig();
				break;
			}
			pUserNode = pUserNode->pNext;
		}

	}

	nRet = SendHead(pCurrUser->userSocket, &resHead);
	return nRet;
}

