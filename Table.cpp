#include <string>
#include <iostream>
#include "sqlite3.h"
#include "Table.h"

/*
    Constructor
*/
Table::Table(std::string nameVal, std::string opTypeVal)
    : name{nameVal}, operationType{opTypeVal}
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
int Table::tableOperation(std::string operationType, std::string tableName, std::string sql, bool verbose)
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
