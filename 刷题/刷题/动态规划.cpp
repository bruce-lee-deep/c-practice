//1.쳲�������
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
class Solution_1 {
public :
	int fib(int n) {
		vector<int>dp(n+1);
		if (n == 0) {
			return 0;
		}
		if (n == 1) {
			return 1;
		}
		dp[0] = 0;
		dp[1] = 1;
		int res=0;
		int i;
		for (i = 2; i <= n; i++) {
			dp[i] = dp[i - 1] + dp[i - 2];
		}
		return dp[i];
	}
};
//2.��¥��
class Solution_2 {
public:
	int climbStairs(int n) {
		vector<int>dp(n+1);//dp[i]��ʾ��i��̨�׵ķ�����dp[i]=dp[i-1]+dp[i-2]
		if (n == 1) return 1;
		if (n == 2) return 2;
		dp[1] = 1;
		dp[2] = 2;
		for (int i = 3; i <= n; i++) {
			dp[i] = dp[i - 1] + dp[i - 2];
		}
		return dp[n];
	}
};
//3.��ͬ·��
class Solution_3 {
public:
	int uniquePaths(int m, int n) {
		/*vector<vector<int>>dp(m, vector<int>(n));//�����άvector��dp[i][j]��ʾ����ʼ�㵽����Ϊ��i,j����·����
		//Ŀ������dp[m-1][n-1]
		//״̬ת�Ʒ��̣�dp[i][j]=dp[i-1][j]+dp[i][j-1]
		for (int i = 0; i < n; i++) {
			dp[0][i] = 1;//��һ��
		}
		for (int i = 0;  i< m; i++) {
			dp[i][0] = 1;//��һ��
		}
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			}
		}
		return dp[m - 1][n - 1];*/

		//ÿ�μ���ֻ�õ���ǰ�к���һ�����ݣ�ֻ��Ҫһά������һ�����ݼ���
		vector<int>dp(n, 1);//��һ��ȫ����1
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				dp[j] = dp[j] + dp[j - 1];//dp[j]��ʾ�õ���Ϸ���Ϊ��û���£���dp[j-1]�Ѿ����´���ľ���ǰ��ĵ�
			}
		}
		return dp[n-1];
	}
};
//4.��ͬ·��II
class Solution_4 {
public:
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		int m = obstacleGrid.size();
		int n = obstacleGrid[0].size();
		vector<vector<int>>dp(m,vector<int>(n));
		//���ȶ���ʼ�㸳ֵ
		if (obstacleGrid[0][0] == 1) {
			dp[0][0] = 0;
		}
		else {
			dp[0][0] = 1;
		}
		for (int i = 1; i < m; i++) {
			if (obstacleGrid[i][0] == 1) {
				dp[i][0] == 0;
			}else{
				dp[i][0] = dp[i - 1][0];
			}
		}
		for (int i = 1; i < n; i++) {
			if (obstacleGrid[0][i] == 1) {
				dp[0][i] == 0;
			}
			else {
				dp[0][i] = dp[0][i-1];
			}
		}
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				if (obstacleGrid[i][j] == 1) {
					dp[i][j] = 0;
				}
				else {
					dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
				}
			}
		}
		return dp[m- 1][n-1];
	}
};
//5.��С·����
class Solution_5{
public:
	int minPathSum(vector<vector<int>>& grid) {
		int m = grid.size();
		int n = grid[0].size();
		vector<vector<int>>dp(m, vector<int>(n));
		//״̬ת�Ʒ��̣�dp[i][j]=min(dp[i-1][j],dp[i][j-1])
		dp[0][0] = grid[0][0];
		//����һ�к͵�һ�и�ֵ
		for (int i = 1; i < m; i++) {
			dp[i][0] = grid[i][0] + dp[i - 1][0];
		}
		for (int i = 1; i < n; i++) {
			dp[0][i] = grid[0][i] + dp[0][i - 1];
		}
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				dp[i][j] =grid[i][j]+ min(dp[i - 1][j], dp[i][j - 1]);
			}
		}
		return dp[m - 1][n - 1];
	}
};

//6.�����������
class Solution_6 {
public:
	int lengthOfLIS(vector<int>& nums) {
		int size = nums.size();
		if (size == 0) {
			return 0;
		}
		vector<int>dp(size,1);//dp[i]��ʾ��nums[i]Ϊ��β������������У���ʼ����λ1
		int res = 0;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < i; j++) {
				if(nums[j]<nums[i]) dp[i] = max(dp[j] + 1, dp[i]);
			}
			res = max(res, dp[i]);
		}
		return res;
	}
};
//��̬�滮+���ֲ���
class Solution_6_1 {
public:
	int lengthOfLIS(vector<int>& nums) {
		vector<int>tails;//tails[i]��ʾ����Ϊi+1�ĵ��������е���Сβ��Ԫ��
		for (int num : nums) {
			//����tails�е�һ�����ڵ���num��Ԫ��λ��
			auto it = lower_bound(tails.begin(), tails.end(),num);
			if (it == tails.end()) {
				tails.push_back(num);
			}
			else {
				*it = num;
			}
		}
		return tails.size();
	}
};

//7.�˻�����������
class Solution_7{
public:
	int maxProduct(vector<int>& nums) {
		int len=nums.size();
		int res=INT_MIN;
		int maxP =1;
		int minP =1;
		for (int i = 0; i < len; i++) {
			if (nums[i] < 0) {
				int temp = maxP;
				maxP = minP;
				minP = temp;
			}
			maxP = max(maxP * nums[i], nums[i]);
			minP = min(maxP * nums[i], nums[i]);
			res = max(res, maxP);
		}
		return res;
	}
};

//8.���Ч����
class Solution_8{
public:
	int longestValidParentheses(string s) {
		int size = s.length();
		vector<int>dp(size, 0);
		int maxVal = 0;
		for (int i = 1; i < size; i++) {
			if (s[i] == ')') {
				if (s[i - 1] == '(') {
					dp[i] = 2;
					if (i - 2 >= 0) {
						dp[i] = dp[i] + dp[i - 2];
					}
				}
				else if (dp[i - 1] > 0) {
					if ((i - dp[i - 1] - 1) >= 0 && s[i - dp[i - 1] - 1] == '(') {
						dp[i] = dp[i - 1] + 2;
						if ((i - dp[i - 1] - 2 >= 0)) {
							dp[i] = dp[i] + dp[i - dp[i - 1] - 2];
						}
					}
				}
			}
			maxVal = max(maxVal, dp[i]);
		}
		return maxVal;
	}
};
//��ջʵ��
#include<stack>
#include<string>
class Solution_8_1 {
	int longestValidParentheses(string s) {
		stack<int>stk;
		//��ʼѹ��-1��Ϊ��׼��������㳤��
		stk.push(-1);
		int max_len = 0;

		for (int i = 0; i < s.length(); ++i) {
			if (s[i] == '(') {
				//��������ջ
				stk.push(i);
			}
			else {
				//�����ţ��ȵ���ջ��Ԫ��
				stk.pop();

				if (stk.empty()) {
					//ջΪ�գ�����ǰ������ջ��Ϊ�»�׼
					stk.push(i);
				}
				else {
					//���㵱ǰ��Ч���Ȳ��������ֵ
					max_len = max(max_len, i - stk.top());
				}
			}
		}
		return max_len;
	}
};
int main() {
	string s = "()(())";
	Solution_8 sol;
	int res=sol.longestValidParentheses(s);
	cout << res;
	return 0;
}