#pragma once
#include <string>

class Application
{
private:
    std::string name;

public:
    Application(std::string name_val);
    int initTableOperation(std::string operation, std::string tableName, const char *sql, bool verbose = false);
};
