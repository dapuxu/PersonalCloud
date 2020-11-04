#include "share_mem.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

ShareMen::ShareMen()
{

}

ShareMen::~ShareMen()
{
	if (NULL != Shm_In_List) {
		List_Del_List(&Shm_In_List);
	}

	if (NULL != Shm_Out_List) {
		List_Del_List(&Shm_Out_List);
	}

	if (1 == Flag_Master) {
		if(shmdt(Shm_Addr) == -1) {
	        DBG_PRINT(DBG_MODULE_ERROR, "shmdt failed\n");
	        exit(EXIT_FAILURE);
	    }

	    if(shmctl(ShmID, IPC_RMID, 0) == -1) {
	        DBG_PRINT(DBG_MODULE_ERROR,  "shmctl(IPC_RMID) failed\n");
	        exit(EXIT_FAILURE);
	    }
	}
}

signed char ShareMen::Share_Mem_Mount(int key, unsigned int size, unsigned short block_size, char flag_master, unsigned char in_addr, unsigned short in_size, unsigned char out_addr, unsigned short out_size)
{
	//共享内存标识符 //创建共享内存
	unsigned short i, lenght = 0;
	SHM_DATA_T *shm_block = NULL;
	char *start_addr = NULL, *end_addr = NULL;
	if (0 >= key || sizeof(SHM_DATA_T) > size || sizeof(SHM_DATA_T) > block_size)
		return 0;

	DBG_PRINT(DBG_MODULE_SHARTMEM, "key:%d, master:%d size:%d, block_size:%d, In(%d, %d), Out(%d, %d)\n", key, flag_master, size, block_size, in_addr, in_size, out_addr, out_size);
	if (1 == flag_master) {
		ShmID = shmget((key_t)key, size, 0666|IPC_CREAT);
		Flag_Master = 1;
	} else {
		ShmID = shmget((key_t)key, size, 0666);
	}
    if(ShmID == -1) {
        DBG_PRINT(DBG_MODULE_ERROR, "shmget failed\n");
        exit(EXIT_FAILURE);
    }

    Shm_Addr = shmat(ShmID, 0, 0);/* 将共享内存连接到当前进程的地址空间 */
    if(Shm_Addr == (void*)-1) {
        DBG_PRINT(DBG_MODULE_ERROR, "shmat failed\n");
        exit(EXIT_FAILURE);
    }  
    DBG_PRINT(DBG_MODULE_SHARTMEM,"\nMemory attached at %X\n", (int)Shm_Addr);  //设置共享内存

	Shm_Info.data_block_size = block_size;
	if (size > in_addr * block_size) {
		start_addr = (char *)Shm_Addr + in_addr * block_size;
		lenght = (size > in_size*block_size)?in_size*block_size:size;
		end_addr = start_addr + lenght;
		DBG_PRINT(DBG_MODULE_SHARTMEM, "lenght:%d, in_size:%d, block_size:%d\n", lenght, in_size, block_size);
		Shm_Info.addr_in_start = (void *)start_addr;
		Shm_Info.addr_in_end = (void *)end_addr;
		for (i=0;i < (end_addr-start_addr)/block_size; i++) {
			shm_block = (SHM_DATA_T *)(start_addr+block_size*i);
			shm_block->flag_w = 1;
			shm_block->data = start_addr+block_size*i + sizeof(Shm_Info);
			shm_block->buflen = block_size - sizeof(Shm_Info);
			memset(shm_block->data, 0x0, shm_block->buflen);
			memcpy(shm_block->data, "The block of %d", sizeof("The block of %d"));
			Shm_In_List = List_Add(&Shm_In_List, (void *)shm_block, block_size, DATA_TYPE_MASK_NET_SHAREMEM, 1);
		}
		DBG_PRINT(DBG_MODULE_SHARTMEM, "Creat share mem, In: addr:%p~%p, %dblock\n", Shm_Info.addr_in_start, Shm_Info.addr_in_end, (end_addr-start_addr)/block_size);
	}

	if (size > out_addr * block_size) {
		start_addr = (char *)Shm_Addr + out_addr * block_size;
		lenght = (size > out_size*block_size)?out_size*block_size:size;
		end_addr = start_addr + lenght;
		DBG_PRINT(DBG_MODULE_SHARTMEM, "lenght:%d, out_size:%d, block_size:%d\n", lenght, out_size, block_size);
		Shm_Info.addr_out_start = (void *)start_addr;
		Shm_Info.addr_out_end = (void *)end_addr;
		for (i=0;i < (end_addr-start_addr)/block_size; i++) {
			shm_block = (SHM_DATA_T *)(start_addr+block_size*i);
			shm_block->flag_w = 1;
			shm_block->data = start_addr+block_size*i + sizeof(Shm_Info);
			shm_block->buflen = block_size - sizeof(Shm_Info);
			DBG_PRINT(DBG_MODULE_TEST,"The block:%s\n", (char *)shm_block->data);
			Shm_Out_List = List_Add(&Shm_Out_List, (void *)shm_block, block_size, DATA_TYPE_MASK_NET_SHAREMEM, 1);
		}
		DBG_PRINT(DBG_MODULE_SHARTMEM, "Creat share mem, Out: addr:%p~%p, %dblock\n", Shm_Info.addr_out_start, Shm_Info.addr_out_end, (end_addr-start_addr)/block_size);
	}
	return 1;
}

