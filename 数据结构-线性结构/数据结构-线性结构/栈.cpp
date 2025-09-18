#ifndef SEQ_STACK_H
#define SEQ_STACK_H
#include<iostream>
#include<cassert>//����assert�꣬�����ڵ��Թ����н��ж��Լ�飬������費�������������������Ϣ
using namespace std;
/*template<typename T>
class SepStack {
private:
	T* data;//����ջԪ�ص�����
	int top;//ջ��ָ�룬ָ��ջ��Ԫ��
	int capacity;//ջ������
	const int DEFAULT_CAPACITY = 10;//Ĭ�ϳ�ʼ���������ڹ��캯��
	//���ݣ���������
	void resize() {
		int newCapacity = capacity * 2;
		T* newData = new T[newCapacity];
		//��ֵ�����ݵ�������
		for (int i = 0; i <= top; i++) {
			newData[i]data[i];
		}
		//�ͷž������ڴ�
		delete[]dat;
		//��������
		data = newData;
		capacity = newCapacity;
	}
public:
	//���캯��
	SepStack() {
		capacity = DEFAULT_CAPACITY;
		data = new T[capacity];
		top = -1;//��ʾ��ջ
	}
	//��������
	~SepStack() {
		delete[]data;
		data = nullptr;
	}
	//��ջ
	void push(const T& value) {
		//�����ջ������
		if (top == capacity - 1) {
			resize();
		}
		data[++top] = value;//�ȼ�1��ʹ��
	}
	//��ջ
	void pop() {
		assert(!isEmpty() && "ջΪ�գ��޷�ִ�г�ջ����");
		top--;
	}
	//��ȡջ��Ԫ��
	T& getTop() {
		assert(!isEmpty() && "ջΪ�գ��޷���ȡջ��Ԫ��");
		return data[top];
	}
	//���ջ�Ƿ�Ϊ��
	bool isEmpty() const{
		return top == -1;
	}
	//��ȡջ�Ĵ�С
	int size()const {
		return top + 1;
	}
	//���ջ
	void clear() {
		top = -1;
	}
};*/


template<typename T>
struct Node {
	T data;
	Node* next;
	//���캯��
	Node(const T& value) :data(value), next(nullptr) {}
};
template<typename T>
class LinkedStack {
private:
	Node<T>* top;//ջ��ָ�룬ָ��ջ���ڵ�
	int count;//ջ��Ԫ�ظ���
public:
	//���캯��
	LinkedStack():top(nullptr),count(0){}
	//��������
	~LinkedStack() {
		clear();
	}
	//��ջ����
	void push(const T& value) {
		//�����½ڵ�
		Node<T>* newNode = new Node<T>(value);
		//�½ڵ�ָ��ǰջ
		newNode->next = top;
		//����ջ��ָ��
		top = newNode;
		count++;
	}
	//��ջ����
	void pop() {
		assert(!isEmpty() && "ջΪ�գ��޷���ջ");
		//���浱ǰͷ�ڵ�
		Node<T>* temp = top;
		//����ջ��ָ��
		top = top->next;
		//�ͷ�ԭջ��ָ���ڴ�
		delete temp;
		//ջ��Ԫ�ظ�����1
		count--;
	}
	//��ȡջ��Ԫ��
	T& getTop() {
		assert(!isEmpty() && "ջΪ�գ��޷���ȡջ��Ԫ��");
		return top->data;
	}
	//����Ƿ�Ϊ��ջ
	bool isEmpty() {
		return top == nullptr;
	}
	//��ȡջ�Ĵ�С
	int size()const {
		return count;
	}
	//���ջ
	void clear() {
		while (top != nullptr) {
			Node<T>* temp = top;
			top = top->next;
			delete temp;
		}
		//��������
		count = 0;
	}
};
#endif

