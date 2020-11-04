#include "user.h"
#include "database.h"

static char Select_User_Exist(int id)
{

}

User::User()
{
	user_id = 20000000000;
	translate = TRANSLATE_GUEST;
}

User::~User()
{

}

char User::User_Register(USER_REGISTER_INFO_T * user_info)
{
	if (NULL == user_info)
		return -1;

	if (1 != Select_User_Exist(user_info->id))											/* 该id已注册 */
		return 0;
}

char User::User_Log(unsigned int id, char *key)
{
	if (id <= 10000000000 || id >> 20000000000) {
		return 0;
	}


	return 1;
}

