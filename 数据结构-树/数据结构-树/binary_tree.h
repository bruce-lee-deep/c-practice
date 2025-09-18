#pragma once
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>

// �������ڵ�ṹ
template <typename T>
struct BinaryTreeNode {
    T data;                  // �ڵ�洢������
    BinaryTreeNode* left;    // ���ӽڵ�ָ��
    BinaryTreeNode* right;   // ���ӽڵ�ָ��

    // ���캯��
    BinaryTreeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

// ��������
template <typename T>
class BinaryTree {
private:
    BinaryTreeNode<T>* root;  // ���ڵ�ָ��

    // �ݹ�������
    void destroy(BinaryTreeNode<T>* node) {
        if (node == nullptr) return;
        destroy(node->left);  // ������������
        destroy(node->right); // ������������
        delete node;          // ���ɾ����ǰ�ڵ�
    }

    // �ݹ����ڵ㣨��ֵ��С���룬�γɶ�����������
    BinaryTreeNode<T>* insert(BinaryTreeNode<T>* node, const T& value) {
        if (node == nullptr) {
            return new BinaryTreeNode<T>(value);  // �ҵ�����λ�ã������½ڵ�
        }

        // �ݹ���뵽��������������
        if (value < node->data) {
            node->left = insert(node->left, value);
        }
        else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        // ��ȵ�ֵ�����루���Ը��������޸ģ�

        return node;
    }

    // �ݹ���ҽڵ�
    bool search(BinaryTreeNode<T>* node, const T& value) const {
        if (node == nullptr) return false;  // δ�ҵ�
        if (node->data == value) return true;  // �ҵ�

        // �ݹ������������������
        if (value < node->data) {
            return search(node->left, value);
        }
        else {
            return search(node->right, value);
        }
    }

    // �ҵ���Сֵ�ڵ㣨����ڵ㣩
    BinaryTreeNode<T>* findMin(BinaryTreeNode<T>* node) const {
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // �ݹ�ɾ���ڵ�
    BinaryTreeNode<T>* remove(BinaryTreeNode<T>* node, const T& value) {
        if (node == nullptr) return nullptr;  // �ڵ㲻����

        // ����Ҫɾ���Ľڵ�
        if (value < node->data) {
            node->left = remove(node->left, value);
        }
        else if (value > node->data) {
            node->right = remove(node->right, value);
        }
        else {
            // �ҵ�Ҫɾ���Ľڵ�

            // ���1��Ҷ�ӽڵ㣨û���ӽڵ㣩
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            // ���2��ֻ��һ���ӽڵ�
            else if (node->left == nullptr) {
                BinaryTreeNode<T>* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                BinaryTreeNode<T>* temp = node->left;
                delete node;
                return temp;
            }
            // ���3���������ӽڵ�
            else {
                // �ҵ��������е���Сֵ�ڵ�
                BinaryTreeNode<T>* temp = findMin(node->right);
                // ����Сֵ�滻��ǰ�ڵ��ֵ
                node->data = temp->data;
                // ɾ���������е���Сֵ�ڵ�
                node->right = remove(node->right, temp->data);
            }
        }
        return node;
    }

    // �ݹ�������� (��->��->��)
    void preOrder(BinaryTreeNode<T>* node) const {
        if (node == nullptr) return;
        std::cout << node->data << " ";  // ���ʸ��ڵ�
        preOrder(node->left);            // ����������
        preOrder(node->right);           // ����������
    }

    // �ݹ�������� (��->��->��)
    void inOrder(BinaryTreeNode<T>* node) const {
        if (node == nullptr) return;
        inOrder(node->left);             // ����������
        std::cout << node->data << " ";  // ���ʸ��ڵ�
        inOrder(node->right);            // ����������
    }

    // �ݹ������� (��->��->��)
    void postOrder(BinaryTreeNode<T>* node) const {
        if (node == nullptr) return;
        postOrder(node->left);           // ����������
        postOrder(node->right);          // ����������
        std::cout << node->data << " ";  // ���ʸ��ڵ�
    }

    // �������ĸ߶�
    int height(BinaryTreeNode<T>* node) const {
        if (node == nullptr) return 0;
        // ���ĸ߶� = max(�������߶�, �������߶�) + 1
        return std::max(height(node->left), height(node->right)) + 1;
    }

    // ����ڵ�����
    int countNodes(BinaryTreeNode<T>* node) const {
        if (node == nullptr) return 0;
        // �ڵ����� = �������ڵ��� + �������ڵ��� + 1(��ǰ�ڵ�)
        return countNodes(node->left) + countNodes(node->right) + 1;
    }

public:
    // ���캯��
    BinaryTree() : root(nullptr) {}

    // ��������
    ~BinaryTree() {
        destroy(root);
        root = nullptr;
    }

    // ����Ԫ�أ�Ĭ�ϰ���������������
    void insert(const T& value) {
        root = insert(root, value);
    }

    // ����Ԫ��
    bool search(const T& value) const {
        return search(root, value);
    }

    // ɾ��Ԫ��
    void remove(const T& value) {
        root = remove(root, value);
    }

    // ����������ݹ飩
    void preOrder() const {
        std::cout << "Pre-order traversal: ";
        preOrder(root);
        std::cout << std::endl;
    }

    // ����������ݹ飩
    void inOrder() const {
        std::cout << "In-order traversal: ";
        inOrder(root);
        std::cout << std::endl;
    }

    // ����������ݹ飩
    void postOrder() const {
        std::cout << "Post-order traversal: ";
        postOrder(root);
        std::cout << std::endl;
    }

    // ��α�����������ȣ�
    void levelOrder() const {
        std::cout << "Level-order traversal: ";
        if (root == nullptr) {
            std::cout << std::endl;
            return;
        }

        std::queue<BinaryTreeNode<T>*> q;
        q.push(root);

        while (!q.empty()) {
            BinaryTreeNode<T>* current = q.front();
            q.pop();

            std::cout << current->data << " ";  // ���ʵ�ǰ�ڵ�

            // ���ӽڵ�������
            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
        std::cout << std::endl;
    }

    // �ǵݹ��������
    void preOrderIterative() const {
        std::cout << "Pre-order iterative: ";
        if (root == nullptr) {
            std::cout << std::endl;
            return;
        }

        std::stack<BinaryTreeNode<T>*> s;
        s.push(root);

        while (!s.empty()) {
            BinaryTreeNode<T>* current = s.top();
            s.pop();

            std::cout << current->data << " ";  // ���ʸ��ڵ�

            // ���ӽڵ�����ջ�����ӽڵ����ջ��ջ��LIFO��
            if (current->right != nullptr) {
                s.push(current->right);
            }
            if (current->left != nullptr) {
                s.push(current->left);
            }
        }
        std::cout << std::endl;
    }

    // ��ȡ���ĸ߶�
    int height() const {
        return height(root);
    }

    // ��ȡ�ڵ�����
    int countNodes() const {
        return countNodes(root);
    }

    // ������Ƿ�Ϊ��
    bool isEmpty() const {
        return root == nullptr;
    }
};

#endif // BINARY_TREE_H
