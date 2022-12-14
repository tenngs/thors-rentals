#include <string>
#include "Sql.h"

/*
    Sqlite table create statement getters.
    Returns a sqlite statement depending on
    tableName attribute.
*/
const std::string Sql::getCreateStmnt(std::string const &tableName)
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
    Sqlite table drop statement getters.
    Returns a sqlite statement depending on
    tableName attribute.
*/
const std::string Sql::getDropStmnt(std::string const &tableName)
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
    Sqlite table insert statement getters.
    Returns a sqlite statement depending on
    tableName attribute.
*/
const std::string Sql::getInsertStmnt(std::string const &tableName)
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
    Various getters for system's sqlite statements
*/
const std::string Sql::getAddCustomerStmnt()
{
    return this->addCustomerStmnt;
}

const std::string Sql::getAddStaffStmnt()
{
    return this->addSystemAccessStaffStmnt;
}

const std::string Sql::getAddSkisSnowboardStmnt()
{
    return this->addSkisSnowboarsStmnt;
}

const std::string Sql::getAddAtvStmnt()
{
    return this->addAtvStmnt;
}

const std::string Sql::getValidateUsernameStmnt()
{
    return this->validateUsernameStmnt;
}

const std::string Sql::getValidateUnamePasswordStmnt()
{
    return this->validateUnamePasswordStmnt;
}

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

const std::string Sql::getCustomerSurname()
{
    return this->customerSurname;
}

const std::string Sql::getAtvMake()
{
    return this->atvMake;
}

const std::string Sql::getAtvModel()
{
    return this->atvModel;
}

const std::string Sql::getSkisSBsMake()
{
    return this->skisSBsMake;
}

const std::string Sql::getSkisSBsModel()
{
    return this->skisSBsModel;
}

const std::string Sql::getSalesRepID()
{
    return this->salesRepID;
}

const std::string Sql::getTotalSkis()
{
    return this->totalSkis;
}

const std::string Sql::getSkisForRent()
{
    return this->skisForRent;
}

const std::string Sql::getTotalSBsForRent()
{
    return this->totalSnowboards;
}

const std::string Sql::getSBsForRent()
{
    return this->snowboardsForRent;
}

const std::string Sql::getTotalAtvs()
{
    return this->totalATVs;
}

const std::string Sql::getATVsForRent()
{
    return this->ATVsForRent;
}

const std::string Sql::getTotalCustomers()
{
    return this->totalCustomers;
}

const std::string Sql::getTotalStaff()
{
    return this->totalStaff;
}

const std::string Sql::getTotalAccessStaff()
{
    return this->totalAppAccessStaff;
}

const std::string Sql::getChangeAvailabilityATVs()
{
    return this->changeAvailabilityATVs;
}

const std::string Sql::getChangeAvailabilitySkisSBs()
{
    return this->changeAvailabilitySkisSBs;
}

const std::string Sql::getAddToOrders()
{
    return this->addToOrdersStmnt;
}

const std::string Sql::getEquipmentTypeOnLoan()
{
    return this->equipmentTypeOnLoan;
}
const std::string Sql::getReturnDatetime()
{
    return this->returnDatetime;
}

const std::string Sql::getEquipmentIDsOnLoan(int type)
{
    if (type == 1)
    {
        return this->equipmentIDsOnLoanType1;
    }
    if (type == 2)
    {
        return this->equipmentIDsOnLoanType2;
    }
    if (type == 3)
    {
        return this->equipmentIDsOnLoanType3;
    }
}

const std::string Sql::getOrdersSum()
{
    return this->ordersSum;
}

const std::string Sql::getStaffIDs()
{
    return this->staffIDs;
}

const std::string Sql::getSystemAccessStaffIDs()
{
    return this->systemAccessStaffIDs;
}