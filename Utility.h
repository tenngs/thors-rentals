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