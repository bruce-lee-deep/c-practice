#pragma once
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>

// 二叉树节点结构
template <typename T>
struct BinaryTreeNode {
    T data;                  // 节点存储的数据
    BinaryTreeNode* left;    // 左子节点指针
    BinaryTreeNode* right;   // 右子节点指针

    // 构造函数
    BinaryTreeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

// 二叉树类
template <typename T>
class BinaryTree {
private:
    BinaryTreeNode<T>* root;  // 根节点指针

    // 递归销毁树
    void destroy(BinaryTreeNode<T>* node) {
        if (node == nullptr) return;
        destroy(node->left);  // 先销毁左子树
        destroy(node->right); // 再销毁右子树
        delete node;          // 最后删除当前节点
    }

    // 递归插入节点（按值大小插入，形成二叉搜索树）
    BinaryTreeNode<T>* insert(BinaryTreeNode<T>* node, const T& value) {
        if (node == nullptr) {
            return new BinaryTreeNode<T>(value);  // 找到合适位置，创建新节点
        }

        // 递归插入到左子树或右子树
        if (value < node->data) {
            node->left = insert(node->left, value);
        }
        else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        // 相等的值不插入（可以根据需求修改）

        return node;
    }

    // 递归查找节点
    bool search(BinaryTreeNode<T>* node, const T& value) const {
        if (node == nullptr) return false;  // 未找到
        if (node->data == value) return true;  // 找到

        // 递归查找左子树或右子树
        if (value < node->data) {
            return search(node->left, value);
        }
        else {
            return search(node->right, value);
        }
    }

    // 找到最小值节点（最左节点）
    BinaryTreeNode<T>* findMin(BinaryTreeNode<T>* node) const {
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // 递归删除节点
    BinaryTreeNode<T>* remove(BinaryTreeNode<T>* node, const T& value) {
        if (node == nullptr) return nullptr;  // 节点不存在

        // 查找要删除的节点
        if (value < node->data) {
            node->left = remove(node->left, value);
        }
        else if (value > node->data) {
            node->right = remove(node->right, value);
        }
        else {
            // 找到要删除的节点

            // 情况1：叶子节点（没有子节点）
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            // 情况2：只有一个子节点
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
            // 情况3：有两个子节点
            else {
                // 找到右子树中的最小值节点
                BinaryTreeNode<T>* temp = findMin(node->right);
                // 用最小值替换当前节点的值
                node->data = temp->data;
                // 删除右子树中的最小值节点
                node->right = remove(node->right, temp->data);
            }
        }
        return node;
    }

    // 递归先序遍历 (根->左->右)
    void preOrder(BinaryTreeNode<T>* node) const {
        if (node == nullptr) return;
        std::cout << node->data << " ";  // 访问根节点
        preOrder(node->left);            // 遍历左子树
        preOrder(node->right);           // 遍历右子树
    }

    // 递归中序遍历 (左->根->右)
    void inOrder(BinaryTreeNode<T>* node) const {
        if (node == nullptr) return;
        inOrder(node->left);             // 遍历左子树
        std::cout << node->data << " ";  // 访问根节点
        inOrder(node->right);            // 遍历右子树
    }

    // 递归后序遍历 (左->右->根)
    void postOrder(BinaryTreeNode<T>* node) const {
        if (node == nullptr) return;
        postOrder(node->left);           // 遍历左子树
        postOrder(node->right);          // 遍历右子树
        std::cout << node->data << " ";  // 访问根节点
    }

    // 计算树的高度
    int height(BinaryTreeNode<T>* node) const {
        if (node == nullptr) return 0;
        // 树的高度 = max(左子树高度, 右子树高度) + 1
        return std::max(height(node->left), height(node->right)) + 1;
    }

    // 计算节点数量
    int countNodes(BinaryTreeNode<T>* node) const {
        if (node == nullptr) return 0;
        // 节点总数 = 左子树节点数 + 右子树节点数 + 1(当前节点)
        return countNodes(node->left) + countNodes(node->right) + 1;
    }

public:
    // 构造函数
    BinaryTree() : root(nullptr) {}

    // 析构函数
    ~BinaryTree() {
        destroy(root);
        root = nullptr;
    }

    // 插入元素（默认按二叉搜索树规则）
    void insert(const T& value) {
        root = insert(root, value);
    }

    // 查找元素
    bool search(const T& value) const {
        return search(root, value);
    }

    // 删除元素
    void remove(const T& value) {
        root = remove(root, value);
    }

    // 先序遍历（递归）
    void preOrder() const {
        std::cout << "Pre-order traversal: ";
        preOrder(root);
        std::cout << std::endl;
    }

    // 中序遍历（递归）
    void inOrder() const {
        std::cout << "In-order traversal: ";
        inOrder(root);
        std::cout << std::endl;
    }

    // 后序遍历（递归）
    void postOrder() const {
        std::cout << "Post-order traversal: ";
        postOrder(root);
        std::cout << std::endl;
    }

    // 层次遍历（广度优先）
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

            std::cout << current->data << " ";  // 访问当前节点

            // 将子节点加入队列
            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
        std::cout << std::endl;
    }

    // 非递归先序遍历
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

            std::cout << current->data << " ";  // 访问根节点

            // 右子节点先入栈，左子节点后入栈（栈是LIFO）
            if (current->right != nullptr) {
                s.push(current->right);
            }
            if (current->left != nullptr) {
                s.push(current->left);
            }
        }
        std::cout << std::endl;
    }

    // 获取树的高度
    int height() const {
        return height(root);
    }

    // 获取节点数量
    int countNodes() const {
        return countNodes(root);
    }

    // 检查树是否为空
    bool isEmpty() const {
        return root == nullptr;
    }
};

#endif // BINARY_TREE_H
