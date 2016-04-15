#include "BaseData.h"

extern SOCKET g_connectSocket;
extern UserData g_myUser;

int GetOnlineUserList();

int GetAllUserList();

int RecvUserData();

void PrintOnlineUser(char *buf);

void PrintUser(char *buf);

void SetCurrentUserData(char *buf);

int GetCurrentUserData();