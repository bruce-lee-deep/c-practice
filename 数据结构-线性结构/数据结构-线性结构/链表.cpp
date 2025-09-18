//����Ҫ�޸�ͷָ�뱾��Ĵ��ݲ������봫ͷָ������û����ں���ĩβ����headָ�룬��Ҫ��Ϊ�˷�ֹ�ڴ�й¶
#include<iostream>
using namespace std;

//��������ṹ
struct ListNode {
	int val;
	ListNode* next;
	//���캯��
	ListNode(int x) :val(x), next(nullptr){}
};

//�����ṹ
ListNode* creatLinkedList(int arr[], int n) {
	//Ԫ��Ϊ��ʱֱ�ӷ��ؿؿ�ָ��
	if (n == 0) {
		return nullptr;
	}
	ListNode* head = new ListNode(arr[0]);
	//currentָ��ָ��ǰ�������Ľڵ㣬���ڽڵ�֮�������
	ListNode* current = head;
	//ѭ�������ڵ�
	for (int i = 1; i < n; i++) {
		current->next = new ListNode(arr[i]);
		current = current->next;
	}
	return head;
}

//��ӡ����
void printLinkedList(ListNode* head) {
	ListNode* current = head;
	//ʹ��while��ѭ��
	while (current!= nullptr) {
		cout << current->val<<"->";
		current = current->next;
	}
}

//�ͷ������ڴ�
void deleteLinkedList(ListNode* head) {
	ListNode* current = head;
	while (current != nullptr) {
		ListNode* next = current->next;
		delete current;
		current = next;
	}
}

//����Ŀ��ֵ
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
//ͨ��Ŀ��ֵɾ���ڵ�
ListNode* deleteNodeByTarget(ListNode* head, int target) {
	//������������
	if (head == nullptr) {
		cout << "����Ϊ�գ��޷�ɾ����" << endl;
		return nullptr;
	}
	//����ͷ�ڵ����Ŀ��ֵ�����
	if (head->val == target) {
		ListNode* temp = head;//����ͷ�ڵ�ĵ�ַ
		head = head->next;//����ͷ�ڵ�
		delete temp;//�ͷ�ԭͷ�ڵ���ڴ�
		return head;
	}
	ListNode* current = head;
	while (current->next!=nullptr) {//ѭ������Ӧ�ø�Ϊ�ж�current->next�������ָ�����
		if (current->next->val == target) {
			ListNode* temp = current->next;//������Ҫɾ���Ľڵ�
			current->next = current->next->next;//����Ҫɾ���Ľڵ�
			delete temp;//�ͷ�ɾ���ڵ���ڴ�
			return head;
		}
		else {
			current = current->next;
		}
	}
	cout << "û���ҵ�Ҫɾ���Ľڵ�" << endl;
	return head;
}
//ͨ������ɾ���ڵ�
ListNode* deleteNodeByPosition(ListNode* head, int position) {
	//����Ƿ�Ϊ������
	if (head == nullptr) {
		cout << "�������޷�ɾ��" << endl;
		return nullptr;
	}
	//���ȿ���ͷ�ڵ�Ϊɾ���������
	if (position == 0) {
		ListNode* temp = head;
		head = head->next;
		delete temp;
		return head;
	}
	//�ų�����Ϊ���������
	if (position < 0) {
		cout << "����Ϊ�������޷�ɾ����" << endl;
		return head;
	}
	else {
		ListNode* current = head;
		//ѭ��position-1���ҵ�����ǰ���Ǹ��ڵ�
		for (int i = 0; i < position - 1; i++) {
			//�ų�����Խ������
			if (current->next->next == nullptr) {
				cout << "����Խ�磬�޷�ɾ����" << endl;
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

//����ڵ�
//������ͷ�������½ڵ�
void insertAtBeginning(ListNode*& head, int data) {
	//�����½ڵ�
	ListNode* newNode = new ListNode(data);
	//�½ڵ��ָ��ָ��ԭ����ͷ�ڵ�
	newNode->next = head;
	//����ͷ�ڵ�Ϊ�½ڵ�
	head = newNode;
}
//������β�������½ڵ�
void insertAtEnd(ListNode*& head, int data) {
	//�����½ڵ�
	ListNode* newNode = new ListNode(data);
	newNode->next = nullptr;
	//�������Ϊ�ա�ֱ����Ϊͷ�ڵ�
	if (head == nullptr) {
		head = newNode;
		return;
	}
	//�ҵ����һ���ڵ�
	ListNode* last = head;
	//���ڵ��ָ��ָ���ʱ��˵���ҵ����һ��ָ��
	while (last->next != nullptr) {
		last = last->next;
	}
	last->next = newNode;
}
//��ָ���Ľڵ������½ڵ�
void insertAfter(ListNode*& head, int prevData, int data) {
	// �ҵ�ǰ���ڵ�
	ListNode* prevNode = head;
	while (prevNode != nullptr && prevNode->val != prevData) {
		prevNode = prevNode->next;
	}

	// ���δ�ҵ�ǰ���ڵ�
	if (prevNode == nullptr) {
		cout << "δ�ҵ�ֵΪ " << prevData << " �Ľڵ�" << endl;
		return;
	}

	// �����½ڵ�
	ListNode* newNode = new ListNode(data);

	// �������
	newNode->next = prevNode->next;
	prevNode->next = newNode;
}

//��������
//�ϲ�������������
ListNode* merge(ListNode* l1, ListNode* l2) {
	ListNode* dummy = new ListNode(0);//�����ƽڵ�򻯲���
	ListNode* current = dummy;
	//�Ƚϲ��ϲ��ڵ�
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
	//ƴ��ʣ��ڵ�
	current->next = l1 ? l1 : l2;
	ListNode* result = dummy->next;
	delete dummy;
	return result;
}
//�鲢����������
ListNode* sortList(ListNode* head) {
	//������򵱸��ڵ�ֱ�ӷ���
	if (!head || !head->next)return head;
	//���е�
	ListNode* slow = head;
	ListNode* fast = head->next;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}
	ListNode* mid = slow->next;
	slow->next = nullptr;//�ָ�����
	//�ݹ����򲢺ϲ�
	return merge(sortList(head), sortList(mid));
}

//˫������
//����˫������ṹ��
struct Node {
	int data;
	Node* prev;
	Node* next;
	Node(int val) :data(val), prev(nullptr), next(nullptr) {};
};
//˫������ĸ��ֲ����뵥���������ƣ�ֻ����Ҫ�޸�ǰ������ָ���ָ��

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