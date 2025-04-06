# Sliding window Problems

## Fixed size sliding win problems
### Aproach
    1. While iterating save the value or index
    2. if win size if reached store the res based on conditon and reduce win size
    3. Return the res

### 1. Max Sum Subarray of size K
> Given an array of integers arr[]  and a number k. Return the maximum sum of a subarray of size k.
```bash
Input: arr[] = [100, 200, 300, 400] , k = 2
Output: 700
Explanation: arr3  + arr4 = 700, which is maximum.
Input: arr[] = [100, 200, 300, 400] , k = 4
Output: 1000
Explanation: arr1 + arr2 + arr3 + arr4 = 1000, which is maximum.
```

```cpp
    int maximumSumSubarray(vector<int>& arr, int k) {
        // code here
        int s = 0;
        int max_sm = 0;
        int sm = 0;
        for (int i = 0; i < arr.size(); i++) {
            sm += arr[i];
            /* Check if win size is reached*/
            if (i - s + 1 == k) {
               max_sm = max(max_sm, sm);
               sm -= arr[s];
               s++;
            }
        }
        
        return max_sm;
    }
```