#include <iostream>
#include <limits>
#include "Board.h"
#include "SudokuSolver.h"
#include "Utilities.h"

void displayMenu() {
    std::cout << Utilities::BOLD << Utilities::CYAN << "\n=== SUDOKU SOLVER MENU ===\n" << Utilities::RESET;
    std::cout << "1. Load Sample Puzzle (sample.txt)\n";
    std::cout << "2. Enter Puzzle Manually\n";
    std::cout << "3. Validate Current Board\n";
    std::cout << "4. Solve Instantly\n";
    std::cout << "5. Solve with Visualization (Step-by-Step)\n";
    std::cout << "6. Save Solved Puzzle\n";
    std::cout << "7. Reset Board\n";
    std::cout << "8. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    Board board;
    SudokuSolver solver(board);
    int choice;

    while (true) {
        board.printBoard();
        displayMenu();
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                if (board.loadFromFile("sample.txt")) {
                    std::cout << Utilities::GREEN << "Puzzle loaded successfully!\n" << Utilities::RESET;
                } else {
                    std::cout << Utilities::RED << "Error: Could not load sample.txt\n" << Utilities::RESET;
                }
                Utilities::sleepMs(1000);
                break;
            case 2:
                board.inputManually();
                break;
            case 3:
                if (board.validateBoard()) {
                    std::cout << Utilities::GREEN << "The current board is VALID.\n" << Utilities::RESET;
                } else {
                    std::cout << Utilities::RED << "The current board is INVALID! Please check the constraints.\n" << Utilities::RESET;
                }
                Utilities::sleepMs(2000);
                break;
            case 4:
            case 5:
                if (!board.validateBoard()) {
                    std::cout << Utilities::RED << "Cannot solve an invalid board.\n" << Utilities::RESET;
                    Utilities::sleepMs(2000);
                    break;
                }
                solver.setStepByStep(choice == 5);
                std::cout << Utilities::YELLOW << "Solving...\n" << Utilities::RESET;
                if (solver.solve()) {
                    board.printBoard();
                    std::cout << Utilities::GREEN << Utilities::BOLD << "\nSudoku Solved Successfully!\n" << Utilities::RESET;
                    std::cout << Utilities::CYAN << "Execution Time: " << Utilities::RESET << solver.getExecutionTime() << " ms\n";
                    std::cout << Utilities::CYAN << "Recursive Calls: " << Utilities::RESET << solver.getRecursiveCalls() << "\n";
                } else {
                    std::cout << Utilities::RED << "No solution exists for this Sudoku.\n" << Utilities::RESET;
                }
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore();
                std::cin.get();
                break;
            case 6:
                if (board.saveToFile("solved_sudoku.txt")) {
                    std::cout << Utilities::GREEN << "Saved to solved_sudoku.txt\n" << Utilities::RESET;
                } else {
                    std::cout << Utilities::RED << "Error saving file.\n" << Utilities::RESET;
                }
                Utilities::sleepMs(1500);
                break;
            case 7:
                board.reset();
                std::cout << Utilities::YELLOW << "Board reset.\n" << Utilities::RESET;
                Utilities::sleepMs(1000);
                break;
            case 8:
                std::cout << Utilities::CYAN << "Exiting... Thank you for using Sudoku Solver!\n" << Utilities::RESET;
                return 0;
            default:
                std::cout << Utilities::RED << "Invalid choice. Please try again.\n" << Utilities::RESET;
                Utilities::sleepMs(1000);
        }
    }
    return 0;
}
