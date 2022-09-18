#include <string>
#include <iostream>
#include "Table.h"
#include "Sql.h"
#include "Display.h"
#include "InitApplication.h"

/*
    Constuctor that initialises app's name
    and calls another function to drop, initialise
    and populate system's tables and to display
    a "loading" text and login ASCII art banner.

*/
InitApplication::InitApplication(std::string name_val)
    : name{name_val} { initApp(); };

/*
    Function to drop, initialise
    and populate system's tables and to display
    a "loading" text and login ASCII art banner.
*/
void InitApplication::initApp()
{
    Sql sql;
    Display disp;

    // drop all existing tables
    Table customersDrop{"customers", "DROP"};
    customersDrop.execTableOperation(customersDrop.getOperationType(), customersDrop.getTableName(), sql.getDropStmnt(customersDrop.getTableName()), true);

    Table ordersDrop{"orders", "DROP"};
    ordersDrop.execTableOperation(ordersDrop.getOperationType(), ordersDrop.getTableName(), sql.getDropStmnt(ordersDrop.getTableName()), true);

    Table system_accessDrop{"system_access", "DROP"};
    system_accessDrop.execTableOperation(system_accessDrop.getOperationType(), system_accessDrop.getTableName(), sql.getDropStmnt(system_accessDrop.getTableName()), true);

    Table staffDrop{"staff", "DROP"};
    staffDrop.execTableOperation(staffDrop.getOperationType(), staffDrop.getTableName(), sql.getDropStmnt(staffDrop.getTableName()), true);

    // create tables
    Table customersCreate{"customers", "CREATE"};
    customersCreate.execTableOperation(customersCreate.getOperationType(), customersCreate.getTableName(), sql.getCreateStmnt(customersCreate.getTableName()), true);

    Table ordersCreate{"orders", "CREATE"};
    ordersCreate.execTableOperation(ordersCreate.getOperationType(), ordersCreate.getTableName(), sql.getCreateStmnt(ordersCreate.getTableName()), true);

    Table system_accessCreate{"system_access", "CREATE"};
    system_accessCreate.execTableOperation(system_accessCreate.getOperationType(), system_accessCreate.getTableName(), sql.getCreateStmnt(system_accessCreate.getTableName()), true);

    Table staffCreate{"staff", "CREATE"};
    staffCreate.execTableOperation(staffCreate.getOperationType(), staffCreate.getTableName(), sql.getCreateStmnt(staffCreate.getTableName()), true);

    // insert test data to tables
    Table customersInsert{"customers", "INSERT INTO"};
    customersInsert.execTableOperation(customersInsert.getOperationType(), customersInsert.getTableName(), sql.getInsertStmnt(customersInsert.getTableName()), true);

    Table system_accessInsert{"system_access", "INSERT INTO"};
    system_accessInsert.execTableOperation(system_accessInsert.getOperationType(), system_accessInsert.getTableName(), sql.getInsertStmnt(system_accessInsert.getTableName()), true);

    Table staffInsert{"staff", "INSERT INTO"};
    staffInsert.execTableOperation(staffInsert.getOperationType(), staffInsert.getTableName(), sql.getInsertStmnt(staffInsert.getTableName()), true);

    disp.displayBreakText("LOADING... PLEASE WAIT...", true);
    disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_login.txt");
}
