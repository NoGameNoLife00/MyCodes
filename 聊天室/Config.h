#include "BaseData.h"

#define CONFIG_FILE "config.txt"
#define DEFAULT_BUFLEN 512
#define FILE_BUFLEN    100
#define INPUT_BUFLEN   1024
#define KEY            23

typedef struct _UserDataNode
{
	char userName[USER_NAME_LEN];
	char userPwd[USER_PWD_LEN];
	int  userLevel;				 // 用户权限
	_UserDataNode *pNext;
}UserDataNode, *PUserDataNode;

typedef struct _UserOnlineNode
{
	PUserDataNode userData;
	SOCKET userSocket;
	_UserOnlineNode *pPrior;
	_UserOnlineNode *pNext;
}UerOnlienNode, *PUserOnlineNode;

extern PUserDataNode g_pUserDataBegin;
extern PUserDataNode g_pUserDataEnd;

extern PUserOnlineNode g_pUserOnlineBegin;
extern PUserOnlineNode g_pUserOnlineEnd;

// 配置模块
int InitConfig();

int SaveConfig();

int CloseConfig();

void Encrpty(char *pSource, char *pDestination);

void Decrypt(char *pSource, char *pDestination);
