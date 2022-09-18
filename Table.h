/*
    This class contains utility functions in relation
    to executing a table operation using Sqlite exec and
    getters for tablename and operation type. Note: Sqlite
    exec is utilised because NO user-entered data is used
    in table operations.
*/
#pragma once

#include <vector>

class Table
{
private:
    std::string name;
    std::string operationType; // "DROP", "INSERT INTO", "CREATE"
    std::string sqlStmnt;

public:
    Table();
    Table(std::string nameVal, std::string opTypeVal);
    std::string getSqlStatement();
    std::string getTableName();
    std::string getOperationType();
    int execTableOperation(std::string operationType, std::string tableName, std::string sql, bool verbose = false);
    bool searchTextValuesFromDB(std::string val1, std::string sqlStmnt);
    bool searchTextValuesFromDB(std::string val1, std::string val2, std::string sqlStmnt);
    void appInsertTableOperation(std::string successMsg, std::vector<std::string> infoCollection, int numberOfQuestions, std::string sql);
};