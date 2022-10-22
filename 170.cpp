#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <chrono>
using namespace std;

unsigned int nodes = 0;

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

//Uniform Cost Search skipping over repeats
int uniformSearch(vector<int>initial) {
    queue<Node> q; //Queue holding nodes
    vector<vector<int>> repeatedStates; //Vector holding repeated states
    q.push(Node(initial,0)); //Initial state with depth of 0 pushed into queue
    while (true) {
        if (q.empty()) //Empty queue means solution not found
            return -1; //Return failure
        else if (solved(q.front().puzzle)){  //If goal state is reached
            printVector(q.front().puzzle);
            return q.front().depth; //Return depth of solution if found
        }

        vector<int> currentPuzzle = q.front().puzzle; //Current puzzle 
        if (find(repeatedStates.begin(), repeatedStates.end(),currentPuzzle) == repeatedStates.end()){ //If not a repeated state
            nodes++; //Counting nodes
            repeatedStates.push_back(currentPuzzle); //Add state into repeatedStates vector
        
            int nodeDepth = q.front().depth;
            auto blankPosition = find(currentPuzzle.begin(), currentPuzzle.end(), 9) - currentPuzzle.begin(); //Position of the blank piece
            if (blankPosition == 0) { //Possible moves for the blank spot at the 0th position
                q.push(Node(moveRight(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
                q.push(Node(moveDown(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
            }
            else if (blankPosition == 1) { //Possible moves for the blank spot at the 1th position
                q.push(Node(moveLeft(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
                q.push(Node(moveRight(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
                q.push(Node(moveDown(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
            }
            else if (blankPosition == 2) { //Possible moves for the blank spot at the 2th position
                q.push(Node(moveLeft(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
                q.push(Node(moveDown(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
            }
            else if (blankPosition == 3) { //Possible moves for the blank spot at the 0=3th position
                q.push(Node(moveUp(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
                q.push(Node(moveRight(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
                q.push(Node(moveDown(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
            }
            else if (blankPosition == 4) { //Possible moves for the blank spot at the 4th position
                q.push(Node(moveRight(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
                q.push(Node(moveLeft(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
                q.push(Node(moveUp(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
                q.push(Node(moveDown(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
            }
            else if (blankPosition == 5) { //Possible moves for the blank spot at the 5th position
                q.push(Node(moveUp(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
                q.push(Node(moveDown(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
                q.push(Node(moveLeft(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
            }
            else if (blankPosition == 6) { //Possible moves for the blank spot at the 6th position
                q.push(Node(moveRight(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
                q.push(Node(moveUp(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
            }
            else if (blankPosition == 7) { //Possible moves for the blank spot at the 7th position
                q.push(Node(moveUp(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
                q.push(Node(moveLeft(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
                q.push(Node(moveRight(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
            }
            else if (blankPosition == 8) { //Possible moves for the blank spot at the 8th position
                q.push(Node(moveUp(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
                q.push(Node(moveLeft(currentPuzzle, blankPosition, nodeDepth),q.front().depth + 1));
            }
        }
    q.pop();  // Remove front node 
    }
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
        auto start = std::chrono::high_resolution_clock::now();
        cout << "Depth: " <<  uniformSearch(puzzle) << endl;
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
        cout << "Duration: " << duration.count() << " miliseconds" << endl;
        cout << "Nodes: " << nodes << endl;
    }
    else if (userInput == 2) {

    }
    else if (userInput == 3) {

    }
    return 0;
}