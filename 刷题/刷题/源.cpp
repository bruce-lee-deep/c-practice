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

//���������֮��
/*class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        //�ж�����ĸ���
        int len = nums.size();
        if (nums.size() == 1) {
            return nums[0];
        }
        //������dp[i]��ʾ��nums[i]��β������������
        //vector<int>dp(len);
        //dp[0] = nums[0];
        //�������ÿһ�����ֽ�βʱ���������ĺ�
        //�Կռ��Ż�
        int pre = 0;//������¼��ǰ��ֵ������һ����dp[i]һ�߸������ֵ
        int res=nums[0];
        for (int num : nums) {
            pre = max(num, pre + num);
            res = max(res, pre);//��ǰ���ֵ�͵�ǰֵ�Ƚ�
        }
        return res;
    }
};
//�����ⷨ������
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int res = INT_MIN;//�Ƚ�������ó������ϵ���Сֵ
        int size = nums.size();
        for (int i = 0; i < size; i++) {
            //���ѭ�������������ǰ��
            int sum = 0;
            for (int j = i; j < size; j++) {
                //��ѭ������������ĺ��
                sum+= nums[j];
                res = max(res, sum);
            }
            sum = 0;
        }
        return res;
    }
};
//̰���㷨���ռ�O��1��,ʱ��O��n��
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int res = INT_MIN;
        int size = nums.size();
        int sum = 0;
        for (int i = 0; i < size; i++) {
            sum += nums[i];
            res = max(res, sum);
            if (sum < 0) {//���ֲ�֮��С��0ʱ����Ҫ����Ѱ���Ӵ��ˣ����ڵ�res���ǵ�ǰѰ�ҵ��Ӵ������ֵ
                sum = 0;
            }
        }
        return res;
    }
};*/