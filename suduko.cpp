#include <iostream>
#include <cstdlib>
#include <ctime>

#define N 9

bool solveSudoku(int grid[N][N]);
bool findUnassignedLocation(int grid[N][N], int &row, int &col);
bool isSafe(int grid[N][N], int row, int col, int num);
void printGrid(int grid[N][N]);
void generatePuzzle(int grid[N][N], int difficulty);

int main() {

    int grid[N][N] = {0};

    int difficulty;
    std::cout << "Enter difficulty level (1-3): ";
    std::cin >> difficulty;
    generatePuzzle(grid, difficulty);

    std::cout << "Generated Sudoku Puzzle:\n";
    printGrid(grid);

    char choice;
    std::cout << "Solve the puzzle? (y/n): ";
    std::cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        if (solveSudoku(grid)) {
            std::cout << "Solved Sudoku:\n";
            printGrid(grid);
        } else {
            std::cout << "No solution exists for the given puzzle!\n";
        }
    }

    return 0;
}

bool findUnassignedLocation(int grid[N][N], int &row, int &col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0)
                return true;
        }
    }
    return false;
}

bool isSafe(int grid[N][N], int row, int col, int num) {

    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num)
            return false;
    }

    for (int x = 0; x < N; x++) {
        if (grid[x][col] == num)
            return false;
    }

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num)
                return false;
        }
    }
    return true;
}

bool solveSudoku(int grid[N][N]) {
    int row, col;
    if (!findUnassignedLocation(grid, row, col))
        return true; 

    for (int num = 1; num <= N; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid))
                return true;
            grid[row][col] = 0; 
        }
    }
    return false;
}

void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            std::cout << grid[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

void generatePuzzle(int grid[N][N], int difficulty) {
    int filledCells;
    switch (difficulty) {
        case 1: filledCells = 36; break; // Easy
        case 2: filledCells = 30; break; // Medium
        case 3: filledCells = 25; break; // Hard
        default: filledCells = 36;
    }

    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < N; i += 3) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                int num;
                do {
                    num = rand() % N + 1;
                } while (!isSafe(grid, i + j, i + k, num));
                grid[i + j][i + k] = num;
            }
        }
    }

    solveSudoku(grid);

    for (int i = 0; i < N * N - filledCells; i++) {
        int row, col;
        do {
            row = rand() % N;
            col = rand() % N;
        } while (grid[row][col] == 0);
        grid[row][col] = 0;
    }
}

