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