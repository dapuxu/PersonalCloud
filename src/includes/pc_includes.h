#ifndef __pc_includes_H__
#define __pc_includes_H__
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lib_debug.h"

#define DB_PATH										"/opt/cloud/db/data.db"		/* 数据库地址 */

/**************************************** 功能模块开关 ***************************************/
#define FUNC_SWITCH_DEBUG                           1                           /* 调试开关 */



/**************************************** 调试模块开关 ***************************************/
#if FUNC_SWITCH_DEBUG
#define DBG_ENABLE									DEBUG_SWITCH_OPEN
#define DBG_DISENABLE								DEBUG_SWITCH_CLOSE
#else
#define DBG_ENABLE									DEBUG_SWITCH_CLOSE
#define DBG_DISENABLE								DEBUG_SWITCH_CLOSE

#endif

#define DBG_MODULE_ERROR							DBG_ENABLE					/* 异常 */
#define DBG_MODULE_COMMON							DBG_ENABLE					/* 通用 */
#define DBG_MODULE_DATABASE							DBG_ENABLE					/* 数据库模块 */
#define DBG_MODULE_SHARTMEM							DBG_ENABLE					/* 共享内存模块 */
#define DBG_MODULE_TEST								DBG_ENABLE					/* 临时调试 */

#endif
