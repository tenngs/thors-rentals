/*
    Provides a login facility for
    a user. User is given 3 attempts each to
    enter a correct username and password. The
    validity of login details are checked from system_access
    table in thors_rentals database.
    If the table does not contain user-entered
    login details, login is denied.
*/
#pragma once

class Login
{
public:
    bool loginPrompt();
    std::string getPassword(const char *prompt);
};