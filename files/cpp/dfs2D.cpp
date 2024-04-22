#include <bits/stdc++.h>
using namespace std;
void dfs2D(vector<vector<int>>& matrix, vector<vector<bool>>& visited, int row, int col) {
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    visited[row][col] = true;
    for (const auto& dir : directions) {
        int new_row = row + dir.first;
        int new_col = col + dir.second;
        if (new_row >= 0 && new_row < matrix.size() && new_col >= 0 && new_col < matrix[0].size()
            && !visited[new_row][new_col] && matrix[new_row][new_col] == 1) {
            dfs2D(matrix, visited, new_row, new_col);
        }
    }
}