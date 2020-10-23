#include "server.h"
#include <iostream>
#include "lib_debug.h"


using namespace std;

Server::Server()
{
	net.port = 0;
	net.connect_max = 0;
	net.connect_num = 0;
	net.fd = -1;
	net.flag_valid = 0;
	net.connect = NULL;
	net.Net_Server_Data_Handle = NULL;
}

Server::~Server()
{
	if (net.flag_valid == 1)
		Server_Close();
}

/*******************************************************************************************************************
**	函数名:Thread_Net_Server
**	描	述:服务器线程
**	参	数:[in]server:服务器参数
**	返回值:无
********************************************************************************************************************/
static void *Thread_Net_Server(void* server)
{

	if (NULL == server)
		return NULL;

	Net_Creat_Server((LIB_NET_SERVER_T *)server);
	DBG_PRINT(1, "Exit server\n");
	return NULL;
}

/*******************************************************************************************************************
**	函数名:Creat_Server
**	描	述:创建服务器
**	参	数:[in]port:端口号
**         [in]conn_max:最大连接数
**         [in]Server_Data_Handle:数据处理回调
**	返回值:无
********************************************************************************************************************/
int Server::Creat_Server(unsigned short port, unsigned short conn_max, void (*Server_Data_Handle)(LIB_NET_CONNECT_T *, char *, unsigned short))
{
	pthread_t DemoThreadServer;

	net.port = port;
	net.connect_max = conn_max;
	net.Net_Server_Data_Handle = Server_Data_Handle;

	if (pthread_create(&DemoThreadServer, NULL, Thread_Net_Server, (void *)(&net)) != 0) {
        DBG_PRINT(1, "pthread_create Demo_Net_Server_Thread failed.\n");
		return 0;
    }
	return 1;
}

/*******************************************************************************************************************
**	函数名:Server_Close
**	描	述:关闭服务器
**	参	数:无
**	返回值:无
********************************************************************************************************************/
int Server::Server_Close(void)
{
	Net_Delect_Server(&net);
	return 1;
}