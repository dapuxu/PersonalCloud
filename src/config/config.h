#ifndef __CONFIG_H__
#define __CONFIG_H__
#include "pc_includes.h"
#include "lib_file.h"

typedef struct {
	char *item[10];
	unsigned char item_num;
}CONF_PARAM_T;

class Conf
{
	public:
		Conf();
		~Conf();
		char Conf_Init(char *path);
		char Conf_Get_Param(CONF_PARAM_T *param, char *buf, unsigned char buflen);
		char Conf_Update_Param_Value(CONF_PARAM_T *param, double value);
		char Conf_Update_Param_String(CONF_PARAM_T *param, char *data);
	private:
		FILE_BLOCK_T conf;
};
#endif