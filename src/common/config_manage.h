#ifndef __CONFIG_MANAGE_H__
#define __CONFIG_MANAGE_H__
#include "config.h"

#define CONF_SYS_PATH									"sys_config"

//系统配置文件根目录
#define CONF_SYS_ROOT_USER_CONF							"user_conf"
#define CONF_SYS_ROOT_SERVER							"server"

//系统配置文件次级目录目录
#define CONF_SYS_SUB_I_SERVER_LISTEN					"server_listen"
#define CONF_SYS_SUB_I_SERVER_VIDEO						"server_video"


//系统配置文件三级目录目录
#define CONF_SYS_SUB_II_SERVER_PORT						"port"
#define CONF_SYS_SUB_II_SERVER_CONN_MAX					"connect_max"


enum {
	SERVER_TYPE_LISTNE = 0,								/* 业务服务器 */
	SERVER_TYPE_VIDEO,									/* 视频服务器 */
	SERVER_TYPE_MAX
};
#endif
