/*

Given a grid of size n*m (n is the number of rows and m is the number of columns in the grid) consisting of '0's (Water) and '1's(Land). Find the number of islands.

Note: An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically or diagonally i.e., in all 8 directions.

Example 1:

Input:
grid = {{0,1},{1,0},{1,1},{1,0}}

Output:
1

Explanation:
The grid is-
0 1
1 0
1 1
1 0
All lands are connected.

Example 2:

Input:
grid = {{0,1,1,1,0,0,0},{0,0,1,1,0,1,0}}

Output:
2

Expanation:
The grid is-
0 1 1 1 0 0 0
0 0 1 1 0 1 0 
There are two islands :- one is colored in blue 
and other in orange.

Your Task:
You don't need to read or print anything. Your task is to complete the function numIslands() which takes the grid as an input parameter and 
returns the total number of islands.

Expected Time Complexity: O(n*m)
Expected Space Complexity: O(n*m)

Constraints:
1 ≤ n, m ≤ 500

======================================================================================================================================================================

class Solution {
    void bfs(vector<vector<char>> &grid, vector<vector<bool>> &visited, int row, int col) {
        int n = grid.size();
        int m = grid[0].size();
        visited[row][col] = true;
        queue<pair<int, int>> q;
        q.push({row, col});
        while(!q.empty()) {
            int crow = q.front().first;
            int ccol = q.front().second;
            q.pop();
            for(int i = -1 ; i <= 1 ; i++) {
                for(int j = -1 ; j <= 1 ; j++) {
                    int nrow = crow + i;
                    int ncol = ccol + j;
                    if(nrow >= 0 and nrow < n and ncol >= 0 and ncol < m and grid[nrow][ncol] == '1' and !visited[nrow][ncol]) {
                        visited[nrow][ncol] = true;
                        q.push({nrow, ncol});
                    }
                }
            }
        }
    }
  public:
    // Function to find the number of islands.
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        int ans = 0;
        for(int row = 0 ; row < n ; row++) {
            for(int col = 0 ; col < m ; col++) {
                if(!visited[row][col] and grid[row][col] == '1') {
                    ans++;
                    bfs(grid, visited, row, col);
                }
            }
        }
        return ans;
    }
};

*/
