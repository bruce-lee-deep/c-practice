#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//ǰ����������ڵ� ������ ������
void preorder(vector<int>& heap, int index) {
	if (index >= heap.size()) return;
	cout << heap[index] << " ";
	//����������
	preorder(heap, 2 * index+1);
	//����������
	preorder(heap, 2 * index+2);
}
//��������������� ���ڵ� ������
void inorder(vector<int>& heap, int index) {
	if (index >= heap.size())return;
	//����������
	inorder(heap, 2 * index + 1);
	cout << heap[index] << " ";//���ʸ��ڵ�
	//����������
	inorder(heap, 2 * index + 2);
}
//��������������� ������ ���ڵ�
void postorder(vector<int>& heap, int index) {
	if (index >= heap.size())return;
	//����������
	postorder(heap, 2 * index + 1);
	//����������
	postorder(heap, 2 * index + 2);
	cout << heap[index] << " " << endl;//���ʸ��ڵ�
}
void operationToHeap(vector<int>& heap) {
	//�������ѣ�Ĭ�ϣ�
	make_heap(heap.begin(), heap.end());
	//make_heap(heap.begin(),heap.end(),greater<int>());//��С��
	//����Ԫ��
	heap.push_back(2);
	//ά�ֶ�����
	push_heap(heap.begin(), heap.end());
	cout << "�Ѷ�Ԫ�أ�" << heap.front() << endl;
	//�Ƴ��Ѷ�Ԫ��
	pop_heap(heap.begin(), heap.end());//���Ѷ�Ԫ���Ƶ�ĩβ����ǰ���Ԫ���ٴν��жѶ�����
	heap.pop_back();//ɾ��
}

//����ѣ�����������֧�ֿ��ٺϲ���������һ����С�Ѻϲ�����
//�ڵ�ṹ
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