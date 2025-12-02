# Graph Problems

1. [Island Perimeter](#island-perimeter)
1. [Number of Islands](#number-of-islands)
1. [Max Area of Island](#max-area-of-island)
1. [Islands and Treasure](#islands-and-treasure)
1. [Rotting Fruit](#rotting-fruit)

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
### Islands and Treasure
> You are given a m × n 2D grid initialized with these three possible values:
- -1 - A water cell that can not be traversed.
- 0 - A treasure chest.
- INF - A land cell that can be traversed. We use the integer 2^31 - 1 = 2147483647 to represent INF.

Fill each land cell with the distance to its nearest treasure chest. If a land cell cannot reach a treasure chest then the value should remain INF.

Assume the grid can only be traversed up, down, left, or right.

Modify the grid in-place.
```bash
Example 1:

Input: [
  [2147483647,-1,0,2147483647],
  [2147483647,2147483647,2147483647,-1],
  [2147483647,-1,2147483647,-1],
  [0,-1,2147483647,2147483647]
]

Output: [
  [3,-1,0,1],
  [2,2,1,-1],
  [1,-1,2,-1],
  [0,-1,3,4]
]


Example 2:

Input: [
  [0,-1],
  [2147483647,2147483647]
]

Output: [
  [0,-1],
  [1,2]
]
```
Apporach:
- Run BFS from each treasure node
- And for each inifinity cell found add + 1

```cpp
class Solution {
public:
    void islandsAndTreasure(vector<vector<int>>& grid) {
    
        int m = grid.size();
        int n = grid[0].size();

        queue<pair<int, int>> q;
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (!grid[r][c]) {
                    q.push({r,c});
                }
            }
        }

        vector<vector<int>> dirs = {{-1, 0}, {1, 0},
                                    {0, -1}, {0, 1}};

        while (!q.empty()) {
            int row = q.front().first;
            int col = q.front().second;
            q.pop();

            for (int i = 0; i < 4; i++) {
                int r = row + dirs[i][0];
                int c = col + dirs[i][1];

                if (r < 0 || r >= m || c < 0 ||
                    c >= n || grid[r][c] != INT_MAX) {
                    continue;
                }

                grid[r][c] = grid[row][col] + 1;
                q.push({r, c});
            }
        }
    }
};
```
### Rotting Fruit
> You are given a 2-D matrix grid. Each cell can have one of three possible values:

0 representing an empty cell
1 representing a fresh fruit
2 representing a rotten fruit
Every minute, if a fresh fruit is horizontally or vertically adjacent to a rotten fruit, then the fresh fruit also becomes rotten.

Return the minimum number of minutes that must elapse until there are zero fresh fruits remaining. If this state is impossible within the grid, return -1.

```bash
Example 1:

Input: grid = [[1,1,0],[0,1,1],[0,1,2]]
Output: 4

Example 2:

Input: grid = [[1,0,1],[0,2,0],[1,0,1]]
Output: -1
```

Aproach:
- store the no of fresh fruits
- level order using bfs, make adjacent fruit bad while traversing and reduce fresh fruit count.
- after the traversal check if fresh fruit count is 0 
- if yes return time else -1
```cpp
class Solution {
   const vector<vector<int>> dir = {{-1,0}, {1,0}, {0, -1}, {0, 1}};
public:
    int orangesRotting(vector<vector<int>>& grid) {
        const int R = grid.size();
        const int C = grid[0].size();
        int time = 0;
        int fresh = 0;

        queue<pair<int, int>> q;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++ ) {
                if (grid[i][j] == 2)
                    q.push({i,j});
                if (grid[i][j] == 1)
                    fresh++;
            }
        }

        while (fresh > 0 && !q.empty()) {
            int len = q.size();
            for (int i = 0; i < len; i++) {
                int rw = q.front().first;
                int cl = q.front().second;

                q.pop();
                
                for (int i = 0; i < dir.size(); i++) {
                    int r = rw + dir[i][0];
                    int c = cl + dir[i][1];

                    if (r < 0 || r >= R || c < 0 || c >= C || !grid[r][c] || grid[r][c] == 2)
                        continue;
                    
                    fresh--;
                    grid[r][c] = 2;
                    q.push({r,c});
                }
            }

            time++;
        }

        return !fresh? time : -1;
    }
};

```