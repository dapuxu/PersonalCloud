#ifndef __LIB_FILE_H__
#define __LIB_FILE_H__

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct {
	char file_path[128];
	char flag_lock;
}FILE_BLOCK_T;

/*******************************************************************************************************************
**	函数名:File_Init
**	描	述:文件块初始化
**	参	数:[in]block:文件块
**         [in]file_path:文件路径
**	返回值:1-存在/0-不存在
********************************************************************************************************************/
char File_Init(FILE_BLOCK_T *block,char *file_path);

/*******************************************************************************************************************
**	函数名:File_Access
**	描	述:检测文件是否存在
**	参	数:[in]file_path:文件路径
**	返回值:1-存在/0-不存在
********************************************************************************************************************/
char File_Access(char *file_path);

/*******************************************************************************************************************
**	函数名:File_Size
**	描	述:获取文件大小
**	参	数:[in]file_path:文件路径
**	返回值:文件数据大小
********************************************************************************************************************/
unsigned int File_Size(char *file_path);

/*******************************************************************************************************************
**	函数名:File_Write_Cover
**	描	述:覆盖写入文件
**	参	数:[in]file_path:文件路径
**		   [in]data:数据
**		   [in]datalen:数据大小
**	返回值:数据写入大小
********************************************************************************************************************/
signed int File_Write_Cover(FILE_BLOCK_T *block, char *data, int datalen);

/*******************************************************************************************************************
**	函数名:File_Write_Add
**	描	述:追加写入文件
**	参	数:[in]file_path:文件路径
**		   [in]data:数据
**		   [in]datalen:数据大小
**	返回值:数据写入大小
********************************************************************************************************************/
signed int File_Write_Add(FILE_BLOCK_T *block, char *data, int datalen);

/*******************************************************************************************************************
**	函数名:File_Read
**	描	述:读取文件数据
**	参	数:[in]block:文件块
**		   [in]buf:缓存
**		   [in]buflen:缓存大小
**	返回值:读取到的数据大小
********************************************************************************************************************/
unsigned int File_Read(FILE_BLOCK_T *block, char *buf, int buflen);

/*******************************************************************************************************************
**	函数名:File_Read
**	描	述:读取文件指定行数据
**	参	数:[in]block:文件块
**		   [in]line:指定行
**		   [in]buf:缓存
**		   [in]buflen:缓存大小
**	返回值:读取到的数据大小
********************************************************************************************************************/
unsigned int File_Read_Line(FILE_BLOCK_T *block, unsigned short line, char *buf, int buflen);

#ifdef __cplusplus
}
#endif

#endif