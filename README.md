# Code_snippets
- [Binary Search Problems](coding_problems/binary_search/readme.md)
- [Sliding Window Problems](coding_problems/sliding_window/readme.md)
- [Stack Problems](coding_problems/stack/readme.md)
- [Heap Problems](coding_problems/heap/readme.md)
- [Recursion Problems](coding_problems/recursion/readme.md)
- [Backtracking Problems](coding_problems/backtracking/readme.md)
- [Tree Problems](trees/readme.md)
- [Math And Geometry Porblems](coding_problems/math_geometry/readme.md)
- [Bit Hacks](bits_hacks/readme.md)

# Contents
- [Tips](#tips)
- [STL Usage](#stl-usage)
  - [Priority Queues](#priority-queue)
  - [Vectors](#vectors)

* __Substring__ -> set should be continuous
* __Subsequence__ -> Should be in order not need to be continuous
* __Subset__ -> all posible combinations 

## Tips
- When trying to apply a greedy approch always try to find a counter example

## Count Number of Digits
```python
def number_of_digits(x):
  count = 0
  while (x > 0):
    x = x // 10
    count+=1
  return count
```

## count consecutive onse
```python
def findMaxConsecutiveOnes(self, nums: List[int]) -> int:
        gcount = 0
        count = 0
        for x in nums:
            if x == 1:
                count +=1
                if count > gcount:
                    gcount = count
            elif x == 0:
                
                count = 0
            else:
                pass
        return gcount
```
## 561. Array Partition

make n pairs (a1, b1), (a2, b2), ..., (an, bn) such that the sum of min(ai, bi) for all i is maximized. Return the maximized sum.
```cpp
int sum=0;
        sort(nums.begin(),nums.end());
        for(int i=0; i<nums.size(); i++){
            if(i%2=0){
                sum=sum+nums[i];
            }
        }
        return sum;
```

##  2553. Separate the Digits in an Array.eg 12,33==1,2,3,3

```cpp
 vector<int> separateDigits(vector<int>& nums) {
        vector<int> answer;
        int n= nums.size();
        for(int i=0; i<n; i++){
            vector<int> temp;

            while(nums[i]>0){
                temp.push_back(nums[i]%10);
                nums[i]=nums[i]/10;
            }
            reverse(temp.begin(),temp.end());
            for(int x=0;x<temp.size();x++){
            answer.push_back(temp[x]);
            }
        }
        
        return answer;
    }
```

## linklist traverse
```cpp
  ListNode* temp = head;
        while(temp!= NULL){
            cout<<temp->val<<" ";
            temp= temp->next;
        }
 ```
## array to integer number basic
```cpp
int array_to_int(vector<int> v, int rflag) {
    int val = 0;
    
    if (rflag) {
        /* generating number in reverse*/
        for (int i = v.size() - 1; i >= 0; i--) {
            val = val *10 + v[i];
        }
        
    }else {
        /* generating number */
        for (int i = 0; i < v.size(); i++) {
            val = val *10 + v[i];
        }
    }
    return val;
}

int main() {
    std::cout << "Hello World!\n";
    int key = 1234;
    int tmp = key;
    int d = 0;
    int rkey = 0;
    
    while(tmp) {
        /*number to digits*/
        d =  tmp %10;
        tmp /= 10;
        
        /*digits to number*/
        rkey = rkey* 10 + d;
    }
    
    std::cout<< key <<" " << rkey<<std::endl;
    
    std::vector<int> v = {1, 2, 3, 4};
    
    std::cout<<"normal int : "<< array_to_int(v, 0) <<std::endl;
    std::cout<<"reverse int : "<< array_to_int(v, 1) <<std::endl;
    
}
```

## character count using array
```cpp
string data = "hello world how are you";
    vector<int> letter_count(26, 0);
    
    for(int i = 0; i < data.size(); i++) {
        if(data[i] == ' ') continue;
        int index = data[i] - 97;
    
        letter_count[index] = letter_count[index] + 1;   
    }
    
    for(int i = 0; i < data.size(); i++) {
       cout << letter_count[i] <<endl;
    }    
```
## character count using hash_table
```cpp
unordered_map<char, int> hash_map;
    for(int i = 0; i < data.size(); i++) {
        if(data[i] == ' ') continue;
        hash_map[data[i]]  = hash_map[data[i]] + 1; 
    }
    
    for (auto i: hash_map)
        cout << i.first << ":" << i.second <<endl;
```
## create a compartor without function
```cpp
struct
{
  bool operator()(int a, int b) const { return a < b; }
}customless;

sort(a.begin(), a.end(), customless);
```
## search element in 2d array function
```cpp
bool search(int arr[][3], int target){
      for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(arr[i][j] == target)
            return 1;
        }
    }  
    return 0;
}
```
## find sum of row in 2d array function
```cpp
void sumrowwise(int arr[][3]){
      
      for(int i=0; i<3; i++){
        int sum=0;
        for(int j=0; j<3; j++){
            sum += arr[i][j];
        }
        cout<<sum<<" ";
    }
    cout<<endl;
}

```
## find sum of col in 2d array function
```cpp
void sumcolwise(int arr[][3]){
      
      for(int i=0; i<3; i++){
        int sum=0;
        for(int j=0; j<3; j++){
            sum += arr[j][i];
        }
        cout<<sum<<" ";
    }
    cout<<endl;
}
```
## find max row sum and index of row in 2d array function
```cpp
int largestrowsum(int arr[][3]){
     int max = INT_MIN;
     int rowindex=-1;
     for(int i=0; i<3; i++){
        int sum=0;
        for(int j=0; j<3; j++){
            sum += arr[i][j];
        }
        if(sum > max){
            max = sum;
            rowindex = i;
        }
    }
    cout<< "rowindex of row having maximum sum is" << rowindex<<endl;;
    return max;
}
```
## find max col sum and index of col in 2d array function
```cpp
int largestcolsum(int arr[][3]){
     int max = INT_MIN;
     int colindex=-1;
     for(int i=0; i<3; i++){
        int sum=0;
        for(int j=0; j<3; j++){
            sum += arr[j][i];
        }
        if(sum > max){
            max = sum;
            colindex = i;
        }
    }
    cout<< "rowindex of col having maximum sum is" << colindex<<endl;;
    return max;
}
```
## STL usage
1. ### Priority Queue
```cpp

priority_queue<T, Conatiner, Comparator> pq;

Params:
T	-	The type of the stored elements.  
Container	-	The type of the underlying container to use to store the elements.
Compare	-	A Compare type providing a strict weak ordering.
eg 
priority_queue<int, vector<int>, greater<int>> pq;

APIS:
front()
push_back()
pop_back()

```
2. ### Vectors  
  * Initializations:
  ```cpp
  vector<T> v1; => default initialization, v1 is empty;
  
  vector<T> v2(v1); => v2 has copy of each element of v1;
  
  vector<T> v2 = v1; => Equivalemnt of v2(v1);
  
  vector<T> v3(n,val); => v3 has n elements with value val;
  
  vector<T> v4(n); => v4 has n copies of vale-initialied object;
  
  vector<T> v5{a,b,c}; => definig;
  
  vector<T> v5 = {a,b,c}; => same as above;
  ```
  Initializing 2d vectors
  ```cpp
  vector<vector<int>> table<ROWS_COUNT, vector<int>(COLS_COUNT)>;
  
  vector<vector<int>> table<ROWS_COUNT, vector<int>(COLS_COUNT, val)>;
  ```


