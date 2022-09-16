#include <string>
#include <iostream>
#include "Application.h"
#include "Sql.h"
#include "Table.h"

int main()
{

    // init app, create and populate tables with test data
    Application app{"Thor's Tantalising Arctic Equipment Rental AKA Thor's Rentals"};
    Sql sql;

    // tableOperation(std::string operationType, std::string tableName, std::string sql, bool verbose)
    // DROP TABLES
    Table customersDrop{"customers", "DROP"};
    customersDrop.tableOperation(customersDrop.getOperationType(), customersDrop.getTableName(), sql.getDropStmnt(customersDrop.getTableName()), true);

    Table ordersDrop{"orders", "DROP"};
    ordersDrop.tableOperation(ordersDrop.getOperationType(), ordersDrop.getTableName(), sql.getDropStmnt(ordersDrop.getTableName()), true);

    Table system_accessDrop{"system_access", "DROP"};
    system_accessDrop.tableOperation(system_accessDrop.getOperationType(), system_accessDrop.getTableName(), sql.getDropStmnt(system_accessDrop.getTableName()), true);

    Table staffDrop{"staff", "DROP"};
    staffDrop.tableOperation(staffDrop.getOperationType(), staffDrop.getTableName(), sql.getDropStmnt(staffDrop.getTableName()), true);

    // CREATE TABLES
    Table customersCreate{"customers", "CREATE"};
    customersCreate.tableOperation(customersCreate.getOperationType(), customersCreate.getTableName(), sql.getCreateStmnt(customersCreate.getTableName()), true);

    Table ordersCreate{"orders", "CREATE"};
    ordersCreate.tableOperation(ordersCreate.getOperationType(), ordersCreate.getTableName(), sql.getCreateStmnt(ordersCreate.getTableName()), true);

    Table system_accessCreate{"system_access", "CREATE"};
    system_accessCreate.tableOperation(system_accessCreate.getOperationType(), system_accessCreate.getTableName(), sql.getCreateStmnt(system_accessCreate.getTableName()), true);

    Table staffCreate{"staff", "CREATE"};
    staffCreate.tableOperation(staffCreate.getOperationType(), staffCreate.getTableName(), sql.getCreateStmnt(staffCreate.getTableName()), true);

    // INSERT INTO TABLES
    Table customersInsert{"customers", "INSERT INTO"};
    customersInsert.tableOperation(customersInsert.getOperationType(), customersInsert.getTableName(), sql.getInsertStmnt(customersInsert.getTableName()), true);

    Table system_accessInsert{"system_access", "INSERT INTO"};
    system_accessInsert.tableOperation(system_accessInsert.getOperationType(), system_accessInsert.getTableName(), sql.getInsertStmnt(system_accessInsert.getTableName()), true);

    Table staffInsert{"staff", "INSERT INTO"};
    staffInsert.tableOperation(staffInsert.getOperationType(), staffInsert.getTableName(), sql.getInsertStmnt(staffInsert.getTableName()), true);

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
