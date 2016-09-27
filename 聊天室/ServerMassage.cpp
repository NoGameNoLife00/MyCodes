#include "ServerMassage.h"
#include "stdio.h"


int GroupMassage(PUserOnlineNode pCurrUser, DataHead *head)
{
	int nRet = SUCCESS;
	PUserOnlineNode pOnlineNode = g_pUserOnlineBegin;
	char *buf = (char *)malloc(head->dataLen);
	if (buf ==  NULL)
	{
		printf("Malloc Failed!\n");
		return ERROR_MALLOC;
	}

	nRet = RecvData(pCurrUser->userSocket, buf, head->dataLen);
	if (nRet == SUCCESS)
	{
		while (pOnlineNode)
		{
			nRet = SendHead(pOnlineNode->userSocket, head);
			if (nRet == SUCCESS)
			{
				nRet = SendData(pOnlineNode->userSocket, buf, head->dataLen);
			}
			pOnlineNode = pOnlineNode->pNext;
		}
	}
	printf("%s 发送了群消息！\n", pCurrUser->userData->userName);
	return nRet;

}

int PrivateMassage(PUserOnlineNode pCurrUser, DataHead *head)
{
	int nRet = SUCCESS;
	DataHead resHead;
	PrivateChat *pChat;
	PUserOnlineNode pOnlineNode = g_pUserOnlineBegin;
	char *buf = (char *)malloc(head->dataLen);
	char *toUser;

	if (buf == NULL)
	{
		printf("Malloc Failed!\n");
		return ERROR_MALLOC;
	}

	resHead.sign = DEFAULT_SIGN;
	resHead.cmd = CMD_PRIVATECHAT;
	resHead.dataLen = 0;

	nRet = RecvData(pCurrUser->userSocket, buf, head->dataLen);
	pChat = (PrivateChat *)buf;
	toUser = buf + sizeof(PrivateChat) + pChat->fromUserLen;

	while (pOnlineNode)
	{
		if (strcmp(toUser, pOnlineNode->userData->userName) == 0)
		{
			nRet = SendHead(pOnlineNode->userSocket, head);
			if (nRet != SUCCESS)
			{
				break;
			}
			// 发送消息
			nRet = SendData(pOnlineNode->userSocket, buf, head->dataLen);
			printf("[%s] 对 [%s] 发送了消息\n", pCurrUser->userData->userName, toUser);
			resHead.response = RES_SUCCESS;
			break;
		}
		pOnlineNode = pOnlineNode->pNext;
	}

	if (nRet != SUCCESS)
	{
		printf("[%s] 发生私聊信息失败！\n", pCurrUser->userData->userName);
		resHead.response = RES_FAULT;
	}

	nRet = SendHead(pCurrUser->userSocket, &resHead);
	return nRet;
}
