#include <WinSock2.h>
// 产品码
#define DEFAULT_SIGN 5720

// 应答码 
#define RES_FAULT   -1  // 失败
#define RES_NULL    00  // 无
#define RES_SUCCESS 01  // 成功

// 命令码
#define CMD_NULL                    00	// 无
#define CMD_REGIEST                 10  // 注册
#define CMD_LOGIN                   11  // 登录
#define CMD_LOGOUT		            12  // 登出
#define CMD_PRIVATECHAT             20  // 私聊
#define CMD_GROUPCHAT               21  // 群聊
#define CMD_GET_USER_NAME           30  // 获取所有用户
#define CMD_GET_USER_NAME_ONLINE    31  // 获取所以在线用户
#define CMD_SEND_USER_NAME          32  // 发送用户名
#define CMD_SEND_USER_NAME_ONLINE   33	// 发送在线用户名
#define CMD_SET_USER_NAME           40  // 设置用户名
#define CMD_SET_USER_PWD            41  // 设置用户密码
#define CMD_SET_USER_LEVEL          42  // 设置用户权限
#define CMD_SET_USER_OFFLINE        43  // 强制用户下线

// 应用内部错误码
#define SUCCESS 00
#define ERROR_MALLOC 01
#define ERROR_RECV 02
#define ERROR_SEND 03
#define ERROR_ACCEPT 04
#define ERROR_OTHER 100


#define USER_NAME_LEN 20
#define USER_PWD_LEN  20

// 用户权限
#define LEVEL_USER			00
#define LEVEL_AMMIN			01
#define LEVEL_SUPER_ADMIN   02

typedef struct _DataHead
{
	int sign;		// 产品标志
	int response;   // 应答码
	int cmd;		// 命令码
	int dataLen;	// 数据长度
}DataHead;

typedef struct _PrivateChat
{
	int fromUserLen;
	int toUserLen;
	int massagLen;
	char *pFromUser;
	char *pToUser;
	char *pMassage;
}PrivateChat;

typedef struct _GroupChat
{
	int fromUserLen;
	int massageLen;
	char *pFromUser;
	char *pMassage;
}GroupChat;

// 通信模块(公用)
int RecvDataHead(SOCKET connSocket, DataHead *pDataHead);
int SendDataHead(SOCKET connSocket, DataHead *pDataHead);
int RecvMassage(SOCKET connSocket, char *buf, int bufLen);



