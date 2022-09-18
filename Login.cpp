
#include <string>
#include <iostream>

#include "Login.h"
#include "Sql.h"
#include <windows.h>
#include "Table.h"
#include "Utility.h"

/*
    Provides three attempts each to enter a valid
    username and password for a user.
    Displays textual login prompt for user.
*/
bool Login::loginPrompt()
{
    std::string enteredUsername;
    int usernameAttempt = 3;
    bool usernameCorrect = false;
    int passwordAttempt = 3;
    std::string sqlInit{};

    Utility utils;
    Sql sql;
    Table systemAccess{"system_access", "UPDATE"};

    while (usernameAttempt != 0)
    {
        --usernameAttempt;
        std::cout << "|---Please enter username" << std::endl;
        std::cout << "|---TR~Login~$: ";

        std::cin >> enteredUsername;

        if (systemAccess.searchTextValuesFromDB(enteredUsername, sql.getValidateUsernameStmnt()))
        {
            std::cout << "|---Username found - all good" << std::endl;
            usernameCorrect = true;
            break;
        }
        else if (usernameAttempt != 1)
        {
            std::cout << "|---Username not found. You have " << usernameAttempt << " attempts remaining. -- " << std::endl;
            if (usernameAttempt == 0)
            {
                return false;
            }
        }
        else
        {
            std::cout << "|---Username not found. You have " << usernameAttempt << " attempt remaining." << std::endl;
        }
    }
    if (usernameCorrect)
    {
        while (passwordAttempt != 0)
        {
            --passwordAttempt;
            std::cout << "|---Please enter password" << std::endl;
            std::string enteredPassword = Login::getPassword("|---TR~Login~$: ");

            if (systemAccess.searchTextValuesFromDB(enteredPassword, enteredUsername, sql.getValidateUnamePasswordStmnt()))
            {
                std::cout << "|---password bueno - logging in" << std::endl;
                utils.pause(2);

                // set currently logged on user LOGGED_ON field to 1 to
                // indicate a user that is currently logged on
                sqlInit = sql.getUpdateSystemAccessStaffStmnt() + enteredUsername + "\';";
                systemAccess.execTableOperation(systemAccess.getOperationType(), systemAccess.getTableName(), sqlInit);

                return true;
            }
            else if (passwordAttempt != 1)
            {
                std::cout << "|---Incorrect password. You have " << passwordAttempt << " attempts remaining. -- " << std::endl;
                if (passwordAttempt == 0)
                {
                    return false;
                }
            }
            else
            {
                std::cout << "|---Incorrect password. You have " << passwordAttempt << " attempt remaining." << std::endl;
            }
        }
    }
}

/*
    Provides a utility whereas a user-entered
    password is masked as asterisks
*/
std::string Login::getPassword(const char *prompt)
{
    const char BACKSPACE = 8;
    const char RETURN = 13;

    std::string password;
    unsigned char ch = 0;

    std::cout << prompt;

    DWORD con_mode;
    DWORD dwRead;

    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

    GetConsoleMode(hIn, &con_mode);
    SetConsoleMode(hIn, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

    while (ReadConsoleA(hIn, &ch, 1, &dwRead, NULL) && ch != RETURN)
    {
        if (ch == BACKSPACE)
        {
            if (password.length() != 0)
            {
                std::cout << "\b \b";
                password.resize(password.length() - 1);
            }
        }
        else
        {
            password += ch;
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return password;
}