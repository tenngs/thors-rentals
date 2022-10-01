/*
    Provides a class where current Order details
    are stored. Other classes utilise this class
    to get information about a current order.
    Current order is defined as a rental order
    that a user is currently completing. Previous
    orders that are given a STATUS of 0 (open)
*/
#pragma once

class Order
{
    // order's attributes
    // setters and getters are used to retrieve or
    // manipulate these variables
private:
    int salesRepID;
    int customerID;
    std::string customerFirstName;
    std::string customerSurname;
    int equipmentType;
    int equipmentID;
    std::string equipmentMake;
    std::string equipmentModel;
    int rentalHours;
    int rentalDays;
    int rentalCost;
    std::string returnDateTime;

public:
    // getters
    int getOrderID();
    int getID(std::string const &type);
    std::string getName(std::string const &type);
    int getEquipment(std::string const &choice);
    std::string getEquipmentStyle(std::string const &choice);
    int getRental(std::string const &type);
    double getRental();
    std::string getReturnDateTime();
    std::string getEquipmentStyle();
    int getSalesRepID();

    // setters
    void setID(std::string const &type, int const &ID);
    void setName(std::string const &type, std::string const &name);
    void setEquipment(std::string const &type, int const &value);
    void setEquipmentStyle(std::string const &choice, std::string const &value);
    void setRental(std::string const &type, int const &value);
    void setRental(double const &cost);
    void setReturnDateTime(std::string const &time);
    void setSalesRepID(int const &id);
};
