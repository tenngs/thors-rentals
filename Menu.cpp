#include <iostream>
#include <set>
#include <vector>
#include <string>
#include "Display.h"
#include "Utility.h"
#include "Table.h"
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
    // init valid range
    std::set<int> validDigits({1, 2, 3, 4, 5, 6, 7});
    bool Shutdown = false;
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
                // Mainmenu::showInitRentalMenu();
                break;
            case 5:
                std::cout << "This is case 5" << std::endl;
                break;
            case 6:
                // Mainmenu::showStatisticsMenu();
                // std::cout << "This is case 6" << std::endl;
                break;
            case 7:
                // Utility::shutdown();
                break;
            }
        }
    }
}

/*
    Displays and facilitates Add Customer menu options
    for a user. Utilises a std::vector<std::string>
    to collect pieces of user-entered information that
    will be upon confirmation from a user utilised to
    add a customer to customers table.
*/
void Menu::addCustomerMenu()
{
    // initialise variables to be used in capturing user
    // input and to perform table operations
    std::vector<std::string> customerInfo{};
    std::string infoPiece{};
    std::string successMsg = "Customer added successfully";
    std::string answer = {};

    Display disp;
    Utility utils;
    Sql sql;
    Table customers;

    while (true)
    {
        // clear screen, display location banners
        // and ask for customer information
        system("cls");
        disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals.txt");
        disp.displayASCIIArtFromFile("ASCIIArt/add_customer.txt");

        std::cout << "|---Please enter customer's first name" << std::endl;
        std::cout << "|---TR~Add Customer~$: ";
        std::cin >> infoPiece;
        customerInfo.push_back(infoPiece);

        std::cout << "|---Please enter customer's surname" << std::endl;
        std::cout << "|---TR~Add Customer~$: ";
        std::cin >> infoPiece;
        std::cin.ignore();
        customerInfo.push_back(infoPiece);

        std::cout << "|---Please enter customer's first line of address" << std::endl;
        std::cout << "|---TR~Add Customer~$: ";
        std::getline(std::cin, infoPiece);
        customerInfo.push_back(infoPiece);

        std::cout << "|---Please enter customer's postcode" << std::endl;
        std::cout << "|---TR~Add Customer~$: ";
        std::cin >> infoPiece;
        customerInfo.push_back(infoPiece);

        std::cout << "|---Please enter customer's city" << std::endl;
        std::cout << "|---TR~Add Customer~$: ";
        std::cin >> infoPiece;
        customerInfo.push_back(infoPiece);

        std::cout << "|---Please enter customer's email" << std::endl;
        std::cout << "|---TR~Add Customer~$: ";
        std::cin >> infoPiece;
        customerInfo.push_back(infoPiece);

        // clear screen
        system("cls");
        // show banners
        disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals.txt");
        disp.displayASCIIArtFromFile("ASCIIArt/add_customer.txt");
        // display user info they have entered
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

    // TO DO: create universal sqlite bind insert to table function
    // and call it at the end
    // if user confirms that their input is correct
    // then insert information to a table in DB
    customers.appInsertTableOperation(successMsg, customerInfo, customerInfo.size(), sql.getAddCustomerStmnt());
}

/*
    Displays and facilitates Add Staff menu options
    for a user. Utilises a std::vector<std::string>
    to collect pieces of user-entered information that
    will be upon confirmation from a user utilised to
    add a staff member to system_access table thereby
    granting that staff member access to this application.
*/
void Menu::addStaffMenu()
{

    std::vector<std::string> staffInfo{};
    std::string infoPiece{};
    std::string successMsg = "Staff member added and granted app access successfully";
    std::string answer = {};

    Display disp;
    Utility utils;
    Sql sql;
    Table staff;

    while (true)
    {
        // clear screen, display location banners
        // and ask for customer information
        system("cls");
        disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_add_staff.txt");

        std::cout << "|---Please enter staff member's username" << std::endl;
        std::cout << "|---TR~Add Staffr~$: ";
        std::cin >> infoPiece;
        std::cin.ignore();
        staffInfo.push_back(infoPiece);

        std::cout << "|---Please enter staff member's password" << std::endl;
        std::cout << "|---TR~Add Staff~$: ";
        std::getline(std::cin, infoPiece);
        staffInfo.push_back(infoPiece);

        // push back a string zero to indicate that the staff
        // member is not currently logged on
        staffInfo.push_back(std::to_string(0));
        // clear screen
        system("cls");
        // show banners
        disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_add_staff.txt");

        // display user info they have entered
        std::cout << "\tYou entered: \n\n";
        std::cout << "\tUsername: "
                  << "\t" << staffInfo[0] << std::endl;
        std::cout << "\tPassword: "
                  << "\t" << staffInfo[1] << std::endl;

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

    // TO DO: create universal sqlite bind insert to table function
    // and call it at the end
    // if user confirms that their input is correct
    // then insert information to a table in DB

    staff.appInsertTableOperation(successMsg, staffInfo, staffInfo.size(), sql.getAddStaffStmnt());
}

void Menu::addItemMenu()
{
    std::vector<std::string> equipmentInfo{};
    std::string infoPiece{};
    std::string successMsg = {};
    std::string sqlStmnt = {};
    std::string answer = {};
    bool run = true;
    std::set<int> validDigits({1, 2});
    int choice{};

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

        if ((!(std::cin >> choice)) || (!(utils.validateDigits(choice, validDigits))))
        {
            std::cout << "|---Thor is not happy - Please enter numbers 1-2 only" << std::endl;
            utils.pause(3);
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }

        else
        {
            switch (choice)
            {
            case 1:
                system("cls");
                disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_add_item.txt");
                std::cout << "|---Please enter make" << std::endl;
                std::cout << "|---TR~Add Skis & Snowboards~$: ";
                std::cin >> infoPiece;
                equipmentInfo.push_back(infoPiece);

                std::cout << "|---Please enter model" << std::endl;
                std::cout << "|---TR~Add Skis & Snowboards~$: ";
                std::cin >> infoPiece;
                std::cin.ignore();
                equipmentInfo.push_back(infoPiece);

                std::cout << "|---Please enter price per hour" << std::endl;
                std::cout << "|---TR~Add Skis & Snowboards~$: ";
                std::getline(std::cin, infoPiece);
                equipmentInfo.push_back(infoPiece);

                std::cout << "|---Please enter price per day" << std::endl;
                std::cout << "|---TR~Add Skis & Snowboards~$: ";
                std::cin >> infoPiece;
                equipmentInfo.push_back(infoPiece);

                std::cout << "|---Please enter equipment type: [1] skis - [2] Snowboard" << std::endl;
                std::cout << "|---TR~Add Skis & Snowboards~$: ";
                // TO DO: Validate 1 or 2
                std::cin >> infoPiece;
                equipmentInfo.push_back(infoPiece);

                std::cout << "|---Please enter rental status\n:" << std::endl;
                std::cout << "|---[0] for NOT available for rent" << std::endl;
                std::cout << "|---[1] for AVAILABLE for rent" << std::endl;
                std::cout << "\n|---TR~Add Skis & Snowboards~$: ";
                std::cin >> infoPiece;
                equipmentInfo.push_back(infoPiece);

                // user is entering type 1 - skis & snowboards
                // infoPiece = std::to_string(1);
                // equipmentInfo.push_back(infoPiece);
                // clear screen
                system("cls");
                // show banners
                disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_add_item.txt");
                std::cout << "\tYou entered: \n\n";
                std::cout << "\tMake: "
                          << "\t\t\t" << equipmentInfo[0] << std::endl;
                std::cout << "\tModel: "
                          << "\t\t\t" << equipmentInfo[1] << std::endl;
                std::cout << "\tPrice per hour: "
                          << "\t" << equipmentInfo[2] << std::endl;
                std::cout << "\tPrice per day: "
                          << "\t\t" << equipmentInfo[3] << std::endl;
                std::cout << "\tEquipment type: "
                          << "\t" << equipmentInfo[4] << std::endl;
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
                std::cin >> infoPiece;
                equipmentInfo.push_back(infoPiece);

                std::cout << "|---Please enter model" << std::endl;
                std::cout << "|---TR~Add ATV~$: ";
                std::cin >> infoPiece;
                std::cin.ignore();
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
                equipmentInfo.push_back(infoPiece);

                std::cout << "|---Please enter price per hour" << std::endl;
                std::cout << "|---TR~Add ATV~$: ";
                std::getline(std::cin, infoPiece);
                equipmentInfo.push_back(infoPiece);

                std::cout << "|---Please enter price per day" << std::endl;
                std::cout << "|---TR~Add ATV~$: ";
                std::cin >> infoPiece;
                equipmentInfo.push_back(infoPiece);

                std::cout << "|---Please enter 0 for not available for rent" << std::endl;
                std::cout << "|---Or 1 for available for rent" << std::endl;
                std::cout << "|---TR~Add ATV~$: ";
                std::cin >> infoPiece;
                equipmentInfo.push_back(infoPiece);

                system("cls");
                disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_add_item.txt");

                std::cout << "\tYou entered: \n\n";
                std::cout << "\tMake: "
                          << "\t\t\t" << equipmentInfo[0] << std::endl;
                std::cout << "\tModel: "
                          << "\t\t\t" << equipmentInfo[1] << std::endl;
                std::cout << "\tReg: "
                          << "\t\t\t" << equipmentInfo[2] << std::endl;
                std::cout << "\tFuel type: "
                          << "\t\t" << equipmentInfo[3] << std::endl;
                std::cout << "\tPrice per hour: "
                          << "\t" << equipmentInfo[4] << std::endl;
                std::cout << "\tPrice per day: "
                          << "\t\t" << equipmentInfo[5] << std::endl;
                std::cout << "\tAvailable: "
                          << "\t\t" << equipmentInfo[6] << std::endl;

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

    inventory.appInsertTableOperation(successMsg, equipmentInfo, equipmentInfo.size(), sqlStmnt);
}
