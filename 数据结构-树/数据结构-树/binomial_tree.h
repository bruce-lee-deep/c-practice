#pragma once
#ifndef BINOMIAL_TREE_H
#define BINOMIAL_TREE_H

#include <iostream>
#include <vector>
#include <queue>

// 二项树节点结构
template <typename T>
struct BinomialTreeNode {
    T key;                  // 节点存储的值
    int degree;             // 节点的度数（子节点数量）
    BinomialTreeNode* parent;   // 父节点指针
    BinomialTreeNode* child;    // 最左子节点指针
    BinomialTreeNode* sibling;  // 右兄弟节点指针

    // 构造函数
    BinomialTreeNode(const T& k) : key(k), degree(0),
        parent(nullptr), child(nullptr), sibling(nullptr) {
    }
};

// 二项树类
template <typename T>
class BinomialTree {
private:
    BinomialTreeNode<T>* root;  // 树的根节点

    // 递归销毁树
    void destroy(BinomialTreeNode<T>* node) {
        if (node == nullptr) return;
        // 先销毁子节点
        destroy(node->child);
        // 再销毁兄弟节点
        destroy(node->sibling);
        delete node;
    }

    // 递归先序遍历
    void preOrder(BinomialTreeNode<T>* node, std::vector<T>& result) const {
        if (node == nullptr) return;
        result.push_back(node->key);
        preOrder(node->child, result);
        preOrder(node->sibling, result);
    }

    // 递归后序遍历
    void postOrder(BinomialTreeNode<T>* node, std::vector<T>& result) const {
        if (node == nullptr) return;
        postOrder(node->child, result);
        result.push_back(node->key);
        postOrder(node->sibling, result);
    }

public:
    // 构造函数
    BinomialTree() : root(nullptr) {}

    // 用指定值创建一棵B0树
    BinomialTree(const T& key) : root(new BinomialTreeNode<T>(key)) {}

    // 析构函数
    ~BinomialTree() {
        clear();
    }

    // 复制构造函数
    BinomialTree(const BinomialTree<T>& other) {
        root = copyTree(other.root, nullptr);
    }

    // 赋值运算符
    BinomialTree<T>& operator=(const BinomialTree<T>& other) {
        if (this != &other) {
            clear();
            root = copyTree(other.root, nullptr);
        }
        return *this;
    }

    // 移动构造函数
    BinomialTree(BinomialTree<T>&& other) noexcept : root(other.root) {
        other.root = nullptr;
    }

    // 移动赋值运算符
    BinomialTree<T>& operator=(BinomialTree<T>&& other) noexcept {
        if (this != &other) {
            clear();
            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }

    // 判断树是否为空
    bool isEmpty() const {
        return root == nullptr;
    }

    // 获取树的度数（根节点的度数）
    int degree() const {
        return root ? root->degree : -1;
    }

    // 获取根节点的值
    T rootValue() const {
        if (isEmpty()) {
            throw std::runtime_error("Tree is empty");
        }
        return root->key;
    }

    // 合并两棵度数相同的二项树
    // 返回新的树，原树将不再可用
    static BinomialTree<T> merge(BinomialTree<T>& tree1, BinomialTree<T>& tree2) {
        // 确保两棵树度数相同
        if (tree1.degree() != tree2.degree()) {
            throw std::invalid_argument("Cannot merge trees of different degrees");
        }

        // 确保tree1的根值小于等于tree2的根值
        if (tree1.root->key > tree2.root->key) {
            std::swap(tree1, tree2);
        }

        // 将tree2链接为tree1根节点的子节点
        BinomialTreeNode<T>* root2 = tree2.root;
        root2->parent = tree1.root;
        root2->sibling = tree1.root->child;
        tree1.root->child = root2;
        tree1.root->degree++;

        // 标记tree2为已空
        tree2.root = nullptr;

        return std::move(tree1);
    }

    // 获取根节点的子节点列表（作为独立的B_{k-1}, B_{k-2}, ..., B_0树）
    std::vector<BinomialTree<T>> getChildren() {
        std::vector<BinomialTree<T>> children;
        if (isEmpty() || root->child == nullptr) {
            return children;
        }

        BinomialTreeNode<T>* current = root->child;
        while (current != nullptr) {
            // 保存下一个兄弟节点
            BinomialTreeNode<T>* next = current->sibling;

            // 断开当前节点与父节点和兄弟节点的连接
            current->parent = nullptr;
            current->sibling = nullptr;

            // 创建新的二项树并添加到列表
            BinomialTree<T> childTree;
            childTree.root = current;
            children.push_back(std::move(childTree));

            current = next;
        }

        // 清除原根节点的子节点指针
        root->child = nullptr;
        root->degree = 0;

        return children;
    }

    // 先序遍历
    std::vector<T> preOrder() const {
        std::vector<T> result;
        preOrder(root, result);
        return result;
    }

    // 后序遍历
    std::vector<T> postOrder() const {
        std::vector<T> result;
        postOrder(root, result);
        return result;
    }

    // 层次遍历
    std::vector<T> levelOrder() const {
        std::vector<T> result;
        if (isEmpty()) return result;

        std::queue<BinomialTreeNode<T>*> q;
        q.push(root);

        while (!q.empty()) {
            BinomialTreeNode<T>* node = q.front();
            q.pop();
            result.push_back(node->key);

            // 先将子节点加入队列（按从左到右顺序）
            BinomialTreeNode<T>* child = node->child;
            while (child != nullptr) {
                q.push(child);
                child = child->sibling;
            }
        }

        return result;
    }

    // 打印树结构
    void print(int indent = 0) const {
        if (isEmpty()) {
            std::cout << "Empty tree" << std::endl;
            return;
        }
        printTree(root, indent);
    }

    // 清空树
    void clear() {
        destroy(root);
        root = nullptr;
    }

private:
    // 复制树的辅助函数
    BinomialTreeNode<T>* copyTree(BinomialTreeNode<T>* node, BinomialTreeNode<T>* parent) {
        if (node == nullptr) return nullptr;

        BinomialTreeNode<T>* newNode = new BinomialTreeNode<T>(node->key);
        newNode->degree = node->degree;
        newNode->parent = parent;
        newNode->child = copyTree(node->child, newNode);
        newNode->sibling = copyTree(node->sibling, parent);

        return newNode;
    }

    // 打印树结构的辅助函数
    void printTree(BinomialTreeNode<T>* node, int indent) const {
        if (node == nullptr) return;

        // 打印当前节点
        for (int i = 0; i < indent; ++i) {
            std::cout << "  ";
        }
        std::cout << "|-- " << node->key << " (degree: " << node->degree << ")" << std::endl;

        // 打印子节点
        printTree(node->child, indent + 1);

        // 打印兄弟节点
        printTree(node->sibling, indent);
    }
};

#endif // BINOMIAL_TREE_H

