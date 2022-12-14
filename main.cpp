#include <string>
#include <iostream>
#include "InitApplication.h"
#include "Utility.h"
#include "Login.h"
#include "Order.h"
#include "Menu.h"
/*
   Driver from where the app is initialised
   and operated.
*/
int main()
{
    // drop if exist, create and populate tables with test data
    // utilising Sqlite statements from Sql class
    InitApplication app{"Thor's Tantalising Arctic Equipment Rental AKA Thor's Rentals"};
    Login appLogin;
    Menu appMenu;
    Utility utils;

    if (appLogin.loginPrompt())
    {
        appMenu.mainMenu();
    }
    else
    {
        utils.shutdown();
    }
    return 0;
}
