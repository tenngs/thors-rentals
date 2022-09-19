/*
    This class contains utility functions in relation
    to displaying menus, capturing user-entered
    information and upon validation and confirmation
    from a user, adding this information in various
    tables in the DB.
*/
#pragma once

class Menu
{
public:
    void showMainMenuBanner();
    void mainMenu();
    void addCustomerMenu();
    void addStaffMenu();
    void addItemMenu();
    void InitRentalMenu();
};