#ifndef __DATABASE_H__
#define __DATABASE_H__
#include "pc_includes.h"

enum {
	DB_OPERA_COMMON = 0,
	DB_OPERA_CREAT,
	DB_OPERA_INSERT,
	DB_OPERA_SELECT,
	DB_OPERA_UPDATE,
	DB_OPERA_DETECT,
	DB_OPERA_MAX
};

class Database 
{
	public:
		char *errmsg;

		Database();
		~Database();
		char Database_Init(char *db_path);
		char Database_Exec(unsigned char opera, char *statement,  int (*CallBack)(void *, int, char **, char **));
	private:
		char path[32];
		int Database_Handle(void *data, int argc, char **argv, char **azColName);
		char db_opera;
};

#endif