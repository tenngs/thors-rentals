/*
    Contains utility functions to display items
    such as text, ASCII art table columns and
    available equipment to rent
*/
#pragma once

class Display
{
public:
    void displayBreakText(std::string const &text, bool clearScreen);
    void displayASCIIArtFromFile(std::string const &filename);
    void displayAvailableEquipment(std::string const &tableName, int const &type);
    void displayATVTableColumns();
    void displaySnowboardTableColumns();
    void displaySkiTableColumns();
};