Problem description from LeetCode:

In this problem, a rooted tree is a directed graph such that, there is exactly one node (the root) for which all other nodes are descendants of this node, plus every node has exactly one parent, except for the root node which has no parents.
The given input is a directed graph that started as a rooted tree with n nodes (with distinct values from 1 to n), with one additional directed edge added. The added edge has two different vertices chosen from 1 to n, and was not an edge that already existed.
The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [ui, vi] that represents a directed edge connecting nodes ui and vi, where ui is a parent of child vi.
Return an edge that can be removed so that the resulting graph is a rooted tree of n nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array.

Example 1:
Input: edges = [[1,2],[1,3],[2,3]]
Output: [2,3]

Example 2:
Input: edges = [[1,2],[2,3],[3,4],[4,1],[1,5]]
Output: [4,1]

Constraints:
n == edges.length
3 <= n <= 1000
edges[i].length == 2
1 <= ui, vi <= n
ui != vi

My understanding:

There must be 1 closed loop formed by all or part of these edges.
The edge which closes the loop shall be the return.
All cases can be divided into 2 basic types:

Type0:
1/ All edges are in this close loop, and it it the easiest case.
2/ Return the second edge that shares the same son.

1 - >4
|    ^
v    | 
2 - >3

Type1:
1/ Some edges are not in the loop.
2/ The root node may or may not be in the loop.
3/ So it is ressonable to divide it into two types.

Type1A:
1/ Root node is not in the loop.
2/ Return the edge forming the loop and sharing the same son.

1
v
2 < 5
v   ^
3 > 4

Type1B:
1/ Root is in the loop.
2/ return the edge forming the loop.

1
^
2 < 5
v   ^
3 > 4

Solution:
1/ Find the 2 edges sharing the same son node: first and second.
2/ If first can't be found, return the edge forming the loop, it is type1B.
3/ Need to consider whether first or second should be returned.
4/ Cut second after finding first and second.

class Solution 
{
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) 
    {
        int n = edges.size(), i, x, y;
        vector<int> root(n + 1), first, second;
        
        for(auto &edge: edges)
        {
            if(0 == root[edge[1]])
            {
                root[edge[1]] = edge[0];
            }
            else
            {
                //remember the 2 edges that end in the same node
                first = {root[edge[1]], edge[1]};
                second = edge;
                edge[1] = 0;
            }
        }
        
        for(i = 0; i <= n; i ++)
        {
            root[i] = i;
        }
        
        for(auto &edge: edges)
        {
            //searching for a loop
            if(0 == edge[1])
            {
                continue;
            }
            
            x = helper(root, edge[0]);
            y = helper(root, edge[1]);
            
            if(x == y)
            {
                return first.empty() ? edge: first;
            }
            
            root[y] = x;
        }
        
        return second;
    }
    
    int helper(vector<int> &root, int i)
    {
        return (i == root[i]) ? i: helper(root, root[i]);
    }
};

Reference:
https://leetcode.com/problems/redundant-connection-ii/discuss/108058/one-pass-disjoint-set-solution-with-explain
https://leetcode.com/problems/redundant-connection-ii/discuss/108045/C++Java-Union-Find-with-explanation-O(n)
https://www.cnblogs.com/grandyang/p/8445733.html