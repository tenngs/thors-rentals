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
}

std::string Sql::getDropStmnt(std::string tableName)
{
    if (tableName == "customers")
    {
        return this->customersDropStmnt;
    }
}

std::string Sql::getInsertStmnt(std::string tableName)
{
    if (tableName == "customers")
    {
        return this->customersInsertStmnt;
    }
}

// std::string Sql::getcustomersInitInsert()
// {
//     return this->customersInitInsert;
// }