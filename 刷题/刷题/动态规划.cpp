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
class Solution {
public:
	int maxProduct(vector<int>& nums) {
		int len=nums.size();
		int res=nums[0];
		int maxP = nums[0];
		int minP = nums[0];
		for (int i = 1; i < len; i++) {
			maxP = max(maxP * nums[i], maxP);
			minP = min(maxP * nums[i], maxP);
			res = max(res, maxP);
		}
		return res;
	}
};



int main() {
	vector<int>nums = {10,9,2,5,3,7,101,18};
	Solution_6 sol;
	int res=sol.lengthOfLIS(nums);
	cout << res;
	return 0;
}