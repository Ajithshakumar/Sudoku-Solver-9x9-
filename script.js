const boardEl = document.getElementById('sudoku-board');
const loadBtn = document.getElementById('load-btn');
const solveInstantlyBtn = document.getElementById('solve-instantly-btn');
const visualizeBtn = document.getElementById('visualize-btn');
const resetBtn = document.getElementById('reset-btn');

const statusText = document.getElementById('status-text');
const timeText = document.getElementById('time-text');
const callsText = document.getElementById('calls-text');

let grid = Array(9).fill().map(() => Array(9).fill(0));
let inputs = [];
let recursiveCalls = 0;
let isVisualizing = false;
let stopRequested = false;

const samplePuzzle = [
    [5, 3, 0, 0, 7, 0, 0, 0, 0],
    [6, 0, 0, 1, 9, 5, 0, 0, 0],
    [0, 9, 8, 0, 0, 0, 0, 6, 0],
    [8, 0, 0, 0, 6, 0, 0, 0, 3],
    [4, 0, 0, 8, 0, 3, 0, 0, 1],
    [7, 0, 0, 0, 2, 0, 0, 0, 6],
    [0, 6, 0, 0, 0, 0, 2, 8, 0],
    [0, 0, 0, 4, 1, 9, 0, 0, 5],
    [0, 0, 0, 0, 8, 0, 0, 7, 9]
];

function initBoard() {
    boardEl.innerHTML = '';
    inputs = [];
    for (let i = 0; i < 9; i++) {
        let rowInputs = [];
        for (let j = 0; j < 9; j++) {
            const input = document.createElement('input');
            input.type = 'text';
            input.maxLength = 1;
            input.className = 'cell';
            input.dataset.row = i;
            input.dataset.col = j;
            input.addEventListener('input', handleInput);
            boardEl.appendChild(input);
            rowInputs.push(input);
        }
        inputs.push(rowInputs);
    }
}

function handleInput(e) {
    const val = e.target.value;
    if (!/^[1-9]$/.test(val)) {
        e.target.value = '';
    } else {
        e.target.classList.add('original');
    }
}

function loadSample() {
    resetBoard();
    for (let i = 0; i < 9; i++) {
        for (let j = 0; j < 9; j++) {
            if (samplePuzzle[i][j] !== 0) {
                inputs[i][j].value = samplePuzzle[i][j];
                inputs[i][j].classList.add('original');
            }
        }
    }
    statusText.textContent = "Sample Loaded";
    statusText.className = "";
}

function resetBoard() {
    stopRequested = true;
    for (let i = 0; i < 9; i++) {
        for (let j = 0; j < 9; j++) {
            inputs[i][j].value = '';
            inputs[i][j].className = 'cell';
            grid[i][j] = 0;
        }
    }
    recursiveCalls = 0;
    callsText.textContent = "0";
    timeText.textContent = "0 ms";
    statusText.textContent = "Waiting for input...";
    statusText.className = "";
    toggleButtons(false);
}

function syncGridFromUI() {
    for (let i = 0; i < 9; i++) {
        for (let j = 0; j < 9; j++) {
            grid[i][j] = inputs[i][j].value ? parseInt(inputs[i][j].value) : 0;
        }
    }
}

function isValid(board, row, col, num) {
    for (let x = 0; x < 9; x++) {
        if (board[row][x] === num || board[x][col] === num) return false;
    }
    let startRow = row - row % 3, startCol = col - col % 3;
    for (let i = 0; i < 3; i++) {
        for (let j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] === num) return false;
        }
    }
    return true;
}

function findEmpty(board) {
    for (let i = 0; i < 9; i++) {
        for (let j = 0; j < 9; j++) {
            if (board[i][j] === 0) return [i, j];
        }
    }
    return null;
}

// Instant Solve Algorithm
function solveSudokuInstant(board) {
    recursiveCalls++;
    const emptyPos = findEmpty(board);
    if (!emptyPos) return true;
    
    let [row, col] = emptyPos;
    for (let num = 1; num <= 9; num++) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num;
            if (solveSudokuInstant(board)) return true;
            board[row][col] = 0;
        }
    }
    return false;
}

// Async Solve Algorithm for Visualization
const delay = ms => new Promise(res => setTimeout(res, ms));

async function solveSudokuVisual(board) {
    if (stopRequested) return false;
    recursiveCalls++;
    callsText.textContent = recursiveCalls;
    
    const emptyPos = findEmpty(board);
    if (!emptyPos) return true;
    
    let [row, col] = emptyPos;
    inputs[row][col].classList.add('solving');
    
    for (let num = 1; num <= 9; num++) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num;
            inputs[row][col].value = num;
            await delay(10); // UI Sleep
            
            if (await solveSudokuVisual(board)) {
                inputs[row][col].classList.remove('solving');
                inputs[row][col].classList.add('solved');
                return true;
            }
            
            board[row][col] = 0;
            inputs[row][col].value = '';
            await delay(10);
        }
    }
    inputs[row][col].classList.remove('solving');
    return false;
}

function toggleButtons(disabled) {
    loadBtn.disabled = disabled;
    solveInstantlyBtn.disabled = disabled;
    visualizeBtn.disabled = disabled;
}

async function startSolve(visualize) {
    syncGridFromUI();
    stopRequested = false;
    recursiveCalls = 0;
    callsText.textContent = "0";
    timeText.textContent = "Solving...";
    statusText.textContent = visualize ? "Visualizing Backtracking..." : "Solving...";
    statusText.className = "solving";
    toggleButtons(true);
    
    const start = performance.now();
    
    let success = false;
    if (visualize) {
        success = await solveSudokuVisual(grid);
    } else {
        success = solveSudokuInstant(grid);
        if (success) {
            for (let i = 0; i < 9; i++) {
                for (let j = 0; j < 9; j++) {
                    if (!inputs[i][j].classList.contains('original')) {
                        inputs[i][j].value = grid[i][j];
                        inputs[i][j].classList.add('solved');
                    }
                }
            }
        }
    }
    
    const end = performance.now();
    timeText.textContent = (end - start).toFixed(2) + " ms";
    callsText.textContent = recursiveCalls;
    
    if (success) {
        statusText.textContent = "Solved Successfully!";
        statusText.className = "solved";
    } else {
        if (!stopRequested) {
            statusText.textContent = "No Solution Exists!";
            statusText.className = "error";
        }
    }
    toggleButtons(false);
}

loadBtn.addEventListener('click', loadSample);
resetBtn.addEventListener('click', resetBoard);
solveInstantlyBtn.addEventListener('click', () => startSolve(false));
visualizeBtn.addEventListener('click', () => startSolve(true));

initBoard();
