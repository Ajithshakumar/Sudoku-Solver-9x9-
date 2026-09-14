#include "SudokuSolver.h"
#include "Utilities.h"
#include <chrono>

SudokuSolver::SudokuSolver(Board& b) : board(b), recursiveCalls(0), executionTimeMs(0.0), stepByStep(false) {}

void SudokuSolver::setStepByStep(bool enable) {
    stepByStep = enable;
}

bool SudokuSolver::isSafe(int row, int col, int num) const {
    return board.isValidInput(row, col, num);
}

bool SudokuSolver::solve() {
    recursiveCalls = 0;
    auto start = std::chrono::high_resolution_clock::now();
    
    bool result = solveSudoku(0, 0);
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    executionTimeMs = duration.count();
    
    return result;
}

bool SudokuSolver::solveSudoku(int row, int col) {
    recursiveCalls++;
    
    // Find the next empty cell
    if (!board.findEmptyCell(row, col)) {
        return true; // Puzzle solved
    }

    // Try all numbers from 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(row, col, num)) {
            // Assign tentatively
            board.setCell(row, col, num);
            
            if (stepByStep) {
                board.printBoardWithHighlight(row, col, "Solving... Backtracking Algorithm at work");
                Utilities::sleepMs(50); // Small delay for visualization
            }

            // Recursively solve the rest of the board
            if (solveSudoku(row, col)) {
                return true;
            }

            // Backtrack: If assigning num doesn't lead to a solution, reset it
            board.setCell(row, col, 0);
            
            if (stepByStep) {
                board.printBoardWithHighlight(row, col, "Backtracking... undoing " + std::to_string(num));
                Utilities::sleepMs(20);
            }
        }
    }
    return false; // Triggers backtracking
}

long long SudokuSolver::getRecursiveCalls() const {
    return recursiveCalls;
}

double SudokuSolver::getExecutionTime() const {
    return executionTimeMs;
}
