#include <iostream>
using namespace std;

// Define the size of the Sudoku grid (9x9)
const int N = 9;

// Function to print the Sudoku grid
void printGrid(int grid[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if it's safe to place a number in a cell
bool isSafe(int grid[N][N], int row, int col, int num)
{
    // Check if the number is not already present in the row or column
    for (int i = 0; i < N; i++)
    {
        if (grid[row][i] == num || grid[i][col] == num)
        {
            return false;
        }
    }

    // Check if the number is not already present in the 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[i + startRow][j + startCol] == num)
            {
                return false;
            }
        }
    }

    return true; // It's safe to place the number
}

// Recursive function to solve the Sudoku puzzle
bool solveSudoku(int grid[N][N])
{
    int row, col;

    // Find an empty cell (cell with value 0)
    bool foundEmptyCell = false;
    for (row = 0; row < N; row++)
    {
        for (col = 0; col < N; col++)
        {
            if (grid[row][col] == 0)
            {
                foundEmptyCell = true;
                break;
            }
        }
        if (foundEmptyCell)
        {
            break;
        }
    }

    // If there are no empty cells, the Sudoku is solved
    if (!foundEmptyCell)
    {
        return true;
    }

    // Try filling the empty cell with numbers 1 to 9
    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(grid, row, col, num))
        {
            // Place the number if it's safe
            grid[row][col] = num;

            // Recursively solve the rest of the Sudoku
            if (solveSudoku(grid))
            {
                return true;
            }

            // If placing the number didn't lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }

    return false; // If no number can be placed in the current cell
}

int main()
{
    int grid[N][N];

    // Input the Sudoku grid (0 represents empty cells)
    cout << "Enter the Sudoku grid (9x9) with empty cells as 0:" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> grid[i][j];
        }
    }

    if (solveSudoku(grid))
    {
        cout << "Solved Sudoku:" << endl;
        printGrid(grid);
    }
    else
    {
        cout << "No solution exists." << endl;
    }

    return 0;
}

