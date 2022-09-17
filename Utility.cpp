#include <windows.h>
#include <fstream>
#include <string>
#include <chrono>
#include <unordered_set>
#include <set>
#include <algorithm>
#include "mingw.thread.h"

#include "Utility.h"

/*
    Sets cursor position on screen to xPos and yPos
*/
void Utility::gotoXY(int xPos, int yPos)
{
    COORD coord;
    coord.X = xPos;
    coord.Y = yPos;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/*
    Pauses execution for number of seconds determined
    by the function argument
*/
void Utility::pause(int seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

/*
    Validates [Y/N] user input by utilising a set
    of valid answers.
    If user input is found in the set --> answer is valid
*/
bool Utility::validateYesOrNo(std::string word)
{

    {
        const static std::unordered_set<std::string> validWords({"Y", "N", "y", "n"});
        return validWords.count(word) == 1;
    }
}

/*
    Validates user-entered numeric input by utilising a set
    of valid numbers.
    If user input is found in the set --> answer is valid
*/
bool Utility::validateDigits(int digit, std::set<int> validDigits)
{

    {
        return validDigits.count(digit) == 1;
    }
}

/*
    Returns a lowercase version of an argument string
*/
std::string Utility::lowerStr(std::string str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

/*
    Function to determine current time from
    system clock.
    Returns the time as std::string in
    HH:MM format.
    Where,

    HH = hour
    MM = minutes on the hour
*/

std::string Utility::getCurrentTime()
{
    time_t rawtime;
    struct tm *timeinfo;
    char hourBuffer[80];
    char minBuffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(hourBuffer, sizeof(hourBuffer), "%H", timeinfo);
    strftime(minBuffer, sizeof(minBuffer), "%M", timeinfo);

    std::string strHours(hourBuffer);
    std::string strMins(minBuffer);

    return strHours + ":" + strMins;
}