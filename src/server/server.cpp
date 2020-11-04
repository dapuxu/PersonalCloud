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
**	函数名:Creat_Server
**	描	述:创建服务器
**	参	数:[in]port:端口号
**         [in]conn_max:最大连接数
**         [in]Server_Data_Handle:数据处理回调
**	返回值:无
********************************************************************************************************************/
int Server::Creat_Server(unsigned short port, unsigned short conn_max, void (*Server_Data_Handle)(LIB_NET_CONNECT_T *, char *, unsigned short))
{
	net.port = port;
	net.connect_max = conn_max;
	net.Net_Server_Data_Handle = Server_Data_Handle;

	Net_Creat_Server(&net);
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