# Graph Problems

1. [Island Perimeter](#island-perimeter)
1. [Number of Islands](#number-of-islands)
1. [Max Area of Island](#max-area-of-island)

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

### Number of Islands
> Given a 2D grid grid where '1' represents land and '0' represents water, count and return the number of islands.

An island is formed by connecting adjacent lands horizontally or vertically and is surrounded by water. You may assume water is surrounding the grid (i.e., all the edges are water).

```bash
Example 1:

Input: grid = [
    ["0","1","1","1","0"],
    ["0","1","0","1","0"],
    ["1","1","0","0","0"],
    ["0","0","0","0","0"]
  ]
Output: 1
Example 2:

Input: grid = [
    ["1","1","0","0","1"],
    ["1","1","0","0","1"],
    ["0","0","1","0","0"],
    ["0","0","0","1","1"]
  ]
Output: 4
```
Aproach:
- dfs on each element
- set visitied node as 0
```cpp
class Solution {

    void dfs (vector<vector<char>>& grid, int r, int c)
    {
        if (r < 0 || r == grid.size() || c < 0 || c == grid[0].size() || grid[r][c] == '0')
            return;
        
        grid[r][c] = '0';

        dfs(grid, r - 1, c);
        dfs(grid, r + 1, c);
        dfs(grid, r, c - 1);
        dfs(grid, r, c + 1);
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int count = 0;

        if (!grid.size())
            return 0;
    
        int rows = grid.size();
        int cols = grid[0].size();

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == '1') {
                    dfs(grid, r, c);
                    count++;
                }
            }
        }

        return count;
    }
};
```

### Max Area of Island 
> You are given a matrix grid where grid[i] is either a 0 (representing water) or 1 (representing land).

An island is defined as a group of 1's connected horizontally or vertically. You may assume all four edges of the grid are surrounded by water.

The area of an island is defined as the number of cells within the island.

Return the maximum area of an island in grid. If no island exists, return 0.

```bash
Input: grid = [
  [0,1,1,0,1],
  [1,0,1,0,1],
  [0,1,1,0,1],
  [0,1,0,0,1]
]

Output: 6
Explanation: 1's cannot be connected diagonally, so the maximum area of the island is 6.
```

```cpp
class Solution {
    int dfs(vector<vector<int>>& grid, int r, int c)
    {
        int count  = 0;
        if (r < 0 || r == grid.size() || c < 0 || c == grid[0].size() || grid[r][c] == 0)
            return count;
        
        grid[r][c] = 0;
        count++;

        count += dfs(grid, r - 1, c);
        count += dfs(grid, r + 1, c);
        count += dfs(grid, r, c - 1);
        count += dfs(grid, r, c + 1);

        return count;
    }
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int count = 0;
        int res  = 0;

        if (!grid.size())
            return 0;
    
        int rows = grid.size();
        int cols = grid[0].size();

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == 1) {
                    count = dfs(grid, r, c);
                    res = max(res, count);
                }
            }
        }

        return res;
    }
};

```