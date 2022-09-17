#pragma once

class Display
{
public:
    void displayBreakText(std::string text, bool clearScreen);
    void displayASCIIFromFile(std::string filename);
    void displayATVTableColumns();
    void displaySnowboardTableColumns();
    void displaySkiTableColumns();
};