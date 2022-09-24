#include <string>
#include <iostream>
#include <vector>
#include <unordered_set>
#include "sqlite3.h"
#include "Utility.h"
#include "Sql.h"
#include "Menu.h"
#include "Table.h"

/*
    Constructor
*/
Table::Table(std::string nameVal, std::string opTypeVal)
    : name{nameVal}, operationType{opTypeVal}
{
}
Table::Table()
{
}

/*
    Sqlite statement getter
*/
std::string Table::getSqlStatement()
{
    return this->sqlStmnt;
}

/*
    Table name getter
*/
std::string Table::getTableName()
{
    return this->name;
}

/*
    Table operation type getter
    "DROP", "CREATE", "INSERT INTO"
*/
std::string Table::getOperationType()
{
    return this->operationType;
}

/*
    Performs data operations on tables in thors_rentals DB.
    Takes as arguments an operation type ("DROP", "CREATE", "INSERT INTO"),
    tablename that the operation is conserned with and sqlite3 command
    for the operation, respectively. Boolean verbose is utilised
    to determine whether error/success message should be printed
    on screen.
    NOTE: sqlite3_exec is used to perform these operation because
    only test data - NOT user-entered data - is inserted during
    app initiation. Hence, no SQL injection opportunities exist.
*/
int Table::execTableOperation(std::string operationType, std::string tableName, std::string sql, bool verbose)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    // Open database
    rc = sqlite3_open("thors_rentals.db", &db);

    if (rc)
    {
        std::cout << "Can't open database: \n"
                  << sqlite3_errmsg(db);
        return 0;
    }
    else
    {
        if (verbose)
        {
            std::cout << "Thors_rentals DB opened successfully\n";
        }
    }

    // Execute SQL statement
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        std::cout << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }
    else
    {
        if (verbose)
        {
            std::cout << operationType << " operation on " << tableName << " table OK\n\n "
                      << std::endl;
        }
    }
    sqlite3_close(db);
    return 0;
}

/*
    Overloaded DB function that returns a Boolean
    depending on whether an argument std::string
    val1 is found in the DB in relation to the argument
    SQL statement. Utilised in whether a username
    or password exist in the DB matching the argument.
    Uses sqlite3_bind_text to bind user-entered data
    to prepared statements.

*/
bool Table::determineExistenceTextValuesInDB(std::string val1, std::string sqlStmnt)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("thors_rentals.db", &db);

    if (rc)
    {
        std::cout << "DB Error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
    }

    // use and construct prepared statement
    // because of user-entered data
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sqlStmnt.c_str(), sqlStmnt.length(), &stmt, nullptr);

    // bind user-specified values to SQL statement
    sqlite3_bind_text(stmt, 1, val1.c_str(), val1.length(), SQLITE_STATIC);

    // if query has result-rows and thefore a match is found
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return true;
    }
    else
    {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    }
}

/*
    Overloaded DB function that returns a Boolean
    depending on whether std::string arguments
    val1, val2 are found in the DB in relation to the argument
    SQL statement. Utilised in determining whether
    a username or password exist in the DB matching
    the arguments. Uses sqlite3_bind_text to bind user-entered data
    to prepared statements.

*/
bool Table::determineExistenceTextValuesInDB(std::string val1, std::string val2, std::string sqlStmnt)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("thors_rentals.db", &db);

    if (rc)
    {
        std::cout << "DB Error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
    }

    // use and construct prepared statement
    // because of user-entered data
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sqlStmnt.c_str(), sqlStmnt.length(), &stmt, nullptr);

    // bind user-specified values to SQL statement
    sqlite3_bind_text(stmt, 1, val1.c_str(), val1.length(), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, val2.c_str(), val2.length(), SQLITE_STATIC);

    // if query has result-rows and thefore a match is found
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return true;
    }
    else
    {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    }
}

/*
    Utilises std::vector<std::string> which should be filled with
    details to be inserted to a table. Loops over that
    collection, binds text to SQL statement and inserts data
    to a table in DB.
*/
void Table::appInsertTableOperation(std::string successMsg, std::vector<std::string> infoCollection, std::string sql)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc{};
    Utility utils;
    Menu mainMenu;

    rc = sqlite3_open("thors_rentals.db", &db);

    if (rc)
    {
        std::cout << "DB Error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
    }

    // Construct prepared statement
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, nullptr);

    // Bind user specified customer information
    // to SQL statement by iterating over infoCollection
    // string vector
    for (int index = 0; index < infoCollection.size(); ++index)
    {
        sqlite3_bind_text(stmt, index + 1, infoCollection[index].c_str(), infoCollection[index].length(), SQLITE_STATIC);
    }

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        std::cout << "Something went wrong: " << sqlite3_errmsg(db) << std::endl;
        std::cout << "Please try again" << std::endl;
        utils.pause(3);
    }
    else
    {
        std::cout << "\n\t" << successMsg << std::endl;
        utils.pause(3);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    system("cls");
    mainMenu.mainMenu();
}

