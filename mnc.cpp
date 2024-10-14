#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <tuple>

using namespace std;

// Check if the state is valid: missionaries should never be outnumbered by cannibals on any bank
bool is_valid_state(int M, int C) {
    return (M == 0 || M >= C) && (M == 3 || (3 - M) >= (3 - C));
}

// Get possible successor states based on the current state
vector<tuple<int, int, int>> get_successors(int M, int C, int B) {
    vector<tuple<int, int, int>> successors;
    vector<pair<int, int>> moves = {{1, 0}, {0, 1}, {1, 1}, {2, 0}, {0, 2}};

    for (auto move : moves) {
        int m = move.first;
        int c = move.second;
        int new_M, new_C, new_B;

        if (B == 1) {  // Boat is on the left bank
            new_M = M - m;
            new_C = C - c;
            new_B = 0;
        } else {  // Boat is on the right bank
            new_M = M + m;
            new_C = C + c;
            new_B = 1;
        }

        // Check if new state is valid
        if (new_M >= 0 && new_M <= 3 && new_C >= 0 && new_C <= 3 && is_valid_state(new_M, new_C)) {
            successors.push_back(make_tuple(new_M, new_C, new_B));
        }
    }

    return successors;
}

// BFS function to solve the Missionary and Cannibal problem
vector<tuple<int, int, int>> bfs_missionaries_and_cannibals() {
    tuple<int, int, int> initial_state = make_tuple(3, 3, 1);
    tuple<int, int, int> goal_state = make_tuple(0, 0, 0);
    
    queue<pair<tuple<int, int, int>, vector<tuple<int, int, int>>>> q;
    set<tuple<int, int, int>> visited;

    // Enqueue the initial state and mark it visited
    q.push({initial_state, {}});
    visited.insert(initial_state);

    while (!q.empty()) {
        auto current = q.front();
        tuple<int, int, int> state = current.first;
        vector<tuple<int, int, int>> path = current.second;
        q.pop();

        int M = get<0>(state);
        int C = get<1>(state);
        int B = get<2>(state);

        // If goal state is reached, return the path
        if (state == goal_state) {
            path.push_back(state);
            return path;
        }

        // Get all valid successor states
        for (auto successor : get_successors(M, C, B)) {
            if (visited.find(successor) == visited.end()) {
                visited.insert(successor);
                vector<tuple<int, int, int>> new_path = path;
                new_path.push_back(state);
                q.push({successor, new_path});
            }
        }
    }

    return {};  // No solution found
}

int main() {
    vector<tuple<int, int, int>> solution = bfs_missionaries_and_cannibals();

    if (!solution.empty()) {
        for (auto step : solution) {
            int M = get<0>(step);
            int C = get<1>(step);
            int B = get<2>(step);
            cout << "(" << M << ", " << C << ", " << B << ")\n";
        }
    } else {
        cout << "No solution found.\n";
    }

    return 0;
}
