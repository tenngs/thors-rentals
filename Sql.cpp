#include <string>
#include "Sql.h"

// constructor
// Sql::Sql(std::customersInitCreate)
//     : name{name_val}
// {
// }

// SQL getters
std::string Sql::getCreateStmnt(std::string tableName)
{
    if (tableName == "customers")
    {
        return this->customersCreateStmnt;
    }

    if (tableName == "orders")
    {
        return this->ordersCreateStmnt;
    }

    if (tableName == "staff")
    {
        return this->staffCreateStmnt;
    }

    if (tableName == "system_access")
    {
        return this->systemAccessCreateStmnt;
    }
}

std::string Sql::getDropStmnt(std::string tableName)
{
    if (tableName == "customers")
    {
        return this->customersDropStmnt;
    }
    if (tableName == "orders")
    {
        return this->ordersDropStmnt;
    }

    if (tableName == "staff")
    {
        return this->staffDropStmnt;
    }

    if (tableName == "system_access")
    {
        return this->system_accessDropStmnt;
    }
}

std::string Sql::getInsertStmnt(std::string tableName)
{
    if (tableName == "customers")
    {
        return this->customersInsertStmnt;
    }
    if (tableName == "staff")
    {
        return this->customersInsertStmnt;
    }
    if (tableName == "system_access")
    {
        return this->systemAccessInsertStmnt;
    }
}
