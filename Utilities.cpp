#include "Utilities.h"
#include <iostream>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#endif

const std::string Utilities::RESET = "\033[0m";
const std::string Utilities::BOLD = "\033[1m";
const std::string Utilities::RED = "\033[31m";
const std::string Utilities::GREEN = "\033[32m";
const std::string Utilities::YELLOW = "\033[33m";
const std::string Utilities::BLUE = "\033[34m";
const std::string Utilities::CYAN = "\033[36m";

void Utilities::clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void Utilities::sleepMs(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
