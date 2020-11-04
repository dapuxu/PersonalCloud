#include <iostream>
#include "lib_debug.h"
#include "lib_string.h"
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

static int Data_Handle(int src, char *data, unsigned short datalen)
{
	DBG_PRINT(DBG_MODULE_COMMON, "The cloud-service get data of server, port:%d, datalen:%d\n", src, datalen);
	Display_Hex(data, datalen);
	shm.Shm_Put(src, 0, (void *)data, datalen);
	return 1;
}

int main(int argc, char *argv[])
{
	DEBUG_INFO debug;
	Conf conf;
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
	Conf_Get_Share_Mem_Block_Info(1, &shm_in_addr, &shm_in_size, &shm_out_addr, &shm_out_size);
	
	shm.Share_Mem_Mount(shm_key, shm_block_size * shm_block_num, shm_block_size, 1, shm_in_addr, shm_in_size, shm_out_addr, shm_out_size);
	node = shm.Shm_In_List;
	DBG_PRINT(DBG_MODULE_TEST,"Service share memory info\n");
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

	while (1) {
		DBG_PRINT(DBG_MODULE_SHARTMEM, "In list:%s, data:%s\n", shm.Shm_In_List?"exist":"null", shm.Shm_In_List->data?"exist":"null");
		if (NULL != shm.Shm_In_List && NULL != shm.Shm_In_List->data) {
			shm_block = (SHM_DATA_T *)shm.Shm_In_List->data;
			DBG_PRINT(DBG_MODULE_SHARTMEM, "wait data from %p\n", shm_block->data);
			while (!shm_block->flag_r) {
				usleep(1000 * 100);
			}
			ret = shm.Shm_Get(&dest, &src, (void *)buf, buflen);
			if (ret > 0)
				Data_Handle(src, buf, ret);
		}
		usleep(1000 * 1000);
	}

	return 1;
}
