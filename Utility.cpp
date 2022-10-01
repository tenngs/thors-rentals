#include <windows.h>
#include <fstream>
#include <string>
#include <chrono>
#include <iostream>
#include <vector>
#include <regex>
#include <unordered_set>
#include <set>
#include <algorithm>
#include "stdlib.h"
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
void Utility::goToXY(int const &xPos, int const &yPos)
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
void Utility::pause(int const &seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}
/*
    Validates [Y/N] user input by utilising a set
    of valid answers.
    If user input is found in the set --> answer is valid.
*/
bool Utility::validateYesOrNo(std::string const &word)
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
bool Utility::validateDigits(int const &digit, std::set<int> const &validDigits)
{

    {
        return validDigits.count(digit) == 1;
    }
}
/*
    Returns a lowercase version of an argument string.
*/
std::string Utility::lowerStr(std::string &str)
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
    utils.pause(2);
    system("cls");
    disp.displayASCIIArtFromFile("ASCIIArt/goodbye.txt");
    utils.pause(2);
    exit(0);
}
/*
    Determines which fuction is utilised to calculate
    a return datetime for rental equipment depending
    whether rental duration is measured in days or hours.
    Returns rental duration datetime as a std::string
*/
std::string Utility::calculateReturnDatetime(Order &initOrder)
{
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
        // Note: Thor's rentals is a 24h/day business
        // if it would instead close at 20:00 hours,
        // a return statement stating that equipment
        // can not be rented as the return time is
        // past shop's daily closing time should be
        // added here. Adjust the value that is currently
        // 20 to customise shop's closing time
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
    int type arguments return values as follows:

    1 = year (YYYY)
    2 = month (MM)
    3 = day (DD)
    4 = year-month-day (YYYY-MM-DD)
*/
std::string Utility::getCurrentTimeDetails(int const &type)
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
/*
    Determines whether argument int year is
    a leap year.
*/
bool Utility::isLeap(int &year)
{
    if (year % 100 != 0 && year % 4 == 0 || year % 400 == 0)
    {
        return true;
    }
    return false;
}
/*
    Given a date as arguments day, month, year,
    returns number of days elapsed from the beginning
    of current year.
*/
int Utility::offsetDays(int &day, int &month, int &year)
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
/*
    Given a year and days elapsed in it (int year, int offset),
    finds date by storing results in day and month1.
*/
void Utility::revoffsetDays(int &offset, int &year, int *day, int *month1)
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
/*
    Sets current order details to Order class.
*/
void Utility::setOrderDetails(Order &initOrder)
{
    std::string strCustomerID{std::to_string(initOrder.getID("customer"))};
    std::string strEquipmentID{std::to_string(initOrder.getEquipment("id"))};

    Utility utils;
    Table initRental;
    Sql sql;

    // calculate and set total rental cost
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
/*
    Gets current order details from Order class and inserts them to orders table
    in thors_rentals DB.
*/
void Utility::addOrderDetails(Order &initOrder)
{
    Sql sql;
    std::string sqlStmnt{};
    std::string successMsg{"Thor is very happy! Rental process is complete!"};
    Table orders{"INSERT INTO", "orders"};
    std::vector<std::string> orderDetails;

    std::string salesRepID{std::to_string(initOrder.getID("sales"))};
    std::string customerID{std::to_string(initOrder.getID("customer"))};
    std::string equipmentType{std::to_string(initOrder.getEquipment("type"))};
    std::string equipmentID{std::to_string(initOrder.getEquipment("id"))};
    std::string rentalHours{std::to_string(initOrder.getRental("hours"))};
    std::string rentalDays{std::to_string(initOrder.getRental("days"))};
    std::string rentalCost{std::to_string(initOrder.getRental())};
    std::string returnDateTime{initOrder.getReturnDateTime() + ".000"};
    std::string status{std::to_string(1)};
    // status 1 = rental "open" (equipment on loan)
    // status 0 = rental "closed" (equipment returned)

    orderDetails.push_back(salesRepID);
    orderDetails.push_back(customerID);
    orderDetails.push_back(equipmentType);
    orderDetails.push_back(equipmentID);
    orderDetails.push_back(rentalHours);
    orderDetails.push_back(rentalDays);
    orderDetails.push_back(rentalCost);
    orderDetails.push_back(returnDateTime);
    orderDetails.push_back(status);

    orders.appInsertTableOperation(successMsg, orderDetails, sql.getAddToOrders());
}
/*
    Takes in std::unordered_set<int> and returns it as std::set<int>
    Ie. makes an unordered set to a set.
*/
std::set<int> Utility::unorderedToOrdered(std::unordered_set<int> notOrderedSet)
{
    std::set<int> s;
    for (auto val : notOrderedSet)
    {
        s.insert(val);
    }
    return s;
}
/*
    Uses regex to determine whether argument std::string is valid
    UK postcode.
*/
bool Utility::postcodeCheck(std::string const &postcode)
{
    std::regex postcodePattern("^((([a-zA-Z][0-9])|([a-zA-Z][0-9]{2})|([a-zA-Z]{2}[0-9])|([a-zA-Z]{2}[0-9]{2})|([A-Za-z][0-9][a-zA-Z])|([a-zA-Z]{2}[0-9][a-zA-Z]))(\\s*[0-9][a-zA-Z]{2})$)");
    return regex_match(postcode, postcodePattern);
}
/*
    Uses regex to determine whether argument std::string is valid
    email address.
*/
bool Utility::emailCheck(std::string const &email)
{
    std::regex emailPattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(email, emailPattern);
}
/*
    Returns argument std::string as all uppercase std::string.
*/
std::string Utility::toUpperCase(std::string &str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}
/*
    Checks whether argument std::string contains only letters
    and whitespace characters.
*/
bool Utility::lettersAndSpacesOnly(std::string const &input)
{
    for (auto &i : input) // check each character in the input string
    {
        // is it an alphabetical character or whitespace?
        if (!(std::isalpha(i) || (std::isspace(i))))
            return false;
    }
    return true;
}
/*
    Checks whether argument std::string contains
    whitespace characters.
*/
bool Utility::noSpacesOnly(std::string const &input)
{
    for (auto &i : input) // check each character in the input string
    {
        // is it whitespace?
        if (std::isspace(i))
            return false;
    }
    return true;
}
/*
    Checks whether argument std::string contains
    only letters.
*/
bool Utility::lettersOnly(std::string const &input)
{
    for (auto &i : input) // check each character in the input string
    {
        // is it an alphabetical character or whitespace?
        if (!(std::isalpha(i)))
        {
            return false;
        }
    }
    return true;
}
/*
    Capitalises each first letter of argument std::string
    and returns it.
*/
std::string Utility::capitaliseAllFirstLetters(std::string &input)
{
    for (int x = 0; x < input.length(); x++)
    {
        if (x == 0)
        {
            input[x] = toupper(input[x]);
        }
        else if (input[x - 1] == ' ')
        {
            input[x] = toupper(input[x]);
        }
    }

    return input;
}

/*
    inserts IDs that are valid staff IDs, but do NOT have
    system access to std::unordered_set<int> and returns
    it. For example:
    Staff IDs:                  1, 2, 3, 4, 5
    System access staff IDs:    1, 2, 3
    returns validStaffIDs:      4, 5
*/
std::unordered_set<int> Utility::getValidStaffIDS(std::unordered_set<int> staffIDs, std::unordered_set<int> systemAccessStaffIDs)
{
    std::unordered_set<int> validStaffIDs{};

    for (auto num : staffIDs)
    {
        if (systemAccessStaffIDs.find(num) == systemAccessStaffIDs.end())
        {
            validStaffIDs.insert(num);
        }
    }
    return validStaffIDs;
}