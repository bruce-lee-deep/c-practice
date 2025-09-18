#pragma once
#ifndef BINOMIAL_HEAP_H//��������û�����������ִ������ĳ�������������ֱ������endif
#define BINOMIAL_HEAP_H//�����û����������¶���
#include<iostream>
#include<climits>
using namespace std;
//�������ڵ�ṹ
template<typename T>
struct BinomialNode {
	T key;                 //�ڵ㴢���ֵ
	int degree;            //�ڵ�Ķ������ӽڵ�ĸ������ӽڵ�Ķ�������Ϊdegree-1,degree-2,,,,,,0��
	BinomialNode* parent;  //���常�ڵ�ָ��
	BinomialNode* child;   //�ӽڵ�ָ�루�����ӽڵ㣩
	BinomialNode* sibling; //�ֵܽڵ�ָ�루���ֵܣ�

	//���캯��
	BinomialNode(const T&k):key(k),degree(0),parent(nullptr),child(nullptr), sibling(nullptr){}
};

// ������������ʵ�ַ�ʽ��
// ���������á�����-���ֵܡ�����ṹ��ʾ��ÿ���ڵ��� child ָ�������ӽڵ㣬sibling ָ�����ֵܡ�
// ���������������Ч�ر�ʾ�ͱ�����������
// BinomialNode �Ѳ��ô�����ṹ��

//�������
template<typename T>
class BinomialHeap {
private:
	BinomialNode<T>* head;//�����ͷָ��
	//��������ͬ�����Ķ���������������������С������
	BinomialNode<T>* linkTrees(BinomialNode<T>* tree1, BinomialNode<T>* tree2) {
		if (tree1->key > tree2->key) {
			swap(tree1, tree2);
		}

		//�ϲ�����
		tree2->parent = tree1;
		tree2->sibing = tree1->child;
		tree1->child = tree2;
		tree1->degree++;

		return tree1;
	}
	//�ϲ���������ѵ�������������������
	BinomialNode<T>* mergeHeaps(BinomialHeap<T>& other) {
		BinomialNode<T>* newHead = nullptr;//�ϲ����µĶ��������
		BinomailNode<T>** current = &newHead;
		BinomialNode<T>* h1 = head;
		BinomialNode<T>* h2 = other.head;

		//�ϲ�������������
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

		//����ʣ��ڵ�
		if(h1!=nullptr){
			*current = h1;
		}
		else {
			*current = h2;
		}

		return newHead;
	}

	//��ת�ڵ��������������ȡ��Сֵ�����ӽڵ�
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

	//��ӡ�������ĸ�������
	void printTree(BinomialNode<T>* node, int depth) const {
		if (node == nullptr) return;

		// ��ӡ��ǰ�ڵ�
		for (int i = 0; i < depth; ++i) {
			std::cout << "  ";
		}
		std::cout << "|-- " << node->key << " (degree: " << node->degree << ")" << std::endl;

		// ��ӡ�ӽڵ�
		printTree(node->child, depth + 1);

		// ��ӡ�ֵܽڵ�
		printTree(node->sibling, depth);
	}

	// ���ٶ������ĸ�������
	void destroyTree(BinomialNode<T>* node) {
		if (node == nullptr) return;
		destroyTree(node->child);
		destroyTree(node->sibling);
		delete node;
	}
public:
    // ���캯��
    BinomialHeap() : head(nullptr) {}

    // ��������
    ~BinomialHeap() {
        clear();
    }

    // �����Ƿ�Ϊ��
    bool isEmpty() const {
        return head == nullptr;
    }

    // ����Ԫ��
    void insert(const T& key) {
        BinomialHeap<T> tempHeap;
        tempHeap.head = new BinomialNode<T>(key);
        *this = merge(tempHeap);
    }

    // ������Сֵ
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

    // ��ȡ��Сֵ
    T extractMin() {
        if (isEmpty()) {
            throw std::runtime_error("Heap is empty");
        }

        // �ҵ���С�ڵ㼰��ǰ��
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

        // �Ӹ��������Ƴ���С�ڵ�
        if (prevMin == nullptr) {
            head = minNode->sibling;
        }
        else {
            prevMin->sibling = minNode->sibling;
        }

        // ������С�ڵ���ӽڵ㣬�����µĶ����
        BinomialHeap<T> childHeap;
        childHeap.head = reverseList(minNode->child);

        // ������Сֵ���ͷŽڵ�
        T minKey = minNode->key;
        delete minNode;

        // �ϲ�ʣ�ಿ�ֺ��ӽڵ��
        *this = merge(childHeap);

        return minKey;
    }

    // �ϲ����������
    BinomialHeap<T> merge(BinomialHeap<T>& other) {
        BinomialHeap<T> result;
        result.head = mergeHeaps(other);

        // ���������ͬ����
        if (result.head == nullptr) {
            return result;
        }

        BinomialNode<T>* prev = nullptr;
        BinomialNode<T>* current = result.head;
        BinomialNode<T>* next = current->sibling;

        while (next != nullptr) {
            // ���1����ǰ�ڵ�����һ���ڵ������ͬ����������¸��ڵ��Ҷ�����ͬ
            if (current->degree != next->degree ||
                (next->sibling != nullptr && next->sibling->degree == current->degree)) {
                prev = current;
                current = next;
            }
            else {
                // ���2����ǰ�ڵ�����һ���ڵ������ͬ���ϲ�����
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

        // ��ձ��ϲ��Ķ�
        other.head = nullptr;
        return result;
    }

    // ��ӡ�ѽṹ
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

    // ��ն�
    void clear() {
        destroyTree(head);
        head = nullptr;
    }
};
};
#endif

