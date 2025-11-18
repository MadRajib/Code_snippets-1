# Heap Problems

### Aproach & Identification
    1. if find k largest -> min heap
    2. if find k smallest -> max heap

    - kth largest means  -> smallest element in k len array
    - kth smallest means -> largest element in k len array

### 1. Kth Smallest Element
> Given an array and a number k where k is smaller than size of array,
we need to find the k’th smallest element in the given array.
It is given that all array elements are distinct.
```bash
Example:
Input: arr[] = {7, 10, 4, 3, 20, 15}
k = 3
Output: 7 . 

```

```cpp
    KthSmallest(int k, vector<int>& nums) {
        priority_queue<int> maxheap;
        for (int i = 0; i < nums.size(); i++) {
            maxheap.push(nums[i]);
            if (maxheap.size() > k) {
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

### 2. Sort an kth sorted array
> Given an array of n elements, where each element is at most k away from its target position
 devise an algorithm that sorts in O(n log k) time.
 For example,
 let us consider k is 2, an element at index 7 in the sorted array, can be at indexes 5, 6, 7, 8, 9 in the given array.

```bash
Example:
Input : arr[] = {6, 5, 3, 2, 8, 10, 9}
k = 3 
Output : arr[] = {2, 3, 5, 6, 8, 9, 10} . 

```
```cpp
    sort(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> minheap;
        int j = 0;
        for (int i = 0; i < nums.size(); i++){
            minheap.push(nums[i]);
            if (minheap.size() > k) {
                nums[j] = minheap.top();
                j++;
                minheap.pop();
            }
        }

        while (minheap.size > 0) {
            nums[j++] = minheap.top();
            minheap.pop();
        }
    }
```
### 3. K closest elements in an unsoreted array
>  Given a integer array arr, two integers k and x, return the k closest integers to x in the array.
The result should also be sorted in ascending order.

An integer a is closer to x than an integer b if:

|a - x| < |b - x|, or
|a - x| == |b - x| and a < b
 
```bash
Example 1:

Input: arr = [1,2,3,4,5], k = 4, x = 3

Output: [1,2,3,4]

Example 2:

Input: arr = [1,1,2,3,4,5], k = 4, x = -1

Output: [1,1,2,3]
```
```cpp
vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        priority_queue<pair<int, int>> maxheap;
        vector<int> res;

        for (auto n: arr) {
            maxheap.push({abs(x - n), n});
            if (maxheap.size() > k) {
                maxheap.pop();
            }
        }

       
        while (maxheap.size() > 0) {
            res.push_back(maxheap.top().second);
            maxheap.pop();
        }
        sort(res.begin(), res.end());
        return res;
    }
```
Note: If sorrted array is given better to use binary search.
 
### 347. Top K Frequent Elements
> Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.
```bash
Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Example 2:

Input: nums = [1], k = 1
Output: [1]
```

```cpp
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> result;
        unordered_map<int, int> map;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;


        //build a number count table
        for(auto x: nums)
            map[x]++;
        
        for(auto x: map) {
            min_heap.push({x.second, x.first});
            if(min_heap.size() > k)
                min_heap.pop();
        }
        
        while(!min_heap.empty()){
            result.push_back(min_heap.top().second);
            min_heap.pop();
        }
        return result;
    }
```

### 973. K Closest Points to Origin
> Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane and an integer k, return the k closest points to the origin (0, 0).

The distance between two points on the X-Y plane is the Euclidean distance (i.e., √(x1 - x2)2 + (y1 - y2)2).

You may return the answer in any order. The answer is guaranteed to be unique (except for the order that it is in).

```cpp
private:
    struct CustomCompare {
        bool operator()(vector<int>p, vector<int> q) {
            return  p[0]*p[0] + p[1]*p[1] < q[0]*q[0] + q[1]*q[1];
        }
    };
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        priority_queue<vector<int>, vector<vector<int>>, CustomCompare> mxhp;

        for (auto p: points) {
            mxhp.push(p);
            if (mxhp.size() > k)
                mxhp.pop();
        }

        vector<vector<int>> res;

        while (!mxhp.empty()) {
            res.push_back(mxhp.top());
            mxhp.pop();
        }


        return res;
        
    }
```

### Minimum Cost of ropes
> Given an array, arr[] of rope lengths, connect all ropes into a single rope with the minimum total cost. The cost to connect two ropes is the sum of their lengths. 

```bash
Examples:

Input: arr[] = [4, 3, 2, 6]
Output: 29
Explanation: We can connect the ropes in following ways.
1) First connect ropes of lengths 2 and 3. Which makes the array [4, 5, 6]. Cost of this operation 2 + 3 = 5. 
2) Now connect ropes of lengths 4 and 5. Which makes the array [9, 6]. Cost of this operation 4 + 5 = 9.
3) Finally connect the two ropes and all ropes have connected. Cost of this operation 9 + 6 =15. Total cost is 5 + 9 + 15 = 29. This is the optimized cost for connecting ropes. 
Other ways of connecting ropes would always have same or more cost. For example, if we connect 4 and 6 first (we get three rope of 3, 2 and 10), then connect 10 and 3 (we get two rope of 13 and 2). Finally we connect 13 and 2. Total cost in this way is 10 + 13 + 15 = 38.
Input: arr[] = [4, 2, 7, 6, 9]
Output: 62 
Explanation: First, connect ropes 4 and 2, which makes the array [6, 7, 6, 9]. Cost of this operation 4 + 2 = 6. 
Next, add ropes 6 and 6, which results in [12, 7, 9]. Cost of this operation 6 + 6 = 12.
Then, add 7 and 9, which makes the array [12,16]. Cost of this operation 7 + 9 = 16. And
finally, add these two which gives [28]. Hence, the total cost is 6 + 12 + 16 + 28 = 62.
Input: arr[] = [10]
Output: 0
Explanation: Since there is only one rope, no connections are needed, so the cost is 0.
```

```cpp
int minCost(vector<int>& arr) {
        // code here
        priority_queue<int, vector<int>, greater<int>> minhp;
        int res = 0;
        int temp = 0;
        
        for (auto x: arr)
            minhp.push(x);
        
        while (minhp.size() >= 2) {
            temp = minhp.top();
            minhp.pop();
            
            temp += minhp.top();
            minhp.pop();
            
            minhp.push(temp);
            res += temp;
            
        }
        
        return res;
    
    }
```