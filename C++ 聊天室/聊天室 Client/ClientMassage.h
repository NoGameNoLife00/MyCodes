#include "BaseData.h"

extern UserData g_myUser;
extern SOCKET g_connectSocket;

int SendGroupMassage(char *pMassage);

int SendPrivateMassage(char *pToUser, char *pMassage);

void PrintGroupMassage(char *buf);

void PrintPrivateMassage(char *recvbuf);