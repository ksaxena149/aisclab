#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct PuzzleState {
    vector<vector<int>> puzzle;
    int x, y;  // Position of the empty tile (0)
    int heuristic;

    PuzzleState(vector<vector<int>> p, int xPos, int yPos) {
        puzzle = p;
        x = xPos;
        y = yPos;
        heuristic = calculateHeuristic();
    }

    // Heuristic function: count of misplaced tiles
    int calculateHeuristic() {
        int misplaced = 0;
        vector<vector<int>> goal = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 0}
        };
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (puzzle[i][j] != 0 && puzzle[i][j] != goal[i][j]) {
                    misplaced++;
                }
            }
        }
        return misplaced;
    }

    // Display the current puzzle state
    void display() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << puzzle[i][j] << " ";
            }
            cout << endl;
        }
        cout << "Heuristic: " << heuristic << endl;
    }
};

// Check if a state is the goal state
bool isGoalState(vector<vector<int>>& puzzle) {
    vector<vector<int>> goal = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };
    return puzzle == goal;
}

// Generate neighbors by moving the blank tile
vector<PuzzleState> getNeighbors(PuzzleState& state) {
    vector<PuzzleState> neighbors;
    int dx[] = {-1, 1, 0, 0}; // up, down, left, right
    int dy[] = {0, 0, -1, 1};
    
    for (int i = 0; i < 4; i++) {
        int newX = state.x + dx[i];
        int newY = state.y + dy[i];
        
        // Check if the new position is within bounds
        if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) {
            vector<vector<int>> newPuzzle = state.puzzle;
            swap(newPuzzle[state.x][state.y], newPuzzle[newX][newY]);
            neighbors.push_back(PuzzleState(newPuzzle, newX, newY));
        }
    }
    
    return neighbors;
}

// Hill climbing algorithm to solve the 8-puzzle
void hillClimbing(vector<vector<int>>& puzzle) {
    int startX, startY;
    
    // Find the position of the blank tile
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzzle[i][j] == 0) {
                startX = i;
                startY = j;
                break;
            }
        }
    }

    PuzzleState current(puzzle, startX, startY);
    
    while (true) {
        current.display();

        if (isGoalState(current.puzzle)) {
            cout << "Reached goal state!" << endl;
            break;
        }
        
        vector<PuzzleState> neighbors = getNeighbors(current);
        
        // Find the neighbor with the best heuristic
        PuzzleState* bestNeighbor = nullptr;
        for (int i = 0; i < neighbors.size(); i++) {
            if (bestNeighbor == nullptr || neighbors[i].heuristic < bestNeighbor->heuristic) {
                bestNeighbor = &neighbors[i];
            }
        }

        // If no improvement, stop
        if (bestNeighbor->heuristic >= current.heuristic) {
            cout << "No better neighbor found. Stopping." << endl;
            break;
        }

        // Move to the best neighbor
        current = *bestNeighbor;
    }
}

int main() {
    vector<vector<int>> puzzle = {
        {1, 2, 3},
        {4, 0, 5},
        {7, 8, 6}
    };
    
    cout << "Starting Hill Climbing for 8-puzzle problem..." << endl;
    hillClimbing(puzzle);
    
    return 0;
}
