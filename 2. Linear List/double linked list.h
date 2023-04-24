using namespace std;

//双链表结点结构定义
template <typename DataType>
struct DNode
{
    DataType data;                  //初始化数据域
    DNode<DataType> *prior, *next;  //初始化前驱指针和后继指针
};

//定义双链表类
template <typename DataType>
class DLinkList
{
public:
    DLinkList();
    ~DLinkList();
    int Length();
    DataType Get(int i);
    int Locate(DataType x);
    void InsertNextDNode(DNode<DataType> *p, DNode<DataType> *s);
    DataType DeleteDNode(DNode<DataType> *p);
    int Empty();
    void PrintDLinkList();
private:
    DNode<DataType> *first;         //双链表的头指针
};

//双链表无参构造函数
template <typename DataType>
DLinkList<DataType>::DLinkList()
{
    first = new DNode<DataType>;    //分配一个头结点
    first->prior = nullptr;         //头结点的 prior 指针永远为空指针
    first->next = nullptr;          //头结点后继结点暂时为空
}

//析构函数，循环释放各个结点
template <typename DataType>
DLinkList<DataType>::~DLinkList()
{
    while (first->next != nullptr)
        DeleteDNode(first->next);   //删除头结点的后继结点
    delete(first);                  //释放头结点存储空间
    first = nullptr;                //头指针置空
}

//求双链表的长度并以 int 形式返回
template <typename DataType>
int DLinkList<DataType>::Length()
{
    DNode<DataType> *p = first->next;
    int count = 0;
    while (p != nullptr)            //遍历双链表
    {
        p = p->next;
        count++;
    }
    return count;
}

//按位查找双链表中第 i 个元素的数据域的值（设头结点是第 0 位）
template <typename DataType>
DataType DLinkList<DataType>::Get(int i)
{
    DNode<DataType> *p = first->next;   //初始化工作指针 p 为头结点的后继
    int n = 1;                          //初始化计数器从第一个结点开始计算
    while (p != nullptr)
    {
        if (n == i)                     //当前计数器值与需要查找的元素的位数相同时即为查找成功
            return p->data;             //返回查找到的结点的数据域
        else
        {
            i++;
            p = p->next;
        }
    }
    throw "查找位置非法";
}

//按值查找双链表中第一个数据域与待查找值相同的元素的位数
template <typename DataType>
int DLinkList<DataType>::Locate(DataType x)
{
    DNode<DataType> *p = first->next;
    int count = 1;
    while (p != nullptr)
    {
        if (p->data == x)
            return count;
        else
        {
            count++;
            p->next;
        }
    }
    throw "没有找到与带查找值相同的结点数据域";
}

//在 p 结点之后插入 s 结点
template <typename DataType>
void DLinkList<DataType>::InsertNextDNode(DNode<DataType> *p, DNode<DataType> *s)
{
    if (p == nullptr || s == nullptr)
        throw "非法参数";
    s->next = p->next;
    if (p->next != nullptr)
        p->next->prior = s;
    s->prior = p;
    p->next = s;
    cout << "成功在 " << p->data << " 之后插入 " << s->data << endl;
}

//删除指针 p 指向的结点，并返回节点中存储的数据
template <typename DataType>
DataType DLinkList<DataType>::DeleteDNode(DNode<DataType> *p)
{
    if (p == nullptr || p->prior == nullptr)    //当 p 为空或 p 为头结点时无法删除
        throw "非法结点";
    DataType data = p->data;                    //存储被删结点中的数据
    (p->prior)->next = p->next;                 //将 p 的前驱结点的后继指针指向 p 的后继结点
    if (p->next != nullptr)                     //当 p 为双链表中最后一位时 next 指向空指针，空指针不存在前驱结点
        (p->next)->prior = p->prior;            //当 p 不为双链表中最后一位时 p 的后继结点的前驱指针指向 p 的前驱结点
    delete(p);                                  //释放 p 的存储空间
    return data;                                //返回被删除节点中存储的数据
}

//判断双链表是否为空，若为空则返回 1
template <typename DataType>
int DLinkList<DataType>::Empty()
{
    if (first->next = nullptr)
        return 1;
    return 0;
}

//遍历双链表，打印链表中数据域
template <typename DataType>
void DLinkList<DataType>::PrintDLinkList()
{
    DNode<DataType> *p = first->next;       //初始化工作指针 p
    while (p != nullptr)
    {
        cout << p->data << " ";
        p = p->next;                        //工作指针 p 后移
    }
    cout << endl;
}

//定义带尾指针的循环单链表类，基本操作与单链表类似
template <typename DataType>
class CirSingLinkList
{
public:
    CirSingLinkList();
    int Empty();
private:
    Node<DataType> *rear;       //声明循环单链表尾指针，rear->next 即为头结点，便于对头结点终端结点的操作
    //Node<DataType> *first;    //声明循环单链表头结点
};

//无参构造函数，初始化循环单链表
template <typename DataType>
CirSingLinkList<DataType>::CirSingLinkList()
{
    rear = new Node<DataType>;
    rear->next = rear;          //空循环单链表终端结点指向结点本身
}

//判断循环单链表是否为空，若为空表则返回 1
template <typename DataType>
int CirSingLinkList<DataType>::Empty()
{
    if (rear->next == rear)
        return 1;
    else
        return 0;
}

//定义 循环双链表 类，基本操作与双链表类似，遍历链表时需注意循环条件，通常判断工作指针是否等于头指针
template <typename DataType>
class CirDLinkList
{
public:
    CirDLinkList();
    int Empty();
private:
    DNode<DataType> *first;     //声明循环双链表头指针
};

//无参构造函数，初始化循环双链表
template <typename DataType>
CirDLinkList<DataType>::CirDLinkList()
{
    first = new DNode<DataType>;
    first->next = first;
    first->prior = first;
}

//判断循环双链表是否为空，若为空表，则返回 1
template <typename DataType>
int CirDLinkList<DataType>::Empty()
{
    if (first->next = first)
        return 1;
    else
        return 0;
}