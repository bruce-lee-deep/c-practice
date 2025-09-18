#pragma once
#ifndef BINOMIAL_HEAP_H//如果这个宏没被定义过，就执行下面的程序，如果被定义就直接跳到endif
#define BINOMIAL_HEAP_H//如果宏没被定义就重新定义
#include<iostream>
#include<climits>
using namespace std;
//二项数节点结构
template<typename T>
struct BinomialNode {
	T key;                 //节点储存的值
	int degree;            //节点的度数（子节点的个数，子节点的度数依次为degree-1,degree-2,,,,,,0）
	BinomialNode* parent;  //定义父节点指针
	BinomialNode* child;   //子节点指针（最左子节点）
	BinomialNode* sibling; //兄弟节点指针（右兄弟）

	//构造函数
	BinomialNode(const T&k):key(k),degree(0),parent(nullptr),child(nullptr), sibling(nullptr){}
};

// 二项树的链表实现方式：
// 二项树常用“左孩子-右兄弟”链表结构表示，每个节点有 child 指向最左子节点，sibling 指向右兄弟。
// 这样可以用链表高效地表示和遍历二项树。
// BinomialNode 已采用此链表结构。

//二项堆类
template<typename T>
class BinomialHeap {
private:
	BinomialNode<T>* head;//链表的头指针
	//将两个相同度数的二项数连接起来，保持最小堆性质
	BinomialNode<T>* linkTrees(BinomialNode<T>* tree1, BinomialNode<T>* tree2) {
		if (tree1->key > tree2->key) {
			swap(tree1, tree2);
		}

		//合并操作
		tree2->parent = tree1;
		tree2->sibing = tree1->child;
		tree1->child = tree2;
		tree1->degree++;

		return tree1;
	}
	//合并两个二项堆的链表，按度数递增排序
	BinomialNode<T>* mergeHeaps(BinomialHeap<T>& other) {
		BinomialNode<T>* newHead = nullptr;//合并后新的二项堆链表
		BinomailNode<T>** current = &newHead;
		BinomialNode<T>* h1 = head;
		BinomialNode<T>* h2 = other.head;

		//合并两个有序链表
		while (h1 != nullptr && h2 != nullptr) {
			if (h1->degree <= h2->degree) {
				*current = h1;
				h1=h1->sibling;
			}
			else {
				*current = h2;
				h2 = h2->sibling;
			}
			current = &((*current)->sibling);
		}

		//处理剩余节点
		if(h1!=nullptr){
			*current = h1;
		}
		else {
			*current = h2;
		}

		return newHead;
	}

	//反转节点的子链表，用于提取最小值后处理子节点
	BinomialNode<T>* reverseList(BinomialNode<T>* node) {
		BinomialNode<T>* prev = nullptr;
		BinomialNode<T>* current = node;
		BinomialNode<T>* next = nullptr;

		while (current != nullptr) {
			next = current->sibling;
			current->sibling = prev;
			current->parent = nullptr;
			prev = current;
			current = next;
		}

		return prev;
	}

	//打印二项树的辅助函数
	void printTree(BinomialNode<T>* node, int depth) const {
		if (node == nullptr) return;

		// 打印当前节点
		for (int i = 0; i < depth; ++i) {
			std::cout << "  ";
		}
		std::cout << "|-- " << node->key << " (degree: " << node->degree << ")" << std::endl;

		// 打印子节点
		printTree(node->child, depth + 1);

		// 打印兄弟节点
		printTree(node->sibling, depth);
	}

	// 销毁二项树的辅助函数
	void destroyTree(BinomialNode<T>* node) {
		if (node == nullptr) return;
		destroyTree(node->child);
		destroyTree(node->sibling);
		delete node;
	}
public:
    // 构造函数
    BinomialHeap() : head(nullptr) {}

    // 析构函数
    ~BinomialHeap() {
        clear();
    }

    // 检查堆是否为空
    bool isEmpty() const {
        return head == nullptr;
    }

    // 插入元素
    void insert(const T& key) {
        BinomialHeap<T> tempHeap;
        tempHeap.head = new BinomialNode<T>(key);
        *this = merge(tempHeap);
    }

    // 查找最小值
    T findMin() const {
        if (isEmpty()) {
            throw std::runtime_error("Heap is empty");
        }

        BinomialNode<T>* minNode = head;
        BinomialNode<T>* current = head->sibling;

        while (current != nullptr) {
            if (current->key < minNode->key) {
                minNode = current;
            }
            current = current->sibling;
        }

        return minNode->key;
    }

    // 提取最小值
    T extractMin() {
        if (isEmpty()) {
            throw std::runtime_error("Heap is empty");
        }

        // 找到最小节点及其前驱
        BinomialNode<T>* minNode = head;
        BinomialNode<T>* prevMin = nullptr;
        BinomialNode<T>* current = head->sibling;
        BinomialNode<T>* prevCurrent = head;

        while (current != nullptr) {
            if (current->key < minNode->key) {
                minNode = current;
                prevMin = prevCurrent;
            }
            prevCurrent = current;
            current = current->sibling;
        }

        // 从根链表中移除最小节点
        if (prevMin == nullptr) {
            head = minNode->sibling;
        }
        else {
            prevMin->sibling = minNode->sibling;
        }

        // 处理最小节点的子节点，创建新的二项堆
        BinomialHeap<T> childHeap;
        childHeap.head = reverseList(minNode->child);

        // 保存最小值并释放节点
        T minKey = minNode->key;
        delete minNode;

        // 合并剩余部分和子节点堆
        *this = merge(childHeap);

        return minKey;
    }

    // 合并两个二项堆
    BinomialHeap<T> merge(BinomialHeap<T>& other) {
        BinomialHeap<T> result;
        result.head = mergeHeaps(other);

        // 处理度数相同的树
        if (result.head == nullptr) {
            return result;
        }

        BinomialNode<T>* prev = nullptr;
        BinomialNode<T>* current = result.head;
        BinomialNode<T>* next = current->sibling;

        while (next != nullptr) {
            // 情况1：当前节点与下一个节点度数不同，或存在下下个节点且度数相同
            if (current->degree != next->degree ||
                (next->sibling != nullptr && next->sibling->degree == current->degree)) {
                prev = current;
                current = next;
            }
            else {
                // 情况2：当前节点与下一个节点度数相同，合并它们
                if (current->key <= next->key) {
                    current->sibling = next->sibling;
                    current = linkTrees(current, next);
                }
                else {
                    if (prev == nullptr) {
                        result.head = next;
                    }
                    else {
                        prev->sibling = next;
                    }
                    current = linkTrees(next, current);
                }
            }
            next = current->sibling;
        }

        // 清空被合并的堆
        other.head = nullptr;
        return result;
    }

    // 打印堆结构
    void printHeap() const {
        if (isEmpty()) {
            std::cout << "Heap is empty" << std::endl;
            return;
        }

        std::cout << "Binomial Heap structure:" << std::endl;
        BinomialNode<T>* current = head;
        while (current != nullptr) {
            printTree(current, 0);
            current = current->sibling;
        }
    }

    // 清空堆
    void clear() {
        destroyTree(head);
        head = nullptr;
    }
};
};
#endif

