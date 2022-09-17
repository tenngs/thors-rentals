#include <windows.h>
#include <fstream>
#include <string>
#include <chrono>
#include <unordered_set>
#include <set>
#include <algorithm>
#include "mingw.thread.h"
#include "Display.h"

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

/*
    Reads a (text) file line-by-line and returns
    it as a string
*/
std::string Utility::getContents(std::ifstream &file)
{
    std::string lines = "";
    if (file)
    {
        while (file.good())
        {
            std::string temp;
            std::getline(file, temp);
            temp += "\n";

            lines += temp;
        }
        return lines;
    }
    else
    {
        return "File does not exist - check maybe?";
    }
}

/*
    Displays "old school SHUTTING DOWN...." message and
    ASCII art informing a user that their session is
    terminated
*/
void Utility::shutdown()
{
    Display disp;
    Utility utils;
    disp.displayBreakText("SHUTTING DOWN... PLEASE WAIT...", true);
    disp.displayASCIIFromFile("ASCIIArt/session_terminated.txt");
    // wait
    utils.pause(2);
    // clear screen
    system("cls");
    // display goodbye.txt
    disp.displayASCIIFromFile("goodbye.txt");
    // wait
    utils.pause(2);
}