void Table::appToOrdersTableFromOrder(std::string successMsg, std::vector<std::string> infoCollection, std::string sql)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc{};
    Utility utils;
    Menu mainMenu;

    rc = sqlite3_open("thors_rentals.db", &db);

    if (rc)
    {
        std::cout << "DB Error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
    }

    // Construct prepared statement
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, nullptr);

    // Bind user specified customer information
    // to SQL statement by iterating over infoCollection
    // string vector
    for (int index = 0; index < infoCollection.size(); ++index)
    {
        sqlite3_bind_text(stmt, index + 1, infoCollection[index].c_str(), infoCollection[index].length(), SQLITE_STATIC);
    }

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        std::cout << "Something went wrong: " << sqlite3_errmsg(db) << std::endl;
        std::cout << "Please try again" << std::endl;
        utils.pause(3);
    }
    else
    {
        std::cout << "\n\t" << successMsg << std::endl;
        utils.pause(3);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    system("cls");
    mainMenu.mainMenu();
}

int Table::searchNumericValuesFromDB(std::string sqlStmnt)

{
    int stat{};
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc{};
    sqlite3_stmt *stmt;

    Utility utils;

    rc = sqlite3_open("thors_rentals.db", &db);
    rc = sqlite3_prepare_v2(db, sqlStmnt.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        std::cout << "Something went wrong: " << sqlite3_errmsg(db) << std::endl;
        std::cout << "Please try again" << std::endl;
        utils.pause(3);
        return 1;
    }
    sqlite3_bind_int(stmt, 1, 1);
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        stat = sqlite3_column_int(stmt, 0);
    }
    if (rc != SQLITE_DONE)
    {
        std::cout << "Something went wrong: " << sqlite3_errmsg(db) << std::endl;
        std::cout << "Please try again" << std::endl;
        utils.pause(3);
        return 1;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return stat;
}

std::unordered_set<int> Table::getAvailableEquipmentIDs(std::string tableName, int type)
{
    std::string sqlStmnt{};
    std::string strType{};
    strType = std::to_string(type);
    Sql sql;

    sqlStmnt = sql.getAvailableEquipIDsV1() + tableName + sql.getAvailableEquipIDsV2() + strType;

    sqlite3 *db;
    std::unordered_set<int> validEquipmentIDs{};
    sqlite3_stmt *selectStmt;

    sqlite3_open("thors_rentals.db", &db);
    if (sqlite3_prepare(db, sqlStmnt.c_str(), -1, &selectStmt, 0) == SQLITE_OK)
    {
        // count number of columns in table
        int ctotal = sqlite3_column_count(selectStmt);
        int res = 0;

        while (true)
        {
            res = sqlite3_step(selectStmt);
            if (res == SQLITE_ROW)
            {

                for (int i = 0; i < ctotal; i++)
                {
                    // loop times the number of columns in table
                    int j = sqlite3_column_int(selectStmt, i);
                    if (j != 0)
                    {
                        validEquipmentIDs.insert(j);
                    }
                }
            }

            if (res == SQLITE_DONE || res == SQLITE_ERROR)
            {
                break;
            }
        }
    }
    return validEquipmentIDs;
}

double Table::calculateRentalCost(Order &initOrder)
{
    std::string sqlStmnt{};
    std::string tableName{};
    std::string duration{};
    std::string eqID{};
    double rentalPeriodCost;
    double totalRentalCost;
    int rentalDays = initOrder.getRental("days");
    int rentalHours = initOrder.getRental("hours");
    Table initRental;

    switch (initOrder.getEquipment("type"))
    {
    case 3:
        tableName = "inventory_atvs";
        break;
    default:
        tableName = "inventory_skis_snowboards";
        break;
    }

    switch (rentalDays)
    {
    case 0:
        duration = "PRICE_HOUR";
        break;

    default:
        duration = "PRICE_DAY";
        break;
    }

    sqlStmnt = "SELECT " + duration + " FROM " + tableName + " WHERE id = " + std::to_string(initOrder.getEquipment("id")) + ";";
    rentalPeriodCost = initRental.searchNumericValuesFromDB(sqlStmnt);

    if (duration == "PRICE_HOUR")
    {
        totalRentalCost = rentalPeriodCost * rentalHours;
    }
    else
    {
        totalRentalCost = rentalPeriodCost * rentalDays;
    }

    return totalRentalCost;
}

std::string Table::searchTextValuesFromDB(std::string sqlStmnt)

{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc{};
    sqlite3_stmt *stmt;

    size_t len;
    const unsigned char *uc;
    std::string textValue;

    Utility utils;

    rc = sqlite3_open("thors_rentals.db", &db);
    rc = sqlite3_prepare_v2(db, sqlStmnt.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        std::cout << "Something went wrong: " << sqlite3_errmsg(db) << std::endl;
        std::cout << "Please try again" << std::endl;
        utils.pause(3);
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        textValue = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
    }
    if (rc != SQLITE_DONE)
    {
        std::cout << "Something went wrong: " << sqlite3_errmsg(db) << std::endl;
        std::cout << "Please try again" << std::endl;
        utils.pause(3);
    }
    // TO DO: print const char* value
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return textValue;
}
