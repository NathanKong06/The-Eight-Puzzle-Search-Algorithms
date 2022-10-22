#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <chrono>
using namespace std;

int main (){
    int userInput;
    vector<int> puzzle;
    cout << "Enter initial state, 9 for the blank item" << endl;
    for (unsigned int i = 0; i < 9; ++i) {
        cin >> userInput;
        puzzle.push_back(userInput);
    }

    cout << "Initial State" << endl;
    //printVector(puzzle);

    cout << "Press 1 for Uniform Cost Search (Skip Repeats), 2 for A* with Misplaced Tile Heuristic, or 3 for A* with Manhattan Distance Heuristic" << endl;
    cin >> userInput;
    if (userInput == 1) {

    }
    else if (userInput == 2) {

    }
    else if (userInput == 3) {

    }
    return 0;
}