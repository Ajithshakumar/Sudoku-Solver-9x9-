#include "Board.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <set>

Board::Board() {
    grid.assign(9, std::vector<int>(9, 0));
    original.assign(9, std::vector<bool>(9, false));
}

void Board::reset() {
    grid.assign(9, std::vector<int>(9, 0));
    original.assign(9, std::vector<bool>(9, false));
}

int Board::getCell(int row, int col) const {
    return grid[row][col];
}

void Board::setCell(int row, int col, int value) {
    grid[row][col] = value;
}

std::vector<std::vector<int>>& Board::getGrid() {
    return grid;
}

bool Board::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    
    reset();
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            file >> grid[i][j];
            if (grid[i][j] != 0) {
                original[i][j] = true;
            }
        }
    }
    file.close();
    return true;
}

bool Board::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            file << grid[i][j] << (j == 8 ? "" : " ");
        }
        file << "\n";
    }
    file.close();
    return true;
}

void Board::inputManually() {
    reset();
    std::cout << Utilities::CYAN << "Enter the 9x9 Sudoku board (use 0 for empty cells):\n" << Utilities::RESET;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            std::cin >> grid[i][j];
            if (grid[i][j] != 0) {
                original[i][j] = true;
            }
        }
    }
}

void Board::printBoard() const {
    printBoardWithHighlight(-1, -1, "");
}

void Board::printBoardWithHighlight(int hRow, int hCol, const std::string& status) const {
    Utilities::clearScreen();
    std::cout << Utilities::BOLD << Utilities::CYAN << "\n=== SUDOKU SOLVER ===\n" << Utilities::RESET;
    if (!status.empty()) {
        std::cout << Utilities::YELLOW << "Status: " << status << "\n" << Utilities::RESET;
    }
    std::cout << Utilities::BLUE << "+-------+-------+-------+\n" << Utilities::RESET;
    
    for (int i = 0; i < 9; ++i) {
        std::cout << Utilities::BLUE << "| " << Utilities::RESET;
        for (int j = 0; j < 9; ++j) {
            if (i == hRow && j == hCol) {
                std::cout << Utilities::GREEN << Utilities::BOLD << grid[i][j] << Utilities::RESET << " ";
            } else if (original[i][j]) {
                std::cout << Utilities::BOLD << grid[i][j] << Utilities::RESET << " ";
            } else if (grid[i][j] == 0) {
                std::cout << ". ";
            } else {
                std::cout << Utilities::CYAN << grid[i][j] << Utilities::RESET << " ";
            }
            
            if ((j + 1) % 3 == 2) {
                std::cout << Utilities::BLUE << "| " << Utilities::RESET;
            }
        }
        std::cout << "\n";
        
        if ((i + 1) % 3 == 2) {
            std::cout << Utilities::BLUE << "+-------+-------+-------+\n" << Utilities::RESET;
        }
    }
    std::cout << "\n";
}

bool Board::isValidInput(int row, int col, int value) const {
    // Check row
    for (int i = 0; i < 9; i++) {
        if (i != col && grid[row][i] == value) return false;
    }
    // Check column
    for (int i = 0; i < 9; i++) {
        if (i != row && grid[i][col] == value) return false;
    }
    // Check 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ((i + startRow != row || j + startCol != col) && grid[i + startRow][j + startCol] == value) {
                return false;
            }
        }
    }
    return true;
}

bool Board::validateBoard() const {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] != 0 && !isValidInput(i, j, grid[i][j])) {
                return false;
            }
        }
    }
    return true;
}

bool Board::findEmptyCell(int& row, int& col) const {
    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}
