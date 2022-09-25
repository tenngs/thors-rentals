/*
    This class contains utility functions in relation
    to executing a table operations using Sqlite exec
    and sqlite_bindXXX depending whether a query is
    from system-entered data or user-entered data,
    respectively.
    Note: Sqlite exec is utilised only when
    NO user-entered data is handled to prevent SQL-injection
    attacks in table operations.
*/
#pragma once

#include <vector>
#include <unordered_set>
#include "Order.h"

class Table
{
private:
    std::string name;
    // "DROP", "INSERT INTO", "CREATE", "UPDATE"
    std::string operationType;
    std::string sqlStmnt;

public:
    Table();
    Table(std::string nameVal);
    Table(std::string nameVal, std::string opTypeVal);
    std::string getSqlStatement();
    std::string getTableName();
    std::string getOperationType();
    int execTableOperation(std::string operationType, std::string tableName, std::string sql, bool verbose = false);
    bool determineExistenceTextValuesInDB(std::string val1, std::string sqlStmnt);
    bool determineExistenceTextValuesInDB(std::string val1, std::string val2, std::string sqlStmnt);
    int searchNumericValuesFromDB(std::string sqlStmnt);
    std::string searchTextValuesFromDB(std::string sqlStmnt);

    void appInsertTableOperation(std::string successMsg, std::vector<std::string> infoCollection, std::string sql);
    std::unordered_set<int> getAvailableEquipmentIDs(std::string sqlStmnt);
    double calculateRentalCost(Order &initOrder);
    std::string calculateReturnDatetime(Order &initOrder);
    void appToOrdersTableFromOrder(std::string successMsg, std::vector<std::string> infoCollection, std::string sql);
};