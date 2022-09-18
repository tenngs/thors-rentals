/*
    This class contains utility functions in relation
    to displaying items such as text, ASCII art
    and table columns.
*/
#pragma once

class Display
{
public:
    void displayBreakText(std::string text, bool clearScreen);
    void displayASCIIArtFromFile(std::string filename);
    void displayATVTableColumns();
    void displaySnowboardTableColumns();
    void displaySkiTableColumns();
};