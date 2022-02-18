#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>

#include "cell.cpp" // Stores the information about the domain of each cell in the matrix

using namespace std;

class sudoku
{
private:
    vector<vector<int>> matrix;       // Stores board where empty spaces are represented with a 0 and the rest are integers accordingly
    vector<vector<cell>> cellDomains; // Stores the possible domains for each cell

    set<int> getDomain(int i, int j)
    {
        return cellDomains[i][j].domain;
    }

    void pruneDomains() // Ensures node consistency, prunes the domain of all cells so that all values within the domains satisfy the constraints
    {
        for (int i = 0; i < matrix.size(); i++) // For each row
        {
            for (int j = 0; j < matrix.size(); j++) // For each column
            {
                if (matrix[i][j] > 0) // If it's an already assigned value
                {
                    for (int k = 0; k < matrix.size(); k++) // Prune the domains of all cells within the digit's row
                    {
                        cellDomains[i][k].domain.erase(matrix[i][j]);
                    }
                    for (int k = 0; k < matrix.size(); k++) // Prune the domains of all cells within the digit's column
                    {
                        cellDomains[k][j].domain.erase(matrix[i][j]);
                    }
                    for (int k = (i / 3) * 3; k < (i / 3) * 3 + 3; k++) // Prune the domains of all cells within the digit's box
                        for (int l = (j / 3) * 3; l < (j / 3) * 3 + 3; l++)
                            cellDomains[k][l].domain.erase(matrix[i][j]);
                }
            }
        }
    }

    bool backtrack() // Backtracking function
    {
        for (int row = 0; row < matrix.size(); row++) // Loops through the rows and columns of the matrix
        {
            for (int col = 0; col < matrix[0].size(); col++)
            {
                if (matrix[row][col] != 0) // If the place is already assigned, don't do anything, move to the next loop iteration
                    continue;

                for (auto &num : cellDomains[row][col].domain) // Else, loop from 1 to 9
                {
                    if (isConsistent(row, col, num) == true)
                    {
                        matrix[row][col] = num;  // Assign
                        if (backtrack() == true) // Recurse function, if consistency is reached, return true
                            return true;
                        else
                            matrix[row][col] = 0; // If the subsequent recursive calls return false, that means we have to change this assigned value
                    }
                }

                return false;
            }
        }
        return true;
    }

    bool isConsistent(int row, int col, int num) // Node Consistency
    {
        for (int i = 0; i < 9; i++) // Horizontal and Vertical Checking
            if (matrix[i][col] == num || matrix[row][i] == num)
                return false;

        for (int i = (row / 3) * 3; i < (row / 3) * 3 + 3; i++) // Box Checking
            for (int j = (col / 3) * 3; j < (col / 3) * 3 + 3; j++)
                if (matrix[i][j] == num) // If we find a match with the given num, the current assignment is inconsistent so return false
                    return false;

        return true;
    }

public:
    sudoku(string fileName) // Constructor, takes a fileName and opens it
    {
        matrix = vector<vector<int>>(9, vector<int>(9, 0)); // Initializes an empty 9x9 matrix
        cellDomains = vector<vector<cell>>(9, vector<cell>(9));

        readFile(fileName);
    }

    void readFile(string fileName)
    {
        ifstream file(fileName);

        if (!file.good()) // If file doesn't exist...
        {
            cout << "Invalid file name!" << endl;
            return;
        }

        string line;

        int currRow = 0;
        int currCol = 0;

        while (getline(file, line)) // Read file line by line
        {
            currCol = 0;
            for (int i = 0; i < line.size(); i++) // Read each column from file
            {
                char c = line[i];
                if ((c == '|' && i > 0 && line[i - 1] == '|') || isdigit(c)) // If character is a space or is a digit
                {
                    if (isdigit(c)) // If it's a digit, set the appropriate value at current index to the digit else keep it zero
                        matrix[currRow][currCol] = c - '0';
                    currCol++;
                }
            }
            currRow++;
        };
    }

    void display()
    {
        for (int i = 0; i < matrix.size(); i++) // Loop through all values within the matrix and output them
        {
            cout << "|";
            for (int j = 0; j < matrix[0].size(); j++)
            {
                cout << (matrix[i][j] == 0 ? " " : to_string(matrix[i][j])) << "|";
            }
            cout << endl;
        }
        cout << endl;
    }

    void solve() // Wrapper for backtrack function
    {
        pruneDomains(); // Guarantees Node Consistency
        backtrack();    // Performs backtracking
    }
};
