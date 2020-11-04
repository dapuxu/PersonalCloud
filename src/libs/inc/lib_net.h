#ifndef __LIB_NET_H__
#define __LIB_NET_H__
#include <pthread.h>
#include "lib_list.h"

#ifdef __cplusplus
extern "C"
{
#endif


typedef struct {
	int fd;
	int epoll_fd;
	char addr[32];
	unsigned short port;
	unsigned char flag_valid;
}LIB_NET_CONNECT_T;

typedef struct {
	int epoll_fd;
	unsigned short listen_num;
}LIB_NET_EPOLL_T;

typedef struct {
	int fd;
	int epoll_fd;
	unsigned short port;
	LIST_T *connect;									/* 接入信息链表 */
	LIST_T *recv_poll;									/* epoll数据接收描述符链表 */
	LIST_T *recv_thread;								/* 接收线程链表*/
	unsigned char flag_valid;
	unsigned short connect_num;
	unsigned short connect_max;							/* 最大服务器连接数 */
	unsigned short poll_num;
	unsigned short poll_max;							/* 最大epoll监听线程数 */
	pthread_mutex_t conn_lock;							/* 链路锁 */
	pthread_mutex_t recv_lock;							/* epoll锁 */
	pthread_cond_t cond1;
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
**	参	数:[in/out]net:服务器信息
**	返回值:1-成功/0-已有同端口服务器/-1-失败
********************************************************************************************************************/
signed char Net_Creat_Server(LIB_NET_SERVER_T *net);

/*******************************************************************************************************************
**	函数名:Net_Delect_Server
**	描	述:关闭服务器，并关闭相关链接
**	参	数:[in/out]server_list:服务器链表
**		   [in]port:监听端口
**		   [in]connect_max:最大连接数量
**	返回值:1-成功/0-已有同端口服务器/-1-失败
********************************************************************************************************************/
void Net_Delect_Server(LIB_NET_SERVER_T *server);

#ifdef __cplusplus
}
#endif

#endif
