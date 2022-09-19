#include <string>
#include "Sql.h"

/*
    Sqlite create statement getters.
    Returns a Sqlite statement depending on
    tableName attribute.
*/
const std::string Sql::getCreateStmnt(std::string tableName)
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

    if (tableName == "inventory_skis_snowboards")
    {
        return this->inventorySkisSBsCreateStmnt;
    }
}

/*
    Sqlite drop statement getters.
    Returns a Sqlite statement depending on
    tableName attribute.
*/
const std::string Sql::getDropStmnt(std::string tableName)
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

/*
    Sqlite insert statement getters.
    Returns a Sqlite statement depending on
    tableName attribute.
*/
const std::string Sql::getInsertStmnt(std::string tableName)
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
    if (tableName == "inventory_skis_snowboards")
    {
        return this->inventorySkisSBsInsertStmnt;
    }
}

/*
    Add customer to table getter.
*/
const std::string Sql::getAddCustomerStmnt()
{
    return this->addCustomerStmnt;
}

/*
    Add staff to table getter.
*/
const std::string Sql::getAddStaffStmnt()
{
    return this->addSystemAccessStaffStmnt;
}

/*
    Add skis / snowboard to table getter.
*/
const std::string Sql::getAddSkisSnowboardStmnt()
{
    return this->addSkisSnowboarsStmnt;
}

/*
    Add ATV to table getter.
*/
const std::string Sql::getAddAtvStmnt()
{
    return this->addAtvStmnt;
}

/*
    Validate username from DB getter.
*/
const std::string Sql::getValidateUsernameStmnt()
{
    return this->validateUsernameStmnt;
}

/*
    Validate username and password from DB getter.
*/
const std::string Sql::getValidateUnamePasswordStmnt()
{
    return this->validateUnamePasswordStmnt;
}

/*
    Update system access staff getter.
    Utilised to set the status of person who is
    logged on/
*/
const std::string Sql::getUpdateSystemAccessStaffStmnt()
{
    return this->updateSystemAccessStaffStmnt;
}