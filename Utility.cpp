#include <windows.h>
#include <fstream>
#include <string>
#include <chrono>
#include <iostream>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <ctime>
#include "mingw.thread.h"
#include "sqlite3.h"
#include "Display.h"
#include "Sql.h"
#include "Table.h"
#include "Utility.h"

/*
    Sets cursor position on screen to xPos and yPos.
*/
void Utility::goToXY(int xPos, int yPos)
{
    COORD coord;
    coord.X = xPos;
    coord.Y = yPos;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/*
    Pauses execution for number of seconds determined
    by the function argument.
*/
void Utility::pause(int seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

/*
    Validates [Y/N] user input by utilising a set
    of valid answers.
    If user input is found in the set --> answer is valid.
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
    If user input is found in the set --> answer is valid.
*/
bool Utility::validateDigits(int digit, std::set<int> validDigits)
{

    {
        return validDigits.count(digit) == 1;
    }
}

/*
    Returns a lowercase version of an argument string.
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
    Reads a text file line-by-line and returns
    it as a string.
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
    terminated.
*/
void Utility::shutdown()
{
    Display disp;
    Utility utils;
    disp.displayBreakText("SHUTTING DOWN... PLEASE WAIT...", true);
    disp.displayASCIIArtFromFile("ASCIIArt/session_terminated.txt");
    // wait
    utils.pause(2);
    // clear screen
    system("cls");
    // display goodbye.txt
    disp.displayASCIIArtFromFile("ASCIIArt/goodbye.txt");
    // wait
    utils.pause(2);
}
std::string Utility::calculateReturnDatetime(Order &initOrder)
{

    // int days = initOrder.getRental("days");

    switch (initOrder.getRental("days"))
    {
    case 0:
        // hourly
        return Utility::getReturnDatetimeHourly(initOrder);
        break;

    default:
        // daily
        return Utility::getReturnDatetimeDaily(initOrder);
        break;
    }
}

/*
    A function to determine due back date and time
    when a customer rents equipment by the hour.
    Takes rental hours as an argument and returns
    due back date and time as YYYY-MM-DD HH:MM
    Where,
    YYYY = year
    MM = month
    DD = day
    HH = hour
    MM = minutes on the hour
*/
std::string Utility::getReturnDatetimeHourly(Order &initOrder)
{
    time_t rawtime;
    struct tm *timeinfo;
    char hourBuffer[80];
    char minBuffer[80];
    char dateBuffer[80];

    int currentHours{};
    int currentMins{};
    int rentalHours = initOrder.getRental("hours");

    std::string resultHours{};
    std::string resultMins{};

    std::set<int> zeroAddDigits;
    for (int i = 1; i < 10; ++i)
    {
        zeroAddDigits.insert(i);
    }

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(hourBuffer, sizeof(hourBuffer), "%H", timeinfo);
    strftime(minBuffer, sizeof(minBuffer), "%M", timeinfo);

    currentHours = std::stoi(hourBuffer);
    currentMins = std::stoi(minBuffer);

    Utility utils;

    if (currentHours + rentalHours == 9)
    {
        resultHours = "0" + std::to_string(currentHours + rentalHours);
    }
    else
    {
        resultHours = std::to_string(currentHours + rentalHours);
    }

    if (currentHours + rentalHours > 20)
    {
        // TO DO: RETURN NO RENTAL CAUSE SHOP AINT OPEN
    }

    if (utils.validateDigits(currentMins, zeroAddDigits))
    {
        resultMins = "0" + std::to_string(currentMins);
    }
    else
    {
        resultMins = std::to_string(currentMins);
    }

    return utils.getCurrentTimeDetails(4) + " " + resultHours + ":" + resultMins;
}

/*
    A function to determine due back date and time
    when a customer rents equipment by number of days.
    Takes rental start day, month, year and rental
    duration in days as arguments and returns
    due back date and time as YYYY-MM-DD HH:MM
    Where,
    YYYY = year
    MM = month
    DD = day
    HH = hour
    MM = minutes on the hour
    Takes in account leap years.
*/
std::string Utility::getReturnDatetimeDaily(Order &initOrder)
{
    Utility utils;
    int startYear = std::stoi(utils.getCurrentTimeDetails(1));  // year
    int startMonth = std::stoi(utils.getCurrentTimeDetails(2)); // month
    int startDay = std::stoi(utils.getCurrentTimeDetails(3));   // day

    int offset1 = utils.offsetDays(startDay, startMonth, startYear);
    int remDays = utils.isLeap(startYear) ? (366 - offset1) : (365 - offset1);

    int resultYear{};
    int offset2{}; // offset days in result year
    int resultMonth{};
    int resultDay{};
    int rentalDays = initOrder.getRental("days");

    std::string returnResultDay{};
    std::string returnResultMonth{};

    if (rentalDays <= remDays)
    {
        resultYear = startYear;
        offset2 = offset1 + rentalDays;
    }

    else
    {
        rentalDays -= remDays;
        resultYear = startYear + 1;
        int y2days = utils.isLeap(resultYear) ? 366 : 365;
        while (rentalDays >= y2days)
        {
            rentalDays -= y2days;
            resultYear++;
            y2days = utils.isLeap(resultYear) ? 366 : 365;
        }
        offset2 = rentalDays;
    }

    // Find values of day and month from
    // offset of result year.

    utils.revoffsetDays(offset2, resultYear, &resultDay, &resultMonth);

    if (resultDay >= 0 && resultDay < 10)
    {
        returnResultDay = "0" + std::to_string(resultDay);
    }
    else
    {
        returnResultDay = std::to_string(resultDay);
    }

    if (resultMonth >= 1 && resultMonth < 10)
    {
        returnResultMonth = "0" + std::to_string(resultMonth);
    }
    else
    {
        returnResultMonth = std::to_string(resultMonth);
    }

    return std::to_string(resultYear) + "-" + returnResultMonth + "-" + returnResultDay + " " + utils.getCurrentTime();
}

/*
    A function to determine current month, day, year
    or year+month+day by function argument,
    Arguments return values as follows:

    1 = year (YYYY)
    2 = month (MM)
    3 = day (DD)
    4 = year-month-day (YYYY-MM-DD)
*/
std::string Utility::getCurrentTimeDetails(int type)
{
    std::set<int> zeroAddDigits;
    for (int i = 1; i < 10; ++i)
    {
        zeroAddDigits.insert(i);
    }

    std::string resultMonth{};
    std::string resultDay{};
    std::string resultYear{};

    Utility utils;
    // current date/time based on current system
    time_t now = time(0);
    tm *ltm = localtime(&now);

    if (utils.validateDigits((1 + ltm->tm_mon), zeroAddDigits))
    {
        resultMonth = "0" + std::to_string(1 + ltm->tm_mon);
    }
    else
    {
        resultMonth = std::to_string(1 + ltm->tm_mon);
    }

    if (utils.validateDigits((ltm->tm_mday), zeroAddDigits))
    {
        resultDay = "0" + std::to_string(ltm->tm_mday);
    }
    else
    {
        resultDay = std::to_string(ltm->tm_mday);
    }
    resultYear = std::to_string(1900 + ltm->tm_year);

    // return by argument type
    // 1 - year, 2 - month, 3 - day, 4 - combination
    switch (type)
    {
    case 1:
        return resultYear;
    case 2:
        return resultMonth;
    case 3:
        return resultDay;
    case 4:
        return resultYear + "-" + resultMonth + "-" + resultDay;
    }
}

// determine a leap year from an input year
bool Utility::isLeap(int y)
{
    if (y % 100 != 0 && y % 4 == 0 || y % 400 == 0)
        return true;

    return false;
}

// Given a date, returns number of days elapsed
// from the  beginning of the current year (1st
// jan).
int Utility::offsetDays(int day, int month, int year)
{
    Utility utils;
    int offset = day;

    switch (month - 1)
    {
    case 11:
        offset += 30;
    case 10:
        offset += 31;
    case 9:
        offset += 30;
    case 8:
        offset += 31;
    case 7:
        offset += 31;
    case 6:
        offset += 30;
    case 5:
        offset += 31;
    case 4:
        offset += 30;
    case 3:
        offset += 31;
    case 2:
        offset += 28;
    case 1:
        offset += 31;
    }

    if (utils.isLeap(year) && month > 2)
        offset += 1;

    return offset;
}

// Given a year and days elapsed in it, finds
// date by storing results in d and m.
void Utility::revoffsetDays(int offset, int year, int *day, int *month1)
{
    int month[13] = {0, 31, 28, 31, 30, 31, 30,
                     31, 31, 30, 31, 30, 31};

    Utility utils;
    if (utils.isLeap(year))
        month[2] = 29;

    int i;
    for (i = 1; i <= 12; i++)
    {
        if (offset <= month[i])
            break;
        offset = offset - month[i];
    }

    *day = offset;
    *month1 = i;
}

void Utility::setOrderDetails(Order &initOrder)
{
    std::string strCustomerID{std::to_string(initOrder.getID("customer"))};
    std::string strEquipmentID{std::to_string(initOrder.getEquipment("id"))};

    Utility utils;
    Table initRental;
    Sql sql;

    // calculate total rental cost
    initOrder.setRental(initRental.calculateRentalCost(initOrder));
    // set return datetime
    initOrder.setReturnDateTime(utils.calculateReturnDatetime(initOrder));

    initOrder.setName("first", initRental.searchTextValuesFromDB(sql.getCustomerFirstName() + strCustomerID));
    initOrder.setName("last", initRental.searchTextValuesFromDB(sql.getCustomerSurname() + strCustomerID));

    if (initOrder.getEquipment("type") == 3)
    {
        initOrder.setEquipmentStyle("make", initRental.searchTextValuesFromDB(sql.getAtvMake() + strEquipmentID));
        initOrder.setEquipmentStyle("model", initRental.searchTextValuesFromDB(sql.getAtvModel() + strEquipmentID));
    }
    else
    {
        initOrder.setEquipmentStyle("make", initRental.searchTextValuesFromDB(sql.getSkisSBsMake() + strEquipmentID));
        initOrder.setEquipmentStyle("model", initRental.searchTextValuesFromDB(sql.getSkisSBsModel() + strEquipmentID));
    }

    initOrder.setSalesRepID(initRental.searchNumericValuesFromDB(sql.getSalesRepID()));
}

void Utility::addOrderDetails(Order &initOrder)
{
    // grab all order details from Order
    std::vector<std::string> equipmentInfo{};
    equipmentInfo.insert()

        sqlStmnt = sql.getAddAtvStmnt();

    inventory.appInsertTableOperation(successMsg, equipmentInfo, equipmentInfo.size(), sqlStmnt);
    // add them to orders table
    // cout message that rental is complete
    // delete Order
}
