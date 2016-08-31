#include "ClientMassage.h"
#include "stdio.h"

int SendGroupMassage(char *pMassage)
{
	int nRet = SUCCESS;
	DataHead dataHead;
	int msgLen = strlen(pMassage) + 1;
	int bufLen = sizeof(GroupChat) + USER_NAME_LEN + msgLen;
	char *buf = (char *)malloc(bufLen);
	if (buf == NULL)
	{
		printf("Malloc failed!\n");
		return ERROR_MALLOC;
	}

	GroupChat *gChat = (GroupChat *)buf;
	gChat->pFromUser = buf + sizeof(GroupChat);
	gChat->pMassage = buf + sizeof(GroupChat) + USER_NAME_LEN;

	dataHead.sign = DEFAULT_SIGN;
	dataHead.response = RES_NULL;
	dataHead.cmd = CMD_GROUPCHAT;
	dataHead.dataLen = bufLen;

	gChat->fromUserLen = USER_NAME_LEN;
	gChat->massageLen = msgLen;
	memcpy(gChat->pFromUser, g_myUser.userName, USER_NAME_LEN);
	memcpy(gChat->pMassage, pMassage, msgLen);


	nRet = SendHead(g_connectSocket, &dataHead);
	if (nRet == SUCCESS)
	{
		nRet = SendData(g_connectSocket, buf, bufLen);
	}

	free(buf);
	buf = NULL;
	return nRet;
}

int SendPrivateMassage(char *pToUser, char *pMassage)
{
	int nRet = SUCCESS;
	DataHead dataHead;
	int msgLen = strlen(pMassage) + 1;
	int bufLen = USER_NAME_LEN * 2+ msgLen + sizeof(PrivateChat);
	char *buf = (char *)malloc(bufLen);
	PrivateChat *pPChat = (PrivateChat*)buf;
	pPChat->pFromUser = buf + sizeof(PrivateChat);
	pPChat->pToUser = buf + sizeof(PrivateChat) + USER_NAME_LEN;
	pPChat->pMassage = buf + sizeof(PrivateChat) + USER_NAME_LEN * 2;

	pPChat->fromUserLen = USER_NAME_LEN;
	pPChat->toUserLen = USER_NAME_LEN;
	pPChat->massagLen = msgLen;
	memcpy(pPChat->pFromUser, g_myUser.userName, USER_NAME_LEN);
	memcpy(pPChat->pToUser, pToUser, USER_NAME_LEN);
	memcpy(pPChat->pMassage, pMassage, msgLen);

	dataHead.sign = DEFAULT_SIGN;
	dataHead.cmd = CMD_PRIVATECHAT;
	dataHead.dataLen = bufLen;

	nRet = SendHead(g_connectSocket, &dataHead);
	if (nRet == SUCCESS)
	{
		nRet = SendData(g_connectSocket, buf, bufLen);
	}

	free(buf);
	buf = NULL;
	return nRet;
}

void PrintGroupMassage(char *recvbuf)
{
	GroupChat *pGroupChat;
	char *pFromName;
	char *pMassage;
	pGroupChat = (GroupChat *)recvbuf;
	pFromName = recvbuf + sizeof(GroupChat);
	pMassage = recvbuf + sizeof(GroupChat) + pGroupChat->fromUserLen;
	printf("%s: %s\n", pFromName, pMassage);
}

void PrintPrivateMassage(char *recvbuf)
{
	PrivateChat *pPrivChat;
	char *pFromName;
	char *pMassage;

	pPrivChat = (PrivateChat *)recvbuf;
	pFromName = recvbuf + sizeof(PrivateChat);
	pMassage = recvbuf + sizeof(PrivateChat) + pPrivChat->fromUserLen + pPrivChat->toUserLen;
	printf("%s（私）: %s\n", pFromName, pMassage);
}

