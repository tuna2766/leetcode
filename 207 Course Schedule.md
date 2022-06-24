# 207. Course Schedule

There are a total of `numCourses` courses you have to take, labeled from `0` to `numCourses - 1`. You are given an array `prerequisites` where `prerequisites[i] = [ai, bi]` indicates that you **must** take course `bi` first if you want to take course `ai`.

- For example, the pair `[0, 1]`, indicates that to take course `0` you have to first take course `1`.

Return `true` if you can finish all courses. Otherwise, return `false`.

**Example 1:**

```
Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take.
To take course 1 you should have finished course 0. So it is possible.

```

**Example 2:**

```
Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take.
To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.

```

**Constraints:**

- `1 <= numCourses <= 2000`
- `0 <= prerequisites.length <= 5000`
- `prerequisites[i].length == 2`
- `0 <= ai, bi < numCourses`
- All the pairs prerequisites[i] are **unique**.

Using ****Topological Sort :****

```cpp
/*
Runtime: 19 ms, faster than 94.85% of C++ online submissions for Course Schedule.
Memory Usage: 13.3 MB, less than 81.46% of C++ online submissions for Course Schedule.
*/
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> G(numCourses);
        vector<int> indegree(numCourses, 0);
        for(const auto& prerequisite : prerequisites) {
            G[prerequisite[1]].push_back(prerequisite[0]);
            indegree[prerequisite[0]]++;
        }
        
        queue<int> q;
        for(int i = 0; i < numCourses; ++i) 
            if(indegree[i] == 0) q.push(i);
         
        int res = 0;
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            res++;
            
            for(const auto& n : G[node]) {
                indegree[n]--;
                if(indegree[n] == 0) q.push(n);
            }
        }
        if(res == numCourses) return true;
        return false;    
    }
};
```

```cpp
/*
Brute force method.
*/
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        if(prerequisites.size() == 0) return true;
        
        vector<int> locks(numCourses, 0);
        for(const auto& prerequisites : prerequisites) {
            locks[prerequisites[0]]++;
        }
        
        int last = prerequisites.size() - 1;
        while(prerequisites.size() > 0) {
            if(locks[prerequisites[last][1]] == 0) {
                locks[prerequisites[last][0]]--;
                prerequisites.erase(prerequisites.begin() + last);
                last = prerequisites.size() - 1;
            }else {
                last--;
            }
            if(last < 0) break;
        }
        
        int res = true;
        for(const auto& lock : locks) {
            if(lock > 0) {
                res = false;
                break;
            }
        }
        return res;
    }
};
```

> What is ****Topological Sort**** :
> 
- [https://web.ntnu.edu.tw/~algo/DirectedAcyclicGraph.html](https://web.ntnu.edu.tw/~algo/DirectedAcyclicGraph.html)