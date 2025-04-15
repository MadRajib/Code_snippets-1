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
        priority_queue<int, vector<int>, less<int>> maxheap;
        for (int i = 0; i < nums.size(); i++) {
            maxheap.push(nums[i]);
            if (maxheap.size() > k) {
                maxheap.pop();
            }
        }

        return heap.pop();
    }

    KthLargest(int k, vector<int>& nums) {
        priority_queue<int, vector<int>, greater<int>> minheap;
        for (int i = 0; i < nums.size(); i++){
            minheap.push(nums[i]);
            if (minheap.size() > k)
                minheap.pop();
        }

        return heap.pop();
    }
```