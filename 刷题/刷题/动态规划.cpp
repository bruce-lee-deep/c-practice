//1.斐波那契数
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
//2.爬楼梯
class Solution_2 {
public:
	int climbStairs(int n) {
		vector<int>dp(n+1);//dp[i]表示爬i个台阶的方法，dp[i]=dp[i-1]+dp[i-2]
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
//3.不同路径
class Solution_3 {
public:
	int uniquePaths(int m, int n) {
		/*vector<vector<int>>dp(m, vector<int>(n));//定义二维vector，dp[i][j]表示从起始点到坐标为（i,j）的路径数
		//目标是求dp[m-1][n-1]
		//状态转移方程：dp[i][j]=dp[i-1][j]+dp[i][j-1]
		for (int i = 0; i < n; i++) {
			dp[0][i] = 1;//第一行
		}
		for (int i = 0;  i< m; i++) {
			dp[i][0] = 1;//第一列
		}
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			}
		}
		return dp[m - 1][n - 1];*/

		//每次计算只用到当前行和上一行数据，只需要一维保存上一行数据即可
		vector<int>dp(n, 1);//第一行全部是1
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				dp[j] = dp[j] + dp[j - 1];//dp[j]表示该点的上方因为还没更新，而dp[j-1]已经更新代表的就是前面的点
			}
		}
		return dp[n-1];
	}
};
//4.不同路径II
class Solution_4 {
public:
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		int m = obstacleGrid.size();
		int n = obstacleGrid[0].size();
		vector<vector<int>>dp(m,vector<int>(n));
		//首先对起始点赋值
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
//5.最小路径和
class Solution_5{
public:
	int minPathSum(vector<vector<int>>& grid) {
		int m = grid.size();
		int n = grid[0].size();
		vector<vector<int>>dp(m, vector<int>(n));
		//状态转移方程：dp[i][j]=min(dp[i-1][j],dp[i][j-1])
		dp[0][0] = grid[0][0];
		//给第一行和第一列赋值
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

//6.最长递增子序列
class Solution_6 {
public:
	int lengthOfLIS(vector<int>& nums) {
		int size = nums.size();
		if (size == 0) {
			return 0;
		}
		vector<int>dp(size,1);//dp[i]表示以nums[i]为结尾的最长递增子序列，初始都置位1
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
//动态规划+二分查找
class Solution_6_1 {
public:
	int lengthOfLIS(vector<int>& nums) {
		vector<int>tails;//tails[i]表示长度为i+1的递增子序列的最小尾部元素
		for (int num : nums) {
			//查找tails中第一个大于等于num的元素位置
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

//7.乘积最大的子数组
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

//8.最长有效括号
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
//用栈实现
#include<stack>
#include<string>
class Solution_8_1 {
	int longestValidParentheses(string s) {
		stack<int>stk;
		//初始压入-1作为基准，方便计算长度
		stk.push(-1);
		int max_len = 0;

		for (int i = 0; i < s.length(); ++i) {
			if (s[i] == '(') {
				//左括号入栈
				stk.push(i);
			}
			else {
				//右括号，先弹出栈顶元素
				stk.pop();

				if (stk.empty()) {
					//栈为空，将当前索引入栈作为新基准
					stk.push(i);
				}
				else {
					//计算当前有效长度并更新最大值
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