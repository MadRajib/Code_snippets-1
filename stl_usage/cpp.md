## STL Usage
1. [Vectors](#vectors)
1. [Reference a 2D vector globally after construction](#reference-a-2d-vector-globally-after-construction)
1. [Priority Queue](#priority-queue)

### Vectors  
Initializations:
```cpp
vector<T> v1;           // default initialization, v1 is empty;
  
vector<T> v2(v1);       // v2 has copy of each element of v1;
  
vector<T> v2 = v1;      // Equivalemnt of v2(v1);
  
vector<T> v3(n,val);    // v3 has n elements with value val;
  
vector<T> v4(n);        // v4 has n copies of vale-initialied object;
  
vector<T> v5{a,b,c};    // definig;
  
vector<T> v5 = {a,b,c}; // same as above;
```

Initializing 2d vectors
```cpp
vector<vector<int>> table<ROWS_COUNT, vector<int>(COLS_COUNT)>;
  
vector<vector<int>> table<ROWS_COUNT, vector<int>(COLS_COUNT, val)>;
```

### Reference a 2D vector globally after construction

#### 1. Use a global pointer
```cpp
vector<vector<int>> *vis;   // global pointer

void dfs(int x, int y) {
    (*vis)[x][y] = 1;        // use original array (no copy)
}

int main() {
    vector<vector<int>> visited(100, vector<int>(100, 0));
    vis = &visited;          // assign reference via pointer

    dfs(0, 0);
}
```
#### 2. Use a global reference wrapper
- cpp doesn't allows uinitialize global reference
- but we can use a wrapper

```cpp
std::reference_wrapper<vector<vector<int>>> visRef = *(vector<vector<int>>*)nullptr;

void dfs(int x, int y) {
    visRef.get()[x][y] = 1;   // no copy
}

int main() {
    vector<vector<int>> visited(100, vector<int>(100, 0));
    visRef = visited;    // binds reference to the original

    dfs(0, 0);
}
```

#### 3. Make the matrix global directly
```cpp
vector<vector<int>> visited;

void dfs(int x, int y) {
    visited[x][y] = 1;
}

int main() {
    visited.assign(n, vector<int>(m, 0));
}
```

### Priority Queue
```bash

priority_queue<T, Conatiner, Comparator> pq;

Params:
T	-	The type of the stored elements.  
Container	-	The type of the underlying container to use to store the elements.
Compare	-	A Compare type providing a strict weak ordering.
eg 
priority_queue<int, vector<int>, greater<int>> pq;
```
APIS:
```cpp
front()
push_back()
pop_back()
```