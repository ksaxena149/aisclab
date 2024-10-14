#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <limits>
#include <utility>
#include <algorithm>

using namespace std;

// Define the graph using an adjacency list
unordered_map<string, vector<pair<string, int>>> romaniaMap = {
    {"Arad", {{"Zerind", 75}, {"Sibiu", 140}, {"Timisoara", 118}}},
    {"Zerind", {{"Arad", 75}, {"Oradea", 71}}},
    {"Oradea", {{"Zerind", 71}, {"Sibiu", 151}}},
    {"Sibiu", {{"Arad", 140}, {"Oradea", 151}, {"Fagaras", 99}, {"Rimnicu Vilcea", 80}}},
    {"Fagaras", {{"Sibiu", 99}, {"Bucharest", 211}}},
    {"Rimnicu Vilcea", {{"Sibiu", 80}, {"Pitesti", 97}, {"Craiova", 146}}},
    {"Pitesti", {{"Rimnicu Vilcea", 97}, {"Bucharest", 101}}},
    {"Craiova", {{"Rimnicu Vilcea", 146}, {"Pitesti", 138}, {"Drobeta", 120}}},
    {"Timisoara", {{"Arad", 118}, {"Lugoj", 111}}},
    {"Lugoj", {{"Timisoara", 111}, {"Mehadia", 70}}},
    {"Mehadia", {{"Lugoj", 70}, {"Drobeta", 75}}},
    {"Drobeta", {{"Mehadia", 75}, {"Craiova", 120}}},
    {"Bucharest", {{"Fagaras", 211}, {"Pitesti", 101}, {"Giurgiu", 90}}},
    {"Giurgiu", {{"Bucharest", 90}}}
};

// Heuristic values (straight-line distance to Bucharest)
unordered_map<string, int> heuristic = {
    {"Arad", 366}, {"Zerind", 374}, {"Oradea", 380}, {"Sibiu", 253}, {"Fagaras", 176},
    {"Rimnicu Vilcea", 193}, {"Pitesti", 100}, {"Craiova", 160}, {"Timisoara", 329},
    {"Lugoj", 244}, {"Mehadia", 241}, {"Drobeta", 242}, {"Bucharest", 0}, {"Giurgiu", 77}
};

// A* search algorithm
void aStarSearch(string start, string goal) {
    // Priority queue to store nodes for exploration
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> frontier;
    frontier.push({heuristic[start], start});

    unordered_map<string, int> g_cost;  // Cost from start to the node
    g_cost[start] = 0;

    unordered_map<string, string> came_from;  // To store the path
    came_from[start] = "";

    while (!frontier.empty()) {
        string current = frontier.top().second;
        frontier.pop();

        // If we reached the goal, reconstruct the path
        if (current == goal) {
            vector<string> path;
            while (current != "") {
                path.push_back(current);
                current = came_from[current];
            }
            reverse(path.begin(), path.end());
            cout << "Path: ";
            for (const auto& city : path)
                cout << city << " -> ";
            cout << endl;
            return; 
        }

        // Explore the neighbors
        for (const auto& neighbor : romaniaMap[current]) {
            string next_city = neighbor.first;
            int move_cost = neighbor.second;

            int new_g_cost = g_cost[current] + move_cost;

            if (g_cost.find(next_city) == g_cost.end() || new_g_cost < g_cost[next_city]) {
                g_cost[next_city] = new_g_cost;
                int priority = new_g_cost + heuristic[next_city];  // f(n) = g(n) + h(n)
                frontier.push({priority, next_city});
                came_from[next_city] = current;
            }
        }
    }
}

int main() {
    string start = "Arad";
    string goal = "Bucharest";

    aStarSearch(start, goal);

    return 0;
}
