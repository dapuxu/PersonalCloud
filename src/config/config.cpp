#include "config_manage.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lib_cjson.h"

#define SYS_CONFIG 			"config/sys_config"
#define USER_CONFIG 		"config/user_config"

using namespace std;
Conf::Conf()
{

}

Conf::~Conf()
{

}

/*******************************************************************************************************************
**	函数名:Conf_Init
**	描	述:配置文件类初始化
**	参	数:[in]path:文件路径
**	返回值:1-存在/0-不存在
********************************************************************************************************************/
char Conf::Conf_Init(char *path)
{
	int ret;
	if (path == NULL || strlen(path) >= sizeof(conf.file_path))
		return 0;

	memset((void *)&conf, 0x0, sizeof(FILE_BLOCK_T));
	DBG_PRINT(DBG_MODULE_TEST, "path:%s\n", path);
	ret = File_Init(&conf, path);
	DBG_PRINT(DBG_MODULE_TEST, "ret:%d conf:%s\n", ret, conf.file_path);
	return ret;
}

/*******************************************************************************************************************
**	函数名:Conf_Get_Param
**	描	述:获取参数键值
**	参	数:[in]param:各级键名
**         [out]buf:缓存
**         [int]buflen:缓存大小
**	返回值:1-存在/0-不存在
********************************************************************************************************************/
char Conf::Conf_Get_Param(CONF_PARAM_T *param, char *buf, unsigned char buflen)
{
	cJSON * root = NULL;
    cJSON * item = NULL;
	int i = 0, size = 0;
	char *temp = NULL;

	if (NULL == param || NULL == buf || 0 >= buflen || 0 == File_Access(conf.file_path)) {
		DBG_PRINT(DBG_MODULE_ERROR, "param:%s, buf:%s, buflen:%d, file:%s\n", param?"Exist":"NULL", param?"Exist":"NULL", buflen, File_Access(conf.file_path)?"Exist":"NULL");
		DBG_PRINT(DBG_MODULE_TEST, "file_path:%s\n", conf.file_path);
		return 0;
	}

	if (0 == param->item_num|| NULL == param->item[0]) {
		return 0;
	}
	size = File_Size(conf.file_path);
	temp = (char *)malloc(size);
	memset(temp, 0x0, size);
	File_Read(&conf, temp, size);
	root = cJSON_Parse(temp);
	if (NULL == root)
		return 0;

	item = cJSON_GetObjectItem(root, param->item[0]);
	if (NULL == item)
		return 0;

	for (i=1; i < param->item_num && i < 10; i++) {
		if (param->item[i] == NULL)
			return 0;
		item = cJSON_GetObjectItem(item, param->item[i]);
	}
	memcpy(buf, cJSON_Print(item), (strlen(cJSON_Print(item)) < buflen)?strlen(cJSON_Print(item)):buflen);
	free(temp);
	return 1;
}

/*******************************************************************************************************************
**	函数名:Conf_Update_Param_Value
**	描	述:设置参数键值-数字
**	参	数:[in]param:各级键名
**         [int]value:数值
**	返回值:1-成功/0-失败
********************************************************************************************************************/
char Conf::Conf_Update_Param_Value(CONF_PARAM_T *param, double value)
{
	cJSON * root = NULL;
    cJSON * item = NULL;
	int i = 0, size = 0;
	char *temp = NULL;
	
	if (NULL == param || 0 == File_Access(conf.file_path))
		return 0;

	if (0 == param->item_num|| NULL == param->item[0])
		return 0;

	size = File_Size(conf.file_path);
	temp = (char *)malloc(size);
	memset(temp, 0x0, size);
	File_Read(&conf, temp, size);
	root = cJSON_Parse(temp);
	
	if (param->item_num > 1) {
		item = cJSON_GetObjectItem(root, param->item[0]);
		for (i=1; i < (param->item_num-1) && i < 10; i++) {
			if (param->item[i] == NULL)
				return 0;
			item = cJSON_GetObjectItem(item, param->item[i]);
		}
	} else {
		item = root;
	}
	if (param->item[param->item_num-1] == NULL)
		return 0;
	cJSON_ReplaceItemInObject(item, param->item[param->item_num-1], cJSON_CreateNumber(value));
	File_Write_Cover(&conf, cJSON_Print(root), strlen(cJSON_Print(root)));
	free(temp);
	return 1;
}

/*******************************************************************************************************************
**	函数名:Conf_Update_Param_String
**	描	述:设置参数键值-字符串
**	参	数:[in]param:各级键名
**         [int]data:数据
**	返回值:1-成功/0-失败
********************************************************************************************************************/
char Conf::Conf_Update_Param_String(CONF_PARAM_T *param, char *data)
{
	cJSON * root = NULL;
    cJSON * item = NULL;
	int i = 0, size = 0;
	char *temp = NULL;
	
	if (NULL == param || 0 == File_Access(conf.file_path))
		return 0;

	if (0 == param->item_num || NULL == param->item[0] || NULL == data)
		return 0;

	size = File_Size(conf.file_path);
	temp = (char *)malloc(size);
	memset(temp, 0x0, size);
	File_Read(&conf, temp, size);
	root = cJSON_Parse(temp);
	
	if (param->item_num > 1) {
		item = cJSON_GetObjectItem(root, param->item[0]);
		for (i=1; i < (param->item_num-1) && i < 10; i++) {
			if (param->item[i] == NULL)
				return 0;
			item = cJSON_GetObjectItem(item, param->item[i]);
		}
	} else {
		item = root;
	}
	if (param->item[param->item_num-1] == NULL)
		return 0;
	cJSON_ReplaceItemInObject(item, param->item[param->item_num-1], cJSON_CreateString(data));
	File_Write_Cover(&conf, cJSON_Print(root), strlen(cJSON_Print(root)));
	free(temp);
	return 1;
}
