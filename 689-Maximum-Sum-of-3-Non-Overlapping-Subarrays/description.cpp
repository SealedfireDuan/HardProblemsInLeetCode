/**
Given an integer array nums and an integer k, find three non-overlapping subarrays of length k with maximum sum and return them.

Return the result as a list of indices representing the starting position of each interval (0-indexed). If there are multiple answers, return the lexicographically smallest one.

 

Example 1:

Input: nums = [1,2,1,2,6,7,5,1], k = 2
Output: [0,3,5]
Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.
Example 2:

Input: nums = [1,2,1,2,1,2,1,2,1], k = 2
Output: [0,2,4]
 

Constraints:

1 <= nums.length <= 2 * 104
1 <= nums[i] < 216
1 <= k <= floor(nums.length / 3)

Thoughts:
1/ For each starting position of the middle array, the starting postition of the left and right arrays, to get the local max, must be known before.
2/ So DP can be used, lp[n] and rp[n] store the starting positions of local max, lp[i] refers to sums[0] to sum[i], rp[i] sums[i], sum[n - 1].
3/ To get lp, it should be from left to right, right to left for rp.

References:
https://www.cnblogs.com/grandyang/p/8453386.html
https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/discuss/108231/C++Java-DP-with-explanation-O(n)
https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/discuss/108246/C++-O(n)-time-O(n)-space-concise-solution
https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/discuss/108230/Clean-Java-DP-O(n)-Solution.-Easy-extend-to-Sum-of-K-Non-Overlapping-SubArrays
*/
class Solution 
{
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) 
    {
        int i = 0, total = 0, mx = 0, left = 0, right = 0, n = nums.size();
        vector<int> lp(n, 0), rp(n, n - k), sum(n + 1, 0), ans;
        
        for(i = 0; i < n; i ++)
        {
            sum[i + 1] = sum[i] + nums[i];
        }
        
        for(i = k, total = sum[k] - sum[0]; i < n; i ++)
        {
            if(sum[i + 1] - sum[i + 1 - k] > total)
            {
                total = sum[i + 1] - sum[i + 1 - k];
                lp[i] = i + 1 - k;
            }
            else
            {
                lp[i] = lp[i - 1];
            }
        }
        
        for(i = n - 1 - k, total = sum[n] - sum[n - k]; i >= 0; i --)
        {
            if(sum[i + k] - sum[i] >= total)
            {
                total = sum[i + k] - sum[i];
                rp[i] = i;
            }
            else
            {
                rp[i] = rp[i + 1];
            }
        }
        
        for(i = k; i <= n - 2 * k; i ++)
        {
            left = lp[i - 1];
            right = rp[i + k];
            total = sum[left + k] - sum[left] + sum[right + k] - sum[right] + sum[i + k] - sum[i];
            
            if(total > mx)
            {
                mx = total;
                ans = {left, i, right};
            }
        }
        
        return ans;
    }
};
