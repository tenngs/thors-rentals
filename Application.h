#pragma once
#include <string>

class Application
{
private:
    std::string name;
    const char *sql = "CREATE TABLE  app_access_staff("
                      "ID            INTEGER PRIMARY KEY     AUTOINCREMENT,"
                      "USERNAME      VACHAR(50)              NOT NULL UNIQUE,"
                      "PASSWORD      VACHAR(50)              NOT NULL ,"
                      "LOGGED_ON     CHAR(1)                 NOT NULL);";

public:
    Application(std::string name_val);
    int initTableOperation(std::string tableName, const char *sql, bool verbose = false);
    const char *getSqlStatement(const char *sql);
};
