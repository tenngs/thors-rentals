#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Sql.h"
#include "sqlite3.h"
#include "Utility.h"
#include "Display.h"
/*
    Displays "old school'loading'" type of text banner.
    Takes in message that will be displayed as an
    argument and prints characters one after the
    other under the message.
*/
void Display::displayBreakText(std::string const &text, bool clearScreen = false)
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
        // adjust 10000 value to display character
        // faster / slower
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
void Display::displayASCIIArtFromFile(std::string const &filename)
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
    Displays columns for snowboard equipment.
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

/*
    Displays available equipment for rent specified by tableName and
    type arguments, where:
    type 1 = skis
    type 2 = snowboards
    type 3 = ATVs

    And, where:
    tableName = inventory_skis_snowboards // skis & snowboards
    tableName = inventory_atvs // ATVs
*/
void Display::displayAvailableEquipment(std::string const &tableName, int const &type)
{
    sqlite3 *db;
    sqlite3_open("thors_rentals.db", &db);
    sqlite3_stmt *selectStmt;

    std::string sqlStmnt{};
    std::string strType{};
    strType = std::to_string(type);

    Sql sql;

    sqlStmnt = sql.getAvailableEquipV1() + tableName + sql.getAvailableEquipV2() + strType;

    if (sqlite3_prepare(db, sqlStmnt.c_str(), -1, &selectStmt, 0) == SQLITE_OK)
    {
        int ctotal = sqlite3_column_count(selectStmt);
        int res = 0;

        while (1)
        {
            res = sqlite3_step(selectStmt);
            if (res == SQLITE_ROW)
            {
                for (int i = 0; i < ctotal; i++)
                {

                    // read each column in row
                    // display each field and insert tab
                    std::string s = (char *)sqlite3_column_text(selectStmt, i);
                    std::cout << s << "\t";
                }
                std::cout << "\n";

            } // else - no equipment available

            if (res == SQLITE_DONE || res == SQLITE_ERROR)
            {
                break;
            }
        }
    }
}