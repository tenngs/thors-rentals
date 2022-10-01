#include <string>
#include "Order.h"

// getters
int Order::getID(std::string const &type)
{
    if (type == "sales")
    {
        return this->salesRepID;
    }
    if (type == "customer")
    {
        return this->customerID;
    }
}

std::string Order::getName(std::string const &type)
{
    if (type == "first")
    {
        return this->customerFirstName;
    }
    if (type == "last")
    {
        return this->customerSurname;
    }
}

int Order::getEquipment(std::string const &choice)
{
    if (choice == "type")
    {
        return this->equipmentType;
    }
    if (choice == "id")
    {
        return this->equipmentID;
    }
}

std::string Order::getEquipmentStyle(std::string const &choice)

{
    if (choice == "make")
    {
        return this->equipmentMake;
    }
    if (choice == "model")
    {
        return this->equipmentModel;
    }
}

int Order::getRental(std::string const &type)
{
    if (type == "hours")
    {
        return this->rentalHours;
    }
    if (type == "days")
    {
        return this->rentalDays;
    }
}

double Order::getRental()
{
    return this->rentalCost;
}

std::string Order::getReturnDateTime()
{
    return this->returnDateTime;
}

int Order::getSalesRepID()
{
    return this->salesRepID;
}

// setters
void Order::setID(std::string const &type, int const &ID)
{
    if (type == "sales")
    {
        this->salesRepID = ID;
    }
    if (type == "customer")
    {
        this->customerID = ID;
    }
}

void Order::setName(std::string const &type, std::string const &name)
{
    if (type == "first")
    {
        this->customerFirstName = name;
    }
    if (type == "last")
    {
        this->customerSurname = name;
    }
}

void Order::setEquipment(std::string const &type, int const &value)
{
    if (type == "type")
    {
        this->equipmentType = value;
    }
    if (type == "id")
    {
        this->equipmentID = value;
    }
}

void Order::setEquipmentStyle(std::string const &type, std::string const &value)
{
    if (type == "make")
    {
        this->equipmentMake = value;
    }
    if (type == "model")
    {
        this->equipmentModel = value;
    }
}

void Order::setRental(std::string const &type, int const &value)
{
    if (type == "hours")
    {
        this->rentalHours = value;
    }
    if (type == "days")
    {
        this->rentalDays = value;
    }
}

void Order::setRental(double const &cost)
{
    this->rentalCost = cost;
}

void Order::setReturnDateTime(std::string const &time)
{
    this->returnDateTime = time;
}

void Order::setSalesRepID(int const &id)
{
    this->salesRepID = id;
}
