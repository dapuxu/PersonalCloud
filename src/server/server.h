#ifndef _SERVER_H__
#define _SERVER_H__
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

#endif