#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
#include <map>
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
            {
                // TO DO: make one class and call all the functions
                // from there
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

        system("cls");
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
    customers.appInsertTableOperation(successMsg, customerInfo, sql.getAddCustomerStmnt());
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
        // and ask for staff member's information
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

        std::cout << "|---Please enter staff member's staff ID" << std::endl;
        std::cout << "|---TR~Add Staff~$: ";
        std::getline(std::cin, infoPiece);
        staffInfo.push_back(infoPiece);

        system("cls");
        disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_add_staff.txt");

        // display user info they have entered
        std::cout << "\tYou entered: \n\n";
        std::cout << "\tUsername: "
                  << "\t" << staffInfo[0] << std::endl;
        std::cout << "\tPassword: "
                  << "\t" << staffInfo[1] << std::endl;
        std::cout << "\tStaff ID: "
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

    staff.appInsertTableOperation(successMsg, staffInfo, sql.getAddStaffStmnt());
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

                system("cls");
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

    inventory.appInsertTableOperation(successMsg, equipmentInfo, sqlStmnt);
}

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
                    std::cout << "Thor is not happy - please enter a number matching customer ID" << std::endl;
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

void Menu::chooseEquipmentMenu(Order &initOrder)
{
    int userSuppliedEquimentID{};
    int choice{};
    bool run = true;

    std::set<int> validDigits({1, 2, 3, 9});
    std::unordered_set<int> validEquipmentIDs{};

    std::string sqlInit{};
    std::string returnDateTime{};

    const char *sql{};
    int resultID = {};

    Display disp;
    Utility utils;
    Table inventory;
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
                validEquipmentIDs = inventory.getAvailableEquipmentIDs("inventory_skis_snowboards", 1);
                // if no available SBs are in inventory
                if (validEquipmentIDs.size() == 0)
                {
                    std::cout << "No skis available for rent at the moment" << std::endl;
                    system("pause");
                    system("cls");
                    disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_init_rental.txt");
                    break; // TO DO: figure out how to break
                }

                // otherwise display available SBs
                system("cls");
                disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_init_rental.txt");
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
                validEquipmentIDs = inventory.getAvailableEquipmentIDs("inventory_skis_snowboards", 2);
                // if no available SBs are in inventory
                if (validEquipmentIDs.size() == 0)
                {
                    std::cout << "No snowboards available for rent at the moment" << std::endl;
                    system("pause");
                    system("cls");
                    disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_init_rental.txt");
                    break; // TO DO: figure out how to break
                }

                // otherwise display available SBs
                system("cls");
                disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_init_rental.txt");
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
                validEquipmentIDs = inventory.getAvailableEquipmentIDs("inventory_atvs", 3);
                // if no available ATVs are in inventory
                if (validEquipmentIDs.size() == 0)
                {
                    std::cout << "No ATVs available for rent at the moment" << std::endl;
                    system("pause");
                    system("cls");
                    disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_init_rental.txt");
                    break; // TO DO: figure out how to break
                }

                // otherwise display available ATVs
                system("cls");
                disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_init_rental.txt");
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
            case 1: // HOURS

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

            case 2: // DAYS
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

        std::cout << "|-----TR Order #" << initOrder.getOrderID() << "-----|"
                  << std::endl;
        std::cout << "|---------for"
                  << "---------|\n"
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

void Menu::statsMenu()
{
    Display disp;
    Utility utils;
    Menu mainMenu;
    Table table;
    Sql sql;

    std::set<int> validDigits({9});
    int choice{};
    // SQL statements

    int totalSkis = table.searchNumericValuesFromDB(sql.getTotalSkis());
    int skisForRent = table.searchNumericValuesFromDB(sql.getSkisForRent());

    int totalSnowboards = table.searchNumericValuesFromDB(sql.getTotalSBsForRent());
    int snowboardsForRent = table.searchNumericValuesFromDB(sql.getSBsForRent());

    int totalATVs = table.searchNumericValuesFromDB(sql.getTotalAtvs());
    int ATVsForRent = table.searchNumericValuesFromDB(sql.getATVsForRent());

    int totalCustomers = table.searchNumericValuesFromDB(sql.getTotalCustomers());
    int totalStaff = table.searchNumericValuesFromDB(sql.getTotalStaff());
    int totalAppAccessStaff = table.searchNumericValuesFromDB(sql.getTotalAccessStaff());

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
        std::cout << "                     |     GBP Amount Received from All Rentals:                         |" << std::endl;
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

void Menu::receiveItemMenu()
{
    std::string choice{};
    std::string sqlInit{};
    // below integers are cast as std::string
    // because a system function already exist to do the
    // required job with std::string
    // otherwise, a new system function would
    // have to be written
    std::string type1{std::to_string(1)};
    std::string type2{std::to_string(2)};
    std::string type3{std::to_string(3)};
    bool run = true;

    Table orders;
    Sql sql;
    Menu mainMenu;
    Utility utils;

    // check if type 1 or 2 is on loan
    bool type1_2OnLoan{orders.determineExistenceTextValuesInDB(type1, type2, sql.getEquipmentType1_2OnLoan())};
    // check if type 3 is on loan
    bool type3OnLoan{orders.determineExistenceTextValuesInDB(type3, sql.getEquipmentType3OnLoan())};

    if (!(type1_2OnLoan) || (!(type3OnLoan)))
    {
        std::cout << "Nothing on loan at the minute. Please chill." << std::endl;
        utils.pause(3);
        mainMenu.mainMenu();
    }

    if (type1_2OnLoan)
    {
        // SQL statement to get all ids on loan that are type 1 or 2
        // SELECT EQUIPMENT_ID FROM orders WHERE EQUIPMENT_TYPE = 1 OR EQUIPMENT_TYPE = 2 AND STATUS = 1;
        // get all ids in a set
        // iterate through result rows and put them in a set

        // LOOK AT Table::getAvailableEquipmentIDs(std::string tableName, int type)
    }

    if (type3OnLoan)
    {
        // SQL statement to get all ids on loan that are type 3
        // SELECT EQUIPMENT_ID FROM orders WHERE EQUIPMENT_TYPE = 3 AND STATUS = 1;
        // get all ids in a set
    }

    // get all type 3 equipment IDs into a set

    // int equipmentType{};
    // int equipmentID{};

    // Table atvs{"inventory_atvs", "UPDATE"};
    // Table skisSBs{"inventory_skis_snowboards", "UPDATE"};

    // Menu mainMenu;
    // Display disp;
    // Utility utils;
    // Sql sql;

    // while (true)
    // {
    //     system("cls");
    //     disp.displayASCIIArtFromFile("ASCIIArt/thors_rentals_receive_item.txt");

    //     std::cout << "|---Please enter rental equipment type: " << std::endl;
    //     std::cin <
    //         std::cout << "|---Maximum 11 - no half hours allowed" << std::endl;
    //     std::cout << "|---" << std::endl;
    //     std::cout << "|---TR~Init Rental: ";
    // }
}