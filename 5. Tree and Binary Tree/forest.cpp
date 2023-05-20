#include <iostream>

#include "tree.h"

using namespace std;

// 5.4.04 (medium) 编程求以孩子兄弟表示法存储的森林的叶结点数
template <typename DataType>
int CountLeafNodes(TNode<DataType> *node)
{
    if (node == nullptr)
        return 0;                                   // 空树返回 0
    if (node->firstChild == nullptr)                // 若结点无孩子，则该结点必是叶子结点
        return 1 + CountLeafNodes(node->rightSib);  // 返回叶结点和其兄弟子树中的叶子结点数
    else                                            // 孩子子树和兄弟字数中叶子数之和
        return CountLeafNodes(node->firstChild) + CountLeafNodes(node->rightSib);
}

// 5.4.05 (medium) 以孩子兄弟链表为存储结构，请设计递归算法求树的深度
template <typename DataType>
int CalculateDepth(TNode<DataType> *node)
{
    if (node == nullptr)
        return 0;                               // 空节点的深度为0
    int maxChildDepth = 0;
    TNode<DataType> *child = node->firstChild;
    while (child != nullptr)
    {
        int childDepth = CalculateDepth(child); // 递归计算每个孩子节点的深度
        if (childDepth > maxChildDepth)
            maxChildDepth = childDepth;         // 更新最大子节点深度
        child = child->rightSib;
    }
    return maxChildDepth + 1;                   // 当前节点的深度为最大子节点深度加 1
}

// 创建节点并初始化数据
template<typename DataType>
TNode<DataType>* CreateNode(DataType value)
{
    TNode<DataType>* newNode = new TNode<DataType>;
    newNode->data = value;
    newNode->firstChild = nullptr;
    newNode->rightSib = nullptr;
    return newNode;
}

int main()
{
    // 构建一个测试用的森林
    TNode<int> *forestRoot1 = CreateNode(1);
    TNode<int> *node2 = CreateNode(2);
    TNode<int> *node3 = CreateNode(3);
    TNode<int> *node4 = CreateNode(4);
    TNode<int> *node5 = CreateNode(5);
    TNode<int> *node6 = CreateNode(6);
    TNode<int> *forestRoot2 = CreateNode(7);
    TNode<int> *node8 = CreateNode(8);
    TNode<int> *node9 = CreateNode(9);
    TNode<int> *node10 = CreateNode(10);

    forestRoot1->firstChild = node2;
    node2->rightSib = node3;
    node3->rightSib = node4;
    node4->rightSib = node5;
    node5->rightSib = node6;

    forestRoot2->firstChild = node8;
    node8->rightSib = node9;
    node9->rightSib = node10;

    // 输出森林的节点关系
    std::cout << "Forest 1:" << std::endl;
    TNode<int> *current = forestRoot1;
    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->rightSib;
    }
    std::cout << std::endl;

    std::cout << "Forest 2:" << std::endl;
    current = forestRoot2;
    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->rightSib;
    }
    std::cout << std::endl;

    // 计算树的深度
    int depth = CalculateDepth(forestRoot1);
    std::cout << "Tree depth: " << depth << std::endl;

    // 释放节点内存（避免内存泄漏）
    delete forestRoot1;
    delete node2;
    delete node3;
    delete node4;
    delete node5;
    delete node6;
    delete forestRoot2;
    delete node8;
    delete node9;
    delete node10;

    return 0;
}