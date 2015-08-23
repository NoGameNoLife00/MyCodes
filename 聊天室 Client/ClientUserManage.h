#include "BaseData.h"

bool CheckNameAndPwd(char *pUserName, char *pPassword);
int Register(char *pUserName, char *pPassword);
int Login(char *pUserName, char *pPassword);
int Logout();
int SetUserName(char *pNewUserName);
int SetUserPwd(char *pNewUserPwd);
