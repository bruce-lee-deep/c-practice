#ifndef SEQ_STACK_H
#define SEQ_STACK_H
#include<iostream>
#include<cassert>//含有assert宏，用来在调试过程中进行断言检查，如果假设不成立回立马输出错误信息
using namespace std;
/*template<typename T>
class SepStack {
private:
	T* data;//储存栈元素的数组
	int top;//栈顶指针，指向栈顶元素
	int capacity;//栈的容量
	const int DEFAULT_CAPACITY = 10;//默认初始容量，便于构造函数
	//扩容，容量翻倍
	void resize() {
		int newCapacity = capacity * 2;
		T* newData = new T[newCapacity];
		//赋值旧数据到新数组
		for (int i = 0; i <= top; i++) {
			newData[i]data[i];
		}
		//释放旧数组内存
		delete[]dat;
		//更新数据
		data = newData;
		capacity = newCapacity;
	}
public:
	//构造函数
	SepStack() {
		capacity = DEFAULT_CAPACITY;
		data = new T[capacity];
		top = -1;//表示空栈
	}
	//析构函数
	~SepStack() {
		delete[]data;
		data = nullptr;
	}
	//入栈
	void push(const T& value) {
		//如果慢栈则扩容
		if (top == capacity - 1) {
			resize();
		}
		data[++top] = value;//先加1再使用
	}
	//出栈
	void pop() {
		assert(!isEmpty() && "栈为空，无法执行出栈操作");
		top--;
	}
	//获取栈顶元素
	T& getTop() {
		assert(!isEmpty() && "栈为空，无法获取栈顶元素");
		return data[top];
	}
	//检查栈是否为空
	bool isEmpty() const{
		return top == -1;
	}
	//获取栈的大小
	int size()const {
		return top + 1;
	}
	//清空栈
	void clear() {
		top = -1;
	}
};*/


template<typename T>
struct Node {
	T data;
	Node* next;
	//构造函数
	Node(const T& value) :data(value), next(nullptr) {}
};
template<typename T>
class LinkedStack {
private:
	Node<T>* top;//栈顶指针，指向栈顶节点
	int count;//栈中元素个数
public:
	//构造函数
	LinkedStack():top(nullptr),count(0){}
	//析构函数
	~LinkedStack() {
		clear();
	}
	//入栈操作
	void push(const T& value) {
		//创建新节点
		Node<T>* newNode = new Node<T>(value);
		//新节点指向当前栈
		newNode->next = top;
		//跟新栈顶指针
		top = newNode;
		count++;
	}
	//出栈操作
	void pop() {
		assert(!isEmpty() && "栈为空，无法出栈");
		//保存当前头节点
		Node<T>* temp = top;
		//跟新栈顶指针
		top = top->next;
		//释放原栈顶指针内存
		delete temp;
		//栈内元素个数减1
		count--;
	}
	//获取栈顶元素
	T& getTop() {
		assert(!isEmpty() && "栈为空，无法获取栈顶元素");
		return top->data;
	}
	//检查是否为空栈
	bool isEmpty() {
		return top == nullptr;
	}
	//获取栈的大小
	int size()const {
		return count;
	}
	//清空栈
	void clear() {
		while (top != nullptr) {
			Node<T>* temp = top;
			top = top->next;
			delete temp;
		}
		//个数清零
		count = 0;
	}
};
#endif

