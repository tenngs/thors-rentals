#pragma once

class Order
{
private:
    int orderID;
    int salesRepID;
    int customerID;
    std::string customerFirstName;
    std::string customerSurname;
    int equipmentType;
    int equipmentID;
    int rentalHours;
    int rentalDays;
    int rentalCost;
    std::string returnDateTime;

public:
    // const std::string getCreateStmnt(std::string tableName);

    // getters for all
    int getID(std::string type);
    std::string getName(std::string type);
    int getEquipment(std::string type);
    int getRental(std::string type);
    double getRental();
    std::string getReturnDateTime();

    // setters for all
    SetID(std::string type, int ID);
    setName(std::string type, std::string name);
    setEquipment(std::string type, int value);
    setRental(std::string type, int value);
    setRental(double cost);
    setReturnDateTime(std::string time);
};
