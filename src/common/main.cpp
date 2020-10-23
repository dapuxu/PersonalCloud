#include <iostream>
#include "func_switch.h"
#include "lib_net.h"
#include "lib_debug.h"
#include "server.h"
#include "config_manage.h"

using namespace std;

void Display_Hex(char *data, int datalen)
{
	int i;
	if (NULL == data || 0 >= datalen)
		return;

	for(i=0;i<datalen;i++) {
		printf("0x%02x ", data[i]);
	}
	printf("\n");
}

void Server_Data_Handle(LIB_NET_CONNECT_T *conn, char *data, unsigned short datalen)
{
	int i = 0;

	if (NULL == conn)
		return;

	DBG_PRINT(1, "The client(fd:%d, IP:%s, Port:%d) recv data(%d):", conn->fd, conn->addr, conn->port, datalen);
	for (;i < datalen; i++) {
		printf("0x%02x ", data[i]);
	}
	printf("\n");
	Net_Data_Send(conn->fd, data, datalen);
}

int main(int argc, char *argv[])
{
	Server ser;
	DEBUG_INFO debug;
	Conf conf;
	CONF_PARAM_T param;
	char para1[] = "server";
	char para2[] = "server_listen";
	char para3[] = "port";
	char para4[] = "connect_max";
	char conf_path[] = "sys_config";
 	char buf[12] = {0x0};
	int port = 0, conn_max = 0;

	debug.InterfaceType = 1 << INTERFACE_TYPE_CONSOLE;
	Debug_Init(&debug);

	param.item[0] = para1;
	param.item[1] = para2;
	param.item[2] = para3;
	param.item_num = 3;
	conf.Conf_Init(conf_path);

	conf.Conf_Get_Param(&param, buf, sizeof(buf));
	printf("[%s:%d] port:%s",__FUNCTION__, __LINE__, buf);
	port = atoi(buf);

	param.item[2] = para4;
	param.item_num = 3;
	memset(buf, 0x0, sizeof(buf));
	conf.Conf_Get_Param(&param, buf, sizeof(buf));
	printf("[%s:%d] connect_max:%s\n",__FUNCTION__, __LINE__, buf);
	conn_max = atoi(buf);
	ser.Creat_Server(port, conn_max, Server_Data_Handle);

	while (1) {
		sleep(3);
	}
	return 1;
}
