#include<iostream>
using namespace std;
//使用递归实现对无权图的遍历
/*const int N = 5;
int adjMatrix[N][N] = {
	{0,1,1,0,1},
	{0,0,1,1,0},
	{0,0,0,0,1},
	{0,0,0,0,0},
	{0,0,0,0,0}
};
string name = "ABCDE";
bool isChecked[N] = { false };
void DFS(int v) {
	isChecked[v] = true;
	cout <<name[v]<<" ";
	for (int i = 0; i < N; i++) {
		if (adjMatrix[v][i] && !isChecked[i]) {
			DFS(i);
		}
	}
}
int main() {
	cout << "遍历结果为:";
	DFS(0);
	cout << endl;
	return 0;
}*/
//使用邻接表表示有权图
/*#include<vector>
const int N = 5;
vector<pair<int, int>>adjList[N];//pair<邻接点编号，权重>
string name[N]{ "北京","上海","广州","深圳","成都" };
int main() {
	//添加城市与城市之间的路径与距离
	adjList[0].push_back({ 1,100 });
	adjList[0].push_back({ 3,200 });
	adjList[0].push_back({ 4,700 });
	adjList[1].push_back({ 2,350 });
	adjList[1].push_back({ 3,600 });
	adjList[2].push_back({ 4,260 });
	//输出
	for (int i = 0; i < N; i++) {
		for (int j =0; j < N;j++) {
			bool found = false;
			if (i == j) {
				continue;
			}
			for (auto& edge : adjList[i]) {
				if (edge.first ==j) {
					cout << name[i] << "到" << name[j] << "的距离为" << edge.second << "千米" << endl;
				}
			}
			if (!found) {
				cout << name[i] << "到" << name[j] << "还没有高铁" << endl;
			}
		}
	}
	return 0;
}*/
//对有向图的广度优先搜索
/*#include<queue>
const int N = 8;
string name = "ABCDEFGH";
int adjMatrix[N][N] = {
	{0,1,1,0,0,1,0,0},
	{0,0,0,0,0,1,0,0},
	{0,1,0,1,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1},
	{0,1,1,0,1,0,0,0},
	{0,0,0,0,0,0,1,0}
};
void BFS(int start) {
	bool isVisited[N] = { false };
	queue<int>q;
	q.push(start);//把起始的点加入队列
	isVisited[start] = true;//将起始点标记为已访问
	while (!q.empty()) {//如果队列不为空（就是还没有遍历完所有的端点）就继续循环
		//删除队首
		int v = q.front();
		cout << name[v] << " ";
		q.pop();
		//搜索现在起始点的所有下一级并将其加在队列末尾
		for (int i = 0; i < N; i++) {
			if (adjMatrix[start][i] && !isVisited[i]) {//当存在路径且没有被访问过
				q.push(i);//加入队列后要标记为已访问
				isVisited[i] = true;
			}
		}
	}
}
int main() {
	BFS(0);
	return 0;
}*/

