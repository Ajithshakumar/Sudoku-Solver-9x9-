#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

class Utilities {
public:
    static void clearScreen();
    static void sleepMs(int ms);
    
    // ANSI Color Codes
    static const std::string RESET;
    static const std::string BOLD;
    static const std::string RED;
    static const std::string GREEN;
    static const std::string YELLOW;
    static const std::string BLUE;
    static const std::string CYAN;
};

#endif // UTILITIES_H
