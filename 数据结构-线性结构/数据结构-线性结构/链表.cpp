//凡是要修改头指针本身的传递参数必须传头指针的引用或者在函数末尾返回head指针，主要是为了防止内存泄露
#include<iostream>
using namespace std;

//定义链表结构
struct ListNode {
	int val;
	ListNode* next;
	//构造函数
	ListNode(int x) :val(x), next(nullptr){}
};

//创建结构
ListNode* creatLinkedList(int arr[], int n) {
	//元素为空时直接返回控空指针
	if (n == 0) {
		return nullptr;
	}
	ListNode* head = new ListNode(arr[0]);
	//current指针指向当前被创建的节点，便于节点之间的连接
	ListNode* current = head;
	//循环创建节点
	for (int i = 1; i < n; i++) {
		current->next = new ListNode(arr[i]);
		current = current->next;
	}
	return head;
}

//打印链表
void printLinkedList(ListNode* head) {
	ListNode* current = head;
	//使用while来循环
	while (current!= nullptr) {
		cout << current->val<<"->";
		current = current->next;
	}
}

//释放链表内存
void deleteLinkedList(ListNode* head) {
	ListNode* current = head;
	while (current != nullptr) {
		ListNode* next = current->next;
		delete current;
		current = next;
	}
}

//查找目标值
ListNode* findNode(ListNode* head, int target) {
	ListNode* current = head;
	while (current != nullptr) {
		if (current->val == target) {
			return current;
		}
		current = current->next;
	}
	return nullptr;
}
//通过目标值删除节点
ListNode* deleteNodeByTarget(ListNode* head, int target) {
	//处理空链表情况
	if (head == nullptr) {
		cout << "链表为空，无法删除！" << endl;
		return nullptr;
	}
	//处理头节点就是目标值的情况
	if (head->val == target) {
		ListNode* temp = head;//保存头节点的地址
		head = head->next;//更新头节点
		delete temp;//释放原头节点的内存
		return head;
	}
	ListNode* current = head;
	while (current->next!=nullptr) {//循环条件应该改为判断current->next，避免空指针访问
		if (current->next->val == target) {
			ListNode* temp = current->next;//保存需要删除的节点
			current->next = current->next->next;//跳过要删除的节点
			delete temp;//释放删除节点的内存
			return head;
		}
		else {
			current = current->next;
		}
	}
	cout << "没有找到要删除的节点" << endl;
	return head;
}
//通过索引删除节点
ListNode* deleteNodeByPosition(ListNode* head, int position) {
	//检查是否为空链表
	if (head == nullptr) {
		cout << "空链表无法删除" << endl;
		return nullptr;
	}
	//首先考虑头节点为删除对象情况
	if (position == 0) {
		ListNode* temp = head;
		head = head->next;
		delete temp;
		return head;
	}
	//排除索引为负数的情况
	if (position < 0) {
		cout << "索引为负数，无法删除！" << endl;
		return head;
	}
	else {
		ListNode* current = head;
		//循环position-1次找到索引前的那个节点
		for (int i = 0; i < position - 1; i++) {
			//排除索引越界的情况
			if (current->next->next == nullptr) {
				cout << "索引越界，无法删除！" << endl;
				return head;
			}
			current = current->next;
		}
		ListNode* temp = current->next;
		current->next = current->next->next;
		delete temp;
		return head;
	}
}

//插入节点
//在链表头部插入新节点
void insertAtBeginning(ListNode*& head, int data) {
	//创建新节点
	ListNode* newNode = new ListNode(data);
	//新节点的指针指向原来的头节点
	newNode->next = head;
	//更新头节点为新节点
	head = newNode;
}
//在链表尾部插入新节点
void insertAtEnd(ListNode*& head, int data) {
	//创建新节点
	ListNode* newNode = new ListNode(data);
	newNode->next = nullptr;
	//如果链表为空。直接作为头节点
	if (head == nullptr) {
		head = newNode;
		return;
	}
	//找到最后一个节点
	ListNode* last = head;
	//当节点的指针指向空时，说明找到最后一个指针
	while (last->next != nullptr) {
		last = last->next;
	}
	last->next = newNode;
}
//在指定的节点后插入新节点
void insertAfter(ListNode*& head, int prevData, int data) {
	// 找到前驱节点
	ListNode* prevNode = head;
	while (prevNode != nullptr && prevNode->val != prevData) {
		prevNode = prevNode->next;
	}

	// 如果未找到前驱节点
	if (prevNode == nullptr) {
		cout << "未找到值为 " << prevData << " 的节点" << endl;
		return;
	}

	// 创建新节点
	ListNode* newNode = new ListNode(data);

	// 插入操作
	newNode->next = prevNode->next;
	prevNode->next = newNode;
}

//链表排序
//合并两个有序链表
ListNode* merge(ListNode* l1, ListNode* l2) {
	ListNode* dummy = new ListNode(0);//创建哑节点简化操作
	ListNode* current = dummy;
	//比较并合并节点
	while (l1 && l2) {
		if (l1->val < l2->val) {
			current->next = l1;
			l1 = l1->next;
		}
		else {
			current->next = l2;
			l2 = l2->next;
		}
		current = current->next;
	}
	//拼接剩余节点
	current->next = l1 ? l1 : l2;
	ListNode* result = dummy->next;
	delete dummy;
	return result;
}
//归并排序主函数
ListNode* sortList(ListNode* head) {
	//空链表或当个节点直接返回
	if (!head || !head->next)return head;
	//找中点
	ListNode* slow = head;
	ListNode* fast = head->next;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}
	ListNode* mid = slow->next;
	slow->next = nullptr;//分割链表
	//递归排序并合并
	return merge(sortList(head), sortList(mid));
}

//双向链表
//创建双向链表结构体
struct Node {
	int data;
	Node* prev;
	Node* next;
	Node(int val) :data(val), prev(nullptr), next(nullptr) {};
};
//双向链表的各种操作与单向链表类似，只是需要修改前后两个指针的指向

int main(){
	int arr[] = { 1,2,3,4,5,6,7,8,9,0 };
	int n = sizeof(arr) / sizeof(arr[0]);
	ListNode*head=creatLinkedList(arr, n);
	//printLinkedList(head);
	//findNode(head, 7);
	//deleteLinkedList(head);
	//deleteNodeByPosition(head, 9);
	//printLinkedList(head);
	//deleteNodeByPosition(head, 10);
	//printLinkedList(head);
	//deleteNodeByPosition(head, 11);
	//printLinkedList(head);
	return 0;
}