#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
  public:
    vector<int> bfsOfGraph(int V, vector<vector<int>> adj) {
        vector<int> res;
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(0);
        visited[0] = true;
        while(!q.empty()){
            int node = q.front(); q.pop();
            res.push_back(node);
            for(int i = 0; i<adj[node].size(); i++){
                if(!visited[adj[node][i]]){
                    q.push(adj[node][i]);
                    visited[adj[node][i]] = true;
                }
            }
        }
        return res;
    }
};

int main() {
    int tc;
    cout<<"Enter number of test cases: ";
    cin >> tc;
    while (tc--) {
        int V, E;
        cout<<"Enter the number of vertices and edges(space seperated): ";
        cin >> V >> E;

        vector<vector<int>> adj(V);

        for (int i = 0; i < E; i++) {
            int u, v;
            cout<<"Enter two nodes connected of edge "<<i+1<<": ";
            cin >> u >> v;
            adj[u].push_back(v);
        }
        Solution obj;
        vector<int> ans = obj.bfsOfGraph(V, adj);
        cout<<"BFS Traversal: ";
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    return 0;
}