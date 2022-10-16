/*

Given an undirected graph with V vertices and E edges, check whether it contains any cycle or not. 

Example 1:

Input:  
V = 5, E = 5
adj = {{1}, {0, 2, 4}, {1, 3}, {2, 4}, {1, 3}} 

Output: 1

Example 2:

Input: 
V = 4, E = 2
adj = {{}, {2}, {1, 3}, {2}}

Output: 0

Your Task:
You don't need to read or print anything. Your task is to complete the function isCycle() which takes V denoting the number of vertices and
adjacency list as input parameters and returns a boolean value denoting if the undirected graph contains any cycle or not, return 1 if a
cycle is present else return 0.

NOTE: The adjacency list denotes the edges of the graph where edges[i] stores all other vertices to which ith vertex is connected.

Expected Time Complexity: O(V + E)
Expected Space Complexity: O(V)

=========================================================================================================================================================================
*/

// BFS
class Solution {
    bool bfs(vector<int> adj[], vector<bool> &visited, int i) {
        visited[i] = true;
        queue<pair<int, int>> q;
        q.push({i, -1});
        while(!q.empty()) {
            int node = q.front().first;
            int parent = q.front().second;
            q.pop();
            for(int child : adj[node]) {
                if(!visited[child]) {
                    visited[child] = true;
                    q.push({child, node});
                }
                else {
                    if(parent != child) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
  public:
    // Function to detect cycle in an undirected graph.
    bool isCycle(int V, vector<int> adj[]) {
        vector<bool> visited(V, false);
        for(int i = 0 ; i < V ; i++) {
            if(!visited[i]){
                if(bfs(adj, visited, i)) return true;
            }
        }
        return false;
    }
};

// DFS
class Solution {
    bool dfs(vector<int> adj[], vector<bool> &visited, int node, int parent) {
        visited[node] = true;
        for(int child : adj[node]) {
            if(!visited[child]) {
                if(dfs(adj, visited, child, node)) return true;
            }
            else {
                if(child != parent) {
                    return true;
                }
            }
        }
        return false;
    }
  public:
    // Function to detect cycle in an undirected graph.
    bool isCycle(int V, vector<int> adj[]) {
        vector<bool> visited(V, false);
        for(int i = 0 ; i < V ; i++) {
            if(!visited[i]){
                if(dfs(adj, visited, i, -1)) return true;
            }
        }
        return false;
    }
};
