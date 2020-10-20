#ifndef __LIB_NET_H__
#define __LIB_NET_H__

#include <pthread.h>
#include "lib_list.h"

typedef struct {
	int fd;
	char addr[32];
	unsigned short port;
	unsigned char flag_valid;
}LIB_NET_CONNECT_T;

typedef struct {
	int fd;
	unsigned short port;
	LIST_T *connect;
	unsigned char flag_valid;
	unsigned short connect_num;
	unsigned short connect_max;
	void (*Net_Server_Data_Handle)(LIB_NET_CONNECT_T *conn, char *data, unsigned short datalen);
}LIB_NET_SERVER_T;


/*******************************************************************************************************************
**	函数名:Net_Data_Send
**	描	述:数据发送
**	参	数:[in]fd:链路描述符
**		   [in]data:数据
**		   [in]datalen:数据长度
**	返回值:无
********************************************************************************************************************/
unsigned short Net_Data_Send(int fd, char *data, unsigned short datalen);

/*******************************************************************************************************************
**	函数名:Net_Creat_Server
**	描	述:查询字符串中关键词个数
**	参	数:[in/out]server_list:服务器链表
**		   [in]port:监听端口
**		   [in]connect_max:最大连接数量
**	返回值:1-成功/0-已有同端口服务器/-1-失败
********************************************************************************************************************/
signed char Net_Creat_Server(LIB_NET_SERVER_T *server);

/*******************************************************************************************************************
**	函数名:Net_Delect_Server
**	描	述:关闭服务器，并关闭相关链接
**	参	数:[in/out]server_list:服务器链表
**		   [in]port:监听端口
**		   [in]connect_max:最大连接数量
**	返回值:1-成功/0-已有同端口服务器/-1-失败
********************************************************************************************************************/
void Net_Delect_Server(LIB_NET_SERVER_T *server);


#endif
