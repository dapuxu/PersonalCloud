#include "config_manage.h"

/*******************************************************************************************************************
**	函数名:Conf_Get_Server_Port
**	描	述:获取配置文件服务器监听端口
**	参	数:[in]server_type:服务器类型
**	返回值:端口号
********************************************************************************************************************/
int Conf_Get_Server_Port(unsigned char server_type)
{
	int ret = 0;
	Conf conf;
	CONF_PARAM_T param;
	char buf[8] = {0x0};

	if (server_type >= SERVER_TYPE_MAX)
		return 0;

	conf.Conf_Init(CONF_SYS_PATH);
	param.item[0] = CONF_SYS_ROOT_SERVER;
	if (server_type == SERVER_TYPE_LISTNE) {
		param.item[1] = CONF_SYS_SUB_I_SERVER_LISTEN;
	} else if (server_type == SERVER_TYPE_VIDEO) {
		param.item[1] = CONF_SYS_SUB_I_SERVER_VIDEO;
	}
	param.item[2] = CONF_SYS_SUB_II_SERVER_PORT;

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
	int ret = 0;
	Conf conf;
	CONF_PARAM_T param;
	char buf[8] = {0x0};

	if (server_type >= SERVER_TYPE_MAX)
		return 0;

	conf.Conf_Init(CONF_SYS_PATH);
	param.item[0] = CONF_SYS_ROOT_SERVER;
	if (server_type == SERVER_TYPE_LISTNE) {
		param.item[1] = CONF_SYS_SUB_I_SERVER_LISTEN;
	} else if (server_type == SERVER_TYPE_VIDEO) {
		param.item[1] = CONF_SYS_SUB_I_SERVER_VIDEO;
	}
	param.item[2] = CONF_SYS_SUB_II_SERVER_CONN_MAX;

	if (conf.Conf_Get_Param(&param, buf, sizeof(buf)) == 1)
		return atoi(buf);
	else
		return 0;
}

