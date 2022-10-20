/*

The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.

Example 1:

Input: n = 4
Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above

Example 2:

Input: n = 1
Output: [["Q"]]
 

Constraints:
1 <= n <= 9
========================================================================================================================================================================
*/

// Solution 1: 
class Solution {
    
    bool isSafe(int row, int col, vector<string> &board, int n) {
        int i = row;
        int j = col;
        // top-left
        while(i >= 0 and j >= 0) {
            if(board[i][j] == 'Q') return false;
            i--;
            j--;
        }
        // left
        i = row;
        j = col;
        while(j >= 0) {
            if(board[i][j] == 'Q') return false;
            j--;
        }
        // bottom-left
        i = row;
        j = col;
        while(i < n and j >= 0) {
            if(board[i][j] == 'Q') return false;
            i++;
            j--;
        }
        return true;
    }
    
    void solve(int col, vector<string> &board, vector<vector<string>> &ans, int n) {
        if(col == n) {
            ans.push_back(board);
            return;
        }
        for(int row = 0 ; row < n ; row++) {
            if(isSafe(row, col, board, n)) {
                board[row][col] = 'Q';
                solve(col + 1, board, ans, n);
                board[row][col] = '.';
            }
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<string> board(n);
        string s(n, '.');
        for(int i = 0 ; i < n ; i++) {
            board[i] = s;
        }
        solve(0, board, ans, n);
        return ans;
    }
};

//===================================================================================================================================================================

// Solution: 2
class Solution {
    
    void solve(int col, vector<string> &board, vector<vector<string>> &ans, vector<int> &left, vector<int> &top_left, vector<int> &bottom_left, int n) {
        if(col == n) {
            ans.push_back(board);
            return;
        }
        for(int row = 0 ; row < n ; row++) {
            if(left[row] == 0 and top_left[n - 1 + col - row] == 0 and bottom_left[row + col] == 0) {
                board[row][col] = 'Q';
                left[row] = 1;
                top_left[n - 1 + col - row] = 1;
                bottom_left[row + col] = 1;
                solve(col + 1, board, ans, left, top_left, bottom_left, n);
                left[row] = 0;
                top_left[n - 1 + col - row] = 0;
                bottom_left[row + col] = 0;
                board[row][col] = '.';
            }
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<string> board(n);
        string s(n, '.');
        for(int i = 0 ; i < n ; i++) {
            board[i] = s;
        }
        vector<int> left(n, 0);
        vector<int> top_left(2 * n - 1, 0);
        vector<int> bottom_left(2 * n - 1, 0);
        solve(0, board, ans,left, top_left, bottom_left, n);
        return ans;
    }
};
