#include <iostream>

using namespace std;

// 二叉树的存储结构

const int MaxSize = 100;        // 数组最大存储空间
// 二叉树的顺序存储结构
template <typename DataType>
struct SeqBiTree
{
    DataType data[MaxSize];     // 二叉树数据域数组
    int biTreeNum;              // 二叉树数组下标
};

// 二叉链表

// 二叉链表存储结构
template <typename DataType>
struct BiNode
{
    DataType data;
    BiNode<DataType> *lchild, *rchild;
};

// 二叉链表类
template <typename DataType>
class BiTree
{
public:
    BiTree();
    ~BiTree();
    void RecursionPreOrder();
    void RecursionInOrder();
    void RecursionPostOrder();
    void PreOrder();
    void InOrder();
    void PostOrder();
    void LevelOrder();
private:
    BiNode<DataType> *Creat();
    void Release(BiNode<DataType> *bt);
    void RecursionPreOrder(BiNode<DataType> *bt);
    void RecursionInOrder(BiNode<DataType> *bt);
    void RecursionPostOrder(BiNode<DataType> *bt);
    BiNode<DataType> *root;                         // 指向根结点的头指针
};

// 构造函数，建立一棵二叉树
template <typename DataType>
BiTree<DataType>::BiTree()
{
    root = Creat();
}

// 析构函数，释放各结点的存储空间
template <typename DataType>
BiTree<DataType>::~BiTree()
{
    Release(root);
}

// 前序遍历二叉树的递归实现
template <typename DataType>
void BiTree<DataType>::RecursionPreOrder()
{
    RecursionPreOrder(root);
}

// 中序遍历二叉树的递归实现
template <typename DataType>
void BiTree<DataType>::RecursionInOrder()
{
    RecursionInOrder(root);
}

// 后序遍历二叉树的递归实现
template <typename DataType>
void BiTree<DataType>::RecursionPostOrder()
{
    RecursionPostOrder(root);
}

// 前序遍历二叉树的非递归实现
template <typename DataType>
void BiTree<DataType>::PreOrder()
{
    BiNode<DataType> *bt = root;
    BiNode<DataType> *S[100];           // 定义一个顺序栈
    int top = -1;                       // 初始化顺序栈
    while (bt != nullptr || top != -1)  // 栈为空且根指针为空时退出循环
    {
        while (bt != nullptr)           // 根指针 bt 非空
        {
            cout << bt->data;           // 输出
            S[++top] = bt;              // 根指针 bt 入栈
            bt = bt->lchild;            // 准备遍历 bt 的左子树
        }
        if (top != -1)                  // 栈非空
        {
            bt = S[top--];              // 弹出栈顶元素至 bt
            bt = bt->rchild;            // 准备遍历 bt 的右子树
        }        
    }    
}

// 中序遍历二叉树的非递归实现
template <typename DataType>
void BiTree<DataType>::InOrder()
{
    BiNode<DataType> *bt = root;
    BiNode<DataType> *S[100];           // 定义一个顺序栈
    int top = -1;                       // 初始化顺序栈
    while (bt != nullptr || top != -1)  // 栈为空且根指针为空时退出循环
    {
        while (bt != nullptr)           // 根指针 bt 非空
        {
            S[++top] = bt;              // 根指针 bt 入栈
            bt = bt->lchild;            // 准备遍历 bt 的左子树
        }
        if (top != -1)                  // 栈非空
        {
            bt = S[top--];              // 弹出栈顶元素至 bt
            cout << bt->data;           // 输出
            bt = bt->rchild;            // 准备遍历 bt 的右子树
        }        
    }    
}

// 栈元素的结构体类型定义
template <typename DataType>
struct element
{
    BiNode<DataType> *ptr;
    int flag;               // 标志变量，为 1 表示遍历完左子树，栈顶结点不能出栈；值为 2 表示遍历完右子树，栈顶结点可以出栈并访问
};

// 后序遍历二叉树的非递归实现
template <typename DataType>
void BiTree<DataType>::PostOrder()
{
    BiNode<DataType> *bt = root;                // 指针 bt 指向二叉链表的根指针
    element<DataType> S[100];                   // 声明一个顺序栈
    int top = -1;                               // 初始化顺序栈
    while (bt != nullptr || top != -1)          // 栈 S 为空且根指针 bt 为空时退出循环
    {
        while (bt != nullptr)                   // 根指针非空时
        {
            top++;
            S[top].ptr = bt;                    // bt 入栈
            S[top].flag = 1;                    // 标志位置 1
            bt = bt->lchild;                    // 准备遍历 bt 的左子树
        }
        while (top != -1 && S[top].flag == 2)   // 栈 S 非空且栈顶元素标志位为 2 时
        {
            bt = S[top--].ptr;                  // 弹出栈顶元素至 bt
            cout << bt->data;                   // 访问 bt
        }
        if (top != -1)                          // 栈非空
        {
            S[top].flag = 2;                    // 栈顶元素的标志位置 2
            bt = S[top].ptr->rchild;            // 准备遍历栈顶结点的右子树
        }        
    }    
}

