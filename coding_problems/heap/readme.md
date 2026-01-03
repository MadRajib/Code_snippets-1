# Heap Problems

1. [Kth Smallest Element](#1-kth-smallest-element)
1. [Sort an kth sorted array](#2-sort-an-kth-sorted-array)
1. [K closest elements in an unsoreted array](#3-k-closest-elements-in-an-unsoreted-array)
1. [Top K Frequent Elements](#4-top-k-frequent-elements)
1. [K Closest Points to Origin](#5-k-closest-points-to-origin)
1. [Minimum Cost of ropes](#6-minimum-cost-of-ropes)
1. [Task Scheduler](#task-scheduler)
1. [Single Threaded CPU](#single-threaded-cpu)
1. [Find Median From Data Stream](#find-median-from-data-stream)

Note:
```cpp
priority_queue<int> maxheap; // max heap
priority_queue<int, vector<int>, greater<int>> minheap; //min heap

// Custom Comparision operator
struct CustomCompare {
    bool operator()(vector<int>p, vector<int> q) {
        return  p[0]*p[0] + p[1]*p[1] < q[0]*q[0] + q[1]*q[1];
    }
};

priority_queue<vector<int>, vector<vector<int>>, CustomCompare> mxhp;
```

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
Observation:
* if take first k elements, min element in this range
will always be present in this range.
* so we can use min heap to locate it as the topmost element
in heap of k size.

Approach
* We will create an min heap of first k elements
* This heap will capture the min element in this k range of the array.
* we will save the min  element to pos = 0
* we will pop this and add a new element to the heap.
* now the min heap will have second smallest element for the array at top.
* keep this untill array fully iterated.
* pop elements in order as they are smallest to largest.

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
Observation:
* we need to find the k minimum abs(x-elem) 
* We can use max heap to store abs(x-elem) , this will give as k elements from largest diff to smallest diff.
* why no min-heap of size k ?
    * bocz to add a new element we need to discard an old one,
    how will we know which is the fartest element to remove ?
    * In max heap after we add an element, our heap will be k + 1, and the fartest element will always be in top to discard.

Apporoach:
* Create a max heap of abs(x-elem), then pop the elements to an vector.
* return the res after sorting it.

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
 
### 4. Top K Frequent Elements
> Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.
```bash
Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Example 2:

Input: nums = [1], k = 1
Output: [1]
```

Obervation:
* We need to store the count of the element first
* than use it to create a min heap of size k to get the most frequent elements.

Aproach:
* use hash map for the count array
* create a min heap use count as comparison

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

### 5. K Closest Points to Origin
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

### 6. Minimum Cost of ropes
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

Observation:
* If two min elements are joined in every iteration this gives the min cost.
* we can use min heap.

Approach:
* store elements in the min heap.
* pop 2 elements and sum them and push to heap, keep on doing it untill only one element is present in the heap.

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

### Task Scheduler
> You are given an array of CPU tasks tasks, where tasks[i] is an uppercase english character from A to Z. You are also given an integer n.

Each CPU cycle allows the completion of a single task, and tasks may be completed in any order.

The only constraint is that identical tasks must be separated by at least n CPU cycles, to cooldown the CPU.

Return the minimum number of CPU cycles required to complete all tasks.
```bash
Example 1:

Input: tasks = ["X","X","Y","Y"], n = 2

Output: 5
Explanation: A possible sequence is: X -> Y -> idle -> X -> Y.

Example 2:

Input: tasks = ["A","A","A","B","C"], n = 3

Output: 9
Explanation: A possible sequence is: A -> B -> C -> Idle -> A -> Idle -> Idle -> Idle -> A.
```

Apporach:
    - Create a max heap to store tasks with their frequency
    - a tasks queue with remaining execution time and next time to run
    - pick the tasks from the max heap, process a unit and push back to quueue with next running time i.e time + n
    - after processing pick the next task from front of the queuue if its next running time is equal to curren time

```cpp
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> cnt(26, 0);
        priority_queue<int> max_hp;
        // execution time, next execution time
        queue<pair<int, int>> task_q; 

        for (auto t:tasks)
            cnt[t - 'A']++;

        for (auto c: cnt) {
            if (c)
                max_hp.push(c);
        }
            
        
        int time = 0;
        while (!task_q.empty() || !max_hp.empty()) {
            time++;
            
            // take the top task and process it
            if (!max_hp.empty()) {
                int t = max_hp.top() - 1; // -1 to process 1 unit
                max_hp.pop();
        
                if (t)
                    task_q.push({t, time + n});
            }

            // check for tasks in queue to process
            // check for the first task is ready to submit to max heap
            if (!task_q.empty() && task_q.front().second ==  time) {
                max_hp.push(task_q.front().first);
                task_q.pop();
            }
        }

        return time;

    }
};

```
### Single Threaded CPU
> You are given n tasks labeled from 0 to n - 1 represented by a 2D integer array tasks, where tasks[i] = [enqueueTimei, processingTimei] means that the ith task will be available to process at enqueueTime[i] and will take processingTime[i] to finish processing.

You have a single-threaded CPU that can process at most one task at a time and will act in the following way:

If the CPU is idle and there are no available tasks to process, the CPU remains idle.
If the CPU is idle and there are available tasks, the CPU will choose the one with the shortest processing time. If multiple tasks have the same shortest processing time, it will choose the task with the smallest index.
Once a task is started to process, the CPU will process the entire task without stopping.
The CPU can finish a task then start a new one instantly.
Return the order in which the CPU will process the tasks.

```bash
Example 1:

Input: tasks = [[1,4],[3,3],[2,1]]

Output: [0,2,1]
Example 2:

Input: tasks = [[5,2],[4,4],[4,1],[2,1],[3,3]]

Output: [3,4,2,0,1]
```


```cpp
class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> available;
        priority_queue<array<int, 3>, vector<array<int, 3>>, greater<>> pending;

        int n = tasks.size();
        for (int i = 0; i < n; ++i) {
            pending.push({tasks[i][0], tasks[i][1], i});
        }

        vector<int> res;
        long long time = 0;
        while (!pending.empty() || !available.empty()) {
            while (!pending.empty() && pending.top()[0] <= time) {
                auto [enqueueTime, processTime, index] = pending.top();
                pending.pop();
                available.push({processTime, index});
            }

            if (available.empty()) {
                time = pending.top()[0];
                continue;
            }

            auto [processTime, index] = available.top();
            available.pop();
            time += processTime;
            res.push_back(index);
        }

        return res;
    }
};
```

### Find Median From Data Stream
> The median is the middle value in a sorted list of integers. For lists of even length, there is no middle value, so the median is the mean of the two middle values.

For example:

For arr = [1,2,3], the median is 2.
For arr = [1,2], the median is (1 + 2) / 2 = 1.5
Implement the MedianFinder class:

MedianFinder() initializes the MedianFinder object.
void addNum(int num) adds the integer num from the data stream to the data structure.
double findMedian() returns the median of all elements so far.

```bash
Example 1:

Input:
["MedianFinder", "addNum", "1", "findMedian", "addNum", "3" "findMedian", "addNum", "2", "findMedian"]

Output:
[null, null, 1.0, null, 2.0, null, 2.0]

Explanation:
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.findMedian(); // return 1.0
medianFinder.addNum(3);    // arr = [1, 3]
medianFinder.findMedian(); // return 2.0
medianFinder.addNum(2);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0
```

Intuition:
- To efficiently find the median while numbers keep coming, we split the
stream into two halves:

- A max-heap (small) that stores the smaller half of the numbers.
    - The largest number of this half is on top.
- A min-heap (large) that stores the larger half of the numbers.
    - The smallest number of this half is on top.

The goal:

- Ensure both heaps are balanced in size (difference at most 1).
- Ensure all numbers in small are ≤ all numbers in large.

This setup allows:
- Median = top of the bigger heap (if odd count)
- Median = average of both tops (if even count)

This gives O(log n) insert and O(1) median lookup.

```cpp
class MedianFinder {
    priority_queue<int, vector<int>, less<int>> smallHeap;
    priority_queue<int, vector<int>, greater<int>> largeHeap;

public:
    MedianFinder() {}

    void addNum(int num) {
        smallHeap.push(num);
        if (!largeHeap.empty() && smallHeap.top() > largeHeap.top()) {
            largeHeap.push(smallHeap.top());
            smallHeap.pop();
        }
        if (smallHeap.size() > largeHeap.size() + 1) {
            largeHeap.push(smallHeap.top());
            smallHeap.pop();
        }
        if (largeHeap.size() > smallHeap.size() + 1) {
            smallHeap.push(largeHeap.top());
            largeHeap.pop();
        }
    }

    double findMedian() {
        if (smallHeap.size() == largeHeap.size()) {
            return (largeHeap.top() + smallHeap.top()) / 2.0;
        } else if (smallHeap.size() > largeHeap.size()) {
            return smallHeap.top();
        } else {
            return largeHeap.top();
        }
    }
};
```