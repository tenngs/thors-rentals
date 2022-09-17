#include <string>
#include "Sql.h"

// ---Sqlite statement getters
// returns a Sqlite statement depending on tableName attribute
// create statement getters
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

// drop statement getters
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

// insert statement getters
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

// add customer to table getter
std::string Sql::getAddCustomerStmnt()
{
    return this->customerAddStmnt;
}

// add staff to table getter
std::string Sql::getAddStaffStmnt()
{
    return this->accessStaffStmnt;
}

// add skis / snowboard to table getter
std::string Sql::getAddSkiSnowboardStmnt()
{
    return this->staffAddStmnt;
}

// add ATV to table getter
std::string Sql::getAddAtvStmnt()
{
    return this->staffAddStmnt;
}