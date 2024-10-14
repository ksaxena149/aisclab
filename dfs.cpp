#include <iostream>
#include <vector>
using namespace std;

class Solution {
private:
    void dfs(int node, vector<bool>& visited, vector<vector<int>> adj, vector<int>& res){
        visited[node] = true;
        res.push_back(node);
        for(int i = 0; i<adj[node].size(); i++){
            if(!visited[adj[node][i]]){
                dfs(adj[node][i], visited, adj, res);
            }
        }
    }
public:
    vector<int> dfsOfGraph(int V, vector<vector<int>> adj) {
        vector<int> res;
        vector<bool> visited(V, false);
        for(int i = 0; i<V; i++){
            if(!visited[i]){
                dfs(i, visited, adj, res);
            }
        }
        return res;
    }
};


int main() {
    int tc;
    cout << "Enter the number of test cases: ";
    cin >> tc;
    while (tc--) {
        int V, E;
        cout<<"Enter number of vertices and edges (space seperated): ";
        cin >> V >> E;

        vector<vector<int>> adj(V);

        for (int i = 0; i < E; i++) {
            int u, v;
            cout<<"Enter two nodes connected of edge "<<i+1<<": ";
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        Solution obj;
        vector<int> ans = obj.dfsOfGraph(V, adj);
        cout<<"DFS Traversal: ";
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    return 0;
}