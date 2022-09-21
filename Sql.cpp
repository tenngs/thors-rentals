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

    if (tableName == "inventory_atvs")
    {
        return this->inventoryAtvsCreateStmnt;
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

    if (tableName == "inventory_skis_snowboards")
    {
        return this->inventorySkisSBsDropStmnt;
    }

    if (tableName == "inventory_atvs")
    {
        return this->inventoryAtvsDropStmnt;
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
        return this->staffInsertStmnt;
    }
    if (tableName == "system_access")
    {
        return this->systemAccessInsertStmnt;
    }
    if (tableName == "inventory_skis_snowboards")
    {
        return this->inventorySkisSBsInsertStmnt;
    }
    if (tableName == "inventory_atvs")
    {
        return this->inventoryAtvsInsertStmnt;
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

const std::string Sql::getSearchForCustomerIDByNameV1()
{
    return this->searchForCustomerIDByNameV1;
}

const std::string Sql::getSearchForCustomerIDByNameV2()
{
    return this->searchForCustomerIDByNameV2;
}

const std::string Sql::getSearchForCustomerIDByID()
{
    return this->searchForCustomerIDByID;
}

const std::string Sql::getAvailableEquipIDsV1()
{
    return this->availableEquipIDsV1;
}

const std::string Sql::getAvailableEquipIDsV2()
{
    return this->availableEquipIDsV2;
}

const std::string Sql::getAvailableEquipV1()
{
    return this->availableEquipV1;
}

const std::string Sql::getAvailableEquipV2()
{
    return this->availableEquipV2;
}

const std::string Sql::getCustomerFirstName()
{
    return this->customerFirstName;
}
