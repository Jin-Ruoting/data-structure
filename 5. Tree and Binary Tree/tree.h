// 树的存储结构

const int MaxSize = 100;    // 树中最多结点数

// 双亲表示法 (parent expression) 采用一组连续空间来存储每个结点，同时在每个结点中增设一个伪指针，指示其双亲结点在数组中的位置

// 树的结点定义
template<typename DataType>
struct PNode
{
    DataType data;          // 存储树中结点的数据信息
    int parent;             // 存储该结点的双亲在数组中的下标，值为 -1 时表示该结点无双亲，为根节点
};
// 树的类型定义
template<typename DataType>
struct PTree
{
    PNode nodes[MaxSize];   // 双亲表示
    int n;                  // 结点数
};


/* 
* 孩子表示法 (child expression) 是一种基于链表的存储方法，即把每个结点的孩子排列起来，看成是一个线性表，且以单链表存储，称为该结点的孩子链表，则 n 个结点共有 n 个孩子链表（叶子结点的孩子链表为空表）
* n 个孩子链表共有 n 个头指针，这 n 个头指针又构成了一个线性表，为了便于进行查找操作，可采用顺序存储
* 最后，将存放 n 个头指针的数组和存放 n 个结点数据信息的数组结合起来，构成孩子链表的表头数组
* 所以在孩子表示法中，存在两类结点：孩子结点和表头结点
*/

// 孩子结点
struct CTNode
{
    int child;
    CTNode *next;
};
// 表头结点
template<typename DataType>
struct CBNode
{
    DataType data;
    CTNode *firstChild;     // 指向孩子链表的头指针
};

// 孩子兄弟表示法 (children brother expression) 又称为二叉链表表示法
template<typename DataType>
struct TNode
{
    DataType data;                  // 存储该结点的数据信息
    TNode<DataType> *firstChild;    // 存储该结点的第一个孩子结点的存储地址
    TNode<DataType> *rightSib;      // 存储该结点的右兄弟结点的存储地址
};
