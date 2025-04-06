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

### 2. First negative in every window of size k
> Given an array arr[]  and a positive integer k, find the first negative integer for each and every window(contiguous subarray) of size k.

> Note: If a window does not contain a negative integer, then return 0 for that window.
```bash
Input: arr[] = [-8, 2, 3, -6, 10] , k = 2
Output: [-8, 0, -6, -6]
Explanation:
Window [-8, 2] First negative integer is -8.
Window [2, 3] No negative integers, output is 0.
Window [3, -6] First negative integer is -6.
Window [-6, 10] First negative integer is -6.


Input: arr[] = [12, -1, -7, 8, -15, 30, 16, 28] , k = 3
Output: [-1, -1, -7, -15, -15, 0] 
Explanation:
Window [12, -1, -7] First negative integer is -1.
Window [-1, -7, 8] First negative integer is -1.
Window [-7, 8, -15] First negative integer is -7.
Window [8, -15, 30] First negative integer is -15.
Window [-15, 30, 16] First negative integer is -15.
Window [30, 16, 28] No negative integers, output is 0.
```

```cpp
vector<int> firstNegInt(vector<int>& arr, int k) {
        // write code here
        vector<int> res(arr.size() - k + 1);
        int l = arr.size() - 1;
        
        int j = res.size() - 1;
        int prev = -1;
        
        /*Iterate from the last as we have to store the first negative */
        for (int i = l; i >= 0; i--) {
            /*store the last negative seen */
            if (arr[i] < 0)
                prev = i;

            /* if win sz k is hit store last neg and reduce windows from end */
            if (l - i + 1 == k) {

                /* store the res from the last in result vector*/
                if (prev > -1)
                    res[j] = arr[prev];
                else
                    res[j] = 0;
                
                /* check if last remove element is prev neg no then set it to -1 */
                if (prev == l)
                    prev = -1;

                /* go to next result location*/
                j--;
                
                l--;
            }
        }

        return res;
    }
```