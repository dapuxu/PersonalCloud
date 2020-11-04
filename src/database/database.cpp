#include "database.h"
#include "sqlite3.h"
#include <dlfcn.h>

char db_opera_str[DB_OPERA_MAX][32] = {
	"Common opera", \
	"Table created", \
	"Records inserted", \
	"Selceted", \
	"Update", \
	"Delect"};

Database::Database()
{
	db_opera = DB_OPERA_MAX;
}

Database::~Database()
{

}

int Database::Database_Handle(void * data, int argc, char * * argv, char * * azColName)
{
	int i;

	DBG_PRINT(DBG_MODULE_DATABASE, "Opera:%d", db_opera);
	if (NULL != data)
   		DBG_PRINT(DBG_MODULE_DATABASE, "%s: ", (const char*)data);

	if (DEBUG_SWITCH_OPEN == DBG_MODULE_DATABASE) {
	   	for(i=0; i<argc; i++) {
	      	printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	   	}
	   	printf("\n");
	}
   	return 0;
}

char Database::Database_Init(char * db_path)
{
	unsigned char path_size = 0;

	if (NULL == db_path)
		return 0;

	path_size = strlen(db_path);

	if (path_size > sizeof(path))
		return 0;

	memcpy(path, db_path, path_size);
	return 1;
}

char Database::Database_Exec(unsigned char opera, char * statement , int (*CallBack)(void *, int, char **, char **))
{
	sqlite3 *db;
	int  rc;

	if (DB_OPERA_MAX <= opera || NULL == statement)
		return 0;

	rc = sqlite3_open(path, &db);
   	if(rc) {
      	DBG_PRINT(DBG_MODULE_DATABASE,"Can't open database: %s\n", sqlite3_errmsg(db));
      	exit(0);
   	} else {
		DBG_PRINT(DBG_MODULE_DATABASE, "Opened database successfully\n");
   	}
	db_opera = opera;
	DBG_PRINT(DBG_MODULE_DATABASE, "%s\n", statement);
	rc = sqlite3_exec(db, statement, CallBack, NULL, &errmsg);
	if(rc != SQLITE_OK) {
   		DBG_PRINT(DBG_MODULE_DATABASE, "SQL error: %s\n", errmsg);
      	sqlite3_free(errmsg);
   	}else{
      	DBG_PRINT(DBG_MODULE_DATABASE, "%s successfully\n", &db_opera_str[opera-1][0]);
   	}
   	sqlite3_close(db);

	return 1;
}

