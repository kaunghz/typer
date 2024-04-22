def dfs2D(matrix, visited, row, col):
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    visited[row][col] = True
    for dr, dc in directions:
        new_row, new_col = row + dr, col + dc
        if 0 <= new_row < len(matrix) and 0 <= new_col < len(matrix[0]) \
            and not visited[new_row][new_col] and matrix[new_row][new_col] == 1:
            dfs_2d_array(matrix, visited, new_row, new_col)