short ShareMen::Shm_Put(int dest, int src, void * data, unsigned short datalen)
{
	LIST_T *node;
	SHM_DATA_T *shm_block;
	short size;

	DBG_PRINT(DBG_MODULE_TEST,"put data to share memory\n");
	if (0 >= src || NULL == data || 0 == datalen) {
		DBG_PRINT(DBG_MODULE_ERROR, "dest:%d, src:%d, data:%s, datalen:%d\n", dest, src, data?"exist":"null", (int)datalen);
		return 0;
	}

	node = List_Node_Poll(&Shm_Out_List);

	if (NULL == node || DATA_TYPE_MASK_NET_SHAREMEM != node->data_mask) {
		DBG_PRINT(DBG_MODULE_ERROR, "node:%s, mask:%d\n",node?"exist":"null", node->data_mask);
		return -1;
	}

	shm_block = (SHM_DATA_T *)node->data;
	if (NULL == shm_block) {
		DBG_PRINT(DBG_MODULE_ERROR, "The shm_block is null\n");
		return -2;
	}

	if (NULL == shm_block->data) {
		DBG_PRINT(DBG_MODULE_ERROR, "The data of shm_block is null\n");
		return -2;
	}

	while (!shm_block->flag_w) {
		usleep(1000 * 100);
	}
	shm_block->flag_w = 0;
	shm_block->flag_r = 0;
	size = (datalen < shm_block->buflen)?datalen:shm_block->buflen;
	memcpy(shm_block->data, (char *)data, size);
	shm_block->datalen = size;
	shm_block->dest = dest;
	shm_block->souece = src;
	shm_block->flag_r = 1;
	DBG_PRINT(DBG_MODULE_SHARTMEM, "Put data to %p, size:%d\n", shm_block->data, size);
	return size;
}

short ShareMen::Shm_Get(int *dest, int *src, void * buf, unsigned short buflen)
{
	LIST_T *node;
	SHM_DATA_T *shm_block;
	short size;

	if (NULL == dest || NULL == src || NULL == buf || 0 == buflen) {
		DBG_PRINT(DBG_MODULE_ERROR, "dest:%s, src:%s, data:%s, datalen:%d\n", dest?"exist":"null", src?"exist":"null", buf?"exist":"null", (int)buflen);
		return 0;
	}

	node = List_Node_Poll(&Shm_In_List);

	if (NULL == node || DATA_TYPE_MASK_NET_SHAREMEM != node->data_mask) {
		DBG_PRINT(DBG_MODULE_ERROR, "node:%s, mask:%d\n",node?"exist":"null", node->data_mask);
		return -1;
	}

	shm_block = (SHM_DATA_T *)node->data;
	if (NULL == shm_block) {
		DBG_PRINT(DBG_MODULE_ERROR, "The shm_block is null\n");
		return -2;
	}

	if (NULL == shm_block->data) {
		DBG_PRINT(DBG_MODULE_ERROR, "The data of shm_block is null\n");
		return -2;
	}

	while (!shm_block->flag_r) {
		usleep(1000 * 100);
	}
	size = (buflen < shm_block->datalen)?buflen:shm_block->datalen;
	memcpy(buf, shm_block->data, size);
	*dest = shm_block->dest;
	*src = shm_block->souece;
	shm_block->flag_w = 1;
	DBG_PRINT(DBG_MODULE_SHARTMEM, "Get data to %p, size:%d", shm_block->data, size);
	return size;
}