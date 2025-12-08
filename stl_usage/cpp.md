## STL Usage

1. [Vectors](#vectors)
1. [Reference a 2D vector globally after construction](#reference-a-2d-vector-globally-after-construction)
1. [Pair](#pair)
1. [Queue](#queue)
1. [Priority Queue](#priority-queue)
1. [Stack](#stack)


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

### Pair
```bash
template<
    class T1,
    class T2
> struct pair;
```
Initialisation:
```cpp
pair<int, int> pr = {1, 2};
pair<int, string> p2 = make_pair(1, "hello");

pair<int, string> p3;
p3.first = 3;
p3.second = "Cherry";
```

Apis:
```cpp
.first  // get the first element
.second // get the second element
```

### Queue
template <class T, class Container = deque<T> > class queue;

- T - Type of the elements.
- Container - Type of the internal underlying container object where the elements are stored. Its value_type shall be T.

Initialisation:
```cpp
std::queue<int> q;
// front() -> the first element
// back()  -> the last element
```

Apis:
```cpp
// Element Access
front()     // Access the first element
back()      // Access the last element

// Capacity
empty()     // check whether the container is empty
size()      // returns the no of elements

// Modifiers
push()      // inserts element at the end
pop()       // removes the first element
```

Examples:
```cpp
void bfs(*root) {
    queue<int> queue;

    queue.push(root);
    while (!q.empty()) {
        for ( i = q.size(); i >=0 ;i-- ) {
            node = q.front();
            q.pop();
            if (node) {
                q.push(node->left);
                q.push(node->right);
            }
        }
    }
}
```

### Priority Queue
```bash

priority_queue<T, Conatiner, Comparator> pq;

Params:
T	-	The type of the stored elements.  
Container	-	The type of the underlying container to use to store the elements.
Compare	-	A Compare type providing a strict weak ordering.
The expression comp(a,b), where comp is an object of this type and a and b are elements in the container, shall return true if a is considered to go before b in the strict weak ordering the function defines.

The priority_queue uses this function to maintain the elements sorted in a way that preserves heap properties (i.e., that the element popped is the last according to this strict weak ordering).

This can be a function pointer or a function object, and defaults to less<T>, which returns the same as applying the less-than operator (a<b)

```
Intialisation:

```cpp
// max priority queue
priority_queue<int> max_priority_queue;

// min priority queue
priority_queue<int, std::vector<int>, std::greater<int>> min_priority_queue(data.begin(), data.end());
```

APIS:
```cpp

// Capacity
empty()	    // Test whether container is empty
size()      // returns the no of elements

// Access
top()       // Access the top element
front() 

// Modifiers
push()      // inserts element and sorts the underlying container
pop()       // removes the top element
```
Example:
```cpp
KthSmallest(int k, vector<int>& nums) {
    priority_queue<int> maxheap;
    for (int i = 0; i < nums.size(); i++) {
        maxheap.push(nums[i]);
        if (maxheap.size() > k) {
            // pops the top element
            maxheap.pop();
        }
    }

    return heap.top();
}

KthLargest(int k, vector<int>& nums) {
    priority_queue<int, vector<int>, greater<int>> minheap;
    for (int i = 0; i < nums.size(); i++){
        minheap.push(nums[i]);
        if (minheap.size() > k)
            minheap.pop();
    }

    return heap.top();
}
```

### Dequeue
template < class T, class Alloc = allocator<T> > class deque;

- deque (usually pronounced like "deck") is an irregular acronym of double-ended queue. Double-ended queues are sequence containers with dynamic sizes that can be expanded or contracted on both ends (either its front or its back).

Implementation:
```cpp
std::deque<int> d = {7, 5, 16, 8};
```

Apis:
```cpp
// Element access
at(size_type pos)  //access specified element with bounds checking
operator[]         // access specified element
front()            // access the first element
back()             // access the last element

// Capacity
empty()	    // Test whether container is empty
size()      // returns the no of elements

// Modifiers
clear()     // clears the contents
iterator insert( const_iterator pos, const T& value );
iterator insert( const_iterator pos, T&& value );
iterator insert( const_iterator pos,
                 size_type count, const T& value );
template< class InputIt >
iterator insert( const_iterator pos, InputIt first, InputIt last );
iterator insert( const_iterator pos, std::initializer_list<T> ilist );       
// pos	-	iterator before which the content will be inserted
// value	-	element value to insert
// count	-	number of elements to insert
// first, last	-	the pair of iterators defining the range of elements to insert
// ilist	-	std::initializer_list to insert the values from

push_back()     // adds an element to the end
pop_back()      // removes the last element
push_front()    // inserts an element to the beginning
pop_front()     // removes the first element
```

### Stack
template<class T, class Container = std::deque<T> > class stack;

- T - Type of the elements.
- Container - Type of the internal underlying container object where the elements are stored. Its value_type shall be T.

Initialisation:
```cpp
std::stack<int> stk;
```

Apis:
```cpp
// Element Access
top()       // Access the top element

// Capacity
empty()     // check whether the container is empty
size()      // returns the no of elements

// Modifiers
push()      // inserts element at the top
pop()       // removes the top element
```

Examples:
```cpp
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> stack;
    TreeNode* cur = root;

    while (cur || !stack.empty()) {
        while (cur) {
            stack.push(cur);
            cur = cur->left;
        }
        
        cur = stack.top();
        stack.pop();
        res.push_back(cur->val);
        cur = cur->right;
    }

    return res;
}
```