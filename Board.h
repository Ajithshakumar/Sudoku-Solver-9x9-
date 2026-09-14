#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <utility>

class Board {
private:
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<bool>> original;

public:
    Board();
    
    // Basic operations
    void reset();
    int getCell(int row, int col) const;
    void setCell(int row, int col, int value);
    std::vector<std::vector<int>>& getGrid();
    
    // Core features
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;
    void inputManually();
    
    // UI
    void printBoard() const;
    void printBoardWithHighlight(int hRow, int hCol, const std::string& status) const;
    
    // Validation
    bool isValidInput(int row, int col, int value) const;
    bool validateBoard() const;
    
    // Get empty cells for solving
    bool findEmptyCell(int& row, int& col) const;
};

#endif // BOARD_H
