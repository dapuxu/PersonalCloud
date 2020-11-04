#include <iostream>
#include "lib_net.h"
#include "lib_debug.h"
#include "lib_string.h"
#include "server.h"
#include "config_manage.h"
#include "share_mem.h"

using namespace std;
ShareMen shm;
static char app_version[] = "V1.1.1beta1";

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


void Server_Listen_Data_Handle(LIB_NET_CONNECT_T *conn, char *data, unsigned short datalen)
{
	unsigned short total = 0, bytelen;

	if (NULL == conn)
		return;

	
	DBG_PRINT(1, "The client(fd:%d, IP:%s, Port:%d) recv data(%d):", conn->fd, conn->addr, conn->port, datalen);
	Display_Hex(data, (int)datalen);
	while (total < datalen) {
		DBG_PRINT(DBG_MODULE_TEST,"put data to share memory\n");
		bytelen = shm.Shm_Put(0, conn->fd, data + total, datalen-total);
		if (bytelen <= 0)
			break;
		total += bytelen;
	}
}

int main(int argc, char *argv[])
{
	Server ser;
	DEBUG_INFO debug;
	Conf conf;
	int port = 0, conn_max = 0;
	int shm_key, num = 0;
	unsigned short shm_block_size;
	unsigned char shm_block_num, shm_in_addr, shm_out_addr, shm_in_size, shm_out_size;
	SHM_DATA_T *shm_block;
	int dest, src, ret;
	char buf[1024];
	unsigned int buflen = 1024;
	LIST_T *node = NULL;
	
	debug.InterfaceType = 1 << INTERFACE_TYPE_CONSOLE;
	Debug_Init(&debug);

	DBG_PRINT(DBG_MODULE_COMMON, "Server Version:%s\n", (char *)app_version);
	DBG_PRINT(DBG_MODULE_COMMON, "Lib Version:%s\n", String_Lib_Version());

	shm_key = Conf_Get_Share_Mem_Key();
	shm_block_size = sizeof(SHM_DATA_T) + Conf_Get_Share_Mem_Data_Size();
	shm_block_num = Conf_Get_Share_Mem_Block_Num();
	Conf_Get_Share_Mem_Block_Info(0, &shm_in_addr, &shm_in_size, &shm_out_addr, &shm_out_size);

	shm.Share_Mem_Mount(shm_key, shm_block_size * shm_block_num, shm_block_size, 1, shm_in_addr, shm_in_size, shm_out_addr, shm_out_size);
	node = shm.Shm_In_List;
	DBG_PRINT(DBG_MODULE_TEST,"Server share memory info\n");
	do {
		if (NULL != node->data && DATA_TYPE_MASK_NET_SHAREMEM == node->data_mask) {
			shm_block = (SHM_DATA_T *)node->data;
			DBG_PRINT(DBG_MODULE_TEST,"In block[%d]:%p, %p\n", num++, shm_block, shm_block->data);
		}
		node = node->next;
	} while(shm.Shm_In_List != node);

	node = shm.Shm_Out_List;
	num = 0;
	do {
		if (NULL != node->data && DATA_TYPE_MASK_NET_SHAREMEM == node->data_mask) {
			shm_block = (SHM_DATA_T *)node->data;
			DBG_PRINT(DBG_MODULE_TEST,"Out block[%d]:%p, %p\n", num++, shm_block, shm_block->data);
		}
		node = node->next;
	} while(shm.Shm_Out_List != node);

	port = Conf_Get_Server_Port(SERVER_TYPE_LISTNE);
	conn_max = Conf_Get_Server_ConnMax(SERVER_TYPE_LISTNE);
	ser.Creat_Server(port, conn_max, Server_Listen_Data_Handle);
	DBG_PRINT(DBG_MODULE_COMMON, "Creat tcp server, port:%d, max_connect:%d\n", port, conn_max);

	while (1) {
		DBG_PRINT(DBG_MODULE_SHARTMEM, "Out list:%s, data:%s\n", shm.Shm_Out_List?"exist":"null", shm.Shm_Out_List->data?"exist":"null");
		if (NULL != shm.Shm_Out_List && NULL != shm.Shm_Out_List->data) {
			shm_block = (SHM_DATA_T *)shm.Shm_Out_List->data;
			while (!shm_block->flag_r) {
				usleep(1000 * 100);
			}
			ret = shm.Shm_Get(&dest, &src, (void *)buf, buflen);
			if (ret > 0)
				Net_Data_Send(dest, buf, ret);
		}
		usleep(1000 * 1000);
	}

	return 1;
}
