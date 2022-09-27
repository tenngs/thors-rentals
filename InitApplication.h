/*
    Contains a function to
    drop, initialise and populate system's
    tables and to display a "loading" text
    and login ASCII art banner.
*/
#pragma once

class InitApplication
{
private:
    std::string name;

public:
    InitApplication(std::string name_val);
    void initApp();
};
