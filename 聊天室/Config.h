#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "BaseData.h"

#define CONFIG_FILE "config.txt"
#define DEFAULT_BUFLEN 512
#define FILE_BUFLEN    100
#define INPUT_BUFLEN   1024
#define KEY            23


typedef struct _UserDataNode
{
	PUserData userData;
	_UserDataNode *pNext;
}UserDataNode, *PUserDataNode;

typedef struct _UserOnlineNode
{
	PUserData userData;
	SOCKET userSocket;
	_UserOnlineNode *pPrior;
	_UserOnlineNode *pNext;
}UserOnlineNode, *PUserOnlineNode;

extern PUserDataNode g_pUserDataBegin;
extern PUserDataNode g_pUserDataEnd;

extern PUserOnlineNode g_pUserOnlineBegin;
extern PUserOnlineNode g_pUserOnlineEnd;

// ≈‰÷√ƒ£øÈ
int InitConfig();

int SaveConfig();

int CloseConfig();

void Encrpty(char *pSource, char *pDestination);

void Decrypt(char *pSource, char *pDestination);

#endif
