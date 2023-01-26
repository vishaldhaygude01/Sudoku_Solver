#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

using std::cout;
using std::endl;

#define BLANK 0
#define SPACE " "
#define LINE "|"
#define NEW_ROW "-------------------------------------"
#define GRID_FULL std::make_pair(9, 9)

void print_grid(int grid[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        cout << SPACE << SPACE << SPACE << SPACE << endl;
        cout << NEW_ROW << endl;
        for (int j = 0; j < 9; j++)
        {
            cout << SPACE;
            if (BLANK == grid[i][j])
            {
                cout << SPACE;
            }
            else
            {
                cout << grid[i][j];
            }
            cout << SPACE;
            cout << LINE;
        }
    }
    cout << endl
         << NEW_ROW << endl
         << endl;
    ;
}

bool used_in_row(int grid[9][9], int row, int num)
{
    for (int col = 0; col < 9; col++)
        if (grid[row][col] == num)
        {
            return true;
        }
    return false;
}

bool used_in_col(int grid[9][9], int col, int num)
{
    for (int row = 0; row < 9; row++)
        if (grid[row][col] == num)
        {
            return true;
        }
    return false;
}

bool used_in_box(int grid[9][9], int box_start_rpw, int box_start_col, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + box_start_rpw][col + box_start_col] == num)
            {
                return true;
            }
    return false;
}

bool is_safe(int grid[9][9], int row, int col, int num)
{
    return !used_in_row(grid, row, num) &&
           !used_in_col(grid, col, num) &&
           !used_in_box(grid, row - row % 3, col - col % 3, num);
}

std::pair<int, int> get_unassigned_location(int grid[9][9])
{
    for (int row = 0; row < 9; row++)
        for (int col = 0; col < 9; col++)
            if (grid[row][col] == BLANK)
            {
                return std::make_pair(row, col);
            }
    return GRID_FULL;
}

bool solve_soduko(int grid[9][9])
{
    if (GRID_FULL == get_unassigned_location(grid))
    {
        return true;
    }
    std::pair<int, int> row_and_col = get_unassigned_location(grid);
    int row = row_and_col.first;
    int col = row_and_col.second;
    for (int num = 1; num <= 9; num++)
    {
        if (is_safe(grid, row, col, num))
        {
            grid[row][col] = num;

            if (solve_soduko(grid))
            {
                return true;
            }
            grid[row][col] = BLANK;
        }
    }
    return false;
}

int main()
{
    cout << "--------------------------------\n\n\tSudoku Solver\n\n--------------------------------" << endl
         << endl;

    int grid[9][9] = {{0, 9, 0, 0, 0, 0, 8, 5, 3},
                      {0, 0, 0, 8, 0, 0, 0, 0, 4},
                      {0, 0, 8, 2, 0, 3, 0, 6, 9},
                      {5, 7, 4, 0, 0, 2, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 9, 0, 0, 6, 3, 7},
                      {9, 4, 0, 1, 0, 8, 5, 0, 0},
                      {7, 0, 0, 0, 0, 6, 0, 0, 0},
                      {6, 8, 2, 0, 0, 0, 0, 9, 0}};

    print_grid(grid);

    if (true == solve_soduko(grid))
    {
        print_grid(grid);
    }
    else
    {
        cout << "No solution exists for the given Soduko" << endl
             << endl;
    }
    return 0;
}