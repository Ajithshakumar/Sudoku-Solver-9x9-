# Sudoku Solver 🧩 (9x9)

A comprehensive 9×9 Sudoku Solver featuring both an interactive **Web Application** and a powerful **C++ Terminal Application**, powered by the **Backtracking Algorithm**.

---

## 🌟 Implementations

### 1. 🌐 Interactive Web Application
A sleek, responsive web interface built with **HTML5, CSS3, and JavaScript**.
- **Interactive 9×9 Grid**: Enter custom digits or load pre-set puzzles.
- **Backtracking Visualization**: Watch the backtracking solver in action cell-by-cell.
- **Instant Solve**: Instantly compute solutions with performance metrics (time elapsed and recursive call count).
- **Run**: Simply open `index.html` in any modern web browser.

### 2. 💻 C++ Terminal Application
A high-performance, modular CLI application built with **C++17**.
- **Features**: ANSI color-coded boards, step-by-step terminal animation, file input/output (`sample.txt`, `solved_sudoku.txt`), board validation, and performance statistics.
- **Compilation**:
  ```bash
  g++ -std=c++17 main.cpp Board.cpp SudokuSolver.cpp Utilities.cpp -o SudokuSolver
  ```
- **Execution**:
  - Windows: `.\SudokuSolver.exe`
  - Linux/macOS: `./SudokuSolver`

---

## 📁 Repository Structure

```text
SudokuSolver/
│
├── index.html           # Web UI layout
├── style.css            # Web styling and grid design
├── script.js            # Web backtracking algorithm and visualization
│
├── main.cpp             # C++ entry point and interactive menu
├── Board.h              # C++ board data structure and UI header
├── Board.cpp            # C++ grid management, validation, and rendering
├── SudokuSolver.h       # C++ solver logic header
├── SudokuSolver.cpp     # C++ backtracking algorithm implementation
├── Utilities.h          # C++ cross-platform helpers header (colors, sleep)
├── Utilities.cpp        # C++ utility implementations
│
├── sample.txt           # Sample puzzle file
├── test_input.txt       # Test input file
├── Report.md            # Academic project report
└── README.md            # Project documentation
```

---

## 🧠 Algorithm: Backtracking

The Backtracking algorithm explores possible configurations sequentially and backs out when a constraint is violated:
1. **Find an empty cell** on the 9×9 board.
2. **Try digits 1 to 9** sequentially.
3. **Validate constraints**: Check row, column, and 3×3 subgrid for duplicate values.
4. **Recurse**: Move to the next empty cell.
5. **Backtrack**: If no valid number can be placed, reset the cell to `0` and return `false` to try the previous branch.

### Complexity Analysis
- **Time Complexity**: $\mathcal{O}(9^n)$, where $n$ is the number of empty cells (upper bound in worst case).
- **Space Complexity**: $\mathcal{O}(n)$, bounded by the maximum recursion depth.

---

## 📄 Documentation
For detailed theoretical background, design architecture, and testing analysis, see [Report.md](Report.md).
