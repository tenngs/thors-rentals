#pragma once

class Order
{
private:
    // int orderID{0};
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
    // getters for all
    int getOrderID();
    int getID(std::string type);
    std::string getName(std::string type);
    int getEquipment(std::string choice);
    std::string getEquipmentStyle(std::string choice);
    int getRental(std::string type);
    double getRental();
    std::string getReturnDateTime();
    std::string getEquipmentStyle();
    int getSalesRepID();

    // setters for all
    void setID(std::string type, int ID);
    void setName(std::string type, std::string name);
    void setEquipment(std::string type, int value);
    void setEquipmentStyle(std::string choice, std::string value);
    void setRental(std::string type, int value);
    void setRental(double cost);
    void setReturnDateTime(std::string time);
    void setSalesRepID(int id);
    // void incrementOrderID();
    // void decrementOrderID();
};
