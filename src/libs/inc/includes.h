#ifndef __INCLUDES_H__
#define __INCLUDES_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C"
{
#endif


#ifndef bool
#define bool	char
#endif

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

#ifndef NULL
#define NULL	0
#endif

enum {
	DATA_TYPE_MASK_NONE = 0,
	DATA_TYPE_MASK_NET_SERVER,
	DATA_TYPE_MASK_NET_CONNECT,
};

#ifdef __cplusplus
}
#endif

#endif
