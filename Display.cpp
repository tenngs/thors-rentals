#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Utility.h"
#include "Display.h"
/*
    Displays "old school'loading'" type of text banner.
    Takes in message that will be displayed as an
    argument and prints characters one after the
    other under the message.
*/
void Display::displayBreakText(std::string text, bool clearScreen = false)
{
    if (clearScreen)
    {
        system("cls");
    }

    int numChars = text.length();
    int c;
    Utility utils;
    utils.goToXY(50, 25);
    std::cout << text;

    utils.goToXY(50, 27);
    for (int i = 1; i <= numChars; i++)
    {
        // adjust 100000000 value to display character
        // faster / slower
        // dev env: 2 0s removed
        for (int j = 0; j <= 10000; j++)
            ;
        printf("%c", 177);
    }
    Sleep(500);
    system("cls");
}

/*
    Displays ASCII art from .txt file.
*/
void Display::displayASCIIArtFromFile(std::string filename)
{
    Utility utils;
    std::ifstream Reader(filename);
    std::string userIDArt = utils.getContents(Reader);
    Reader.close();
    std::cout << userIDArt << std::endl;
}

/*
    Displays columns for ATV equipment.
*/
void Display::displayATVTableColumns()
{
    std::cout << "\n\n";
    std::cout << "ID\t"
              << "MAKE\t"
              << "MODEL\t\t"
              << "REG\t\t"
              << "FUEL\t"
              << "HOURLY\t"
              << "DAILY\t"
              << "TYPE\t"
              << "AVAILABLE\n\n";
}

/*
    Displays columns for Snowboard equipment.
*/
void Display::displaySnowboardTableColumns()
{
    std::cout << "\n\n";
    std::cout << "ID\t"
              << "MAKE\t\t"
              << "MODEL\t\t"
              << "HOURLY\t"
              << "DAILY\t"
              << "TYPE\t"
              << "AVAILABLE\n\n";
}

/*
    Displays columns for ski equipment.
*/
void Display::displaySkiTableColumns()
{
    std::cout << "\n\n";
    std::cout << "ID\t"
              << "MAKE\t"
              << "MODEL\t"
              << "HOURLY\t"
              << "DAILY\t"
              << "TYPE\t"
              << "AVAILABLE\n\n";
}