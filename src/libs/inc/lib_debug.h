#ifndef __LIB_DEBUG_H__
#define __LIB_DEBUG_H__
#include <stdio.h>
#include "includes.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************* Enum ********************************************/
/* debug调试输出方式 */
typedef enum {
	INTERFACE_TYPE_CONSOLE = 0,								/* 终端输出 */
	INTERFACE_TYPE_UART,									/* 串口输出 */
	INTERFACE_TYPE_NET,										/* TCP输出   */
	INTERFACE_TYPE_LOG,										/* 日志文件存储 */
	INTERFACE_TYPE_LCD,										/* lcd屏输出 */
	INTERFACE_TYPE_MAX
}INTERFACE_TYPE_T;

/* 调试开关 */
typedef enum {
	DEBUG_SWITCH_CLOSE = 0,
	DEBUG_SWITCH_OPEN
}DEBUG_SWITCH_T;


/* 串口奇偶校验 */
typedef enum {
    UART_DATABIT_5 = 5,
    UART_DATABIT_6,
    UART_DATABIT_7,
    UART_DATABIT_8
}UART_DATABIT_T;

/* 串口奇偶校验 */
typedef enum {
    UART_STOPBIT_1 = 1,
    UART_STOPBIT_2
}UART_STOPBIT_T;

/* 串口奇偶校验 */
typedef enum {
    UART_PARITY_NONE,
    UART_PARITY_ODD,
    UART_PARITY_EVEN
}UART_PARITY_T;

/* 串口流控 */
typedef enum {
    UART_FLOWCTRL_NONE,
	UART_FLOWCTRL_SOFT,
	UART_FLOWCTRL_HARD
}UART_FLOWCTRL_T;

/****************************************** Define *******************************************/
#define MAX_DEV_MANE_SIZE		100							/* 设备文件名长度 */

/****************************************** Struct *******************************************/
/*uart 串口信息*/
typedef struct {
	int 				uart_fd;							/* 串口句柄 */
	char 				uart_name[MAX_DEV_MANE_SIZE];		/* 串口设备名 */
	unsigned int 		baudfate;							/* 波特率 */
	unsigned char 		databits;							/* 数据位 */
	unsigned char		stopbits;							/* 停止位 */
	UART_PARITY_T		parity;								/* 奇偶校验:1-奇数,2-偶数 */
	UART_FLOWCTRL_T		flowctrl;							/* 流控:1-软流控,   2-硬流控      */
}DEBUG_UART_INFO;

/*tcp 网络信息*/
typedef struct {
	int 	net_fd;
	bool 	(*Debug_Net_Interface)(char *debug_buf, unsigned int buf_len);
}DEBUG_NET_INFO;

/*file 文件日志信息*/
typedef struct {
	FILE * 				log_fd;
	char 				log_name[MAX_DEV_MANE_SIZE];
	unsigned int 		max_log_size;
}DEBUG_LOG_INFO;

/*tcp 网络信息*/
typedef struct {
	int 	lcd_fd;
	bool 	(*Debug_LCD_Interface)(char *debug_buf, unsigned int buf_len);
}DEBUG_LCD_INFO;

/* debug调试注册信息 */
typedef struct {
	unsigned char 		InterfaceType;
	DEBUG_UART_INFO		*Uart;
	DEBUG_NET_INFO		*Net;
	DEBUG_LOG_INFO		*Log;
	DEBUG_LCD_INFO		*Lcd;
}DEBUG_INFO;

/******************************************* Func *******************************************/

/********************************************************************************************/
/*	函数名:Debug_Msg 																			*/
/*	描	述:调试信息输出		 																	*/
/*	参	数:[in]swit:调试输出开关																	*/
/*		   [in]data:调试输出信息																	*/
/*	返回值:无																					*/
/********************************************************************************************/
void Debug_Msg(char *data);

/********************************************************************************************/
/*	函数名:Debug_Init 																			*/
/*	描	述:调试注册信息回收接口	 																	*/
/*	参	数:[in]info:调试接口注册信息																	*/
/*	返回值:注册成功的接口,bit[0]-控制台 bit[1]-串口 bit[2]-网络												*/
/*			bit[3]-日志文件 bit[4]-LCD屏通道														*/
/********************************************************************************************/
char Debug_Init(DEBUG_INFO *info);

#define DEBUG_TIME 0
#if DEBUG_TIME

unsigned char GetCurrentHour(void);
unsigned char GetCurrentMin(void);
unsigned char GetCurrentSec(void);
unsigned short GetCurrentMsec(void);

#define DBG_PRINT(module, format, ...)  {static char dbg_str[1024] = {0x0}; if(module == 1 && dbg_str != NULL) {sprintf(dbg_str, "[%d:%d:%d:%d][%s:%d]" format,  \
	GetCurrentHour(), GetCurrentMin(), GetCurrentSec(), GetCurrentMsec(), __FUNCTION__, __LINE__, ##__VA_ARGS__); Debug_Msg(dbg_str);}}
#else
#define DBG_PRINT(module, format, ...)  {static char dbg_str[1024] = {0x0}; if(module == 1 && dbg_str != NULL) {sprintf(dbg_str, "[%s:%d]" format, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
	Debug_Msg(dbg_str);}}
#endif

#ifdef __cplusplus
}
#endif
#endif