//普里姆算法求最小生成树
/*#include<iostream>
using namespace std;
const int N = 9;
const int INF = 1000;
int adjMatrix[N][N] = {
	{INF,10,INF,INF,INF,11,INF,INF,INF},
	{10,INF,18,INF,INF,INF,16,INF,12},
	{INF,18,INF,22,INF,INF,INF,INF,INF},
	{INF,INF,22,INF,INF,INF,24,16,21},
	{INF,INF,INF,INF,INF,26,INF,7,INF},
	{11,INF,INF,INF,26,INF,17,INF,INF},
	{INF,16,INF,24,INF,17,INF,19,INF},
	{INF,INF,INF,16,7,INF,19,INF,INF},
	{INF,12,INF,21,INF,INF,INF,INF,INF}
};
void prim() {
	path[0] = 0;
	isVisited[0] = true;
	for (int i = 0; i < N - 1; i++) {
		for (int k = 0; k <=i; k++) {
			for (int j = 0; j < N; j++) {
				if ((adjMatrix[path[k]][j] != INF) && !isVisited[j]) {
					if (minLength > adjMatrix[path[k]][j]) {
						minLength = adjMatrix[path[k]][j];
						path[i + 1] = j;
					}
				}
			}
		}
		isVisited[path[i + 1]] = true;
		sum += minLength;
		minLength = INF;
	}
	cout << "路径为：";
	for (int k = 0; k < N; k++) {
		cout << path[k];
	}
	cout << "总权重为：" << sum << endl;
}
void prim() {
	bool isVisited[N] = { false };
	int sum = 0;
	int lowcost[N];//记录每个未选顶点到已选集合的最小边权
	int parent[N];//记录最小生成树每个顶点的父节点
	//初始化
	for (int i = 0; i < N; i++) {
		lowcost[i] = adjMatrix[0][i];//以0为起点，每个未选顶点到0点的最小边权就是两点的权
		parent[i] = 0;
	}
	isVisited[0] = true;
	for (int i = 1; i < N; i++) {
		int min = INF, k = -1;
		for (int j = 0; j < N; j++) {
			if (!isVisited[j] && lowcost[j] < min) {
				min = lowcost[j];
				k = j;
			}
		}
		if (k == -1) {
			break;
		}
		isVisited[k] = true;
		sum += min;
		cout << "选中边：" << parent[k] << "-" << k << endl;
		for (int j = 0; j < N; j++) {
			if (!isVisited[j] && adjMatrix[k][j] < lowcost[j]) {
				lowcost[j] = adjMatrix[k][j];
				parent[j] = k;
			}
		}
	}
	cout << "最小生成树权重为：" << sum << endl;
}
int main() {
	prim();
	return 0;
}*/

//动态内存管理
/*#include<iostream>
using namespace std;
int main() {
	//简单赋值
	//int* p = (int*)malloc(5*sizeof(int));
	string* p = (string*)calloc(10, sizeof(char));//错误示范，string不能用calloc和malloc分配内存
	if (p == NULL) {
		cout << "内存分配失败" << endl;
		return 1;
	}
	for (int i = 0; i < 5; i++) {
		*(p + i) = (char)i;
	}
	for (int i = 0; i < 5; i++) {
		cout << *(p + i) << endl;
	}
	free(p);
	p = NULL;
	return 0;
}*/

/*#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int n=13, m=9;//边数和顶点数
struct Edge {
	int f, t, w;
};
bool cmp(Edge a,Edge b) {
	return a.w < b.w;
}
Edge edges[13] = {
	{0,1,10},
	{0,5,11},
	{1,2,18},
	{1,6,16},
	{1,8,12},
	{2,3,22},
	{3,6,24},
	{3,7,16},
	{3,8,21},
	{4,5,26},
	{4,7,7},
	{5,6,17},
	{6,7,19}
};
int parent[m];
int find(int x) {//查找根节点是否相同，相同则连通
	if (parent[x] != x) {
		parent[x] = find(parent[x]);//如果不是根节点就继续递归查找，直到找到根节点，根节点的特征是parent[x]=x
	}
	return parent[x];
}
//将两个根节点不同的指向一个相同的节点，就是将两个集合合并为一个集合
void unite(int x,int y) {
	parent[find(x)] = find(y);
}
void kruskal() {
	sort(edges, edges + n, cmp);
	for (int i = 0; i < m; i++) {//起始每个点的标记标记为自己
		parent[i] = i;
	}
	int sum=0;
	int cnt = 0;
	int pos1,pos2;
	for (int i = 0; i < n; i++) {
		pos1 = edges[i].f, pos2 = edges[i].t;
		if (find(pos1)!= find(pos2)){
			cout << "选中边" << pos1 << "->" << pos2 << endl;
			unite(pos1, pos2);
			sum += edges[i].w;
			cnt++;//记录已经走过的点的个数，因为是当所有的点都被访问过就结束，而不是所有的边都要被访问一次
		}
		if (cnt == m) {
			break;
		}
	}
	cout << "总权重为" << sum << endl;
}
int main() {
	kruskal();
	return 0;
}*/

