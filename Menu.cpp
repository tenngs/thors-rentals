#include <iostream>
#include <cmath>
#include <iomanip>
#include <set>
#include <unordered_set>
#include <vector>
#include <map>
#include <regex>
#include <string>
#include "Display.h"
#include "Utility.h"
#include "Display.h"
#include "Table.h"
#include "Order.h"
#include "Sql.h"
#include "Menu.h"
/*
    Displays Main Menu options banner.
*/
void Menu::showMainMenuBanner()
{
    std::cout << "                     *********************************************************************\n";
    std::cout << "                     |-------------------------------------------------------------------|" << std::endl;
    std::cout << "                     |                        Please Choose:                             |" << std::endl;
    std::cout << "                     |-------------------------------------------------------------------|" << std::endl;
    std::cout << "                     |1. Add Customer                         4. Initiate Rental         |" << std::endl;
    std::cout << "                     |2. Add System Access Staff              5. Receive Rental Item     |" << std::endl;
    std::cout << "                     |3. Add Rental Item                      6. Statistics              |" << std::endl;
    std::cout << "                     |-------------------------------------------------------------------|" << std::endl;
    std::cout << "                     |------------------ Press 7 to Exit the Program---------------------|" << std::endl;
    std::cout << "                     *********************************************************************\n";
    std::cout << "\n\n";
    std::cout << "|---TR~Main Menu~$: ";
}
/*
    Displays and facilitates Main menu options
    for a user.
*/
void Menu::mainMenu()
{
    Display disp;
    Menu mainMenu;
    Utility utils;
    disp.displayBreakText("LOADING... PLEASE WAIT...", true);
    std::set<int> validDigits({1, 2, 3, 4, 5, 6, 7});
    int choice{};

    while (true)
    {
        disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_mainmenu.txt");
        mainMenu.showMainMenuBanner();

        if ((!(std::cin >> choice)) || (!(utils.validateDigits(choice, validDigits))))
        {
            std::cout << "|---Thor is not happy - Please enter numbers 1-7 only" << std::endl;
            utils.pause(3);
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            system("cls");
        }
        else
        {
            switch (choice)
            {
            case 1:
                mainMenu.addCustomerMenu();
                break;
            case 2:
                mainMenu.addStaffMenu();
                break;
            case 3:
                mainMenu.addItemMenu();
                break;
            case 4:
            {
                Order *initOrder = new Order;
                mainMenu.initRentalMenu(*initOrder);
                mainMenu.chooseEquipmentMenu(*initOrder);
                mainMenu.rentalDurationMenu(*initOrder);
                mainMenu.confirmDetailsMenu(*initOrder);
                utils.addOrderDetails(*initOrder);
                delete initOrder;
                break;
            }
            case 5:
                mainMenu.receiveItemMenu();
                break;
            case 6:
                mainMenu.statsMenu();
                break;
            case 7:
                utils.shutdown();
                break;
            }
        }
    }
}
/*
    Displays and facilitates Add Customer menu options
    for a user. Utilises a std::vector<std::string>
    to collect pieces of user-entered information that
    will be upon confirmation from a user used to
    add a customer to customers table.
*/
void Menu::addCustomerMenu()
{
    // initialise variables to be used in capturing user
    // input and to perform table operations
    std::vector<std::string> customerInfo{};
    std::string infoPiece{};
    std::string successMsg{"Customer added successfully"};
    std::string answer{};
    std::string postcode{};
    std::string email{};

    Display disp;
    Utility utils;
    Sql sql;
    Table customers;

    while (true)
    {
        system("cls");
        disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals.txt");
        disp.displayASCIIArtFromFile("ASCIIArt/add_customer.txt");

        while (1)
        {
            std::cout << "\n|---Please enter customer's first name [one name only]" << std::endl;
            std::cout << "|---TR~Add Customer~$: ";
            std::cin >> infoPiece;

            if (utils.lettersOnly(infoPiece))
            {
                infoPiece[0] = std::toupper(infoPiece[0]);
                customerInfo.push_back(infoPiece);
                // flush the rest of the line because getline is used next
                std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                break;
            }
            else
            {
                std::cout << "\n|---Thor is not happy - letters only please" << std::endl;
                std::cin.ignore(std::numeric_limits<int>::max(), '\n');
            }
        }

        while (1)
        {
            std::cout << "\n|---Please enter customer's surname" << std::endl;
            std::cout << "|---TR~Add Customer~$: ";
            std::getline(std::cin, infoPiece);

            if (utils.lettersAndSpacesOnly(infoPiece))
            {
                utils.capitaliseAllFirstLetters(infoPiece);
                customerInfo.push_back(infoPiece);
                break;
            }
            else
            {
                std::cout << "\n|---Thor is not happy - letters and whitespace only please" << std::endl;
            }
        }

        std::cout << "\n|---Please enter customer's first line of address" << std::endl;
        std::cout << "|---TR~Add Customer~$: ";
        std::getline(std::cin, infoPiece);
        utils.capitaliseAllFirstLetters(infoPiece);
        customerInfo.push_back(infoPiece);

        while (1)
        {
            std::cout << "\n|---Please enter customer's UK postcode [No spaces]" << std::endl;
            std::cout << "|---TR~Add Customer~$: ";
            std::cin >> postcode;
            if (utils.postcodeCheck(postcode))
            {
                customerInfo.push_back(utils.toUpperCase(postcode));
                std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                break;
            }
            else
            {
                std::cout << "\n|---Thor is not happy - invalid postcode" << std::endl;
            }
        }
        std::cout << "\n|---Please enter customer's city" << std::endl;
        std::cout << "|---TR~Add Customer~$: ";
        std::getline(std::cin, infoPiece);
        utils.capitaliseAllFirstLetters(infoPiece);
        customerInfo.push_back(infoPiece);

        while (1)
        {
            std::cout << "\n|---Please enter customer's email" << std::endl;
            std::cout << "|---TR~Add Customer~$: ";
            std::cin >> email;
            if (utils.emailCheck(email))
            {
                customerInfo.push_back(email);
                break;
            }
            else
            {
                std::cout << "\n|---Thor is not happy - invalid email" << std::endl;
            }
        }
        system("cls");
        disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals.txt");
        disp.displayASCIIArtFromFile("ASCIIArt/add_customer.txt");
        // display user-entered info
        std::cout << "\tYou entered: \n\n";
        std::cout << "\tFirst name: "
                  << "\t\t" << customerInfo[0] << std::endl;
        std::cout << "\tSurname: "
                  << "\t\t" << customerInfo[1] << std::endl;
        std::cout << "\tAdress 1st line: "
                  << "\t" << customerInfo[2] << std::endl;
        std::cout << "\tPostcode: "
                  << "\t\t" << customerInfo[3] << std::endl;
        std::cout << "\tCity: "
                  << "\t\t\t" << customerInfo[4] << std::endl;
        std::cout << "\tEmail: "
                  << "\t\t\t" << customerInfo[5] << std::endl;

        std::cout << "\n\n\tIs this correct [Y/N]: ";
        std::cin >> answer;

        while (!utils.validateYesOrNo(answer))
        {
            std::cout << "\tY or N please: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cin >> answer;
        }

        if (utils.lowerStr(answer) == "n")
        {
            customerInfo.clear();
        }
        else
        {
            break;
        }
    }

    customers.appInsertTableOperation(successMsg, customerInfo, sql.getAddCustomerStmnt());
}
/*
    Displays and facilitates Add Staff menu options
    for a user. Utilises a std::vector<std::string>
    to collect pieces of user-entered information that
    will be upon confirmation from a user utilised to
    add a staff member to system_access table thereby
    granting that staff member login access to this application.
*/
void Menu::addStaffMenu()
{
    std::vector<std::string> staffInfo{};
    std::string infoPiece{};
    std::string successMsg = "Staff member added and granted app access successfully";
    std::string answer = {};

    int staffIDchoice{};

    std::unordered_set<int> staffIDs{};
    std::unordered_set<int> systemAccessStaffIDs{};
    std::unordered_set<int> validStaffIDs{};

    Display disp;
    Utility utils;
    Sql sql;
    Table staff;
    Table system_access;

    while (true)
    {
        while (1)
        {
            system("cls");
            disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_add_staff.txt");
            std::cout << "|---Please enter staff member's ID" << std::endl;
            std::cout << "|---TR~Add Staffr~$: ";
            // get all current staff IDs in a set
            staffIDs = staff.getAvailableIDs(sql.getStaffIDs());
            // get all staff ids from system_access to a set
            systemAccessStaffIDs = staff.getAvailableIDs(sql.getSystemAccessStaffIDs());

            // if staffIDchoice is not numeric or if staffIDchoice is within valid staff IDs that already
            // have system access ---> ask the user to enter a new staffID
            if ((!(std::cin >> staffIDchoice)) || (!(utils.validateDigits(staffIDchoice, utils.unorderedToOrdered(utils.getValidStaffIDS(staffIDs, systemAccessStaffIDs))))))
            {
                std::cout << "\n|---Thor is not happy - Please enter valid staff IDs that do NOT have system access only";
                utils.pause(3);
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
            else
            {
                staffInfo.push_back(std::to_string(staffIDchoice));
                std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                break;
            }
        }

        while (1)
        {

            std::cout << "|---Please enter staff member's username" << std::endl;
            std::cout << "|---TR~Add Staffr~$: ";
            std::cin >> infoPiece;

            // Note: even though std::cin only takes in user input
            // until the first whitespace character, noSpacesOnly() is
            // utilised as a secondary check because of mixed use of
            // std::cin and std::getline()

            // check for uniqueness of username by querying DB
            if (utils.noSpacesOnly(infoPiece) && (!system_access.determineExistenceTextValuesInDB(infoPiece, sql.getValidateUsernameStmnt())))
            {
                staffInfo.push_back(infoPiece);
                std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                break;
            }
            else
            {
                std::cout << "\n|---Thor is not happy - Please enter unique username without whitespace" << std::endl;
            }
        }

        while (1)
        {

            std::cout << "|---Please enter staff member's password" << std::endl;
            std::cout << "|---TR~Add Staff~$: ";

            std::getline(std::cin, infoPiece);
            if (utils.noSpacesOnly(infoPiece))

            {
                staffInfo.push_back(infoPiece);
                break;
            }
            else
            {
                std::cout << "|---Thor is not happy - no whitespaces please" << std::endl;
            }
        }

        // push back a std::string zero to indicate that the staff
        // member that is currently added is not logged on at present
        staffInfo.push_back(std::to_string(0));

        system("cls");
        disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_add_staff.txt");

        // display user-entered info
        std::cout << "\tYou entered: \n\n";
        std::cout << "\tStaff ID: "
                  << "\t" << staffInfo[0] << std::endl;
        std::cout << "\tUsername: "
                  << "\t" << staffInfo[1] << std::endl;
        std::cout << "\tPassword: "
                  << "\t" << staffInfo[2] << std::endl;

        // if not correct --> ask and display customer info agin
        std::cout << "\n\n\tIs this correct [Y/N]: ";
        std::cin >> answer;

        while (!utils.validateYesOrNo(answer))
        {
            std::cout << "\tY or N please: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cin >> answer;
        }

        if (utils.lowerStr(answer) == "n")
        {
            staffInfo.clear();
        }
        else
        {
            break;
        }
    }

    staff.appInsertTableOperation(successMsg, staffInfo, sql.getAddStaffStmnt());
}
/*
    Displays and facilitates Add Rental Item menu options
    for a user. Utilises a std::vector<std::string>
    to collect pieces of user-entered information that
    will be upon confirmation from a user utilised to
    add a rental item to its correct table.
    For example, equipment of type 1 & 2 are added to
    the inventory_skis_snowboards table and ATVs are
    added to inventory_atvs table.
    Provides an option to add an item to rental
    inventory and to specify whether the item is / is NOT
    available for rent currently.
*/
void Menu::addItemMenu()
{
    std::vector<std::string> equipmentInfo{};
    std::string infoPiece{};
    std::string successMsg{};
    std::string sqlStmnt{};
    std::string answer{};
    std::string equipmentType{};

    bool run = true;
    std::set<int> validDigitsOneAndTwo({1, 2});
    std::set<int> validDigitsZeroAndOne({0, 1});
    int choice{};
    int equipmentTypeChoice{};
    int equipmentStatusChoice{};

    double pricePerHourChoice{};
    double pricePerDayChoice{};

    Display disp;
    Utility utils;
    Sql sql;
    Table inventory;

    do
    {
        system("cls");
        disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_add_item.txt");
        std::cout << "|---Please enter [1] to add skis / snowboard or [2] to add ATV" << std::endl;
        std::cout << "|---TR~Add Item~$: ";

        if ((!(std::cin >> choice)) || (!(utils.validateDigits(choice, validDigitsOneAndTwo))))
        {
            std::cout << "|---Thor is not happy - Please enter numbers 1 or 2 only" << std::endl;
            utils.pause(3);
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }

        else
        {
            // flush the stream because going from std::cin to std::getline()
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
            switch (choice)
            {
            case 1:
                system("cls");
                disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_add_item.txt");
                std::cout << "|---Please enter make" << std::endl;
                std::cout << "|---TR~Add Skis & Snowboards~$: ";
                std::getline(std::cin, infoPiece);
                utils.capitaliseAllFirstLetters(infoPiece);
                equipmentInfo.push_back(infoPiece);

                std::cout << "|---Please enter model" << std::endl;
                std::cout << "|---TR~Add Skis & Snowboards~$: ";
                std::getline(std::cin, infoPiece);
                utils.capitaliseAllFirstLetters(infoPiece);
                equipmentInfo.push_back(infoPiece);

                while (1)
                {
                    std::cout << "|---Please enter price per hour" << std::endl;
                    std::cout << "|---TR~Add Skis & Snowboards~$: ";

                    if ((!(std::cin >> pricePerHourChoice)))
                    {
                        std::cout << "|---Thor is not happy - Please enter integers or decimals only" << std::endl;
                        utils.pause(3);
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                    }
                    else
                    {
                        equipmentInfo.push_back(std::to_string(pricePerHourChoice));
                        break;
                    }
                }

                while (1)
                {
                    std::cout << "|---Please enter price per day" << std::endl;
                    std::cout << "|---TR~Add Skis & Snowboards~$: ";

                    if ((!(std::cin >> pricePerDayChoice)))
                    {
                        std::cout << "|---Thor is not happy - Please enter integers or decimals only" << std::endl;
                        utils.pause(3);
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                    }
                    else
                    {
                        equipmentInfo.push_back(std::to_string(pricePerDayChoice));
                        break;
                    }
                }

                while (1)
                {
                    std::cout << "|---Please enter equipment type: [1] skis - [2] Snowboard" << std::endl;
                    std::cout << "|---TR~Add Skis & Snowboards~$: ";

                    if ((!(std::cin >> equipmentTypeChoice)) || (!(utils.validateDigits(equipmentTypeChoice, validDigitsOneAndTwo))))
                    {
                        std::cout << "|---Thor is not happy - Please enter numbers 1 or 2 only" << std::endl;
                        utils.pause(3);
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                    }
                    else
                    {
                        equipmentInfo.push_back(std::to_string(equipmentTypeChoice));
                        break;
                    }
                }

                while (1)
                {
                    std::cout << "|---Please enter rental status\n:" << std::endl;
                    std::cout << "|---[0] for NOT available for rent" << std::endl;
                    std::cout << "|---[1] for AVAILABLE for rent\n"
                              << std::endl;
                    std::cout << "\n|---TR~Add Skis & Snowboards~$: ";

                    if ((!(std::cin >> equipmentStatusChoice)) || (!(utils.validateDigits(equipmentStatusChoice, validDigitsZeroAndOne))))
                    {
                        std::cout << "|---Thor is not happy - Please enter numbers 0 or 1 only" << std::endl;
                        utils.pause(3);
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                    }
                    else
                    {
                        equipmentInfo.push_back(std::to_string(equipmentStatusChoice));
                        break;
                    }
                }

                system("cls");
                disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_add_item.txt");
                std::cout << "\tYou entered: \n\n";
                if (equipmentInfo[4] == "2")
                {
                    std::cout << "\tEquipment type: "
                              << "\tSnowboard" << std::endl;
                }
                else
                {
                    std::cout << "\tEquipment type: "
                              << "\tSkis" << std::endl;
                }
                std::cout << "\tMake: "
                          << "\t\t\t" << equipmentInfo[0] << std::endl;
                std::cout << "\tModel: "
                          << "\t\t\t" << equipmentInfo[1] << std::endl;
                std::cout << "\tPrice per hour: "
                          << "\t" << std::setprecision(3) << std::stod(equipmentInfo[2]) << std::endl;
                std::cout << "\tPrice per day: "
                          << "\t\t" << std::setprecision(4) << std::stod(equipmentInfo[3]) << std::endl;
                std::cout << "\tAvailable: "
                          << "\t\t" << equipmentInfo[5] << std::endl;

                std::cout << "\n\n\tIs this correct [Y/N]: ";
                std::cin >> answer;

                while (!utils.validateYesOrNo(answer))
                {
                    std::cout << "\tY or N please: ";
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cin >> answer;
                }

                if (utils.lowerStr(answer) == "n")
                {
                    equipmentInfo.clear();
                }
                else
                {
                    successMsg = "Skis or snowboards added to rental inventory successfully";
                    sqlStmnt = sql.getAddSkisSnowboardStmnt();
                    run = false;
                    break;
                }
                break;

            case 2:
                system("cls");
                disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_add_item.txt");
                std::cout << "|---Please enter make" << std::endl;
                std::cout << "|---TR~Add ATV~$: ";
                std::getline(std::cin, infoPiece);
                utils.capitaliseAllFirstLetters(infoPiece);
                equipmentInfo.push_back(infoPiece);

                std::cout << "|---Please enter model" << std::endl;
                std::cout << "|---TR~Add ATV~$: ";
                std::getline(std::cin, infoPiece);
                utils.capitaliseAllFirstLetters(infoPiece);
                equipmentInfo.push_back(infoPiece);

                std::cout << "|---Please enter registration" << std::endl;
                std::cout << "|---TR~Add ATV~$: ";
                std::cin >> infoPiece;
                std::cin.ignore();
                equipmentInfo.push_back(infoPiece);

                std::cout << "|---Please enter fuel type" << std::endl;
                std::cout << "|---TR~Add ATV~$: ";
                std::cin >> infoPiece;
                std::cin.ignore();
                utils.capitaliseAllFirstLetters(infoPiece);
                equipmentInfo.push_back(infoPiece);

                while (1)
                {
                    std::cout << "|---Please enter price per hour" << std::endl;
                    std::cout << "|---TR~Add ATV~$: ";

                    if ((!(std::cin >> pricePerHourChoice)))
                    {
                        std::cout << "|---Thor is not happy - Please enter integers or decimals only" << std::endl;
                        utils.pause(3);
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                    }
                    else
                    {
                        equipmentInfo.push_back(std::to_string(pricePerHourChoice));
                        break;
                    }
                }

                while (1)
                {
                    std::cout << "|---Please enter price per day" << std::endl;
                    std::cout << "|---TR~Add ATV~$: ";

                    if ((!(std::cin >> pricePerDayChoice)))
                    {
                        std::cout << "|---Thor is not happy - Please enter integers or decimals only" << std::endl;
                        utils.pause(3);
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                    }
                    else
                    {
                        equipmentInfo.push_back(std::to_string(pricePerDayChoice));
                        equipmentInfo.push_back(std::to_string(3)); // push back equipment type
                        break;
                    }
                }

                while (1)
                {
                    std::cout << "|---Please enter rental status\n:" << std::endl;
                    std::cout << "|---[0] for NOT available for rent" << std::endl;
                    std::cout << "|---[1] for AVAILABLE for rent\n"
                              << std::endl;
                    std::cout << "|---TR~Add ATV~$: ";

                    if ((!(std::cin >> equipmentStatusChoice)) || (!(utils.validateDigits(equipmentStatusChoice, validDigitsZeroAndOne))))
                    {
                        std::cout << "|---Thor is not happy - Please enter numbers 0 or 1 only" << std::endl;
                        utils.pause(3);
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                    }
                    else
                    {
                        equipmentInfo.push_back(std::to_string(equipmentStatusChoice));
                        break;
                    }
                }

                system("cls");
                disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_add_item.txt");

                std::cout << "\tYou entered: \n\n";
                std::cout << "\tEquipment type: "
                          << "\t"
                          << "ATV" << std::endl;
                std::cout << "\tMake: "
                          << "\t\t\t" << equipmentInfo[0] << std::endl;
                std::cout << "\tModel: "
                          << "\t\t\t" << equipmentInfo[1] << std::endl;
                std::cout << "\tReg: "
                          << "\t\t\t" << equipmentInfo[2] << std::endl;
                std::cout << "\tFuel type: "
                          << "\t\t" << equipmentInfo[3] << std::endl;
                std::cout << "\tPrice per hour: "
                          << "\t" << std::setprecision(3) << std::stod(equipmentInfo[4]) << std::endl;
                std::cout << "\tPrice per day: "
                          << "\t\t" << std::setprecision(4) << std::stod(equipmentInfo[5]) << std::endl;
                std::cout << "\tAvailable: "
                          << "\t\t" << equipmentInfo[7] << std::endl;

                std::cout << "\n\n\tIs this correct [Y/N]: ";
                std::cin >> answer;

                while (!utils.validateYesOrNo(answer))
                {
                    std::cout << "\tY or N please: ";
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cin >> answer;
                }
                if (utils.lowerStr(answer) == "n")
                {
                    equipmentInfo.clear();
                }
                else
                {
                    successMsg = "ATV added to rental inventory successfully";
                    sqlStmnt = sql.getAddAtvStmnt();
                    run = false;
                    break;
                }
                break;
            }
        }
    } while (run == true);

    inventory.appInsertTableOperation(successMsg, equipmentInfo, sqlStmnt);
}
/*
    Provides a facility to add a customer that has
    had their details saved in customers table
    to a rental order. Customers can
    be added by providing their valid first and surname or
    customer ID.
*/
void Menu::initRentalMenu(Order &initOrder)
{
    std::map<std::string, int> orderTableInfo;
    std::string firstName{};
    std::string surname{};
    std::string sqlInit{};
    int userSuppliedID{};
    int choice{};
    int resultID{};
    std::set<int> validDigits({1, 2, 9});
    bool run = true;

    Display disp;
    Utility utils;
    Sql sql;
    Table customers;
    Menu initRental;

    do
    {
        system("cls");
        disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_init_rental.txt");

        std::cout << "|---Select customer or press [9] for Main Menu" << std::endl;
        std::cout << "|---Search by: " << std::endl;
        std::cout << "|---" << std::endl;
        std::cout << "|---[1]: First name, Surname" << std::endl;
        std::cout << "|---[2]: ID\n"
                  << std::endl;
        std::cout << "|---" << std::endl;
        std::cout << "|---TR~Init Rental: ";

        if ((!(std::cin >> choice)) || (!(utils.validateDigits(choice, validDigits))))
        {
            std::cout << "|---Thor is not happy - Please enter numbers 1, 2 or 9 only";
            utils.pause(3);
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        else if (choice == 9)
        {
            system("cls");
            initRental.mainMenu();
        }
        else
        {
            switch (choice)
            {
            case 1:

                system("cls");
                disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_init_rental.txt");
                std::cout << "|---Please enter customer's first name: " << std::endl;
                std::cout << "|---TR~Search 4 Customer~$: ";
                std::cin >> firstName;

                std::cout << "|---Please enter customer's surname: " << std::endl;
                std::cout << "|---TR~Search 4 Customer~$: ";
                std::cin >> surname;

                sqlInit = sql.getSearchForCustomerIDByNameV1() + firstName + sql.getSearchForCustomerIDByNameV2() + surname + "\';";
                resultID = customers.searchNumericValuesFromDB(sqlInit);

                if (resultID != 0)
                {
                    std::cout << "|---Customer " << firstName << " " << surname << " found - happy days" << std::endl;
                    utils.pause(3);
                    run = false;
                    break;
                }
                else
                {
                    std::cout << "\n|---No customer records found with:\n|----------------------------------\n|---First name: " << firstName << " \n|---Surname: " << surname << std::endl;
                    std::cout << "\n|---Please re-enter customer details" << std::endl;
                    utils.pause(3);
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    break;
                }

            case 2:
                system("cls");
                disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_init_rental.txt");
                std::cout << "|---Please enter customer's ID: ";
                std::cin >> userSuppliedID;

                sqlInit = sql.getSearchForCustomerIDByID() + std::to_string(userSuppliedID) + "\';";
                resultID = customers.searchNumericValuesFromDB(sqlInit);
                if (resultID != 0)
                {
                    std::cout << "|---Customer with ID " << resultID << " found - happy days" << std::endl;
                    utils.pause(3);
                    run = false;
                    break;
                }
                if (resultID == 0)
                {
                    std::cout << "Thor is not happy - please enter a valid customer ID" << std::endl;
                    utils.pause(3);
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    break;
                }
                std::cout << "|---No customer records with ID " << userSuppliedID << " were found" << std::endl;
                std::cout << "|---Please re-enter customer details" << std::endl;
                utils.pause(3);
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                break;
            }
        }
    } while (run == true);

    initOrder.setID("customer", resultID);
}
/*
    Provides a facility to add an available
    rental item to a rental order. Equipment
    can be selected by their type and ID.
    Shows only available equipment by searching
    inventory tables.
*/
void Menu::chooseEquipmentMenu(Order &initOrder)
{
    int userSuppliedEquimentID{};
    int choice{};
    bool run = true;

    std::set<int> validDigits({1, 2, 3, 9});
    std::unordered_set<int> validEquipmentIDs{};

    std::string sqlStmnt{};
    std::string returnDateTime{};

    int resultID = {};

    Display disp;
    Utility utils;
    Sql sql;
    Table skisSBs{"inventory_skis_snowboards"};
    Table atvs{"inventory_atvs"};
    Menu mainMenu;

    do
    {
        system("cls");
        disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_init_rental.txt");

        std::cout << "|---Select type of equipment to see available items" << std::endl;
        std::cout << "|---Or press [9] for Main Menu" << std::endl;
        std::cout << "|---" << std::endl;
        std::cout << "|---[1]: Skis" << std::endl;
        std::cout << "|---[2]: Snowboard" << std::endl;
        std::cout << "|---[3]: ATV" << std::endl;
        std::cout << "|---" << std::endl;
        std::cout << "|---TR~Init Rental: ";

        if ((!(std::cin >> choice)) || (!(utils.validateDigits(choice, validDigits))))

        {
            std::cout << "|---Thor is not happy - Please enter numbers 1, 2, 3 or 9 only " << std::endl;
            utils.pause(3);
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }

        else if (choice == 9)
        {
            system("cls");
            mainMenu.mainMenu();
        }

        else
        {
            switch (choice)
            {
            case 1:

                sqlStmnt = sql.getAvailableEquipIDsV1() + skisSBs.getTableName() + sql.getAvailableEquipIDsV2() + std::to_string(1);
                validEquipmentIDs = skisSBs.getAvailableIDs(sqlStmnt);
                // if no available SBs are in inventory
                if (validEquipmentIDs.size() == 0)
                {
                    std::cout << "\n|---No skis available for rent at the moment" << std::endl;
                    utils.pause(3);
                    mainMenu.mainMenu();
                    run = false;
                    break;
                }

                // otherwise display available SBs
                system("cls");
                disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_init_rental.txt");
                std::cout << "|---------------------Available Skis---------------------|"
                          << std::endl;
                disp.displaySkiTableColumns();

                disp.displayAvailableEquipment("inventory_skis_snowboards", 1);

                // choose equipment for rent by ID
                std::cout << "\n\n|---Select item by entering its ID" << std::endl;
                std::cout << "|---" << std::endl;
                std::cout << "|---TR~Init Rental: ";

                while ((!(std::cin >> choice)) || (!(validEquipmentIDs.count(choice) == 1)))

                {
                    std::cout << "|---" << std::endl;
                    std::cout << "|---HINT: they are on the left side of your screen" << std::endl;
                    std::cout << "|---Please try again" << std::endl;
                    utils.pause(3);
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "|---" << std::endl;
                    std::cout << "|---TR~Init Rental: ";
                }

                initOrder.setEquipment("type", 1);
                run = false;
                break;

            case 2:
                sqlStmnt = sql.getAvailableEquipIDsV1() + skisSBs.getTableName() + sql.getAvailableEquipIDsV2() + std::to_string(2);

                validEquipmentIDs = skisSBs.getAvailableIDs(sqlStmnt);
                // if no available SBs are in inventory
                if (validEquipmentIDs.size() == 0)
                {
                    std::cout << "\n|---No snowboards available for rent at the moment" << std::endl;
                    utils.pause(3);
                    mainMenu.mainMenu();
                    run = false;
                    break;
                }

                // otherwise display available SBs
                system("cls");
                disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_init_rental.txt");
                std::cout << "|---------------------------Available Snowboards---------------------------|\n"
                          << std::endl;
                disp.displaySnowboardTableColumns();

                disp.displayAvailableEquipment("inventory_skis_snowboards", 2);

                // choose equipment for rent by ID
                std::cout << "\n\n|---Select item by entering its ID" << std::endl;
                std::cout << "|---" << std::endl;
                std::cout << "|---TR~Init Rental: ";

                while ((!(std::cin >> choice)) || (!(validEquipmentIDs.count(choice) == 1)))

                {
                    std::cout << "|---" << std::endl;
                    std::cout << "|---HINT: they are on the left side of your screen" << std::endl;
                    utils.pause(3);
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "|---" << std::endl;
                    std::cout << "|---TR~Init Rental: ";
                }

                initOrder.setEquipment("type", 2);
                run = false;
                break;

            case 3:
                sqlStmnt = sql.getAvailableEquipIDsV1() + atvs.getTableName() + sql.getAvailableEquipIDsV2() + std::to_string(3);

                validEquipmentIDs = atvs.getAvailableIDs(sqlStmnt);
                // if no available ATVs are in inventory
                if (validEquipmentIDs.size() == 0)
                {
                    std::cout << "\n|---No ATVs available for rent at the moment" << std::endl;
                    utils.pause(3);
                    mainMenu.mainMenu();
                    run = false;
                    break;
                }

                // otherwise display available ATVs
                system("cls");
                disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_init_rental.txt");
                std::cout << "|-------------------------------------Available ATVs-------------------------------------|" << std::endl;

                disp.displayATVTableColumns();

                disp.displayAvailableEquipment("inventory_atvs", 3);

                // choose equipment for rent by ID
                std::cout << "\n\n|---Select item by entering its ID" << std::endl;
                std::cout << "|---" << std::endl;
                std::cout << "|---TR~Init Rental: ";

                while ((!(std::cin >> choice)) || (!(validEquipmentIDs.count(choice) == 1)))

                {
                    std::cout << "|---" << std::endl;
                    std::cout << "|---HINT: they are on the left side of your screen" << std::endl;
                    utils.pause(3);
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "|---" << std::endl;
                    std::cout << "|---TR~Init Rental: ";
                }
                initOrder.setEquipment("type", 3);
            }
            break;
        }
    } while (run = true);

    initOrder.setEquipment("id", choice);
}
/*
    Provides a facility for a user to enter a rental
    duration to rental order. Duration can be specified
    as hours (up to 11) or days (up to 28).
*/
void Menu::rentalDurationMenu(Order &initOrder)
{
    int choice{};
    int hoursChoice{};
    int daysChoice{};
    bool run = true;

    Display disp;
    Utility utils;
    Menu mainMenu;
    Table initRental;

    std::set<int> validDigits({1, 2, 9});
    std::set<int> validHours({});
    for (int i = 1; i < 12; ++i)
    {
        validHours.insert(i);
    }

    std::set<int> validDays;
    for (int i = 1; i < 29; ++i)
    {
        validDays.insert(i);
    }

    do
    {
        system("cls");
        disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_init_rental.txt");

        std::cout << "|---Enter rental duration in" << std::endl;
        std::cout << "|---Or press [9] for Main Menu" << std::endl;
        std::cout << "|---" << std::endl;
        std::cout << "|---[1]: Hours" << std::endl;
        std::cout << "|---[2]: Days" << std::endl;

        std::cout << "|---" << std::endl;
        std::cout << "|---TR~Init Rental: ";

        if ((!(std::cin >> choice)) || (!(utils.validateDigits(choice, validDigits))))

        {
            std::cout << "|---Thor is not happy - Please enter numbers 1, 2 or 9 only " << std::endl;

            utils.pause(3);
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }

        else if (choice == 9)
        {
            system("cls");
            mainMenu.mainMenu();
        }

        else
        {
            switch (choice)
            {
            case 1: // hours

                std::cout << "|---Please enter rental duration in hours" << std::endl;
                std::cout << "|---Maximum 11 - no half hours allowed" << std::endl;
                std::cout << "|---" << std::endl;
                std::cout << "|---TR~Init Rental: ";

                while ((!(std::cin >> hoursChoice)) || (!(utils.validateDigits(hoursChoice, validHours))))

                {
                    std::cout << "|---Thor is not happy - Please enter numbers up 11 hours only " << std::endl;

                    utils.pause(3);
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "|---" << std::endl;
                    std::cout << "|---TR~Init Rental: ";
                }

                initOrder.setRental("hours", hoursChoice);
                initOrder.setRental("days", 0);
                run = false;
                break;

            case 2: // days
                std::cout << "|---Please enter rental duration in days" << std::endl;
                std::cout << "|---Maximum 28 - no half days allowed" << std::endl;
                std::cout << "|---" << std::endl;
                std::cout << "|---TR~Init Rental: ";

                while ((!(std::cin >> daysChoice)) || (!(utils.validateDigits(daysChoice, validDays))))

                {
                    std::cout << "|---Thor is not happy - Please enter numbers up 28 days only " << std::endl;

                    utils.pause(3);
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "|---" << std::endl;
                    std::cout << "|---TR~Init Rental: ";
                }

                initOrder.setRental("hours", 0);
                initOrder.setRental("days", daysChoice);
                run = false;
                break;
            }
            break;
        }
    } while (run = true);
}
/*
    Provides a facility for a user to confirm that their
    rental order selections are correct. If a user validates
    that the rental information is correct, selected eqipment
    are marked in their respective inventory databases as
    unavailable. Thus, they will not show as 'available' if
    a user is searching for equipment to rent.
*/
void Menu::confirmDetailsMenu(Order &initOrder)
{
    std::string choice{};
    std::string sqlInit{};
    bool run = true;

    std::set<int> validDigits({1, 2, 3, 9});
    std::unordered_set<int> validEquipmentIDs{};

    int equipmentType{initOrder.getEquipment("type")};
    int equipmentID{initOrder.getEquipment("id")};

    Table atvs{"inventory_atvs", "UPDATE"};
    Table skisSBs{"inventory_skis_snowboards", "UPDATE"};

    Menu mainMenu;
    Display disp;
    Utility utils;
    Sql sql;
    utils.setOrderDetails(initOrder);

    do
    {
        system("cls");
        disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_init_rental.txt");

        std::cout << "|-----Thor's Rentals Order-----|"
                  << std::endl;
        std::cout << "|--------------for"
                  << "-------------|\n"
                  << std::endl;
        std::cout << "|---Sales rep ID: " << initOrder.getSalesRepID()
                  << "\n\n"
                  << std::endl;
        std::cout << "|---Order details: " << std::endl;
        std::cout << "|---" << std::endl;
        std::cout << "|---Customer name: " << initOrder.getName("first") + " " + initOrder.getName("last") << std::endl;
        std::cout << "|---Equipment make/model: " << initOrder.getEquipmentStyle("make") + " " + initOrder.getEquipmentStyle("model") << std::endl;
        std::cout << "|---Equipment ID: " << initOrder.getEquipment("id") << std::endl;
        std::cout << "|---Rental days: " << initOrder.getRental("days") << std::endl;
        std::cout << "|---Rental hours: " << initOrder.getRental("hours") << std::endl;
        std::cout << "|---Total cost: " << initOrder.getRental() << std::endl;
        std::cout << "|---Return date/time: " << initOrder.getReturnDateTime() << std::endl;
        std::cout << "|---" << std::endl;
        std::cout << "|---Is this correct? [Y/N]" << std::endl;
        std::cout << "|---" << std::endl;

        std::cout << "|---TR~Init Rental: ";

        while ((!(std::cin >> choice)) || (!(utils.validateYesOrNo(choice))))

        {
            std::cout << "Y or N please: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cin >> choice;
        }

        if ((utils.lowerStr(choice) == "n"))
        {
            run = false;
            system("cls");
            mainMenu.mainMenu();
        }
        else
        {
            switch (equipmentType)
            {
            case 3:
            {
                // make atv unavailable
                sqlInit = sql.getChangeAvailabilityATVs() + std::to_string(equipmentID);
                atvs.execTableOperation(atvs.getOperationType(), atvs.getTableName(), sqlInit);
                run = false;
                break;
            }
            default:
                // make skis or snowboard unavailable
                sqlInit = sql.getChangeAvailabilitySkisSBs() + std::to_string(equipmentID);
                skisSBs.execTableOperation(skisSBs.getOperationType(), skisSBs.getTableName(), sqlInit);
                run = false;
                break;
            }
        }
        break;

    } while (run = true);
}
/*
    Displays various inventory and business statistics.
    For example, shows the number of various types of
    equipment in total in inventory and how many of them
    are on loan at any one time. Also displays total
    amount of money Thor's Rentals have made from all
    rentals.
*/
void Menu::statsMenu()
{
    Display disp;
    Utility utils;
    Menu mainMenu;
    Table table;
    Sql sql;

    std::set<int> validDigits({9});

    int choice{};
    int execTableOperation(std::string operationType, std::string tableName, std::string sql, bool verbose = false);

    int totalSkis = table.searchNumericValuesFromDB(sql.getTotalSkis());
    int skisForRent = table.searchNumericValuesFromDB(sql.getSkisForRent());

    int totalSnowboards = table.searchNumericValuesFromDB(sql.getTotalSBsForRent());
    int snowboardsForRent = table.searchNumericValuesFromDB(sql.getSBsForRent());

    int totalATVs = table.searchNumericValuesFromDB(sql.getTotalAtvs());
    int ATVsForRent = table.searchNumericValuesFromDB(sql.getATVsForRent());

    int totalCustomers = table.searchNumericValuesFromDB(sql.getTotalCustomers());
    int totalStaff = table.searchNumericValuesFromDB(sql.getTotalStaff());
    int totalAppAccessStaff = table.searchNumericValuesFromDB(sql.getTotalAccessStaff());

    int moneyMade = table.searchNumericValuesFromDB(sql.getOrdersSum());

    system("cls");

    while (true)
    {
        disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_statistics.txt");
        std::cout << "                     *********************************************************************\n";
        std::cout << "                     |                             INVENTORY                             |" << std::endl;
        std::cout << "                     |-------------------------------------------------------------------|" << std::endl;
        std::cout << "                     |       Item             Total in Inventory   Available for Rent    |" << std::endl;
        std::cout << "                     |-------------------------------------------------------------------|" << std::endl;
        std::cout << "                     |    Skis         |  \t\t" << totalSkis << "\t\t" << skisForRent << "                |" << std::endl;
        std::cout << "                     |    Snowboard    |  \t\t" << totalSnowboards << "\t\t" << snowboardsForRent << "                |" << std::endl;
        std::cout << "                     |    ATV          |  \t\t" << totalATVs << "\t\t" << ATVsForRent << "                |" << std::endl;
        std::cout << "                     |-------------------------------------------------------------------|" << std::endl;
        std::cout << "                     |------------------------Press 9 for Main Menu----------------------|" << std::endl;
        std::cout << "                     *********************************************************************\n";
        std::cout << "\n\n\n";

        std::cout << "                     *********************************************************************\n";
        std::cout << "                     |                       CUMULATIVE STATISTICS                       |" << std::endl;
        std::cout << "                     |-------------------------------------------------------------------|" << std::endl;
        std::cout << "                     |     Customers: " << totalCustomers << "                                                  |" << std::endl;
        std::cout << "                     |-------------------------------------------------------------------|" << std::endl;
        std::cout << "                     |     Staff: " << totalStaff << "                                                      |" << std::endl;
        std::cout << "                     |-------------------------------------------------------------------|" << std::endl;
        std::cout << "                     |     Staff with App Access: " << totalAppAccessStaff << "                                      |" << std::endl;
        std::cout << "                     |-------------------------------------------------------------------|" << std::endl;
        std::cout << "                                  GBP Amount Received from All Rentals: " << moneyMade << "                       " << std::endl;
        std::cout << "                     |-------------------------------------------------------------------|" << std::endl;
        std::cout << "                     |------------------------Press 9 for Main Menu----------------------|" << std::endl;
        std::cout << "                     *********************************************************************\n";
        std::cout << "\n\n";

        std::cout << "|---TR~Statistics~$: ";

        if ((!(std::cin >> choice)) || (!(utils.validateDigits(choice, validDigits))))
        {
            std::cout << "|---Thor is not happy - Please enter number 9 only" << std::endl;
            utils.pause(3);
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            system("cls");
        }
        else
        {
            break;
        }
    }
    mainMenu.mainMenu();
}
/*
    Provides a facility to return rental items by their type and ID.
    Provides a possibility to add a late / damaged equipment
    fee to total rental cost. Returned rental items are
    marked as available in their respective rental
    tables and order is marked as closed (0).
*/
void Menu::receiveItemMenu()
{
    // below integers are cast as std::string
    // to be utilised in a pre-written system
    // function

    std::string type1{std::to_string(1)};
    std::string type2{std::to_string(2)};
    std::string type3{std::to_string(3)};

    std::string sqlInit{};
    std::string returnDatetime{};
    std::string lateAnswer{};
    std::string damagedAnswer{};

    bool equipmentOnLoan{};

    int equipmentTypeChoice{};
    int equipmentIDChoice{};
    double lateFeeChoice{};
    double damagedFeeChoice{};
    double totalFees{};

    std::set<int> validDigits({});
    std::unordered_set<int> equipmentIDsOnLoanSkis{};
    std::unordered_set<int> equipmentIDsOnLoanSBs{};
    std::unordered_set<int> equipmentIDsOnLoanAtvs{};

    std::set<int> equipmentIDsOnLoanSkisOrdered{};
    std::set<int> equipmentIDsOnLoanSBsOrdered{};
    std::set<int> equipmentIDsOnLoanAtvsOrdered{};

    std::set<int> trueSizes{};
    int position{};

    Table skisSBs{"inventory_skis_snowboards", "UPDATE"};
    Table skis;
    Table SBs;
    Table atvs{"inventory_atvs", "UPDATE"};
    Table orders{"orders", "UPDATE"};
    Sql sql;
    Menu mainMenu;
    Utility utils;
    Display disp;
    Table table;

    equipmentIDsOnLoanSkis = table.getAvailableIDs(sql.getEquipmentIDsOnLoan(1));
    equipmentIDsOnLoanSBs = table.getAvailableIDs(sql.getEquipmentIDsOnLoan(2));
    equipmentIDsOnLoanAtvs = table.getAvailableIDs(sql.getEquipmentIDsOnLoan(3));

    // if there are no skis IDs that are on loan ---> insert a marker into trueSizes
    if (equipmentIDsOnLoanSkis.size() == 0)
    {
        trueSizes.insert(1);
    }
    else
    {
        // if there are skis IDs that are on loan --- > get all equipment IDs
        // on loan that are type 1 into a set
        // repeat same process for snowboards and ATVs
        equipmentIDsOnLoanSkis = skis.getAvailableIDs(sql.getEquipmentIDsOnLoan(1));
        equipmentIDsOnLoanSkisOrdered = utils.unorderedToOrdered(equipmentIDsOnLoanSkis);
        validDigits.insert(1);
    }

    if (equipmentIDsOnLoanSBs.size() == 0)
    {
        trueSizes.insert(2);
    }
    else
    {
        // get all equipment IDs on loan that are type 2 into a set
        equipmentIDsOnLoanSBs = SBs.getAvailableIDs(sql.getEquipmentIDsOnLoan(2));
        equipmentIDsOnLoanSBsOrdered = utils.unorderedToOrdered(equipmentIDsOnLoanSBs);
        validDigits.insert(2);
    }

    if (equipmentIDsOnLoanAtvs.size() == 0)
    {
        trueSizes.insert(3);
    }
    else
    {
        // get all equipment IDs on loan that are type 3 into a set
        equipmentIDsOnLoanAtvs = atvs.getAvailableIDs(sql.getEquipmentIDsOnLoan(3));
        equipmentIDsOnLoanAtvsOrdered = utils.unorderedToOrdered(equipmentIDsOnLoanAtvs);
        validDigits.insert(3);
    }

    if (trueSizes.size() == 3)
    {
        std::cout << "\n|---Nothing on loan at the minute. Please chill." << std::endl;
        utils.pause(3);
        mainMenu.mainMenu();
    }

    system("cls");
    disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_receive_item.txt");

    while (1)
    {
        // check that only equipment types that are on
        // loan are entered
        // For example, if no skis are on loan, a user cannot
        // enter type 1.
        std::cout << "|---Please enter rental equipment type: " << std::endl;
        std::cout << "|---Press [1] for skis, [2] for snowboard and [3] for ATV"
                  << "\n\n";
        std::cout << "|---TR~Receive Rental~$: ";

        if ((!(std::cin >> equipmentTypeChoice)) || (!(utils.validateDigits(equipmentTypeChoice, validDigits))))
        {
            std::cout << "|---Thor is not happy - Please enter type of equipment that is returned" << std::endl;
            utils.pause(3);
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            system("cls");
            disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_receive_item.txt");
        }
        else
        {
            break;
        }
    }

    switch (equipmentTypeChoice)
    {
    case 1: // skis
        while (1)
        {
            system("cls");
            disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_receive_item.txt");
            std::cout << "|---Please enter skis rental equipment ID: ";

            if ((!(std::cin >> equipmentIDChoice)) || (!(utils.validateDigits(equipmentIDChoice, equipmentIDsOnLoanSkisOrdered))))
            {
                std::cout << "|---Thor is not happy - Please enter valid skis rental equipment ID" << std::endl;
                utils.pause(3);
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                system("cls");
                disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_receive_item.txt");
                std::cout << "|---Please enter valid skis rental equipment ID: ";
                std::cout << "|---TR~Receive Rental~$: ";
            }
            else
            {
                break;
            }
        }
        sqlInit = sql.getReturnDatetime() + std::to_string(equipmentTypeChoice) + " AND EQUIPMENT_ID = " + std::to_string(equipmentIDChoice) + ";";
        break;

    case 2: // SBs
        while (1)
        {
            system("cls");
            disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_receive_item.txt");
            std::cout << "|---Please enter snowboard rental equipment ID: ";

            if ((!(std::cin >> equipmentIDChoice)) || (!(utils.validateDigits(equipmentIDChoice, equipmentIDsOnLoanSBsOrdered))))
            {
                std::cout << "|---Thor is not happy - Please enter valid rental snowboard equipment ID" << std::endl;
                utils.pause(3);
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                system("cls");
                disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_receive_item.txt");
                std::cout << "|---Please enter valid snowboard rental equipment ID: ";
                std::cout << "|---TR~Receive Rental~$: ";
            }
            else
            {
                break;
            }
        }
        sqlInit = sql.getReturnDatetime() + std::to_string(equipmentTypeChoice) + " AND EQUIPMENT_ID = " + std::to_string(equipmentIDChoice) + ";";
        break;

    case 3: // ATVs
        while (1)
        {
            system("cls");
            disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_receive_item.txt");
            std::cout << "|---Please enter ATV rental equipment ID: ";

            if ((!(std::cin >> equipmentIDChoice)) || (!(utils.validateDigits(equipmentIDChoice, equipmentIDsOnLoanAtvsOrdered))))
            {
                std::cout << "|---Thor is not happy - Please enter valid ATV rental equipment ID" << std::endl;
                utils.pause(3);
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                system("cls");
                disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_receive_item.txt");
                std::cout << "|---Please enter valid ATV rental equipment ID: ";
                std::cout << "|---TR~Receive Rental~$: ";
            }
            else
            {
                break;
            }
        }
        sqlInit = sql.getReturnDatetime() + std::to_string(equipmentTypeChoice) + " AND EQUIPMENT_ID = " + std::to_string(equipmentIDChoice) + ";";
        break;
    }

    returnDatetime = orders.searchTextValuesFromDB(sqlInit);
    position = returnDatetime.find(".");

    std::cout << "|---This rental item is due to be returned on: " + returnDatetime.substr(0, position) << std::endl;
    std::cout << "|---Is it late? [Y/N]: ";
    std::cin >> lateAnswer;

    while (!utils.validateYesOrNo(lateAnswer))
    {
        std::cout << "\tY or N please: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cin >> lateAnswer;
    }

    if (utils.lowerStr(lateAnswer) == "y")
    {
        std::cout << "|---Please enter late fee: ";

        while (1)
        {
            if (!(std::cin >> lateFeeChoice))
            {
                std::cout << "|---Thor is not happy - Please enter numbers only" << std::endl;
                utils.pause(3);
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                system("cls");
            }
            else
            {
                break;
            }
        }
    }
    std::cout << "|---Is equipment damaged? [Y/N]: ";
    std::cin >> damagedAnswer;

    while (!utils.validateYesOrNo(damagedAnswer))
    {
        std::cout << "\tY or N please: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cin >> damagedAnswer;
    }

    if (utils.lowerStr(damagedAnswer) == "y")
    {
        std::cout << "|---Please enter damage fee: ";

        while (1)
        {
            if (!(std::cin >> damagedFeeChoice))
            {
                std::cout << "|---Thor is not happy - Please enter numbers only" << std::endl;
                utils.pause(3);
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                system("cls");
            }
            else
            {
                break;
            }
        }
    }

    // If there are fees ---> sum up the fees ---> add them in orders table in total rental cost
    if (lateFeeChoice || damagedFeeChoice)
    {
        totalFees = lateFeeChoice + damagedFeeChoice;
        sqlInit = orders.getOperationType() + " " + orders.getTableName() + " SET COST = COST + " + std::to_string(totalFees) + " WHERE EQUIPMENT_ID = " + std::to_string(equipmentIDChoice) + " AND EQUIPMENT_TYPE = " + std::to_string(equipmentTypeChoice) + ";";
        orders.execTableOperation(orders.getOperationType(), orders.getTableName(), sqlInit);
    }

    // Change received equipment back to available for rent
    // skis and SBs
    if (equipmentTypeChoice != 3)
    {
        sqlInit = skisSBs.getOperationType() + " " + skisSBs.getTableName() + " " + "SET AVAILABLE = 1 WHERE ID = " + std::to_string(equipmentIDChoice);
        skisSBs.execTableOperation(skisSBs.getOperationType(), skisSBs.getTableName(), sqlInit);
    }
    else
    {
        // ATVs
        sqlInit = atvs.getOperationType() + " " + atvs.getTableName() + " " + "SET AVAILABLE = 1 WHERE ID = " + std::to_string(equipmentIDChoice);
        skisSBs.execTableOperation(atvs.getOperationType(), atvs.getTableName(), sqlInit);
    }
    // Change order status to 0 (closed)
    sqlInit = orders.getOperationType() + " " + orders.getTableName() + " SET STATUS = 0 WHERE EQUIPMENT_TYPE = " + std::to_string(equipmentTypeChoice) + " AND EQUIPMENT_ID = " + std::to_string(equipmentIDChoice);
    orders.execTableOperation(orders.getOperationType(), orders.getTableName(), sqlInit);

    // express Thor's happiness when he gets his equipment back
    std::cout << "\nThor is very happy! Equipment received successfully!" << std::endl;
    utils.pause(3);
    mainMenu.mainMenu();
}