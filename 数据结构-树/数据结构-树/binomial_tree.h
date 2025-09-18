#pragma once
#ifndef BINOMIAL_TREE_H
#define BINOMIAL_TREE_H

#include <iostream>
#include <vector>
#include <queue>

// �������ڵ�ṹ
template <typename T>
struct BinomialTreeNode {
    T key;                  // �ڵ�洢��ֵ
    int degree;             // �ڵ�Ķ������ӽڵ�������
    BinomialTreeNode* parent;   // ���ڵ�ָ��
    BinomialTreeNode* child;    // �����ӽڵ�ָ��
    BinomialTreeNode* sibling;  // ���ֵܽڵ�ָ��

    // ���캯��
    BinomialTreeNode(const T& k) : key(k), degree(0),
        parent(nullptr), child(nullptr), sibling(nullptr) {
    }
};

// ��������
template <typename T>
class BinomialTree {
private:
    BinomialTreeNode<T>* root;  // ���ĸ��ڵ�

    // �ݹ�������
    void destroy(BinomialTreeNode<T>* node) {
        if (node == nullptr) return;
        // �������ӽڵ�
        destroy(node->child);
        // �������ֵܽڵ�
        destroy(node->sibling);
        delete node;
    }

    // �ݹ��������
    void preOrder(BinomialTreeNode<T>* node, std::vector<T>& result) const {
        if (node == nullptr) return;
        result.push_back(node->key);
        preOrder(node->child, result);
        preOrder(node->sibling, result);
    }

    // �ݹ�������
    void postOrder(BinomialTreeNode<T>* node, std::vector<T>& result) const {
        if (node == nullptr) return;
        postOrder(node->child, result);
        result.push_back(node->key);
        postOrder(node->sibling, result);
    }

public:
    // ���캯��
    BinomialTree() : root(nullptr) {}

    // ��ָ��ֵ����һ��B0��
    BinomialTree(const T& key) : root(new BinomialTreeNode<T>(key)) {}

    // ��������
    ~BinomialTree() {
        clear();
    }

    // ���ƹ��캯��
    BinomialTree(const BinomialTree<T>& other) {
        root = copyTree(other.root, nullptr);
    }

    // ��ֵ�����
    BinomialTree<T>& operator=(const BinomialTree<T>& other) {
        if (this != &other) {
            clear();
            root = copyTree(other.root, nullptr);
        }
        return *this;
    }

    // �ƶ����캯��
    BinomialTree(BinomialTree<T>&& other) noexcept : root(other.root) {
        other.root = nullptr;
    }

    // �ƶ���ֵ�����
    BinomialTree<T>& operator=(BinomialTree<T>&& other) noexcept {
        if (this != &other) {
            clear();
            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }

    // �ж����Ƿ�Ϊ��
    bool isEmpty() const {
        return root == nullptr;
    }

    // ��ȡ���Ķ��������ڵ�Ķ�����
    int degree() const {
        return root ? root->degree : -1;
    }

    // ��ȡ���ڵ��ֵ
    T rootValue() const {
        if (isEmpty()) {
            throw std::runtime_error("Tree is empty");
        }
        return root->key;
    }

    // �ϲ����ö�����ͬ�Ķ�����
    // �����µ�����ԭ�������ٿ���
    static BinomialTree<T> merge(BinomialTree<T>& tree1, BinomialTree<T>& tree2) {
        // ȷ��������������ͬ
        if (tree1.degree() != tree2.degree()) {
            throw std::invalid_argument("Cannot merge trees of different degrees");
        }

        // ȷ��tree1�ĸ�ֵС�ڵ���tree2�ĸ�ֵ
        if (tree1.root->key > tree2.root->key) {
            std::swap(tree1, tree2);
        }

        // ��tree2����Ϊtree1���ڵ���ӽڵ�
        BinomialTreeNode<T>* root2 = tree2.root;
        root2->parent = tree1.root;
        root2->sibling = tree1.root->child;
        tree1.root->child = root2;
        tree1.root->degree++;

        // ���tree2Ϊ�ѿ�
        tree2.root = nullptr;

        return std::move(tree1);
    }

    // ��ȡ���ڵ���ӽڵ��б���Ϊ������B_{k-1}, B_{k-2}, ..., B_0����
    std::vector<BinomialTree<T>> getChildren() {
        std::vector<BinomialTree<T>> children;
        if (isEmpty() || root->child == nullptr) {
            return children;
        }

        BinomialTreeNode<T>* current = root->child;
        while (current != nullptr) {
            // ������һ���ֵܽڵ�
            BinomialTreeNode<T>* next = current->sibling;

            // �Ͽ���ǰ�ڵ��븸�ڵ���ֵܽڵ������
            current->parent = nullptr;
            current->sibling = nullptr;

            // �����µĶ���������ӵ��б�
            BinomialTree<T> childTree;
            childTree.root = current;
            children.push_back(std::move(childTree));

            current = next;
        }

        // ���ԭ���ڵ���ӽڵ�ָ��
        root->child = nullptr;
        root->degree = 0;

        return children;
    }

    // �������
    std::vector<T> preOrder() const {
        std::vector<T> result;
        preOrder(root, result);
        return result;
    }

    // �������
    std::vector<T> postOrder() const {
        std::vector<T> result;
        postOrder(root, result);
        return result;
    }

    // ��α���
    std::vector<T> levelOrder() const {
        std::vector<T> result;
        if (isEmpty()) return result;

        std::queue<BinomialTreeNode<T>*> q;
        q.push(root);

        while (!q.empty()) {
            BinomialTreeNode<T>* node = q.front();
            q.pop();
            result.push_back(node->key);

            // �Ƚ��ӽڵ������У���������˳��
            BinomialTreeNode<T>* child = node->child;
            while (child != nullptr) {
                q.push(child);
                child = child->sibling;
            }
        }

        return result;
    }

    // ��ӡ���ṹ
    void print(int indent = 0) const {
        if (isEmpty()) {
            std::cout << "Empty tree" << std::endl;
            return;
        }
        printTree(root, indent);
    }

    // �����
    void clear() {
        destroy(root);
        root = nullptr;
    }

private:
    // �������ĸ�������
    BinomialTreeNode<T>* copyTree(BinomialTreeNode<T>* node, BinomialTreeNode<T>* parent) {
        if (node == nullptr) return nullptr;

        BinomialTreeNode<T>* newNode = new BinomialTreeNode<T>(node->key);
        newNode->degree = node->degree;
        newNode->parent = parent;
        newNode->child = copyTree(node->child, newNode);
        newNode->sibling = copyTree(node->sibling, parent);

        return newNode;
    }

    // ��ӡ���ṹ�ĸ�������
    void printTree(BinomialTreeNode<T>* node, int indent) const {
        if (node == nullptr) return;

        // ��ӡ��ǰ�ڵ�
        for (int i = 0; i < indent; ++i) {
            std::cout << "  ";
        }
        std::cout << "|-- " << node->key << " (degree: " << node->degree << ")" << std::endl;

        // ��ӡ�ӽڵ�
        printTree(node->child, indent + 1);

        // ��ӡ�ֵܽڵ�
        printTree(node->sibling, indent);
    }
};

#endif // BINOMIAL_TREE_H