//图转换成二叉树进行存储：孩子兄弟表示法
/*#include<iostream>
#include<queue>
using namespace std;
typedef int BTDataType;
typedef struct BinarytreeNode {
	BTDataType data;
	struct BinarytreeNode* left;
	struct BinarytreeNode* right;
}BTNode;
//初始化节点，舒适节点的指针都是空，所以抽象出一个函数，相当于一个构造函数
BTNode* BuyBTNode(BTDataType x) {
	BTNode* newnode = (BTNode*)malloc(sizeof(BTNode));
	if (newnode == NULL) {
		perror("malloc fail");
		return NULL;
	}
	newnode->data = x;
	newnode->left = NULL;
	newnode->right = NULL;
}
BTNode* CreatBTNode() {
	BTNode* node1 = BuyBTNode(1);
	BTNode* node2 = BuyBTNode(2);
	BTNode* node3 = BuyBTNode(3);
	BTNode* node4 = BuyBTNode(4);
	BTNode* node5 = BuyBTNode(5);
	BTNode* node6 = BuyBTNode(6);

	node1->left = node2;
	node1->right = node4;
	node2->left = node3;
	node4->left = node5;
	node4->right = node6;

	return node1;
}
//前序遍历
//根节点->左子树->右子树
class preorderTraversal {
public:
	void PreOrder(BinarytreeNode* root) {
		if (root == NULL) {
			return;
		}
		cout << root->data << " ";
		PreOrder(root->left);
		PreOrder(root->right);
	}
};
//中旬遍历
//左子树->跟节点->右子树
class inorderTraversal {
public:
	void InOrder(BinarytreeNode* root) {
		if (root == NULL) {
			return;
		}
		InOrder(root->left);
		cout << root->data << " ";
		InOrder(root->right);
	}
};
//后序遍历
//左子树->右子树->根节点
class postorderTraversal {
public:
	void PostOrder(BinarytreeNode* root) {
		if (root == NULL) {
			return;
		}
		PostOrder(root->left);
		PostOrder(root->right);
		cout << root->data << " ";
	}
};
//层序遍历
class levelorderTraversal {
public:
	void LevelOrder(BinarytreeNode* root) {
		if (root == NULL) {
			return;
		}
		queue< BinarytreeNode*>q;
		q.push(root);
		while (!q.empty()) {
			BinarytreeNode* node = q.front();
			q.pop();
			cout << node->data << " ";
			if (node->left) {
				q.push(node->left);
			}
			if (node->right) {
				q.push(node->right);
			}
		}
	}
};
int main() {
	class preorderTraversal sol1;
	class inorderTraversal sol2;
	class postorderTraversal sol3;
	class levelorderTraversal sol4;
	sol1.PreOrder(CreatBTNode());
	cout << endl;
	sol2.InOrder(CreatBTNode());
	cout << endl;
	sol3.PostOrder(CreatBTNode());
	cout << endl;
	sol4.LevelOrder(CreatBTNode());
	cout << endl;
	return 0;
}*/

//用二叉查找树储存数据   9 4 7 17 10 1 25 5
#include<iostream>
struct Node {
	int data;
	Node* left;
	Node* right;
};
Node* creatNode(int x) {
	Node* node=(Node*)malloc(sizeof(Node));
	node->data = x;
	node->left = NULL;
	node->right = NULL;
	return node;
}
Node* insert(Node* root,int x) {
	if (root == NULL) {
		return creatNode(x);
	}
	if (x < root->data) {
		root->left = insert(root->left, x);
	}
	else if (x > root->data) {
		root->right = insert(root->right, x);
	}
	return root;
}
int main() {
	int arr[] = { 9,4,7,17,10,1,25,5 };
	Node* root = NULL;
	for (int i = 0; i < 8; i++) {
		root = insert(root, arr[i]);
	}
	return 0;
}