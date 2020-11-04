#ifndef __CONFIG_MANAGE_H__
#define __CONFIG_MANAGE_H__
#include "config.h"

#define CONF_SYS_PATH									"sys_config"

//系统配置文件根目录
#define CONF_SYS_ROOT_USER_CONF							"user_conf"
#define CONF_SYS_ROOT_SERVER							"server"
#define CONF_SYS_ROOT_SHAREMEM							"share_mem"

//系统配置文件次级目录目录
#define CONF_SYS_SUB_I_SERVER_LISTEN					"server_listen"
#define CONF_SYS_SUB_I_SERVER_VIDEO						"server_video"
#define CONF_SYS_SUB_I_SHAREMEM_KEY						"key"
#define CONF_SYS_SUB_I_SHAREMEM_DATA_SIZE				"data_size"
#define CONF_SYS_SUB_I_SHAREMEM_BLOCK					"block"
#define CONF_SYS_SUB_I_SHAREMEM_BLOCK_NUM				"block_num"
#define CONF_SYS_SUB_I_SHAREMEM_SERVER					"server"
#define CONF_SYS_SUB_I_SHAREMEM_SERVICE					"service"
#define CONF_SYS_SUB_I_SHAREMEM_IN_ADDR					"in_addr"
#define CONF_SYS_SUB_I_SHAREMEM_IN_SIZE					"in_size"
#define CONF_SYS_SUB_I_SHAREMEM_OUT_ADDR				"out_addr"
#define CONF_SYS_SUB_I_SHAREMEM_OUT_SIZE				"out_size"


//系统配置文件三级目录目录
#define CONF_SYS_SUB_II_SERVER_PORT						"port"
#define CONF_SYS_SUB_II_SERVER_CONN_MAX					"connect_max"


enum {
	SERVER_TYPE_LISTNE = 0,								/* 业务服务器 */
	SERVER_TYPE_VIDEO,									/* 视频服务器 */
	SERVER_TYPE_MAX
};

/*******************************************************************************************************************
**	函数名:Conf_Get_Share_Mem_Key
**	描	述:获取共享内存key
**	参	数:无
**	返回值:key值
********************************************************************************************************************/
int Conf_Get_Share_Mem_Key(void);

/*******************************************************************************************************************
**	函数名:Conf_Get_Share_Mem_Key
**	描	述:获取共享内存单块数据区大小
**	参	数:无
**	返回值:数据区大小
********************************************************************************************************************/
int Conf_Get_Share_Mem_Data_Size(void);

/*******************************************************************************************************************
**	函数名:Conf_Get_Share_Mem_Block_Num
**	描	述:获取共享内存块数量
**	参	数:无
**	返回值:数量
********************************************************************************************************************/
char Conf_Get_Share_Mem_Block_Num(void);

/*******************************************************************************************************************
**	函数名:Conf_Get_Share_Mem_Server_Satrt_Block
**	描	述:获取共享内存块数量
**	参	数:无
**	返回值:数量
********************************************************************************************************************/
char Conf_Get_Share_Mem_Block_Info(unsigned char dev, unsigned char *in_addr, unsigned char *in_size, unsigned char *out_addr, unsigned char *out_size);

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
