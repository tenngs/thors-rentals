/*
    This class contains general utility functions in relation
    to various system requirements. It is a "catch all"
    class whereas functions that do not distinctly belong
    to any class or if it is considered that it is
    inefficient to form a class just for a specific function
    or a small number of functions.
*/
#pragma once

#include <set>
#include <unordered_set>
#include "Order.h"

class Utility
{
private:
public:
    void goToXY(int xPos, int yPos);
    void pause(int seconds);
    bool validateYesOrNo(std::string word);
    std::string lowerStr(std::string str);
    bool validateDigits(int digit, std::set<int> validDigits);
    std::string getCurrentTime();
    std::string getContents(std::ifstream &file);
    void shutdown();
    std::string calculateReturnDatetime(Order &initOrder);
    std::string getReturnDatetimeHourly(Order &initOrder);
    std::string getReturnDatetimeDaily(Order &initOrder);
    std::string getCurrentTimeDetails(int type);
    bool isLeap(int);
    int offsetDays(int d, int m, int y);
    void revoffsetDays(int offset, int year, int *day, int *month1);
    void setOrderDetails(Order &initOrder);
    void addOrderDetails(Order &initOrder);
    std::set<int> unorderedToOrdered(std::unordered_set<int> us);
    bool postcodeCheck(std::string postcode);
    bool emailCheck(std::string email);
    std::string toUpperCase(std::string str);
};