#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//前序遍历：根节点 左子树 右子树
void preorder(vector<int>& heap, int index) {
	if (index >= heap.size()) return;
	cout << heap[index] << " ";
	//遍历左子树
	preorder(heap, 2 * index+1);
	//遍历右子树
	preorder(heap, 2 * index+2);
}
//中序遍历：左子树 根节点 右子树
void inorder(vector<int>& heap, int index) {
	if (index >= heap.size())return;
	//遍历左子树
	inorder(heap, 2 * index + 1);
	cout << heap[index] << " ";//访问根节点
	//遍历右子树
	inorder(heap, 2 * index + 2);
}
//后序遍历：左子树 右子树 根节点
void postorder(vector<int>& heap, int index) {
	if (index >= heap.size())return;
	//遍历左子树
	postorder(heap, 2 * index + 1);
	//遍历右子树
	postorder(heap, 2 * index + 2);
	cout << heap[index] << " " << endl;//访问根节点
}
void operationToHeap(vector<int>& heap) {
	//构建最大堆（默认）
	make_heap(heap.begin(), heap.end());
	//make_heap(heap.begin(),heap.end(),greater<int>());//最小堆
	//插入元素
	heap.push_back(2);
	//维持堆特性
	push_heap(heap.begin(), heap.end());
	cout << "堆顶元素：" << heap.front() << endl;
	//移除堆顶元素
	pop_heap(heap.begin(), heap.end());//将堆顶元素移到末尾，对前面的元素再次进行堆顶构建
	heap.pop_back();//删除
}

//二项堆：核心优势是支持快速合并操作，是一堆最小堆合并而成
//节点结构
typedef int ElemType;
typedef struct Node {
	ElemType key;
	int degree;
	struct Node* p;
	struct Node* child;
	struct Node* sibling;
};
//the structor of binominal heap
typedef struct heap {
	Node* head;
}*BinomialHeap;
int main() {
	vector<int>heap = { 3,1,4,1,5,9 };
	return 0;
}