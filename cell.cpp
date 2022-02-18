#include <iostream>
#include <set>

using namespace std;

class cell
{
public:
    set<int> domain; // Domain of each cell, stored in a set to facilitate o(1) insert and erase
    cell()
    {
        for (int i = 1; i < 10; i++) // Initializes the domain of each cell to 1,2,3,4,5,6,7,8,9
            domain.insert(i);
    }
};