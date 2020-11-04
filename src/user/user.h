#ifndef __USER_H__
#define __USER_H__
#include "pc_includes.h"

enum {
	TRANSLATE_GUEST = 0,
	TRANSLATE_USER,
	TRANSLATE_ROOT,
	TRANSLATE_MAX
};

typedef struct {
	unsigned int id;
	char name[12];
	char key[12];
	char gender;
}USER_REGISTER_INFO_T;

class User
{
	public:
		User();
		~User();
		char User_Register(USER_REGISTER_INFO_T *user_info);
		char User_Log(unsigned int id, char *key);
	private:
		unsigned int user_id;
		unsigned char translate;
};

#endif