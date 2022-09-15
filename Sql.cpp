#include <string>
#include "Sql.h"

// constructor
// Sql::Sql(std::customersCreate)
//     : name{name_val}
// {
// }

// SQL getters
std::string Sql::getCustomersCreate()
{
    return this->customersCreate;
}

std::string Sql::getCustomersInsert()
{
    return this->customersInsert;
}