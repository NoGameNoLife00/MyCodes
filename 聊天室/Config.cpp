#include "Config.h"
#include "io.h"
#include "stdio.h"

void GetUserAttr(char *pBuf, char *pName, char *pPwd, int *pLevel)
{
	char strNum[10];
	bool isSpace = true;
	int i, j;
	// 读取用户名
	for (i = 0, j = 0; pBuf[i] != '>'; i++)
	{
		if (isSpace && iscntrl(pBuf[i]))
		{
			continue;
		}
		else if (pBuf[i] == '<')
		{
			isSpace = false;
			continue;
		}
		pName[j++] = pBuf[i];
	}
	pName[j] = '\0';

	// 读取密码
	isSpace = true;
	for (i = i + 1, j = 0; pBuf[i] != '>'; i++)
	{
		if (isspace(pBuf[i]) && isSpace)
		{
			continue;
		}
		else if (pBuf[i] == '<')
		{
			isSpace = false;
			continue;
		}
		pPwd[j++] = pBuf[i];
	}
	pPwd[j] = '\0';

	// 读取用户级别
	for (i = i + 1, j = 0; pBuf[i] != '\0'; i++)
	{
		if (isdigit(pBuf[i]))
		{
			strNum[j++] = pBuf[i];
		}
	}
	strNum[j] = '\0';

	*pLevel = atoi(strNum);
}

int ReadConfig()
{
	int nRet = SUCCESS;
	FILE *file;
	PUserDataNode pNode;
	PUserData pUserData;
	char buf[FILE_BUFLEN];
	char nameBuf[USER_PWD_LEN];
	char ciphertext[USER_PWD_LEN];  // 密文
	char plaintext[USER_PWD_LEN];	// 明文
	int level = -1;
	if ((file = fopen(CONFIG_FILE, "r")) == NULL)
	{
		printf("fopen failed!");
		return ERROR_OTHER;
	}
	g_pUserDataBegin = (PUserDataNode)malloc(sizeof(UserDataNode));
	pUserData = (PUserData)malloc(sizeof(UserData));
	if (g_pUserDataBegin == NULL && pUserData == NULL)
	{
		printf("Malloc failed!");
		return ERROR_MALLOC;
	}

	if (fgets(buf, FILE_BUFLEN, file) != NULL)
	{
		GetUserAttr(buf, nameBuf, ciphertext, &level);
		Decrypt(ciphertext, plaintext);  // 密文转换为明文
		g_pUserDataBegin->userData = pUserData;
		strcpy_s(g_pUserDataBegin->userData->userName, USER_NAME_LEN, nameBuf);
		strcpy_s(g_pUserDataBegin->userData->userPwd, USER_PWD_LEN, plaintext);
		g_pUserDataBegin->userData->userLevel = level;
		g_pUserDataBegin->pNext = NULL;
	}

	pNode = g_pUserDataBegin;
	while (fgets(buf, FILE_BUFLEN, file) != NULL)
	{
		pNode->pNext = (PUserDataNode)malloc(sizeof(UserDataNode));
		pUserData = (PUserData)malloc(sizeof(UserData));
		if (pNode->pNext == NULL && pUserData == NULL)
		{
			printf("Malloc failed!");
			nRet = ERROR_OTHER;
			break;
		}
		pNode = pNode->pNext;

		GetUserAttr(buf, nameBuf, ciphertext, &level);
		Decrypt(ciphertext, plaintext);
		pNode->userData = pUserData;
		strcpy_s(pNode->userData->userName, USER_NAME_LEN, nameBuf);
		strcpy_s(pNode->userData->userPwd, USER_PWD_LEN, plaintext);
		pNode->userData->userLevel = level;
		pNode->pNext = NULL;
	}
	g_pUserDataEnd = pNode;

	fclose(file);
	return nRet;
}

int InitConfig()
{
	int nRet = SUCCESS;
	PUserData pUserData;
	if (_access(CONFIG_FILE, 0) != -1) // 配置文件存在
	{
		nRet = ReadConfig();
	}
	else                             //配置文件不存在
	{
		// 生成超级管理员并保存
		g_pUserDataBegin = (PUserDataNode)malloc(sizeof(UserDataNode));
		pUserData = (PUserData)malloc(sizeof(UserData));
		if (g_pUserDataBegin == NULL || pUserData == NULL)
		{
			printf("Malloc failed!");
			nRet = ERROR_MALLOC;
		}
		else
		{
			g_pUserDataBegin->userData = pUserData;
			strcpy_s(g_pUserDataBegin->userData->userName, USER_NAME_LEN, "SuperAdmin");
			strcpy_s(g_pUserDataBegin->userData->userPwd, USER_PWD_LEN, "123456");
			g_pUserDataBegin->userData->userLevel = LEVEL_SUPER_ADMIN;
			g_pUserDataBegin->pNext = NULL;
			nRet = SaveConfig();
		}
	}
	return nRet;
}

int SaveConfig()
{
	int nRet = SUCCESS;
	char buf[FILE_BUFLEN];
	char ciphertext[FILE_BUFLEN];
	FILE *file;
	PUserDataNode pNode = g_pUserDataBegin;
	if ((file = fopen(CONFIG_FILE, "w")) == NULL)
	{
		return ERROR_OTHER;
	}

	while (pNode)
	{
		Encrpty(pNode->userData->userPwd, ciphertext);//加密
		sprintf_s(buf, FILE_BUFLEN, "<%s> <%s> <%d>\n", pNode->userData->userName,
			ciphertext, pNode->userData->userLevel);
		fwrite(buf, sizeof(char), strlen(buf), file);
		pNode = pNode->pNext;
	}
	fclose(file);
	return nRet;
}

int CloseConfig()
{
	int nRet = SUCCESS;
	PUserDataNode temp;
	nRet = SaveConfig();
	while (g_pUserDataBegin)
	{
		temp = g_pUserDataBegin;
		g_pUserDataBegin = g_pUserDataBegin->pNext;
		free(temp->userData);
		free(temp);
		temp = NULL;
	}
	g_pUserDataBegin = NULL;
	g_pUserDataEnd = NULL;
	return nRet;
}

void Encrpty(char *pSource, char *pDestination)
{
	int i;
	for (i = 0; pSource[i] != '\0'; i++)
	{
		pDestination[i] = pSource[i] ^ KEY;
	}
	pDestination[i] = '\0';
}

void Decrypt(char *pSource, char *pDestination)
{
	int i;
	for (i = 0; pSource[i] != '\0'; i++)
	{
		pDestination[i] = pSource[i] ^ KEY;
	}
	pDestination[i] = '\0';
}