// 层序遍历二叉树
template <typename DataType>
void BiTree<DataType>::LevelOrder()
{
    BiNode<DataType> *Q[100], *q = nullptr;
    int front = -1, rear = -1;              // 队列初始化
    if (root == nullptr)                    // 二叉树为空，算法结束
        return;
    Q[++rear] = root;                       // 根指针入队
    while (front != rear)                   // 当队列非空时
    {
        q = Q[++front];                     // 出队
        cout << q->data << " ";             // 访问结点的数据域
        if (q->lchild != nullptr)           // 若结点 q 存在左孩子
            Q[++rear] = q->lchild;          // 将左孩子指针入队
        if (q->rchild != nullptr)           // 若结点 q 存在右孩子
            Q[++rear] = q->rchild;          // 将右孩子指针入队
    }
}

// 构造函数调用
template <typename DataType>
BiNode<DataType> *BiTree<DataType>::Creat()
{
    BiNode<DataType> *bt;
    char ch;
    cin >> ch;                      // 输入结点的数据信息，假设为字符
    if (ch == '#')                  // 若输入 # 表明为空树
        bt = nullptr;
    else
    {
        bt = new BiNode<DataType>;
        bt->data = ch;              // 将输入的字符赋值给 bt->data
        bt->lchild = Creat();       // 递归建立左子树
        bt->rchild = Creat();       // 递归建立右子树
    }
    return bt;
}

// 析构函数调用
template <typename DataType>
void BiTree<DataType>::Release(BiNode<DataType> *bt)
{
    if (bt == nullptr)
        return;
    else
    {
        Release(bt->lchild);    // 递归释放左子树
        Release(bt->rchild);    // 递归释放右子树
        delete bt;              // 释放根结点
    }    
}

// 前序遍历的递归实现
template <typename DataType>
void BiTree<DataType>::RecursionPreOrder(BiNode<DataType> *bt)
{
    if (bt == nullptr)                  // 递归调用的结束条件
        return;
    else
    {
        cout << bt->data <<" ";         // 访问根节点 bt 的数据域
        RecursionPreOrder(bt->lchild);  // 前序递归遍历 bt 的左子树
        RecursionPreOrder(bt->rchild);  // 前序递归遍历 bt 的右子树
    }    
}

// 中序遍历的递归实现
template <typename DataType>
void BiTree<DataType>::RecursionInOrder(BiNode<DataType> *bt)
{
    if (bt == nullptr)                  // 递归调用的结束条件
        return;
    else
    {
        RecursionInOrder(bt->lchild);   // 中序递归遍历 bt 的左子树
        cout << bt->data <<" ";         // 访问根节点 bt 的数据域
        RecursionInOrder(bt->rchild);   // 中序递归遍历 bt 的右子树
    }    
}

// 后序遍历的递归实现
template <typename DataType>
void BiTree<DataType>::RecursionPostOrder(BiNode<DataType> *bt)
{
    if (bt == nullptr)                  // 递归调用的结束条件
        return;
    else
    {
        RecursionPostOrder(bt->lchild); // 后序递归遍历 bt 的左子树
        RecursionPostOrder(bt->rchild); // 后序递归遍历 bt 的右子树
        cout << bt->data <<" ";         // 访问根节点 bt 的数据域
    }    
}

// 三叉链表存储二叉树，相比二叉链表增加 parent 域存储指向该结点的双亲结点的指针
template <typename DataType>
struct TriNode
{
    DataType data;
    TriNode<DataType> *lchild, *rchild, *parent;
};

// 线索链表的结点结构定义
template <typename DataType>
struct ThrNode
{
    DataType data;
    int ltag;                           // 左标志位，为 0 表示 lchild 指向该结点的左孩子，为 1 表示 lchild 指向该结点的前驱
    int rtag;                           // 右标志位，为 0 表示 rchild 指向该结点的左孩子，为 1 表示 rchild 指向该结点的后继
    ThrNode<DataType> *lchild, *rchild;
};

// 中序线索链表类定义
template <typename DataType>
class InThrBiTree
{
public:
    InThrBiTree();
    ~InThrBiTree();
    ThrNode<DataType> *Next(ThrNode<DataType> *p);
    void InOrder();
private:
    ThrNode<DataType> *Creat();
    void ThrBiTree(ThrNode<DataType> *bt, ThrNode<DataType> *pre);
    void Release(ThrNode<DataType> *bt);
    ThrNode<DataType> *root;                                        // 指向线索链表的头指针
};

// 构造函数，建立中序线索链表
template <typename DataType>
InThrBiTree<DataType>::InThrBiTree()
{
    root = Creat();             // 建立带线索标志的二叉链表
    ThrBiTree(root, nullptr);   // 遍历二叉链表，建立线索
}

// 析构函数，释放各结点的存储空间
template <typename DataType>
InThrBiTree<DataType>::~InThrBiTree()
{
}
