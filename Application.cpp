#include <string>
#include <iostream>

#include "sqlite3.h"
#include "Application.h"

Application::Application(std::string name_val)
    : name{name_val}
{
}

/*
Performs data operations on tables in thors_rentals DB.
Takes as arguments an operation name (drop, create, insert),
tablename that the operation is conserned with and sqlite3 command
for the operation, respectively.
NOTE: sqlite3_exec is used to perform these operation because
only test data - NOT user-entered data - is inserted during
app initiation. Hence, no SQL injection opportunities exist.
*/
int initTableOperation(std::string operation, std::string tableName, const char *sql, bool verbose)
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
    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        std::cout << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }
    else
    {
        if (verbose)
        {
            std::cout << operation << " operation on " << tableName << " table OK\n\n"
                      << std::endl;
        }
    }
    sqlite3_close(db);
    return 0;
}
