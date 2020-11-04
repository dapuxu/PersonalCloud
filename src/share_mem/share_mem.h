#ifndef __SHARE_MEM_H__
#define __SHARE_MEM_H__
#include "pc_includes.h"
#include "lib_list.h"


typedef struct {
	int fd;
	char addr[32];
}SHM_NET_INFO;

typedef struct {
	int souece;
	int dest;
	short buflen;
	char flag_w;
	char flag_r;
	short datalen;
	void *data;
}SHM_DATA_T;

typedef struct {
	void *addr_in_start;
	void *addr_in_end;
	void *addr_out_start;
	void *addr_out_end;
	unsigned short data_block_size;
}SHM_INFO_T;

class ShareMen
{
	public:
		LIST_T *Shm_In_List;
		LIST_T *Shm_Out_List;
		ShareMen();
		~ShareMen();
		signed char Share_Mem_Mount(int key, unsigned int size, unsigned short block_size, char flag_master, unsigned char in_addr, unsigned short in_size, unsigned char out_addr, unsigned short out_size);
		short Shm_Put(int dest, int src, void *data, unsigned short datalen);
		short Shm_Get(int *dest, int *src, void *buf, unsigned short buflen);
	private:
		int ShmID;
		void *Shm_Addr;
		SHM_INFO_T Shm_Info;
		char Flag_Master;
};

#endif