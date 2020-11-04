#ifndef _SERVER_H__
#define _SERVER_H__
#include "pc_includes.h"
#include "lib_net.h"

class Server
{
	public:
		typedef void (*Server_Data_Handle)(LIB_NET_CONNECT_T *, char *, unsigned short);
		Server();
		~Server();
		int Creat_Server(unsigned short port, unsigned short conn_max, void (*Server_Data_Handle)(LIB_NET_CONNECT_T *, char *, unsigned short));
		int Server_Send_Data(char *data, unsigned int datalen);
		int Server_Close(void);
	private:
		LIB_NET_SERVER_T net;
};

void Server_Listen_Data_Handle(LIB_NET_CONNECT_T *conn, char *data, unsigned short datalen);
/*******************************************************************************************************************
**	函数名:Conf_Get_Server_Port
**	描	述:获取配置文件服务器监听端口
**	参	数:[in]server_type:服务器类型
**	返回值:端口号
********************************************************************************************************************/
int Conf_Get_Server_Port(unsigned char server_type);

/*******************************************************************************************************************
**	函数名:Conf_Get_Server_ConnMax
**	描	述:获取配置文件服务器最大接入个数
**	参	数:[in]server_type:服务器类型
**	返回值:端口号
********************************************************************************************************************/
int Conf_Get_Server_ConnMax(unsigned char server_type);
#endif