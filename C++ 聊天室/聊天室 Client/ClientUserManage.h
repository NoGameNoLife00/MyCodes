#include "BaseData.h"

extern SOCKET g_connectSocket;

bool CheckNameAndPwd(char *pUserName, char *pPassword);

int Register(char *pUserName, char *pPassword);

int Login(char *pUserName, char *pUserPwd);

int Logout();

int SetUserName(char *pNewUserName);

int SetUserPwd(char *pNewUserPwd);
