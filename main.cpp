#include <iostream>
#include "sudoku.cpp"

using namespace std;

int main(int argc, char **argv)
{
    string fileName = "inputFiles/";
    string cmd;

    if (argc == 1)
        fileName += "input.txt";
    else
        fileName += argv[1];

    sudoku newGame(fileName);

    cout << endl
         << "Before: " << endl;
    newGame.display();

    newGame.solve();

    cout << "After: " << endl;
    newGame.display();

    return 0;
}