# Graph Problems

1. [Island Perimeter](#island-perimeter)
1. [Number of Islands](#number-of-islands)
1. [Max Area of Island](#max-area-of-island)
1. [Islands and Treasure](#islands-and-treasure)
1. [Rotting Fruit](#rotting-fruit)
1. [Find if Path Exists in Graph](#find-if-path-exists-in-graph)
1. [Clone Graph](#clone-graph)
1. [Surrounded Regions](#surrounded-regions)
1. [Course Schedule](#course-schedule)
1. [Graph Valid Tree](#graph-valid-tree)
1. [Course Schedule II](#course-schedule-ii)
1. [Graph Alogrithms](#graph-alogrithms)
    1. [Cycle Detection In Undirected Graph](#cycle-detection-in-undirected-graph)
    1. [Cycle Detection In Directed Graph](#cycle-detection-in-directed-graph)
    1. [Dijkstras Algorithm](#dijkstras-algorithm)
1. [Network Delay Time](#network-delay-time)
1. [Alien Dictionary](#alien-dictionary)

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

### Surrounded Regions
> You are given a 2-D matrix board containing 'X' and 'O' characters.

If a continous, four-directionally connected group of 'O's is surrounded by 'X's, it is considered to be surrounded.

Change all surrounded regions of 'O's to 'X's and do so in-place by modifying the input board.

```bash 
Example 1:

Input: board = [
  ["X","X","X","X"],
  ["X","O","O","X"],
  ["X","O","O","X"],
  ["X","X","X","O"]
]

Output: [
  ["X","X","X","X"],
  ["X","X","X","X"],
  ["X","X","X","X"],
  ["X","X","X","O"]
]
```

Apporach:
- lets dfs from all the 4 edges when it has O
- mark all the O reachable from the edge O as # this
- after traversal, all the boarded O will remain O but the the O connected to corners O will be marked as #

```cpp
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int ROW = board.size();
        int COL = board[0].size();

        for (int j = 0; j < COL; j++) {
            if (board[0][j] == 'O')
                dfs(board, 0, j);
        
            if (board[ROW - 1][j] == 'O')
                dfs(board, ROW - 1, j);
        }
        
        for (int i = 0; i < ROW; i++) {
            if (board[i][0] == 'O')
                dfs(board, i, 0);
        
            if (board[i][COL - 1] == 'O')
                dfs(board, i, COL - 1);
        }
        
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                if (board[i][j] == '#')
                    board[i][j] = 'O';
                else if (board[i][j] == 'O')
                    board[i][j] = 'X';
            }
        }

    }

    void dfs(vector<vector<char>>& board, int i, int j) {
        //base
        if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size() || board[i][j] != 'O')
            return;

        board[i][j] = '#';
        
        dfs(board, i + 1, j);
        dfs(board, i - 1, j);
        dfs(board, i, j + 1);
        dfs(board, i, j - 1);
    }
};
```

### Course Schedule

> You are given an array prerequisites where prerequisites[i] = [a, b] indicates that you must take course b first if you want to take course a.

The pair [0, 1], indicates that must take course 1 before taking course 0.

There are a total of numCourses courses you are required to take, labeled from 0 to numCourses - 1.

Return true if it is possible to finish all courses, otherwise return false.

```bash
Example 1:

Input: numCourses = 2, prerequisites = [[0,1]]

Output: true
Explanation: First take course 1 (no prerequisites) and then take course 0.

Example 2:

Input: numCourses = 2, prerequisites = [[0,1],[1,0]]

Output: false
Explanation: In order to take course 1 you must take course 0, and to take course 0 you must take course 1. So it is impossible.
```

Apporach:
- use dfs to find cycle detection
- We can erase the course which has no cycle

```cpp
class Solution {
public:
    unordered_map<int, vector<int>> course_map;
    unordered_set<int> visited;
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        
        // Build adj matrix
        for (int i = 0; i < numCourses; i++)
            course_map[i] = {};
        
        for (auto el: prerequisites)
            course_map[el[0]].push_back(el[1]);
        
        for (int i = 0; i < numCourses; i++) {
            if (!dfs(i))
                return false;
        }

        return true;
    }

    bool dfs(int i) {
        // cycle detection
        if (visited.count(i))
            return false;
        
        if (course_map[i].empty())
            return true;

        visited.insert(i);
        for (auto el: course_map[i])
            if(!dfs(el))
                return false;
        
        visited.erase(i);
        course_map[i].clear();
    
        return true;
    }
};

```

### Graph Valid Tree
> Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to check whether these edges make up a valid tree.

```bash
Example 1:

Input:
n = 5
edges = [[0, 1], [0, 2], [0, 3], [1, 4]]

Output:
true
Example 2:

Input:
n = 5
edges = [[0, 1], [1, 2], [2, 3], [1, 3], [1, 4]]

Output:
false
Note:

You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.

```


Apporach:
- if cycle detected in the graph then not a tree
- if every node not reachable from root not then not a tree.

```cpp
class Solution {
public:
    unordered_map<int, vector<int>> adj_mat;
    unordered_set<int> visited;

    bool validTree(int n, vector<vector<int>>& edges) {

        // adj build
        for (int i = 0; i < n; i++)
            adj_mat[i] = {};

        for (auto edge: edges) {
            adj_mat[edge[0]].push_back(edge[1]);
            adj_mat[edge[1]].push_back(edge[0]);
        }
        
        if (!dfs(0, -1))
            return false;

        return visited.size() == n;
    }

    bool dfs(int n, int parent) {

        visited.insert(n);
        
        for (auto e: adj_mat[n]) {

            // if not visited visit
            if (!visited.count(e)) {
                if (!dfs(e, n))
                    return false;
            // already visited ? not parent
            } else if (e != parent) {
                return false;
            }
        }

        return true;
    }
};

```
### Course Schedule II

> You are given an array prerequisites where prerequisites[i] = [a, b] indicates that you must take course b first if you want to take course a.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
There are a total of numCourses courses you are required to take, labeled from 0 to numCourses - 1.

Return a valid ordering of courses you can take to finish all courses. If there are many valid answers, return any of them. If it's not possible to finish all courses, return an empty array.

```bash
Example 1:

Input: numCourses = 3, prerequisites = [[1,0]]

Output: [0,1,2]
Explanation: We must ensure that course 0 is taken before course 1.

Example 2:

Input: numCourses = 3, prerequisites = [[0,1],[1,2],[2,0]]

Output: []
Explanation: It's impossible to finish all courses.

```

Apporach:
- Same as COURSE SCHEDULE I
- save the course if no cycle is found for a start course

```cpp
class Solution {
public:
    vector<int> output;
    unordered_map<int, vector<int>> prereq;

    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        

        vector<bool> visited(numCourses, false);
        vector<bool> recStack(numCourses, false);

        // build adjacency list
        for (const auto& pair : prerequisites) {
            prereq[pair[0]].push_back(pair[1]);
        }

        for (int i = 0; i < numCourses; i++) {
            if (!visited[i]) {
                // return true if cycle detected else returns false
                if (dfs_d_graph(i, visited, recStack))
                    return {};
            }

        }
        return output;
    }

    bool dfs_d_graph(int node, vector<bool>& visited, vector<bool>& recStack) {
        visited[node] = true;

        // add to recursion stack
        recStack[node] = true;
        for (auto n: prereq[node]) {
            if (!visited[n]) {
                if (dfs_d_graph(n, visited, recStack))
                    return true;
            // if visited and still present in rescursion stack
            // cycle present
            } else if (recStack[n]) 
                return true;
        }

        // remove from the recursionstack
        recStack[node] = false;
        output.push_back(node);

        return false;
    }
};
```

## Graph Alogrithms

### Cycle Detection In Undirected Graph

Algo:
- We keep track of visited nodes.
- For every adjacent node v of u:
    - If v is not visited, recurse for v.
    - If v is visited and v != parent, then a cycle is detected.

```cpp
bool dfs_ud_graph(int u, int parent, vector<int> adj[], vector<bool>& visited) {
    
    visited[u] = true;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            if (dfs_ud_graph(v, u, adj, visited))
                return true;
        }
        // If visited and not the parent, it's a cycle
        else if (v != parent) {
            return true;
        }
    }
    return false;
}

bool has_cycle_in_ud_graph(int V, vector<int> adj[]) {
    vector<bool> visited(V, false);
    
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (dfs_ud_graph(i, -1, adj, visited))
                return true;
        }
    }
    return false;
}
```

### Cycle Detection In directed Graph

- Why above logic wont work always for directed graph ?
    - due to cross edges

Track the following state:
- **Unvisited**: Not yet processed.
- **Visiting**: Currently in the recursion stack (ancestor).
- **Visited**: Fully processed and popped off the stack.

Algo:
- Maintain a recursionStack (or use the "Visiting" state).
- For each neighbor v of u:
    - If v is in the recursionStack, Cycle Found.
    - If v is unvisited, recurse.
- Once all neighbors are processed, remove u from the recursionStack.

```cpp
bool dfs_d_graph(int u, vector<int> adj[], vector<bool>& visited, vector<bool>& recStack) {
    visited[u] = true;
    recStack[u] = true; // Add to current path

    for (int v : adj[u]) {
        if (!visited[v]) {
            if (dfs_d_graph(v, adj, visited, recStack))
                return true;
        }
        // If it's already in the recursion stack, it's a back edge
        else if (recStack[v]) {
            return true;
        }
    }

    recStack[u] = false; // Remove from path before backtracking
    return false;
}

bool has_cycle_in_d_graph(int V, vector<int> adj[]) {
    vector<bool> visited(V, false);
    vector<bool> recStack(V, false);
    
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (dfs_d_graph(i, adj, visited, recStack))
                return true;
        }
    }
    return false;
}
```

### Number of Connected Components in an Undirected Graph

> There is an undirected graph with n nodes. There is also an edges array, where edges[i] = [a, b] means that there is an edge between node a and node b in the graph.

The nodes are numbered from 0 to n - 1.

Return the total number of connected components in that graph.

```bash
Example 1:

Input:
n=3
edges=[[0,1], [0,2]]

Output:
1
Example 2:

Input:
n=6
edges=[[0,1], [1,2], [2,3], [4,5]]

Output:
2
```

Apporach:
- create adj list from the edge list
- iterate over all the nodes
- for each dfs from a new unvisited node we will find a new component.

```cpp
class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<bool> visited(n, false);
        vector<vector<int>> adj(n);
    
        int res = 0;
        for (auto e: edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        // iterate over all the nodes
        for (int node = 0; node < n; node++) {
            // when dfs started for a new node a new component is found!
            if (!visited[node]) {
                dfs(node, adj, visited);
                res++;
            }
        }

        return res;

    }

    void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited) {
        visited[node] = true;
        for (auto n: adj[node]) {
            if (!visited[n])
                dfs(n, adj, visited);
        }
    }
};
```

### Dijkstra's Algorithm

Apporach:
- Greedy Aporach
- pick the sortest edge from the neighbours using heap

```cpp
class Solution {
public:
    unordered_map<int, int> shortestPath(int n, vector<vector<int>>& edges, int src) {
        unordered_map<int, int> res;

        unordered_map<int, vector<vector<int>>> adj_list;
        for (auto x: edges) {
            adj_list[x[0]].push_back({x[1], x[2]});
        }

        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> hp;
        hp.push({0, src});

        vector<int> node;
        
        while (!hp.empty()) {
            node = hp.top();
            hp.pop();
            // skip already visted nodes
            if (res.count(node[1]))
                continue;
            
            res[node[1]] = node[0];
            
            for (auto x: adj_list[node[1]]) {
                if (!res.count(x[0]));
                    hp.push({node[0] + x[1], x[0]});
            }
        }

        for (int i =0; i < n; i++) {
            if (!res.count(i))
                res[i] = -1;
        }

        return res;    
    }
};

```

### Network Delay Time
> You are given a network of n directed nodes, labeled from 1 to n. You are also given times, a list of directed edges where times[i] = (ui, vi, ti).

ui is the source node (an integer from 1 to n)
vi is the target node (an integer from 1 to n)
ti is the time it takes for a signal to travel from the source to the target node (an integer greater than or equal to 0).
You are also given an integer k, representing the node that we will send a signal from.

Return the minimum time it takes for all of the n nodes to receive the signal. If it is impossible for all the nodes to receive the signal, return -1 instead.

```bash
Example 1:
Input: times = [[1,2,1],[2,3,1],[1,4,4],[3,4,1]], n = 4, k = 1

Output: 3

Example 2:
Input: times = [[1,2,1],[2,3,1]], n = 3, k = 2
Output: -1
```
Apporach:
- Use Dijkstra algo
```cpp
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        unordered_map<int, vector<vector<int>>> adj_m;
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> hp;
        unordered_map<int, int> res;
        int ret = 0;

        for (auto x: times) {
            adj_m[x[0]].push_back({x[1], x[2]});
        }

        hp.push({0, k});

        vector<int> node;
        while (!hp.empty()) {
            node = hp.top();
            hp.pop();

            // already visited
            if (res.count(node[1]))
                continue;

            res[node[1]] = node[0];
            ret = node[0];

            for (auto x: adj_m[node[1]]) {
                if (!res.count(x[0]))
                    hp.push({node[0] + x[1], x[0]});
            }
        }

        return res.size() == n ? ret : -1;
    }
};
```

### Alien Dictionary
> There is a foreign language which uses the latin alphabet, but the order among letters is not "a", "b", "c" ... "z" as in English.

You receive a list of non-empty strings words from the dictionary, where the words are sorted lexicographically based on the rules of this new language.

Derive the order of letters in this language. If the order is invalid, return an empty string. If there are multiple valid order of letters, return any of them.

A string a is lexicographically smaller than a string b if either of the following is true:

The first letter where they differ is smaller in a than in b.
a is a prefix of b and a.length < b.length.
```bash
Example 1:

Input: ["z","o"]

Output: "zo"
Explanation:
From "z" and "o", we know 'z' < 'o', so return "zo".

Example 2:

Input: ["hrn","hrf","er","enn","rfnn"]

Output: "hernf"
Explanation:

from "hrn" and "hrf", we know 'n' < 'f'
from "hrf" and "er", we know 'h' < 'e'
from "er" and "enn", we know get 'r' < 'n'
from "enn" and "rfnn" we know 'e'<'r'
so one possibile solution is "hernf"
```

Apporach:
- Topological Sort
- Two things:
    - there should be no cycle and
    - strings should be legically sorted

```cpp
class Solution {
public:
    unordered_map<char, vector<char>> adj_m;
    unordered_map<char, bool> visited;
    unordered_map<char, bool> r_stk;
    string foreignDictionary(vector<string>& words) {
        // Neccessary as there can be disconnected graphs as well
        for (const string& w : words) {
            for (char c : w) {
                if (adj_m.find(c) == adj_m.end()) {
                    adj_m[c] = {};
                }
            }
        }

        for (int i = 0; i < words.size() - 1; i++) {
            string w1 = words[i];
            string w2 = words[i + 1];

            int min_len = min(w1.length(), w2.length());

            // check for lexical ordered
            if (w1.length() > w2.length() && w1.substr(0, min_len) == w2)
                return "";
            
            for (int j = 0; j < min_len; j++) {
                if (w1[j] != w2[j]) {
                    adj_m[w1[j]].push_back(w2[j]);
                    break; // break because rest characters will not give any info
                }
            }
        }

        string res = "";
        for(auto x: adj_m) {
            if (dfs(x.first, res))
                return "";
        }

        reverse(res.begin(), res.end());
        return res;
    }

    bool dfs(char x, string& res) {
        if (r_stk[x]) return true;  // Cycle found
        if (visited[x]) return false; // Already processed
        
        visited[x] = true;
        r_stk[x] = true;

        for (auto n: adj_m[x]) {
            if (dfs(n, res))
                return true;
        }

        r_stk[x] = false;
        res += x;
        return false;
    }
};

```