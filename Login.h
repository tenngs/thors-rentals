/*
    This class provides a login facility for
    a user. User is given 3 attempts each to
    enter a correct username and password. The
    validity of login details are checked from a
    Sqlite database. If the database does not
    contain user-entered login details in its
    system_access database, login is denied.
*/
#pragma once

class Login
{
public:
    bool loginPrompt();
    std::string getPassword(const char *prompt);
};