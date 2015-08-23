#include "BaseData.h"
#include "Winsock2.h"
#include "stdio.h"

int RecvHead(SOCKET connSocket, DataHead *pDataHead)
{
	int nRet = SUCCESS;
	if (recv(connSocket, (char *)pDataHead, sizeof(DataHead), 0) < 0)
	{
		printf("recv failed:%d \n", GetLastError());
		nRet = ERROR_RECV;
	}
	return nRet;
}

int SendHead(SOCKET connSocket, DataHead *pDataHead)
{
	int nRet = SUCCESS;
	if (send(connSocket, (char*)pDataHead, sizeof(DataHead), 0) < 0)
	{
		printf("send failed:%d \n", GetLastError());
		nRet = ERROR_SEND;
	}
	return nRet;
}

int RecvData(SOCKET connSocket, char *buf, int bufLen)
{
	int nRet = SUCCESS;
	if (recv(connSocket, buf, bufLen, 0) < 0)
	{
		printf("recv failed!\n");
		nRet = ERROR_RECV;
	}
	return nRet;
}
