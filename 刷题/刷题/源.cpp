#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<algorithm>
using namespace std;
/*class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<vector<string>>& strs) {
        vector<vector<string>>finalGroup;
        int x = 0;
        for (int i = 0; i < strs.size();i++) {
            finalGroup[x].push_back(strs[i]);
            for (int j = i + 1; j = strs.size(); j++) {
                if (compare(strs[i], strs[j])) {
                    finalGroup[x].push_back(" " + strs[j]);
                    strs[j].clear();
                }
            }
            x++;
        }
        return finalGroup;
    }
    bool compare(string s1, string s2) {
        if (s1.length() != s2.length()) {
            return false;
        }
        else {
            for (int i = 0; i < s1.length(); i++) {
                if (s2.find(s1) == string::npos) {
                    return false;
                }
            }
            return false;
        }
    }
};
int main() {
    Solution sol;
    vector<vector<string>>strs = { {"eat"},{"tea"},{"tan"},{"ate"},{"nat"},{"bat"} };
    sol.groupAnagrams(strs);
}*/


/*class Solution {
public:
    vector<vector<string>>groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>>m;
        for (string& s : strs) {
            string sorted_s = s;
            sort(sorted_s.begin(),sorted_s.end());
            m[sorted_s].push_back(s);
        }
        vector<vector<string>>ans;
        ans.reserve(m.size());
        for (auto&kv: m) {
            ans.push_back(kv.second);
        }
        return ans;
    }
};*/

//最大子数组之和
/*class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        //判断数组的个数
        int len = nums.size();
        if (nums.size() == 1) {
            return nums[0];
        }
        //子问题dp[i]表示以nums[i]结尾的最大子数组和
        //vector<int>dp(len);
        //dp[0] = nums[0];
        //计算出以每一个数字结尾时最大子数组的和
        //对空间优化
        int pre = 0;//用来记录当前的值，用于一边求dp[i]一边更新最大值
        int res=nums[0];
        for (int num : nums) {
            pre = max(num, pre + num);
            res = max(res, pre);//当前最大值和当前值比较
        }
        return res;
    }
};
//暴力解法：遍历
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int res = INT_MIN;//先将结果设置成理论上的最小值
        int size = nums.size();
        for (int i = 0; i < size; i++) {
            //外层循环控制子数组的前端
            int sum = 0;
            for (int j = i; j < size; j++) {
                //内循环控制子数组的后端
                sum+= nums[j];
                res = max(res, sum);
            }
            sum = 0;
        }
        return res;
    }
};
//贪心算法：空间O（1）,时间O（n）
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int res = INT_MIN;
        int size = nums.size();
        int sum = 0;
        for (int i = 0; i < size; i++) {
            sum += nums[i];
            res = max(res, sum);
            if (sum < 0) {//当局部之和小于0时，就要重新寻找子串了，现在的res就是当前寻找的子串的最大值
                sum = 0;
            }
        }
        return res;
    }
};*/