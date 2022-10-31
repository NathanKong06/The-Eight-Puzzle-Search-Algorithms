#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <chrono>

using namespace std;

unsigned int nodes = 0;
unsigned int maxUniform = 0;
unsigned int maxMisplaced = 0;
unsigned int maxManhattan = 0;

class Node {
    public:
        vector<int> puzzle; //Vector containing the 8 puzzle
        int depth; //Depth in the tree
        int value; //Heuristic value
        
        Node(vector<int> puzzles, int depths){ //Constructor to create a node
            puzzle = puzzles;
            depth = depths;
            value = 0;
        } 
        Node(vector<int> puzzles, int depths, int values){ //Constructor to create a node with heuristic value
            puzzle = puzzles;
            depth = depths;
            value = values;
        } 
};
    bool operator>(const Node& first, const Node& second) {  //Overload operator for min heap priority queue
        return first.value > second.value; 
    }

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
vector<int> moveDown(vector<int> vect, int blank) {
    swap(vect.at(blank), vect.at(blank+3));
    return vect;
}

//Moves the blank spot up 1 spot
vector<int> moveUp(vector<int> vect, int blank) {
    swap(vect.at(blank), vect.at(blank-3));
    return vect;
}

//Moves the blank spot right 1 spot
vector<int> moveRight(vector<int> vect, int blank) {
    swap(vect.at(blank), vect.at(blank+1));
    return vect;
}

//Moves the blank spot left 1 spot
vector<int> moveLeft(vector<int> vect, int blank) {
    swap(vect.at(blank), vect.at(blank-1));
    return vect;
}

//Uniform Cost Search skipping over repeats
int uniformSearch(vector<int>initial) {
    queue<Node> q; //Queue holding nodes
    vector<vector<int>> repeatedStates; //Vector holding repeated states
    //nodes = MAKE-QUEUE(MAKE-NODE(problem.INITIAL_STATE))
    q.push(Node(initial,0)); //Initial state with depth of 0 pushed into queue
    //loop do
    while (true) {
        //if EMPTY(nodes) then return "failure"
        if (q.empty()) //Empty queue means solution not found
            return -1; //Return failure
        //if problem.GOAL-TEST(node STATE) suceeds then return node
        else if (solved(q.front().puzzle)){  //If goal state is reached
            printVector(q.front().puzzle);
            cout << "Solution Found!" << endl;
            return q.front().depth; //Return depth of solution if found
        }

        vector<int> currentPuzzle = q.front().puzzle; //Current puzzle 
        printVector(currentPuzzle);
        cout << "Depth: " << q.front().depth << endl;
        cout << "g(n): " << q.front().depth << endl;
        cout << "h(n): 0 " << endl;
        if (find(repeatedStates.begin(), repeatedStates.end(),currentPuzzle) == repeatedStates.end()){ //If not a repeated state
            if (maxUniform < q.size())
                maxUniform = q.size();
            nodes++; //Counting nodes
            repeatedStates.push_back(currentPuzzle); //Add state into repeatedStates vector
        
            int nodeDepth = q.front().depth;
            int blankPosition = find(currentPuzzle.begin(), currentPuzzle.end(), 9) - currentPuzzle.begin(); //Position of the blank piece

            //nodes = QUEUEING-FUNCTION(nodes, EXPAND(nodes, problem.OPERATORS))
            if (blankPosition == 0) { //Possible moves for the blank spot at the 0th position
                q.push(Node(moveRight(currentPuzzle, blankPosition),q.front().depth + 1));
                q.push(Node(moveDown(currentPuzzle, blankPosition),q.front().depth + 1));
            }
            else if (blankPosition == 1) { //Possible moves for the blank spot at the 1st position
                q.push(Node(moveLeft(currentPuzzle, blankPosition),q.front().depth + 1));
                q.push(Node(moveRight(currentPuzzle, blankPosition),q.front().depth + 1));
                q.push(Node(moveDown(currentPuzzle, blankPosition),q.front().depth + 1));
            }
            else if (blankPosition == 2) { //Possible moves for the blank spot at the 2nd position
                q.push(Node(moveLeft(currentPuzzle, blankPosition),q.front().depth + 1));
                q.push(Node(moveDown(currentPuzzle, blankPosition),q.front().depth + 1));
            }
            else if (blankPosition == 3) { //Possible moves for the blank spot at the 3rd position
                q.push(Node(moveRight(currentPuzzle, blankPosition),q.front().depth + 1));
                q.push(Node(moveUp(currentPuzzle, blankPosition),q.front().depth + 1));
                q.push(Node(moveDown(currentPuzzle, blankPosition),q.front().depth + 1));
            }
            else if (blankPosition == 4) { //Possible moves for the blank spot at the 4th position
                q.push(Node(moveLeft(currentPuzzle, blankPosition),q.front().depth + 1));
                q.push(Node(moveRight(currentPuzzle, blankPosition),q.front().depth + 1));
                q.push(Node(moveUp(currentPuzzle, blankPosition),q.front().depth + 1));
                q.push(Node(moveDown(currentPuzzle, blankPosition),q.front().depth + 1));
            }
            else if (blankPosition == 5) { //Possible moves for the blank spot at the 5th position
                q.push(Node(moveLeft(currentPuzzle, blankPosition),q.front().depth + 1));
                q.push(Node(moveUp(currentPuzzle, blankPosition),q.front().depth + 1));
                q.push(Node(moveDown(currentPuzzle, blankPosition),q.front().depth + 1));
            }
            else if (blankPosition == 6) { //Possible moves for the blank spot at the 6th position
                q.push(Node(moveRight(currentPuzzle, blankPosition),q.front().depth + 1));
                q.push(Node(moveUp(currentPuzzle, blankPosition),q.front().depth + 1));
            }
            else if (blankPosition == 7) { //Possible moves for the blank spot at the 7th position
                q.push(Node(moveLeft(currentPuzzle, blankPosition),q.front().depth + 1));
                q.push(Node(moveRight(currentPuzzle, blankPosition),q.front().depth + 1));
                q.push(Node(moveUp(currentPuzzle, blankPosition),q.front().depth + 1));

            }
            else if (blankPosition == 8) { //Possible moves for the blank spot at the 8th position
                q.push(Node(moveLeft(currentPuzzle, blankPosition),q.front().depth + 1));
                q.push(Node(moveUp(currentPuzzle, blankPosition),q.front().depth + 1));
            }
        }
    //node = REMOVE-FRONT(nodes)
    q.pop();  // Remove front node 
    }
}

