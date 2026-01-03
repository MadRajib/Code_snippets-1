# Interval Problems

1. [Meeting Rooms](#meeting-rooms)
1. [Insert Interval](#insert-interval)
1. [Non-overlapping Intervals](#non-overlapping-intervals)
1. [Meeting Rooms II](#meeting-rooms-ii)

### Meeting Rooms

> Given an array of meeting time interval objects consisting of start and end times [[start_1,end_1],[start_2,end_2],...] (start_i < end_i), determine if a person could add all meetings to their schedule without any conflicts.

Note: (0,8),(8,10) is not considered a conflict at 8
```bash
Example 1:

Input: intervals = [(0,30),(5,10),(15,20)]

Output: false
Explanation:

(0,30) and (5,10) will conflict
(0,30) and (15,20) will conflict
Example 2:

Input: intervals = [(5,8),(9,15)]

Output: true
```

```cpp
class Solution {
public:
    bool canAttendMeetings(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), [](auto& x, auto& y) {
            return x.start < y.start;
        });
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i].start < intervals[i - 1].end) {
                return false;
            }
        }
        return true;
    }
};

```

### 

### Insert Interval
> You are given an array of non-overlapping intervals intervals where intervals[i] = [start_i, end_i] represents the start and the end time of the ith interval. intervals is initially sorted in ascending order by start_i.

You are given another interval newInterval = [start, end].

Insert newInterval into intervals such that intervals is still sorted in ascending order by start_i and also intervals still does not have any overlapping intervals. You may merge the overlapping intervals if needed.

Return intervals after adding newInterval.

Note: Intervals are non-overlapping if they have no common point. For example, [1,2] and [3,4] are non-overlapping, but [1,2] and [2,3] are overlapping.

```bash
Example 1:
Input: intervals = [[1,3],[4,6]], newInterval = [2,5]

Output: [[1,6]]

Example 2:
Input: intervals = [[1,2],[3,5],[9,10]], newInterval = [6,7]

Output: [[1,2],[3,5],[6,7],[9,10]]
```


Apporach:
1. If n->e < c->s ; push(n); push(c); ret;
2. if n->s > c->e ; push(c); check for next interval, since it can overlap with upcoming intervals
3. else: i.e the n overlapped with c: build a new interval
    - n->s = min(n->s, c->s)
    - n->e = max(n->e, c->e)
    - dont push, check further overlap
4. append the n and return the result

```cpp
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> res;
        int newStart = newInterval[0];
        int newEnd = newInterval[1];
        int n = intervals.size();
        for (int i = 0; i < n; i++) {
            if (intervals[i][0] > newEnd) {
                res.push_back(newInterval);
                copy(intervals.begin() + i, intervals.end(), back_inserter(res));
                return res;
            } else if (intervals[i][1] < newStart) {
                res.push_back(intervals[i]);
            } else {
                newInterval[0] = min(newInterval[0], intervals[i][0]);
                newInterval[1] = max(newInterval[1], intervals[i][1]);
            }
        }
        res.push_back(newInterval);
        return res;
    }
};

```

### Non-overlapping Intervals
> Given an array of intervals intervals where intervals[i] = [start_i, end_i], return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

Note: Intervals are non-overlapping even if they have a common point. For example, [1, 3] and [2, 4] are overlapping, but [1, 2] and [2, 3] are non-overlapping.

```bash
Example 1:

Input: intervals = [[1,2],[2,4],[1,4]]

Output: 1
Explanation: After [1,4] is removed, the rest of the intervals are non-overlapping.

Example 2:

Input: intervals = [[1,2],[2,4]]

Output: 0
```

Apporach:
- We want to remove the minimum number of intervals so that the remaining intervals do not overlap.

- A greedy strategy works well here. After sorting intervals by their start time, we process them from left to right and always keep the interval that ends earlier when an overlap occurs.

Why this works:

- When two intervals overlap, keeping the one with the smaller end time leaves more room for future intervals
- Removing the interval with the larger end is always a worse choice, because it blocks more upcoming intervals
- So instead of choosing which interval to keep globally, we make a local greedy decision whenever an overlap happens.

```cpp
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        int res = 0;
        int prevEnd = intervals[0][1];

        for (int i = 1; i < intervals.size(); i++) {
            int start = intervals[i][0];
            int end = intervals[i][1];
            if (start >= prevEnd) {
                prevEnd = end;
            } else {
                res++;
                prevEnd = min(end, prevEnd);
            }
        }
        return res;
    }
};
```

### Meeting Rooms II
> Given an array of meeting time interval objects consisting of start and end times [[start_1,end_1],[start_2,end_2],...] (start_i < end_i), find the minimum number of days required to schedule all meetings without any conflicts.

Note: (0,8),(8,10) is not considered a conflict at 8.

```bash
Example 1:

Input: intervals = [(0,40),(5,10),(15,20)]

Output: 2
Explanation:
day1: (0,40)
day2: (5,10),(15,20)

Example 2:

Input: intervals = [(4,9)]

Output: 1
```

Apporach:
- One way is to use min heap, so that earliest meeting end can be tracked.
- Another is Greedy apporach: to use condifter start and end as events.

Heap:

We want to find the minimum number of meeting rooms required so that no meetings overlap.

A useful way to think about this is:

- each meeting needs a room from its start time to its end time
- if a meeting starts after or at the same time another meeting ends, they can share the same room
otherwise, we need a new room
- To efficiently track room availability, we use a min heap:

- the heap stores the end times of meetings currently occupying rooms
- the smallest end time is always at the top, representing the room that frees up the earliest
- As we process meetings in order of start time:

- if the earliest-ending meeting finishes before the current one starts, we can reuse that room
otherwise, we must allocate a new room

- The maximum size the heap reaches is the number of rooms needed.
```cpp
class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
            return a.start < b.start;
        });
        priority_queue<int, vector<int>, greater<int>> minHeap;
        for (const auto& interval : intervals) {
            if (!minHeap.empty() && minHeap.top() <= interval.start) {
                minHeap.pop();
            }
            minHeap.push(interval.end);
        }
        return minHeap.size();
    }
};
```

Greedy Apporach Events

Instead of thinking in terms of rooms directly, we can think in terms of events on a timeline:

- when a meeting starts, we need one more room
- when a meeting ends, one room is freed

So the problem reduces to:
- What is the maximum number of meetings happening at the same time?
- If we track how the number of active meetings changes over time, the maximum value we ever reach is exactly the number of rooms we need.

This greedy approach works by:

- converting each meeting into two events (start and end)
- sorting all events by time
- sweeping from left to right while counting active meetings
```cpp
class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        vector<pair<int, int>> time;
        for (const auto& i : intervals) {
            time.push_back({i.start, 1});
            time.push_back({i.end, -1});
        }

        sort(time.begin(), time.end(), [](auto& a, auto& b) {
            return a.first == b.first ? a.second < b.second : a.first < b.first;
        });

        int res = 0, count = 0;
        for (const auto& t : time) {
            count += t.second;
            res = max(res, count);
        }
        return res;
    }
};
```