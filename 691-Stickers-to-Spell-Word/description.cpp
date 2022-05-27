/**
We are given n different types of stickers. Each sticker has a lowercase English word on it.

You would like to spell out the given string target by cutting individual letters from your collection of stickers and rearranging them. You can use each sticker more than once if you want, and you have infinite quantities of each sticker.

Return the minimum number of stickers that you need to spell out target. If the task is impossible, return -1.

Note: In all test cases, all words were chosen randomly from the 1000 most common US English words, and target was chosen as a concatenation of two random words.

 

Example 1:

Input: stickers = ["with","example","science"], target = "thehat"
Output: 3
Explanation:
We can use 2 "with" stickers, and 1 "example" sticker.
After cutting and rearrange the letters of those stickers, we can form the target "thehat".
Also, this is the minimum number of stickers necessary to form the target string.
Example 2:

Input: stickers = ["notice","possible"], target = "basicbasic"
Output: -1
Explanation:
We cannot form the target "basicbasic" from cutting letters from the given stickers.

Constraints:

n == stickers.length
1 <= n <= 50
1 <= stickers[i].length <= 10
1 <= target.length <= 15
stickers[i] and target consist of lowercase English letters.

Thoughts:
1/ Suppose the target string is m letters long, so it has 2^m sub-collection of letters, depending on each letter is present or not.
2/ Use a bit-field curr to represent the current sub-collection
3/ Each letter found in each sticker, if can fill in the curr's bit which is 0, can form another sub-collection.
4/ The total target corresponds to sub-collection[2^m - 1], can be calculated by going through all above.

References:
https://www.cnblogs.com/grandyang/p/8468045.html
https://leetcode.com/problems/stickers-to-spell-word/discuss/108333/Rewrite-of-contest-winner's-solution
https://leetcode.com/problems/stickers-to-spell-word/discuss/108318/C++JavaPython-DP-+-Memoization-with-optimization-29-ms-(C++)
https://leetcode.com/problems/stickers-to-spell-word/discuss/108334/Explaining-StefanPochmann's-Rewrite-of-contest-winner's-solution-and-+java
*/
class Solution 
{
public:
    int minStickers(vector<string>& stickers, string target) 
    {
        int m = target.size(), n = (1 << m), i = 0, j = 0, curr = 0;
        vector<int> dp(n, INT_MAX);
        
        dp[0] = 0;
        
        for(i = 0; i < n; i ++)
        {
            if(INT_MAX == dp[i])
            {
                continue; //This collection can not be formed by all the stickers, so no need to care about.
            }
            
            for(string &str: stickers)
            {
                curr = i;
                
                for(char &c: str)
                {
                    for(j = 0; j < m; j ++)
                    {
                        if(c == target[j] && 0 == ((curr >> j) & 1))
                        {
                            curr |= (1 << j);
                            
                            break;
                        }
                    }
                }
                
                dp[curr] = min(dp[curr], dp[i] + 1);
            }
        }
        
        return INT_MAX == dp[n - 1]? -1: dp[n - 1];
    }
};
