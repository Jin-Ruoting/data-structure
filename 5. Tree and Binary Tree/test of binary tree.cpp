#include <iostream>

#include "Binary Tree.h"
#include "..\3. Stack, Queue and Array\sequential queue.h"

using namespace std;

// 5.2.05 (medium) 已知一颗二叉树按顺序存储结构进行存储，设计一个算法，求编号分别为 i 和 j 的两个结点的最近的公共祖先结点的值
template <typename DataType>
DataType GetLowestCommonAncestor(SeqBiTree<DataType>& tree, int i, int j)
{
    i = i - 1;                              // 将结点编号转换为数组下标
    j = j - 1;
    int index_i = i * 2 + 1;                // 结点 i 左儿子的下标
    int index_j = j * 2 + 1;                // 结点 j 左儿子的下标
    while (index_i != 0 && index_j != 0)    // 寻找结点 i 和结点 j 的共同祖先，直到它们的祖先相同或达到根节点
    {
        index_i = (index_i - 1) / 2;        // 父节点的下标
        index_j = (index_j - 1) / 2;
    }
    if (i == j)                             // 如果结点 i 和结点 j 相同，那么他们自己就是它们的共同祖先
        return tree.data[i];
    while (index_i != index_j)              // 如果结点 i 和结点 j 的共同祖先不是它们自己，那么它们的共同祖先就是它们祖先中的最近公共祖先
    {
        if (index_i > index_j)
            index_i = (index_i - 1) / 2;
        else
            index_j = (index_j - 1) / 2;
    }
    return tree.data[index_i];
}
template <typename DataType>
DataType Comm_Ancestor(SeqBiTree<DataType> T,int i, int j)
{
    if (T.data[i] != '#' && T.data[j] != '#') // 结点存在
    {
        while (i != j)                          // 两个编号不同时循环
        {
            if (i > j)
                i = i/2;                        // 向上找 i 的祖先
            else
                j = j/2;                        // 向上找 j 的祖先
        }
        return T.data[i];
    }    
}

// 5.3.07 (easy) 二叉树按二叉链表形式存储，试编写一个判别给定二叉树是否是完全二叉树的算法
template <typename DataType>
bool IsComplete(BiNode<DataType> *T)
{
    CirQueue<DataType> Q;
    if(!T)
        return true;                        // 空树为满二叉树
    Q.EnQueue(T);
    while (!Q.Empty())
    {
        BiNode<DataType> *p = Q.DeQueue();
        if (p)                              // 结点非空，将其左右子树直接入队
        {
            Q.EnQueue(p->lchild);
            Q.EnQueue(p->rchild);
        }
        else                                // 结点为空，检查其后是否有非空结点
            while (!Q.Empty())
            {
                p = Q.DeQueue();
                if (p)                      // 后续存在非空结点，为非完全二叉树
                    return false;
            }
    }
    return true;
}

// 5.3.08 (easy) 假设二叉树采用二叉链表存储结构存储，试设计一个算法，计算一棵给定二叉树的所有双分支结点的个数
template <typename DataType>
int DsonNodes(BiNode<DataType> *root)
{
    if (root == nullptr)                                            // root 为空结点
        return 0;
    else if (root->lchild != nullptr && root->rchild != nullptr)    // root 为双分支结点
        return DsonNodes(root->lchild) + DsonNodes(root->rchild) + 1;
    else                                                            // root 为单分支结点或叶结点
        return DsonNodes(root->lchild) + DsonNodes(root->rchild);
}

// 5.3.09 (medium) 设树 B 是一棵采用链式存储的二叉树，编写一个把树 B 中所有结点的左、右子树进行交换的函数
template <typename DataType>
void Swap(BiNode<DataType> *B)
{
    if (B)
    {
        Swap(B->lchild);                    // 递归查找左子树
        Swap(B->rchild);                    // 递归查找右子树
        BiNode<DataType> *temp = B->lchild; // 暂存左子树结点指针
        B->lchild = B->rchild;
        B->rchild = temp;
    }    
}

// 5.3.10 (easy) 假设二叉树采用二叉链表存储结构存储，试设计一个算法，求先序遍历序列中第 k (1 ≤ k ≤ 二叉树中结点的个数) 个结点的值
template <typename DataType>
DataType PreNode(BiNode<DataType> *root, int k)
{
    int i = 1;
    if (root == nullptr)
        throw std::invalid_argument("该结点为空");
    if (k == 1)
        return root->data;
    DataType result;
    try
    {
        result = PreNode(root->lchild, k - 1);   // 递归查找左子树
    }
    catch(const std::invalid_argument&)
    {
        result = PreNode(root->rchild, k - 1);   // 递归查找右子树
    }
    return result;
}

// 5.3.16 (medium) 设计一个算法将二叉树的叶结点按从左到右的顺序连成一个单链表，表头指针为 head。二叉树按二叉链表方式存储，链接时用叶结点的右指针域来存放单链表指针
template <typename DataType>
BiNode<DataType> *LeafLinkedList(BiNode<DataType> *bt, BiNode<DataType> *head = nullptr, BiNode<DataType> *rear = nullptr)
{
    if (bt == nullptr)
        return;
    if (bt->lchild == nullptr && bt->rchild == nullptr) // 当前结点为叶结点
    {
        if (head == nullptr)                            // 如果单链表为空
        {
            head = bt;                                  // 当前结点作为头结点
            rear = bt;                                  // 当前结点作为尾结点
        }
        else
        {
            rear->rchild = bt;                          // 单链表不为空，则将当前结点链接到尾结点右指针域
            rear = bt;                                  // 更新尾结点为当前结点
        }        
    }
    LeafLinkedList(bt->lchild);
    LeafLinkedList(bt->rchild);
    rear->rchild = nullptr;                             // 设置链表尾
    return head;
}

// 5.3.17 (medium) 试设计判断两棵二叉树是否相似的算法。所谓二叉树 T1 和 T2 相似，指的是 T1 和 T2 都是空的二叉树或都只有一个根节点；或者 T1 的左子树和 T2 的左子树是相似的，且 T1 的右子树和 T2 的右子树是相似的
template <typename DataType>
bool IsSimilar(BiNode<DataType> *T1, BiNode<DataType> *T2)
{
    if (T1 == nullptr && T2 == nullptr)         // 两棵树都是空的
        return true;
    else if (T1 == nullptr || T2 == nullptr)    // 只有一棵树为空
        return false;
    else                                        // 递归判断，两棵树的左子树和右子树同时相似则相似
        return IsSimilar(T1->lchild, T2->lchild) && IsSimilar(T1->rchild, T2->rchild);
}

int main()
{
    SeqBiTree<char> tree = {{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}, 26};    // 初始化一个顺序存储的二叉树
    BiTree<char> LTree{};   // 初始化一个二叉链表，此处使用 'AB#D##C##' 序列，该序列为扩展二叉树前序遍历序列，见王红梅《数据结构》第 144 页
    // 05
    int i = 2;
    int j = 8;
    char ancestor = GetLowestCommonAncestor(tree, i, j);
    cout << "The lowest common ancestor of node " << i << " and node " << j << " is " << ancestor << endl;

    // 09
    Swap(LTree.Root());
    LTree.LevelOrder();

    // 10
    int k;                  // 想要访问的结点在二叉树先序遍历中的序号
    cout << "请输入需要先序遍历查找元素的序号：";
    cin >> k;
    char r = PreNode(LTree.Root(), k);
    cout << "二叉树先序遍历序列中第 " << k << " 个结点的值为 " << r << endl;


    return 0;
}