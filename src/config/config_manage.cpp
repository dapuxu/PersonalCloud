#include "config_manage.h"

/*******************************************************************************************************************
**	函数名:Conf_Get_Share_Mem_Key
**	描	述:获取共享内存key
**	参	数:无
**	返回值:key值
********************************************************************************************************************/
int Conf_Get_Share_Mem_Key(void)
{
	Conf conf;
	CONF_PARAM_T param;
	char buf[8] = {0x0};

	conf.Conf_Init((char *)CONF_SYS_PATH);
	param.item[0] = (char *)CONF_SYS_ROOT_SHAREMEM;
	param.item[1] =(char *) CONF_SYS_SUB_I_SHAREMEM_KEY;
	param.item_num = 2;

	if (conf.Conf_Get_Param(&param, buf, sizeof(buf)) == 1) 
		return atoi(buf);
	else
		return 0;
}

/*******************************************************************************************************************
**	函数名:Conf_Get_Share_Mem_Key
**	描	述:获取共享内存单块数据区大小
**	参	数:无
**	返回值:数据区大小
********************************************************************************************************************/
int Conf_Get_Share_Mem_Data_Size(void)
{
	Conf conf;
	CONF_PARAM_T param;
	char buf[8] = {0x0};

	conf.Conf_Init((char *)CONF_SYS_PATH);
	param.item[0] = (char *)CONF_SYS_ROOT_SHAREMEM;
	param.item[1] =(char *) CONF_SYS_SUB_I_SHAREMEM_DATA_SIZE;
	param.item_num = 2;

	if (conf.Conf_Get_Param(&param, buf, sizeof(buf)) == 1)
		return atoi(buf);
	else
		return 0;

}

/*******************************************************************************************************************
**	函数名:Conf_Get_Share_Mem_Block_Num
**	描	述:获取共享内存块数量
**	参	数:无
**	返回值:数量
********************************************************************************************************************/
char Conf_Get_Share_Mem_Block_Num(void)
{
	Conf conf;
	CONF_PARAM_T param;
	char buf[8] = {0x0};

	conf.Conf_Init((char *)CONF_SYS_PATH);
	param.item[0] = (char *)CONF_SYS_ROOT_SHAREMEM;
	param.item[1] =(char *) CONF_SYS_SUB_I_SHAREMEM_BLOCK_NUM;
	param.item_num = 2;

	if (conf.Conf_Get_Param(&param, buf, sizeof(buf)) == 1)
		return atoi(buf);
	else
		return 0;

}

/*******************************************************************************************************************
**	函数名:Conf_Get_Share_Mem_Server_Satrt_Block
**	描	述:获取共享内存块数量
**	参	数:无
**	返回值:数量
********************************************************************************************************************/
char Conf_Get_Share_Mem_Block_Info(unsigned char dev, unsigned char *in_addr, unsigned char *in_size, unsigned char *out_addr, unsigned char *out_size)
{
	Conf conf;
	CONF_PARAM_T param;
	char buf[8] = {0x0};
	char ret = 0;

	if (1 < dev)
		return 0;
	
	conf.Conf_Init((char *)CONF_SYS_PATH);
	param.item[0] = (char *)CONF_SYS_ROOT_SHAREMEM;
	param.item[1] =(char *) CONF_SYS_SUB_I_SHAREMEM_BLOCK;
	if (dev == 0)
		param.item[2] =(char *) CONF_SYS_SUB_I_SHAREMEM_SERVER;
	else
		param.item[2] =(char *) CONF_SYS_SUB_I_SHAREMEM_SERVICE;
	param.item_num = 4;

	if (NULL != in_addr) {
		param.item[3] =(char *) CONF_SYS_SUB_I_SHAREMEM_IN_ADDR;
		if (conf.Conf_Get_Param(&param, buf, sizeof(buf)) == 1) {
			*in_addr = (char)atoi(buf);
			ret = 1;
		}
	}

	if (NULL != in_size) {
		param.item[3] =(char *) CONF_SYS_SUB_I_SHAREMEM_IN_SIZE;
		if (conf.Conf_Get_Param(&param, buf, sizeof(buf)) == 1) {
			*in_size = (char)atoi(buf);
			ret = 1;
		}
	}

	if (NULL != out_addr) {
		param.item[3] =(char *) CONF_SYS_SUB_I_SHAREMEM_OUT_ADDR;
		if (conf.Conf_Get_Param(&param, buf, sizeof(buf)) == 1) {
			*out_addr = (char)atoi(buf);
			ret = 1;
		}
	}

	if (NULL != out_size) {
		param.item[3] =(char *) CONF_SYS_SUB_I_SHAREMEM_OUT_SIZE;
		if (conf.Conf_Get_Param(&param, buf, sizeof(buf)) == 1) {
			*out_size = (char)atoi(buf);
			ret = 1;
		}
	}
	return ret;
}

/*******************************************************************************************************************
**	函数名:Conf_Get_Server_Port
**	描	述:获取配置文件服务器监听端口
**	参	数:[in]server_type:服务器类型
**	返回值:端口号
********************************************************************************************************************/
int Conf_Get_Server_Port(unsigned char server_type)
{
	Conf conf;
	CONF_PARAM_T param;
	char buf[8] = {0x0};

	if (server_type >= SERVER_TYPE_MAX)
		return 0;

	conf.Conf_Init((char *)CONF_SYS_PATH);
	param.item[0] = (char *)CONF_SYS_ROOT_SERVER;
	if (server_type == SERVER_TYPE_LISTNE) {
		param.item[1] =(char *) CONF_SYS_SUB_I_SERVER_LISTEN;
	} else if (server_type == SERVER_TYPE_VIDEO) {
		param.item[1] = (char *)CONF_SYS_SUB_I_SERVER_VIDEO;
	}
	param.item[2] = (char *)CONF_SYS_SUB_II_SERVER_PORT;
	param.item_num = 3;

	if (conf.Conf_Get_Param(&param, buf, sizeof(buf)) == 1)
		return atoi(buf);
	else
		return 0;
}

/*******************************************************************************************************************
**	函数名:Conf_Get_Server_ConnMax
**	描	述:获取配置文件服务器最大接入个数
**	参	数:[in]server_type:服务器类型
**	返回值:端口号
********************************************************************************************************************/
int Conf_Get_Server_ConnMax(unsigned char server_type)
{
	Conf conf;
	CONF_PARAM_T param;
	char buf[8] = {0x0};

	if (server_type >= SERVER_TYPE_MAX)
		return 0;

	conf.Conf_Init((char *)CONF_SYS_PATH);
	param.item[0] =(char *) CONF_SYS_ROOT_SERVER;
	if (server_type == SERVER_TYPE_LISTNE) {
		param.item[1] = (char *)CONF_SYS_SUB_I_SERVER_LISTEN;
	} else if (server_type == SERVER_TYPE_VIDEO) {
		param.item[1] = (char *)CONF_SYS_SUB_I_SERVER_VIDEO;
	}
	param.item[2] = (char *)CONF_SYS_SUB_II_SERVER_CONN_MAX;
	param.item_num = 3;

	if (conf.Conf_Get_Param(&param, buf, sizeof(buf)) == 1)
		return atoi(buf);
	else
		return 0;
}

