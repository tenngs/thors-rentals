#include <string>
#include <iostream>
#include "Application.h"
#include "Sql.h"
#include "Table.h"

int main()
{

    // init app, create and populate tables with test data
    Application app{"Thor's Tantalising Arctic Equipment Rental AKA Thor's Rentals"};
    Sql customersSqlStmnts;

    // drop customers table if exists
    Table customersDrop{"customers", "DROP"};
    customersDrop.tableOperation(customersDrop.getOperationType(), customersDrop.getTableName(), customersSqlStmnts.getDropStmnt(customersDrop.getTableName()), true);

    // create thors_rentals DB - this DB is used for all table operations
    // create customers table
    Table customersInit{"customers", "CREATE"};
    customersInit.tableOperation(customersInit.getOperationType(), customersInit.getTableName(), customersSqlStmnts.getCreateStmnt(customersInit.getTableName()), true);

    // insert test data into customers table
    Table customersInsert{"customers", "INSERT INTO"};
    customersInsert.tableOperation(customersInsert.getOperationType(), customersInsert.getTableName(), customersSqlStmnts.getInsertStmnt(customersInsert.getTableName()), true);

    // std::cout << customers.getSqlStatement() << std::endl;
    // if (Login::loginPrompt())
    // {
    //     // TO DO: call table operation function to change
    //     // logged on to 1 for the person who logged on

    //     Mainmenu::showMainMenu();
    // }
    // else
    // {
    //     // exit program
    //     Utility::shutdown();
    //     return 0;
    // }
}