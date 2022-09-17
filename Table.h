#pragma once

class Table
{
private:
    std::string name;
    // "DROP", "INSERT", "CREATE"
    std::string operationType;
    std::string sqlStmnt;

public:
    Table(std::string nameVal, std::string opTypeVal);
    int execTableOperation(std::string operationType, std::string tableName, std::string sql, bool verbose = false);
    std::string getSqlStatement();
    std::string getTableName();
    std::string getOperationType();
};