#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <chrono>
using namespace std;

class Node {
    public:
        vector<int> puzzle; //Vector containing the 8 puzzle
        int depth; //Depth in the tree
        
        Node(vector<int> puzzles, int depths){ //Constructor to create a node
            puzzle = puzzles;
            depth = depths;
        } 
};

//Prints out the 8 puzzle, blank spot (represented with a 9) is not printed
void printVector(vector<int> vec) { 
    cout << "---------------------------" << endl;
    for (unsigned int i = 0; i < 9; i+=3) {
        if (vec.at(i) == 9)
            cout << " " << " " << vec.at(i+1) << " " << vec.at(i+2) << endl;
        else if (vec.at(i+1) == 9)
            cout << vec.at(i)  << " " << " " << " " << vec.at(i+2) << endl;
        else if (vec.at(i+2) == 9)
            cout << vec.at(i)  << " " << vec.at(i+1)  << " " << " " << endl;
        else    
            cout << vec.at(i)  << " " << vec.at(i+1)  << " " << vec.at(i+2) << endl;
    }
}

//Checks if current state is solved
bool solved(vector<int> vec) {
    vector<int> done = {1,2,3,4,5,6,7,8,9};
    if (vec == done)
        return true;
    return false;
}

//Moves the blank spot down 1 spot
vector<int> moveDown(vector<int> vect, int blank, int depth) {
    swap(vect.at(blank), vect.at(blank+3));
    printVector(vect);
    cout << "Depth: " <<  depth << endl;
    return vect;
}

//Moves the blank spot up 1 spot
vector<int> moveUp(vector<int> vect, int blank, int depth) {
    swap(vect.at(blank), vect.at(blank-3));
    printVector(vect);
    cout << "Depth: " <<  depth << endl;
    return vect;
}

//Moves the blank spot right 1 spot
vector<int> moveRight(vector<int> vect, int blank, int depth) {
    swap(vect.at(blank), vect.at(blank+1));
    printVector(vect);
    cout << "Depth: " <<  depth << endl;
    return vect;
}

//Moves the blank spot left 1 spot
vector<int> moveLeft(vector<int> vect, int blank, int depth) {
    swap(vect.at(blank), vect.at(blank-1));
    printVector(vect);
    cout << "Depth: " <<  depth << endl;
    return vect;
}

int main (){
    int userInput;
    vector<int> puzzle;
    cout << "Enter initial state, 9 for the blank item" << endl;
    for (unsigned int i = 0; i < 9; ++i) {
        cin >> userInput;
        puzzle.push_back(userInput);
    }

    cout << "Initial State" << endl;
    printVector(puzzle);

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