//Calculates Misplaced Tile Heuristic
int calculateMisplacedTile(vector<int>initial) {
    int score = 0;
    if (solved(initial)) //If solved puzzle, 0 misplaced tiles
        return 0;
    for (unsigned int i = 0; i < initial.size(); ++i) {
        if (initial.at(i) != 9) { //Skip empty tile
            if (initial.at(i) != (i + 1)) //If the tile is not in the correct spot, increase the misplaced tile score
                score++;
        }
    }
    return score;
}

//Misplaced Tile Heuristic
int misplacedTile(vector<int>initial) {
    //nodes = MAKE-QUEUE(MAKE-NODE(problem.INITIAL_STATE))
    priority_queue<Node, vector<Node>, greater<Node>> q; //Priority Queue holding nodes, sorted by heuristic value (lowest to highest)
    vector<vector<int>> repeatedStates; //Vector holding repeated states
    q.push(Node(initial,0, calculateMisplacedTile(initial))); //Initial state with depth of 0 pushed into queue
    //loop do
    while (true) {
        //if EMPTY(nodes) then return "failure"
        if (q.empty()) //Empty queue means solution not found
            return -1; //Return failure
        //if problem.GOAL-TEST(node STATE) suceeds then return node
        else if (solved(q.top().puzzle)){  //If goal state is reached
            printVector(q.top().puzzle);
            cout << "Solution Found!" << endl;
            return q.top().depth; //Return depth of solution if found
        }

        vector<int> currentPuzzle = q.top().puzzle; //Current puzzle 
        int nodeDepth = q.top().depth;
        int misplacedTileValue = q.top().value;
        //node = REMOVE-FRONT(nodes)
        q.pop(); //Remove current puzzle node

        if (find(repeatedStates.begin(), repeatedStates.end(),currentPuzzle) == repeatedStates.end() && nodeDepth <= 31){ //If not a repeated state
            printVector(currentPuzzle);
            cout << "Depth: " << nodeDepth << endl;
            cout << "Misplaced Tile Value: " << misplacedTileValue << endl;
            cout << "g(n): " << nodeDepth << endl;
            cout << "h(n): " << misplacedTileValue << endl;
            nodes++; //Counting nodes
            if (maxMisplaced < q.size())
                maxMisplaced = q.size();
            repeatedStates.push_back(currentPuzzle); //Add state into repeatedStates vector

            int blankPosition = find(currentPuzzle.begin(), currentPuzzle.end(), 9) - currentPuzzle.begin(); //Position of the blank piece

            //nodes = QUEUEING-FUNCTION(nodes, EXPAND(nodes, problem.OPERATORS))
            if (blankPosition == 0) { //Possible moves for the blank spot at the 0th position
                q.push(Node(moveRight(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveRight(currentPuzzle, blankPosition)) + nodeDepth));
                q.push(Node(moveDown(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveDown(currentPuzzle, blankPosition))+ nodeDepth));
            }
            else if (blankPosition == 1) { //Possible moves for the blank spot at the 1st position
                q.push(Node(moveLeft(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveLeft(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveRight(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveRight(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveDown(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveDown(currentPuzzle, blankPosition))+ nodeDepth));
            }
            else if (blankPosition == 2) { //Possible moves for the blank spot at the 2nd position
                q.push(Node(moveLeft(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveLeft(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveDown(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveDown(currentPuzzle, blankPosition))+ nodeDepth));
            }
            else if (blankPosition == 3) { //Possible moves for the blank spot at the 3rd position
                q.push(Node(moveRight(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveRight(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveUp(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveUp(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveDown(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveDown(currentPuzzle, blankPosition))+ nodeDepth));
            }
            else if (blankPosition == 4) { //Possible moves for the blank spot at the 4th position
                q.push(Node(moveLeft(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveLeft(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveRight(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveRight(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveUp(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveUp(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveDown(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveDown(currentPuzzle, blankPosition))+ nodeDepth));
            }
            else if (blankPosition == 5) { //Possible moves for the blank spot at the 5th position
                q.push(Node(moveLeft(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveLeft(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveUp(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveUp(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveDown(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveDown(currentPuzzle, blankPosition))+ nodeDepth));
            }
            else if (blankPosition == 6) { //Possible moves for the blank spot at the 6th position
                q.push(Node(moveRight(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveRight(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveUp(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveUp(currentPuzzle, blankPosition))+ nodeDepth));
            }
            else if (blankPosition == 7) { //Possible moves for the blank spot at the 7th position
                q.push(Node(moveLeft(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveLeft(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveRight(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveRight(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveUp(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveUp(currentPuzzle, blankPosition))+ nodeDepth));
            }
            else if (blankPosition == 8) { //Possible moves for the blank spot at the 8th position
                q.push(Node(moveLeft(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveLeft(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveUp(currentPuzzle, blankPosition),nodeDepth + 1,calculateMisplacedTile(moveUp(currentPuzzle, blankPosition))+ nodeDepth));
            }
        }
    }
}

//Manhattan Distance Heuristic
int calculateManhattanDistance(vector<int>initial) {
    int score = 0;
    unordered_map<int, pair<int,int>> coordinates; //Represents row, column for each index 
    coordinates[0] = pair<int,int>(1,1);
    coordinates[1] = pair<int,int>(1,2);
    coordinates[2] = pair<int,int>(1,3);
    coordinates[3] = pair<int,int>(2,1);
    coordinates[4] = pair<int,int>(2,2);
    coordinates[5] = pair<int,int>(2,3);
    coordinates[6] = pair<int,int>(3,1);
    coordinates[7] = pair<int,int>(3,2);
    coordinates[8] = pair<int,int>(3,3);

    int incorrectRow;
    int incorrectColumn;
    int correctRow;
    int correctColumn;
    if (solved(initial)) //If solved puzzle, 0 manhattan distance
        return 0;
    for (unsigned int i = 0; i < initial.size(); ++i) {
        if (initial.at(i) != 9) { //Skip empty tile
            if (initial.at(i) != (i + 1)){ //If the tile is not in the correct spot
                incorrectRow = coordinates[i].first; //Current row
                incorrectColumn = coordinates[i].second; //Current column
                correctRow = coordinates[initial.at(i)-1].first; //Tile's correct position row
                correctColumn = coordinates [initial.at(i)-1].second; //Tile's correct position column
                score += abs(correctRow - incorrectRow) + abs(correctColumn - incorrectColumn); //Calculate distance
            }
        }
    }
    return score;
}

int manhattanDistance(vector<int> initial) {
    //nodes = MAKE-QUEUE(MAKE-NODE(problem.INITIAL_STATE))
    priority_queue<Node, vector<Node>, greater<Node>> q; //Priority Queue holding nodes, sorted by heuristic value (lowest to highest)
    vector<vector<int>> repeatedStates; //Vector holding repeated states
    q.push(Node(initial,0, calculateManhattanDistance(initial))); //Initial state with depth of 0 pushed into queue
    //loop do
    while (true) {
        //if EMPTY(nodes) then return "failure"
        if (q.empty()) //Empty queue means solution not found
            return -1; //Return failure
        //if problem.GOAL-TEST(node STATE) suceeds then return node
        else if (solved(q.top().puzzle)){  //If goal state is reached
            printVector(q.top().puzzle);
            cout << "Solution Found!" << endl;
            return q.top().depth; //Return depth of solution if found
        }

        vector<int> currentPuzzle = q.top().puzzle; //Current puzzle 
        int nodeDepth = q.top().depth;
        int manhattanValue = q.top().value;
        //node = REMOVE-FRONT(nodes)
        q.pop(); //Remove current puzzle node

        if (find(repeatedStates.begin(), repeatedStates.end(),currentPuzzle) == repeatedStates.end() && nodeDepth + 1 <= 31){ //If not a repeated state
            printVector(currentPuzzle);
            cout << "Depth: " << nodeDepth << endl;
            cout << "Manhattan Distance Value: " << manhattanValue << endl;
            cout << "g(n): " << nodeDepth << endl;
            cout << "h(n): " << manhattanValue << endl;
            if (maxManhattan < q.size())
                maxManhattan = q.size();
            nodes++; //Counting nodes
            repeatedStates.push_back(currentPuzzle); //Add state into repeatedStates vector

            int blankPosition = find(currentPuzzle.begin(), currentPuzzle.end(), 9) - currentPuzzle.begin(); //Position of the blank piece

            //nodes = QUEUEING-FUNCTION(nodes, EXPAND(nodes, problem.OPERATORS))
            if (blankPosition == 0) { //Possible moves for the blank spot at the 0th position
                q.push(Node(moveRight(currentPuzzle, blankPosition),nodeDepth+ 1,calculateManhattanDistance(moveRight(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveDown(currentPuzzle, blankPosition),nodeDepth + 1,calculateManhattanDistance(moveDown(currentPuzzle, blankPosition))+ nodeDepth));
            }
            else if (blankPosition == 1) { //Possible moves for the blank spot at the 1st position
                q.push(Node(moveLeft(currentPuzzle, blankPosition),nodeDepth + 1,calculateManhattanDistance(moveLeft(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveRight(currentPuzzle, blankPosition),nodeDepth + 1,calculateManhattanDistance(moveRight(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveDown(currentPuzzle, blankPosition),nodeDepth + 1,calculateManhattanDistance(moveDown(currentPuzzle, blankPosition))+ nodeDepth));
            }
            else if (blankPosition == 2) { //Possible moves for the blank spot at the 2nd position
                q.push(Node(moveLeft(currentPuzzle, blankPosition),nodeDepth + 1,calculateManhattanDistance(moveLeft(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveDown(currentPuzzle, blankPosition),nodeDepth + 1,calculateManhattanDistance(moveDown(currentPuzzle, blankPosition))+ nodeDepth));
            }
            else if (blankPosition == 3) { //Possible moves for the blank spot at the 3rd position
                q.push(Node(moveRight(currentPuzzle, blankPosition),nodeDepth + 1,calculateManhattanDistance(moveRight(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveUp(currentPuzzle, blankPosition),nodeDepth + 1,calculateManhattanDistance(moveUp(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveDown(currentPuzzle, blankPosition),nodeDepth + 1,calculateManhattanDistance(moveDown(currentPuzzle, blankPosition))+ nodeDepth));
            }
            else if (blankPosition == 4) { //Possible moves for the blank spot at the 4th position
                q.push(Node(moveLeft(currentPuzzle, blankPosition),nodeDepth + 1,calculateManhattanDistance(moveLeft(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveRight(currentPuzzle, blankPosition),nodeDepth + 1,calculateManhattanDistance(moveRight(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveUp(currentPuzzle, blankPosition),nodeDepth + 1,calculateManhattanDistance(moveUp(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveDown(currentPuzzle, blankPosition),nodeDepth + 1,calculateManhattanDistance(moveDown(currentPuzzle, blankPosition))+ nodeDepth));
            }
            else if (blankPosition == 5) { //Possible moves for the blank spot at the 5th position
                q.push(Node(moveLeft(currentPuzzle, blankPosition),nodeDepth + 1,calculateManhattanDistance(moveLeft(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveUp(currentPuzzle, blankPosition),nodeDepth + 1,calculateManhattanDistance(moveUp(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveDown(currentPuzzle, blankPosition),nodeDepth + 1,calculateManhattanDistance(moveDown(currentPuzzle, blankPosition))+ nodeDepth));
            }
            else if (blankPosition == 6) { //Possible moves for the blank spot at the 6th position
                q.push(Node(moveRight(currentPuzzle, blankPosition),nodeDepth + 1,calculateManhattanDistance(moveRight(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveUp(currentPuzzle, blankPosition),nodeDepth + 1,calculateManhattanDistance(moveUp(currentPuzzle, blankPosition))+ nodeDepth));
            }
            else if (blankPosition == 7) { //Possible moves for the blank spot at the 7th position
                q.push(Node(moveLeft(currentPuzzle, blankPosition),nodeDepth + 1,calculateManhattanDistance(moveLeft(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveRight(currentPuzzle, blankPosition),nodeDepth + 1,calculateManhattanDistance(moveRight(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveUp(currentPuzzle, blankPosition),nodeDepth + 1,calculateManhattanDistance(moveUp(currentPuzzle, blankPosition))+ nodeDepth));
            }
            else if (blankPosition == 8) { //Possible moves for the blank spot at the 8th position
                q.push(Node(moveLeft(currentPuzzle, blankPosition),nodeDepth + 1,calculateManhattanDistance(moveLeft(currentPuzzle, blankPosition))+ nodeDepth));
                q.push(Node(moveUp(currentPuzzle, blankPosition),nodeDepth + 1,calculateManhattanDistance(moveUp(currentPuzzle, blankPosition))+ nodeDepth));
            }
        }
    }
}

int main (){
    int userInput;
    vector<int> puzzle;
    cout << "Enter initial state, 9 for the blank tile. Valid puzzles only, numbers will be inputted from the 1st to last row." << endl;
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
        cout << "Duration: " << duration.count() << " milliseconds" << endl;
        cout << "Nodes: " << nodes << endl;
        cout << "Max Queue Size: " << maxUniform << endl;
    }
    else if (userInput == 2) {
        auto start = std::chrono::high_resolution_clock::now();
        cout << "Depth: " << misplacedTile(puzzle) << endl;
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
        cout << "Duration: " << duration.count() << " milliseconds" << endl;
        cout << "Nodes: " << nodes << endl;
        cout << "Max Queue Size: " << maxMisplaced << endl;

    }
    else if (userInput == 3) {
        auto start = std::chrono::high_resolution_clock::now();
        cout << "Depth: " << manhattanDistance(puzzle) << endl;
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
        cout << "Duration: " << duration.count() << " milliseconds" << endl;
        cout << "Nodes: " << nodes << endl;
        cout << "Max Queue Size: " << maxManhattan << endl;
    }
    return 0;
}