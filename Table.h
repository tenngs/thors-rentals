#pragma once

#include <string>
#include <iostream>
#include "Table.h"

class Table
{
private:
    std::string name;
    // "DROP", "INSERT", "CREATE"
    std::string operationType;
    std::string sqlStmnt;

public:
    Table(std::string nameVal, std::string opTypeVal);
    int tableOperation(std::string operationType, std::string tableName, std::string sql, bool verbose = false);
    std::string getSqlStatement();
    std::string getTableName();
    std::string getOperationType();
};