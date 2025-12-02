# Graph Problems

1. [Island Perimeter](#island-perimeter)

### Island Perimeter
```bash
Input: grid = [
    [1,1,0,0],
    [1,0,0,0],
    [1,1,1,0],
    [0,0,1,1]
]

Output: 18

Input: grid = [[1,0]]

Output: 4
```
Aproach:
- DFS search on every node

```cpp
class Solution {
    vector<vector<int>> grid;
    int rows, cols;

    int dfs(int i, int j) {
        if (i < 0 || j < 0 || i >= rows ||
            j >= cols || grid[i][j] == 0) {
            return 1;
        }

        if (grid[i][j] == -1)
            return 0;
        
        grid[i][j] = -1;
        return dfs(i, j + 1) + dfs(i + 1, j) +
                dfs(i, j - 1) + dfs(i - 1, j);
    }

public:
    int islandPerimeter(vector<vector<int>>& grid) {
        this->grid = grid;
        rows = grid.size();
        cols = grid[0].size();

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 1) {
                    return dfs(i, j);
                }
            }
        }
        return 0;
    }
};
```