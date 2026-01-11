# Graph Problems

1. [Island Perimeter](#island-perimeter)
1. [Number of Islands](#number-of-islands)
1. [Max Area of Island](#max-area-of-island)
1. [Islands and Treasure](#islands-and-treasure)
1. [Rotting Fruit](#rotting-fruit)
1. [Find if Path Exists in Graph](#find-if-path-exists-in-graph)
1. [Clone Graph](#clone-graph)

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
### Pacific Atlantic Water Flow
> There is an m x n rectangular island that borders both the Pacific Ocean and Atlantic Ocean. The Pacific Ocean touches the island's left and top edges, and the Atlantic Ocean touches the island's right and bottom edges.

The island is partitioned into a grid of square cells. You are given an m x n integer matrix heights where heights[r][c] represents the height above sea level of the cell at coordinate (r, c).

The island receives a lot of rain, and the rain water can flow to neighboring cells directly north, south, east, and west if the neighboring cell's height is less than or equal to the current cell's height. Water can flow from any cell adjacent to an ocean into the ocean.

Return a 2D list of grid coordinates result where result[i] = [ri, ci] denotes that rain water can flow from cell (ri, ci) to both the Pacific and Atlantic oceans.

```bash
Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
Explanation: The following cells can flow to the Pacific and Atlantic oceans, as shown below:
[0,4]: [0,4] -> Pacific Ocean 
       [0,4] -> Atlantic Ocean
[1,3]: [1,3] -> [0,3] -> Pacific Ocean 
       [1,3] -> [1,4] -> Atlantic Ocean
[1,4]: [1,4] -> [1,3] -> [0,3] -> Pacific Ocean 
       [1,4] -> Atlantic Ocean
[2,2]: [2,2] -> [1,2] -> [0,2] -> Pacific Ocean 
       [2,2] -> [2,3] -> [2,4] -> Atlantic Ocean
[3,0]: [3,0] -> Pacific Ocean 
       [3,0] -> [4,0] -> Atlantic Ocean
[3,1]: [3,1] -> [3,0] -> Pacific Ocean 
       [3,1] -> [4,1] -> Atlantic Ocean
[4,0]: [4,0] -> Pacific Ocean 
       [4,0] -> Atlantic Ocean
Note that there are other possible paths for these cells to flow to the Pacific and Atlantic oceans.
Example 2:

Input: heights = [[1]]
Output: [[0,0]]
Explanation: The water can flow from the only cell to the Pacific and Atlantic oceans.
```

Apporach:
- DFS from each node closest to the ocean i.e first row, last row, firs col and last colum.
- On each traversel check if the water can flow from the next node to current node, if yes dfs to that node.
- Dont vist a node already visited for a ocean.
- Post iteration check all node, and add to result if a node can be reached from both the ocean.
```cpp
class Solution {
    const vector<pair<int, int>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    int ROWS = 0;
    int COLS = 0;
    vector<vector<int>> heights;
    
    void dfs (int r, int c, vector<vector<vector<bool>>>& visited, int ocean) {
        
        cout <<"r : "<<r << " c: "<<c <<endl;
        visited[r][c][ocean] = true;

        for (auto [dr, dc]: dirs) {
            int nr = r + dr;
            int nc = c + dc;

            if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS 
                && !visited[nr][nc][ocean] && heights[nr][nc] >= heights[r][c])
                dfs(nr, nc, visited, ocean);
        }
    }
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        this->heights = heights;
        ROWS = heights.size();
        COLS = heights[0].size();
        vector<vector<int>> res;
        // each cell has 2 bools:
        // - 0   reacable to pacific ?
        // - 1   reacable to atlantic ?
        vector<vector<vector<bool>>> 
            visited(ROWS, vector<vector<bool>>(COLS, vector<bool>(2, false)));

        for (int c = 0; c < COLS; c++) {
            dfs(0, c, visited, 0); // 0 for pacific
            dfs(ROWS - 1, c, visited, 1); // 1 for atlantic
        }

        for (int r = 0; r < ROWS; r++) {
            dfs(r, 0, visited, 0); // 0 for pacific
            dfs(r, COLS - 1, visited, 1); // 1 for atlantic
        }

        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                if (visited[r][c][0] && visited[r][c][1]) {
                    res.push_back({r,c});
                }
            }
        }

        return res;
    }
};
```

### Find if Path Exists in Graph
> There is a bi-directional graph with n vertices, where each vertex is labeled from 0 to n - 1 (inclusive). The edges in the graph are represented as a 2D integer array edges, where each edges[i] = [ui, vi] denotes a bi-directional edge between vertex ui and vertex vi. Every vertex pair is connected by at most one edge, and no vertex has an edge to itself.

You want to determine if there is a valid path that exists from vertex source to vertex destination.

Given edges and the integers n, source, and destination, return true if there is a valid path from source to destination, or false otherwise.

```bash
Input: n = 3, edges = [[0,1],[1,2],[2,0]], source = 0, destination = 2
Output: true
Explanation: There are two paths from vertex 0 to vertex 2:
- 0 → 1 → 2
- 0 → 2

Input: n = 6, edges = [[0,1],[0,2],[3,5],[5,4],[4,3]], source = 0, destination = 5
Output: false
Explanation: There is no path from vertex 0 to vertex 5.
```
Apporach:
* Create Adjacecy list
* use dfs to iterate throughg all the nodes

```cpp
class Solution {
public:
    unordered_map<int, vector<int>> adj_map;
    unordered_map<int, bool> visited;
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        for (auto edge: edges) {
            adj_map[edge[0]].push_back(edge[1]);
            adj_map[edge[1]].push_back(edge[0]);
        }

        return dfs(source, destination);
    }

    bool dfs(int source, int destination) {
        if (source == destination)
            return true;
        visited[source] = true;
        for (auto n: adj_map[source]) {
            // skip visted
            if (visited.find(n) != visited.end())
                continue;

            if (dfs(n, destination))
                return true;
        }
        return false;
    }
};
```

### Clone Graph

> Given a node in a connected undirected graph, return a deep copy of the graph.

Each node in the graph contains an integer value and a list of its neighbors.

class Node {
    public int val;
    public List<Node> neighbors;
}
The graph is shown in the test cases as an adjacency list. An adjacency list is a mapping of nodes to lists, used to represent a finite graph. Each list describes the set of neighbors of a node in the graph.

For simplicity, nodes values are numbered from 1 to n, where n is the total number of nodes in the graph. The index of each node within the adjacency list is the same as the node's value (1-indexed).

The input node will always be the first node in the graph and have 1 as the value.

```bash
Example 1:



Input: adjList = [[2],[1,3],[2]]

Output: [[2],[1,3],[2]]
Explanation: There are 3 nodes in the graph.
Node 1: val = 1 and neighbors = [2].
Node 2: val = 2 and neighbors = [1, 3].
Node 3: val = 3 and neighbors = [2].

Example 2:



Input: adjList = [[]]

Output: [[]]
Explanation: The graph has one node with no neighbors.

Example 3:

Input: adjList = []

Output: []
Explanation: The graph is empty.
```

Observation:
- seems similar to cloning tree problem i.e recursively building it
- what if there is cycles ? infinite jumps!

Apporach:
- For cycle, use map to map old -> new.
- before cloning a graph at node n, we check if we already saw it.
- if yes return the cached value else recursively clone it.

```cpp
class Solution {
public:
    unordered_map<Node *, Node *> mp;
    Node* cloneGraph(Node* node) {
        return rr_clone(node); 
    }

    Node* rr_clone(Node* node) {
        // base
        if (node == nullptr)
            return nullptr;
        
        if (mp.count(node))
            return mp[node];
        
        Node *clone = new Node(node->val);
        mp[node] = clone;

        for (auto n:node->neighbors)
            clone->neighbors.push_back(rr_clone(n));
        
        return clone;
    }
};
```