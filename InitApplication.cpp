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
    customersDrop.execTableOperation(customersDrop.getOperationType(), customersDrop.getTableName(), sql.getDropStmnt(customersDrop.getTableName()));

    Table ordersDrop{"orders", "DROP"};
    ordersDrop.execTableOperation(ordersDrop.getOperationType(), ordersDrop.getTableName(), sql.getDropStmnt(ordersDrop.getTableName()));

    Table system_accessDrop{"system_access", "DROP"};
    system_accessDrop.execTableOperation(system_accessDrop.getOperationType(), system_accessDrop.getTableName(), sql.getDropStmnt(system_accessDrop.getTableName()));

    Table staffDrop{"staff", "DROP"};
    staffDrop.execTableOperation(staffDrop.getOperationType(), staffDrop.getTableName(), sql.getDropStmnt(staffDrop.getTableName()));

    Table inventorySkisSBs{"inventory_skis_snowboards", "DROP"};
    inventorySkisSBs.execTableOperation(inventorySkisSBs.getOperationType(), inventorySkisSBs.getTableName(), sql.getDropStmnt(inventorySkisSBs.getTableName()));

    Table inventoryAtvs{"inventory_atvs", "DROP"};
    inventoryAtvs.execTableOperation(inventoryAtvs.getOperationType(), inventoryAtvs.getTableName(), sql.getDropStmnt(inventoryAtvs.getTableName()));

    // create tables
    Table customersCreate{"customers", "CREATE"};
    customersCreate.execTableOperation(customersCreate.getOperationType(), customersCreate.getTableName(), sql.getCreateStmnt(customersCreate.getTableName()));

    Table ordersCreate{"orders", "CREATE"};
    ordersCreate.execTableOperation(ordersCreate.getOperationType(), ordersCreate.getTableName(), sql.getCreateStmnt(ordersCreate.getTableName()));

    Table system_accessCreate{"system_access", "CREATE"};
    system_accessCreate.execTableOperation(system_accessCreate.getOperationType(), system_accessCreate.getTableName(), sql.getCreateStmnt(system_accessCreate.getTableName()));

    Table staffCreate{"staff", "CREATE"};
    staffCreate.execTableOperation(staffCreate.getOperationType(), staffCreate.getTableName(), sql.getCreateStmnt(staffCreate.getTableName()));

    Table inventorySkisSBsCreate{"inventory_skis_snowboards", "CREATE"};
    inventorySkisSBsCreate.execTableOperation(inventorySkisSBsCreate.getOperationType(), inventorySkisSBsCreate.getTableName(), sql.getCreateStmnt(inventorySkisSBsCreate.getTableName()));

    Table inventoryAtvsCreate{"inventory_atvs", "CREATE"};
    inventoryAtvsCreate.execTableOperation(inventoryAtvsCreate.getOperationType(), inventoryAtvsCreate.getTableName(), sql.getCreateStmnt(inventoryAtvsCreate.getTableName()));

    // insert test data to tables
    Table customersInsert{"customers", "INSERT INTO"};
    customersInsert.execTableOperation(customersInsert.getOperationType(), customersInsert.getTableName(), sql.getInsertStmnt(customersInsert.getTableName()));

    Table system_accessInsert{"system_access", "INSERT INTO"};
    system_accessInsert.execTableOperation(system_accessInsert.getOperationType(), system_accessInsert.getTableName(), sql.getInsertStmnt(system_accessInsert.getTableName()));

    Table staffInsert{"staff", "INSERT INTO"};
    staffInsert.execTableOperation(staffInsert.getOperationType(), staffInsert.getTableName(), sql.getInsertStmnt(staffInsert.getTableName()));

    Table inventorySkisSBsInsert{"inventory_skis_snowboards", "INSERT INTO"};
    inventorySkisSBsInsert.execTableOperation(inventorySkisSBsInsert.getOperationType(), inventorySkisSBsInsert.getTableName(), sql.getInsertStmnt(inventorySkisSBsInsert.getTableName()));

    Table inventoryAtvsInsert{"inventory_atvs", "INSERT INTO"};
    inventoryAtvsInsert.execTableOperation(inventoryAtvsInsert.getOperationType(), inventoryAtvsInsert.getTableName(), sql.getInsertStmnt(inventoryAtvsInsert.getTableName()));

    disp.displayBreakText("LOADING... PLEASE WAIT...", true);
    disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_login.txt");
}
