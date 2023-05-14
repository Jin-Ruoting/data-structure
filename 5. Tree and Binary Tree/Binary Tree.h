// 二叉树的存储结构

// 顺序存储结构

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
    void PreOrder();
    void InOrder();
    void PostOrder();
    void LevelOrder();
private:
    BiNode<DataType> *Creat();
    void Release(BiNode<DataType> *bt);
    void PreOrder(BiNode<DataType> *bt);
    void InOrder(BiNode<DataType> *bt);
    void PostOrder(BiNode<DataType> *bt);
    BiNode<DataType> *root;
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

// 前序遍历二叉树
template <typename DataType>
void BiTree<DataType>::PreOrder()
{
    PreOrder(root);
}

// 中序遍历二叉树
template <typename DataType>
void BiTree<DataType>::InOrder()
{
    InOrder(root);
}

// 后序遍历二叉树
template <typename DataType>
void BiTree<DataType>::PostOrder()
{
    PostOrder(root);
}

// 层序遍历二叉树
template <typename DataType>
void BiTree<DataType>::LevelOrder()
{
    BiNode<DataType> *Q[100], *q = nullptr;
    
}