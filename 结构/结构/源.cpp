#include<iostream>
using namespace std;
//ʹ�õݹ�ʵ�ֶ���Ȩͼ�ı���
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
	cout << "�������Ϊ:";
	DFS(0);
	cout << endl;
	return 0;
}*/
//ʹ���ڽӱ��ʾ��Ȩͼ
/*#include<vector>
const int N = 5;
vector<pair<int, int>>adjList[N];//pair<�ڽӵ��ţ�Ȩ��>
string name[N]{ "����","�Ϻ�","����","����","�ɶ�" };
int main() {
	//��ӳ��������֮���·�������
	adjList[0].push_back({ 1,100 });
	adjList[0].push_back({ 3,200 });
	adjList[0].push_back({ 4,700 });
	adjList[1].push_back({ 2,350 });
	adjList[1].push_back({ 3,600 });
	adjList[2].push_back({ 4,260 });
	//���
	for (int i = 0; i < N; i++) {
		for (int j =0; j < N;j++) {
			bool found = false;
			if (i == j) {
				continue;
			}
			for (auto& edge : adjList[i]) {
				if (edge.first ==j) {
					cout << name[i] << "��" << name[j] << "�ľ���Ϊ" << edge.second << "ǧ��" << endl;
				}
			}
			if (!found) {
				cout << name[i] << "��" << name[j] << "��û�и���" << endl;
			}
		}
	}
	return 0;
}*/
//������ͼ�Ĺ����������
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
	q.push(start);//����ʼ�ĵ�������
	isVisited[start] = true;//����ʼ����Ϊ�ѷ���
	while (!q.empty()) {//������в�Ϊ�գ����ǻ�û�б��������еĶ˵㣩�ͼ���ѭ��
		//ɾ������
		int v = q.front();
		cout << name[v] << " ";
		q.pop();
		//����������ʼ���������һ����������ڶ���ĩβ
		for (int i = 0; i < N; i++) {
			if (adjMatrix[start][i] && !isVisited[i]) {//������·����û�б����ʹ�
				q.push(i);//������к�Ҫ���Ϊ�ѷ���
				isVisited[i] = true;
			}
		}
	}
}
int main() {
	BFS(0);
	return 0;
}*/

//����ķ�㷨����С������
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
	cout << "·��Ϊ��";
	for (int k = 0; k < N; k++) {
		cout << path[k];
	}
	cout << "��Ȩ��Ϊ��" << sum << endl;
}
void prim() {
	bool isVisited[N] = { false };
	int sum = 0;
	int lowcost[N];//��¼ÿ��δѡ���㵽��ѡ���ϵ���С��Ȩ
	int parent[N];//��¼��С������ÿ������ĸ��ڵ�
	//��ʼ��
	for (int i = 0; i < N; i++) {
		lowcost[i] = adjMatrix[0][i];//��0Ϊ��㣬ÿ��δѡ���㵽0�����С��Ȩ���������Ȩ
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
		cout << "ѡ�бߣ�" << parent[k] << "-" << k << endl;
		for (int j = 0; j < N; j++) {
			if (!isVisited[j] && adjMatrix[k][j] < lowcost[j]) {
				lowcost[j] = adjMatrix[k][j];
				parent[j] = k;
			}
		}
	}
	cout << "��С������Ȩ��Ϊ��" << sum << endl;
}
int main() {
	prim();
	return 0;
}*/

//��̬�ڴ����
/*#include<iostream>
using namespace std;
int main() {
	//�򵥸�ֵ
	//int* p = (int*)malloc(5*sizeof(int));
	string* p = (string*)calloc(10, sizeof(char));//����ʾ����string������calloc��malloc�����ڴ�
	if (p == NULL) {
		cout << "�ڴ����ʧ��" << endl;
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
const int n=13, m=9;//�����Ͷ�����
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
int find(int x) {//���Ҹ��ڵ��Ƿ���ͬ����ͬ����ͨ
	if (parent[x] != x) {
		parent[x] = find(parent[x]);//������Ǹ��ڵ�ͼ����ݹ���ң�ֱ���ҵ����ڵ㣬���ڵ��������parent[x]=x
	}
	return parent[x];
}
//���������ڵ㲻ͬ��ָ��һ����ͬ�Ľڵ㣬���ǽ��������Ϻϲ�Ϊһ������
void unite(int x,int y) {
	parent[find(x)] = find(y);
}
void kruskal() {
	sort(edges, edges + n, cmp);
	for (int i = 0; i < m; i++) {//��ʼÿ����ı�Ǳ��Ϊ�Լ�
		parent[i] = i;
	}
	int sum=0;
	int cnt = 0;
	int pos1,pos2;
	for (int i = 0; i < n; i++) {
		pos1 = edges[i].f, pos2 = edges[i].t;
		if (find(pos1)!= find(pos2)){
			cout << "ѡ�б�" << pos1 << "->" << pos2 << endl;
			unite(pos1, pos2);
			sum += edges[i].w;
			cnt++;//��¼�Ѿ��߹��ĵ�ĸ�������Ϊ�ǵ����еĵ㶼�����ʹ��ͽ��������������еı߶�Ҫ������һ��
		}
		if (cnt == m) {
			break;
		}
	}
	cout << "��Ȩ��Ϊ" << sum << endl;
}
int main() {
	kruskal();
	return 0;
}*/

//ͼת���ɶ��������д洢�������ֵܱ�ʾ��
/*#include<iostream>
#include<queue>
using namespace std;
typedef int BTDataType;
typedef struct BinarytreeNode {
	BTDataType data;
	struct BinarytreeNode* left;
	struct BinarytreeNode* right;
}BTNode;
//��ʼ���ڵ㣬���ʽڵ��ָ�붼�ǿգ����Գ����һ���������൱��һ�����캯��
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
//ǰ�����
//���ڵ�->������->������
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
//��Ѯ����
//������->���ڵ�->������
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
//�������
//������->������->���ڵ�
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
//�������
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

//�ö����������������   9 4 7 17 10 1 25 5
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