#include <string>
#include "Order.h"

// GETTERS
// int Order::getOrderID()
// {
//     return this->orderID;
// }

int Order::getID(std::string type)
{
    // if (type == "order")
    // {
    //     return this->orderID;
    // }
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

int Order::getEquipment(std::string choice)
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

std::string Order::getEquipmentStyle(std::string choice)

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

std::string Order::getReturnDateTime()
{
    return this->returnDateTime;
}

int Order::getSalesRepID()
{
    return this->salesRepID;
}

// SETTERS
void Order::setID(std::string type, int ID)
{
    // if (type == "order")
    // {
    //     this->orderID = ID;
    // }
    if (type == "sales")
    {
        this->salesRepID = ID;
    }
    if (type == "customer")
    {
        this->customerID = ID;
    }
}

void Order::setName(std::string type, std::string name)
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

void Order::setEquipment(std::string type, int value)
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

void Order::setEquipmentStyle(std::string type, std::string value)
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

void Order::setRental(std::string type, int value)
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

void Order::setRental(double cost)
{
    this->rentalCost = cost;
}

void Order::setReturnDateTime(std::string time)
{
    this->returnDateTime = time;
}

void Order::setSalesRepID(int id)
{
    this->salesRepID = id;
}

// void Order::incrementOrderID()
// {
//     this->orderID++;
// }

// void Order::decrementOrderID()
// {
//     this->orderID--;
// }
