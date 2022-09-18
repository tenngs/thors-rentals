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

class Utility
{
private:
public:
    void gotoXY(int xPos, int yPos);
    void pause(int seconds);
    bool validateYesOrNo(std::string word);
    std::string lowerStr(std::string str);
    bool validateDigits(int digit, std::set<int> validDigits);
    std::string getCurrentTime();
    std::string getContents(std::ifstream &file);
    void shutdown();
};