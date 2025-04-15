# Heap Problems

## Heap problems
### Aproach
    1. if find k largest -> min heap
    2. if find k smallest -> max heap 

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
 