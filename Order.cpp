#include <string>
#include "Order.h"

// GETTERS
int Order::getID(std::string type)
{
    if (type == "order")
    {
        return this->orderID;
    }
    if (type == "sales")
    {
        return this->salesRepID;
    }
    if (type == "customer")
    {
        return this->customerID;
    }
}

std::string Order::getName(std::string type)
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

int Order::getEquipment(std::string type)
{
    if (type == "type")
    {
        return this->equipmentType;
    }
    if (type == "id")
    {
        return this->equipmentID;
    }
}

int Order::getRental(std::string type)
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

std::string getReturnDateTime()
{
    return this->returnDateTime;
}

// SETTERS
int Order::setID(std::string type, int ID)
{
    if (type == "order")
    {
        this->orderID = ID;
    }
    if (type == "sales")
    {
        this->salesRepID = ID;
    }
    if (type == "customer")
    {
        this->customerID = ID;
    }
}

Order::setName(std::string type, std::string name)
{
    if (name == "first")
    {
        this->customerFirstName = name;
    }
    if (name == "last")
    {
        this->customerSurname = name;
    }
}

Order::setEquipment(std::string type, int value)
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

Order::setRental(std::string type, int value)
{
    if (type == "hours")
    {
        this->rentalHours = value;
    }
    if (type == "days")
    {
        return this->rentalDays;
    }
}

Order::setRental(double cost)
{
    this->rentalCost = cost;
}

Order::setReturnDateTime(std::string time)
{
    this->returnDateTime = time;
}