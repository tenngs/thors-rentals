/*
    Contains general utility functions in relation
    to various system requirements. It is a "catch all"
    class containing functions that do not distinctly belong
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
    void goToXY(int const &xPos, int const &yPos);
    void pause(int const &seconds);
    bool validateYesOrNo(std::string const &word);
    std::string lowerStr(std::string &str);
    bool validateDigits(int const &digit, std::set<int> const &validDigits);
    std::string getCurrentTime();
    std::string getContents(std::ifstream &file);
    void shutdown();
    std::string calculateReturnDatetime(Order &initOrder);
    std::string getReturnDatetimeHourly(Order &initOrder);
    std::string getReturnDatetimeDaily(Order &initOrder);
    std::string getCurrentTimeDetails(int const &type);
    bool isLeap(int &year);
    int offsetDays(int &day, int &month, int &year);
    void revoffsetDays(int &offset, int &year, int *day, int *month1);
    void setOrderDetails(Order &initOrder);
    void addOrderDetails(Order &initOrder);
    std::set<int> unorderedToOrdered(std::unordered_set<int> notOrderedSet);
    bool postcodeCheck(std::string const &postcode);
    bool emailCheck(std::string const &email);
    std::string toUpperCase(std::string &str);
    bool lettersAndSpacesOnly(std::string const &input);
    bool noSpacesOnly(std::string const &input);
    bool lettersOnly(std::string const &input);
    std::string capitaliseAllFirstLetters(std::string &input);
    std::unordered_set<int> getValidStaffIDS(std::unordered_set<int> staffIDs, std::unordered_set<int> systemAccessStaffIDs);
};