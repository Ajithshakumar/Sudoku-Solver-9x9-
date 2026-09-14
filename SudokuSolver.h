#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include "Board.h"

class SudokuSolver {
private:
    Board& board;
    long long recursiveCalls;
    double executionTimeMs;
    bool stepByStep;

    bool isSafe(int row, int col, int num) const;

public:
    SudokuSolver(Board& b);
    
    // Toggle visualization
    void setStepByStep(bool enable);
    
    // Core backtracking algorithm
    bool solve();
    bool solveSudoku(int row, int col);
    
    // Metrics
    long long getRecursiveCalls() const;
    double getExecutionTime() const;
};

#endif // SUDOKU_SOLVER_H
