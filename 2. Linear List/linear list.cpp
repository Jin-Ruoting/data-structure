#include <iostream>

using namespace std;

const int InitSize = 100;
template <typename DataType>
class SeqList
{
public:
    SeqList();
    SeqList(DataType a[], int n);
    ~SeqList();
    int Length();
    DataType Get(int i);
    int Locate(DataType x);
    void Insert(int i, DataType x);
    DataType Delete(int i);
    int Empty();
    void PrintList();
    DataType data[InitSize];
    int MaxSize, length;
};

template <typename DataType>
SeqList<DataType>::SeqList()
{
    length = 0;
}

template <typename DataType>
SeqList<DataType>::SeqList(DataType a[], int n)
{
    if (n > MaxSize)
        throw "参数非法";
    for (int i = 0; i < n; i++)
        data[i] = a[i];
    length = n;
}

template <typename DataType>
SeqList<DataType>::~SeqList() {}

template <typename DataType>
int SeqList<DataType>::Empty()
{
    if (length == 0)
        return 1;
    else
        return 0;
}

template <typename DataType>
int SeqList<DataType>::Length()
{
    return length;
}

template <typename DataType>
void SeqList<DataType>::PrintList()
{
    for (int i = 0; i < length; i++)
        cout << data[i] << " ";
    cout << endl;
}

template <typename DataType>
DataType SeqList<DataType>::Get(int i)
{
    if (i < 1 || i > length)
        throw "查找位置非法";
    else
        return data[i - 1];
}

template <typename DataType>
int SeqList<DataType>::Locate(DataType x)
{
    for (int i = 0; i < length; i++)
        if (data[i] == x)
            return i + 1;
    return 0;
}

template <typename DataType>
void SeqList<DataType>::Insert(int i, DataType x)
{
    if (length >= MaxSize)
        throw "上溢";
    else if (i < 1 || i > length + 1)
        throw "插入位置错误";
    for (int j = length; j >= i; j--)
        data[j] = data[j - 1];
    data[i - 1] = x;
    length++;
}

template <typename DataType>
DataType SeqList<DataType>::Delete(int i)
{
    DataType x;
    if (length == 0)
        throw "下溢";
    else if (i < 1 || i > length)
        throw "删除位置错误";
    x = data[i - 1];
    for (int j = i; j < length; j++)
        data[j - 1] = data[j];
    length--;
    return x;
}

template <typename DataType>
void deleteSame(SeqList<DataType> &L)
{
    if (L.length == 0)
        throw "该表为空";
    int i = 0, j = 1;
    for (; j < L.length; j++)
        if (L.data[i] != L.data[j])
            L.data[++i] = L.data[j];
    L.length = i + 1;
}

template <typename DataType>
void merge(SeqList<DataType> A, SeqList<DataType> B, SeqList<DataType> &C)
{
    if (A.length + B.length > C.MaxSize)
        throw "新表最大长度过短！";
    int i = 0, j = 0, k = 0;
    while (i < A.length && j < B.length)
    {
        if (A.data[i] <= B.data[j])
            C.data[k++] = A.data[i++];
        else
            C.data[k++] = B.data[j++];
    }
    while (i < A.length)
        C.data[k++] = A.data[i++];
    while (j < B.length)
        C.data[k++] = B.data[j++];
    C.length = k;
    C.PrintList();
}

// 二分查找元素x在有序线性表a中的位置
template <typename DataType>
int binarySearch(SeqList<DataType> &a, int n, int x)
{
    int low = 0, high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (a.data[mid] == x)
            return mid;
        else if (a.data[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1; // 没有找到
}

// 将线性表a中下标为i和i+1的元素交换
template <typename DataType>
void swap(SeqList<DataType> &a, int i)
{
    DataType temp = a.data[i];
    a.data[i] = a.data[i + 1];
    a.data[i + 1] = temp;
}

// 在有序顺序表a中查找元素x，若找到则将其与后继元素交换，否则插入x并保持有序
template <typename DataType>
void searchAndSwapOrInsert(SeqList<DataType> &a, int n, int x)
{
    int index = binarySearch(a, n, x);
    if (index != -1)
    {
        // 找到了x，将其与后继元素交换
        if (index < n - 1)
        {
            swap(a, index);
        }
    }
    else
    {
        // 没有找到x，插入x并保持有序
        int i = n - 1;
        while (i >= 0 && a.data[i] > x)
        {
            a.data[i + 1] = a.data[i];
            i--;
        }
        a.length = n + 1;
        a.data[i + 1] = x;
    }
}

template <typename DataType>
struct Node
{
    DataType data;
    Node<DataType> *next;
};

template <typename DataType>
class LinkList
{
    LinkList();
    LinkList(DataType a[], int n);
    LinkList(int n, DataType a[]);
    ~LinkList();
    int Length();
    DataType Get(int i);
    int Locate(DataType x);
    void Insert(int i, DataType x);
    DataType Delete(int i);
    int Empty();
    void PrintList();

private:
    Node<DataType> *first;
};

template <typename DataType>
LinkList<DataType>::LinkList()
{
    first = new Node<DataType>;
    first->next = nullptr;
}

template <typename DataType>
int LinkList<DataType>::Empty()
{
    if (first->next == nullptr)
        return 1;
    return 0;
}

template <typename DataType>
void LinkList<DataType>::PrintList()
{
    Node<DataType> *p = first->next;
    while (p != nullptr)
    {
        cout << p->data << "\t";
        p = p->next;
    }
    cout << endl;
}

template <typename DataType>
int LinkList<DataType>::Length()
{
    Node<DataType> *p = first->next;
    int count = 0;
    while (p != nullptr)
    {
        p = p->next;
        count++;
    }
    return count;
}

template <typename DataType>
DataType LinkList<DataType>::Get(int i)
{
    Node<DataType> *p = first->next;
    if (i < 1)
        throw "查找位置非法";
    int count = 1;
    while (p != nullptr && count < i)
    {
        p = p->next;
        count++;
    }
    if (p == nullptr)
        throw "查找位置超出表长";
    else
        return p->data;
}

//在单链表中实现按值查找操作
template <typename DataType>
int LinkList<DataType>::Locate(DataType x)
{
    Node<DataType> *p = first->next;    //工作指针p初始化
    int count = 1;                      //累加器count初始化
    while (p != nullptr)
    {
        if (p->data == x)               //将结点p的数据域与待查值进行比较
            return count;               //查找成功返回序号
        p = p-> next;
        count++;
    }
    //循环次数与待查值在单链表中的位置有关，等概率下平均时间复杂度为O(n)

    return 0;                           //退出循环表明查找失败
}

//在单链表中将值为x的新结点插入到第i个位置（a_i-1与a_i之间）
template <typename DataType>
void LinkList<DataType>::Insert(int i, DataType x)
{
    Node<DataType> *p = first, *s = nullptr;
    int count = 0;
    while (p != nullptr && count < i - 1)   //查找第 i-1 个结点
    {
        p = p->next;                        //工作指针 p 后移
        count++;
    }
    if (p == nullptr)                       //表长小于 i-1，没有找到第 i-1 个结点
        throw "插入位置错误";
    else
    {
        s = new Node<DataType>;             //申请结点 s
        s->data = x;                        //数据域为 x
        s->next = p->next;                  //将新结点 s 的 next 域指向第 i 个结点
        p->next = s;                        //将工作指针 p （单链表中第 i-1 个结点）的 next 域指向新建的 s 结点
    }
}

//通过构造函数建立单链表，假设给定的数据元素存放在数组a[n]中

//头插法，每次将新申请的结点插在头节点的后面
template <typename DataType>
LinkList<DataType>::LinkList(DataType a[], int n)
{
    first = new Node<DataType>;                 //初始化头结点，first是之前定义的一个指针变量，但是没有分配存储空间，现在分配一个 DataType 类型大小的存储空间，让指针 first 指向这个空间
    first->next = nullptr;                      //初始化一个空链表
    for (int i = 0; i < n; i++)
    {
        Node<DataType> *s = nullptr;            //初始化一个 Node 类型的指针 s （即将插入的结点），默认为尾标志（tall mark）因此将指针域 s 置为空
        s = new Node<DataType>;                 //为指针 s 分配一个 DataType 类型大小的储存空间，让 s 指向这个空间
        s->data = a[i];                         //置指针 s 的数据域为 a[i] 的值
        s->next = first->next;                  //将新插入的结点 s 的 next 指针指向头结点的 next 指针
        first->next = s;                        //将头结点的 next 指针指向新插入的结点 s
    }
}
//尾插法，每次将新申请的结点插在终端结点的后面
template <typename DataType>
LinkList<DataType>::LinkList(int n, DataType a[])
{
    first = new Node<DataType>;                 //为头结点 first 指针分配 DataTypr 类型大小的存储空间，并让 first 指向这个空间
    Node<DataType> *r = first, *s = nullptr;    //初始化尾指针 r ，由于当前为空链表故尾指针和头指针重合；初始化工作指针 s 置空
    for (int i = 0; i < n; i++)
    {
        s = new Node<DataType>;                 //为指针 s 分配一个 DataType 类型大小的储存空间，让 s 指向这个空间
        s->data = a[i];                         //置指针 s 的数据域为 a[i] 的值
        r->next = s;                            //将原终端结点 r 的 next 指针指向新插入的结点 s
        r = s;                                  //让终端结点 r 指向新插入的结点 s
    }
    r->next = nullptr;                          //循环结束，将终端结点 r 的 next 指针置空
}

//删除操作将单链表的第 i 个结点删去
template <typename DataType>
DataType LinkList<DataType>::Delete(int i)
{
    DataType x;                                 //存储被删除的结点中存放的数据
    Node<DataType> *p = first;                  //工作指针 p 置为 first 指针的值
    Node<DataType> *q = nullptr;                //初始化结点 q 用于暂存被删除结点，置空
    int count = 0;                              //初始化计数器 count
    while (p != nullptr && count < i - 1)       //查找第 i-1 个结点
    {
        p = p-> next;
        count++;
    }
    if (p == nullptr || p->next == nullptr)     //结点 p 不存在或结点 p 的后继结点不存在
        throw "删除位置错误";
    else
    {
        q = p->next;                            //暂存被删除结点 next 指针
        x = p->data;                            //暂存被删除结点数据域
        p->next = q->next;                      //被删除结点 前一结点  next 指针指向被删除结点 next 指针
        delete q;                               //释放暂存的被删除结点
        return x;                               //返回被删除结点数据域中存放的数据
    }
}

//析构函数 销毁单链表，释放存储空间
template <typename DataType>
LinkList<DataType>:: ~LinkList()
{
    Node<DataType> *p = first;      //初始化工作指针 p ，指向单链表头指针 first
    while (first != nullptr)        //遍历每一个结点
    {
        first = first->next;        //头结点移至被释放结点的下一结点
        delete p;                   //释放指针
        p = first;                  //工作指针 p 后移，继续指向当前头指针 first
    }    
}

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
    if (first->next == nullptr)
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

//定义循环双链表类，基本操作与双链表类似，遍历链表时需注意循环条件，通常判断工作指针是否等于头指针
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
    if (first->next == first)
        return 1;
    else
        return 0;
}

//定义静态链表的数组元素
template <typename DataType>
struct SNode
{
    DataType data;          //声明数据域
    int next;               //声明 int 类型的指针域（游标）
};

const int MaxSize = 100;    //定义静态链表数组的最大长度
//定义静态链表类，求表长、按位查找、按值查找、遍历等操作的实现与单链表基本相同
template <typename DataType>
class StaList
{
public:
    StaList();
    StaList(DataType a[], int n);
    ~StaList();
    void Insert(int i, DataType x);
    DataType Delete(int i);
private:
    SNode<DataType> SList[MaxSize];     //声明静态链表数组
    int first;                          //声明静态链表头指针
    int avail;                          //avail 是空闲链表（全部由空闲数组单元组成的单链表）的头指针
};

//无参构造函数，初始化空的静态链表和空闲链表
template <typename DataType>
StaList<DataType>::StaList()
{
    for (int i = 0; i < MaxSize; i++)   //遍历静态链表（数组）
    {
        SList[i].data = NULL;           //数据域置空
        SList[i].next = i + 1;          //每一个游标指向相邻的下一个位置
    }    
    first = 0;                          //头指针指向表中第一个位置，下表为 0
    SList[first].next = -1;             //空表，头指针 next 置 -1，即为空
    SList[MaxSize-1].next = -1;         //MaxSize-1 即为表中最后一位元素下标，next 置 -1
    avail = 1;                          //此时头结点已初始化，空闲链表从数组下标 1 开始
}

//构造函数，建立长度为 n 的静态链表
template <typename DataType>
StaList<DataType>::StaList(DataType a[], int n)
{
    //初始化空的静态链表和空闲链表
    for (int i = 0; i < MaxSize; i++)
    {
        SList[i].data = NULL;
        SList[i].next = i + 1;
    }
    first = 0;
    SList[first].next = -1;
    SList[MaxSize-1].next = -1;
    avail = 1;

    //建立传入的静态链表
    SList[first].next = avail;      //将头结点的 next 指向空闲链表的头结点 avail
    for (int i = 0; i < n; i++)
    {
        SList[avail].data = a[i];   //将数据复制到空闲链表中
        avail = SList[avail].next;  //向后移动空闲链表头结点 avail
    }    
}

//析构函数
template <typename DataType>
StaList<DataType>::~StaList(){}

//从空闲链的最前端摘下一个结点，将该结点插入静态链表中第 i 个位置
template <typename DataType>
void StaList<DataType>::Insert(int i, DataType x)
{
    int p;                                      //初始化工作指针 p
    int n = first;
    while (n < i-1 && SList[n].next != -1)  //找到需要插入结点位置的前一个结点，让工作指针 p 指向这个结点
    {
        p = SList[n].next;
        n++;
    }
    if (SList[n].next == -1)
        throw "没有找到位置 i";
    SList[avail].data = x;                      //将需要插入的元素数据 x 存放入空闲链表的头结点
    int s = avail;                              //不用申请新结点，结点 s 作为新插入结点
    avail = SList[avail].next;                  //将空闲链表头结点在空闲链表上后移一位
    SList[s].next = SList[p].next;              //将下标为 s 的结点插入到下标为 p 的结点后面
    SList[p].next = s;
}

//将静态链表中第 i 位待删结点摘下，再插入空闲链的最前端
template <typename DataType>
DataType StaList<DataType>::Delete(int i)
{
    int p;
    int n = first;
    while (n < i-1 && SList[n].next != -1)
    {
        p = SList[n].next;
        n++;
    }
    if (SList[n].next == -1)
        throw "没有找到位置 i";
    int q = SList[p].next;          //暂存被删结点的下标
    SList[p].next = SList[q].next;  //被删结点的上一结点指向被删结点的下一结点
    SList[q].next = avail;          //将被删除结点插入空闲链表最前端
    avail = q;                      //设置空闲链表头指针为新删除的结点
}

//2.3.01 (esay) 设计一个递归算法，删除不带头结点的单链表 L 中所有值为 x 的结点
template <typename DataType>
void f_2_3_01(Node<DataType> &L, DataType x)
{
    Node<DataType> *p;
    if (L == nullptr)
        return;
    if (L->data == x)
    {
        p = L;
        L = L->next;
        delete(p);                //删除头结点
        f_2_3_01(L, x);           //递归删除剩余的结点
    }
    else                          //若 L 所指结点值不为 x
        f_2_3_01(L->next, x);     //递归删除后面的结点
}

//2.3.02 (esay) 在带头结点的单链表 L 中，删除所有值为 x 的结点，并释放其空间，假设值为 x 的结点不唯一，试编写算法实现以上操作
template <typename DataType>
void f_2_3_02(Node<DataType> &L, DataType x)
{
    Node<DataType> *p = L->next;    //初始化工作指针 p，赋初值头结点后一位
    Node<DataType> *pre = L;        //初始化工作指针前一位指针 pre，赋初值为头结点
    Node<DataType> *q;              //初始化辅助指针 q
    while (p != nullptr)            //遍历链表到末尾时停止
    {
        if (p->data == x)            //数据与待删数据相同时
        {
            pre->next = p->next;    //摘链
            q = p;                  //暂存待删结点
            p = p->next;            //工作指针后移
            delete(q);              //释放被删除结点空间
        }
        else
        {
            pre = p;
            p = p->next;            //后移结点 p 和结点 pre
        }
    }    
}

//2.3.03 (unknown) 设L为带头结点的单链表，编写算法实现从尾到头反向输出每个节点的值

//2.3.04 (esay) 试编写在带头结点的单链表L中删除一个最小值结点的高效算法（假设最小值结点是唯一的）
template <typename DataType>
void f_2_3_04(Node<DataType> &L)
{
    Node<DataType> *pre = L;        //工作指针前驱结点
    Node<DataType> *p = L->next;    //工作指针
    Node<DataType> *minpre = L;     //最小值结点前驱结点
    Node<DataType> *minp = L->next; //最小值结点
    if (p == nullptr)               //若为空
        throw "该表为空！";
    while (p != nullptr)            //遍历链表
    {
        if (p->data < minp->data)   //若当前结点数据域比存储的最小值结点小
        {
            minp = p;               //替换当前存储的最小值结点
            minpre = pre;
        }
        pre = p;                    //后移
        p = p->next;
    }
    minpre->next = minp->next;      //摘除最小值结点
    delete(minp);
}

//2.3.05 (medium) 试编写算法将带头结点的单链表就地逆置，所谓“就地”是指辅助空间复杂度为O(1)
template <typename DataType>
void f_2_3_05(Node<DataType> &L)
{
    Node<DataType> *p, *r;  //初始化工作指针 p 及其后继结点 r
    p = L->next;            //工作指针复制头结点后继节点
    L->next = nullptr;      //将头结点指针域置空
    while (p != nullptr)    //采用头插法将指针 p 指向结点插入链表 L
    {
        r = p->next;        //暂存 p 的后继，以防断链
        p->next = L->next;
        L->next = p;
        p = r;              //后移指针 p
    }    
}

//2.3.07 (easy) 设在一个带表头结点的单链表中所有元素结点的数据值无序，试编写一个函数，删除表中所有介于给定的两个值（作为函数参数给出）之间的元素的元素
template <typename DataType>
void f_2_3_07(Node<DataType> &L, DataType min, DataType max)
{
    Node<DataType> *p = L->next;        //工作指针
    Node<DataType> *pre = L;            //工作指针前驱结点
    while (p != nullptr)
    {
        if (p->data > min && p->data < max)
        {
            pre->next = p->next;        //摘除符合条件结点
            delete(p);
            p = pre->next;              //后移
        }
        else                            //若不符合
        {
            pre = p;
            p = p->next;
        }        
    }    
}

//2.3.10 (medium) 将一个带头结点的单链表A分解为两个带头结点的单链表A和B，使得A表中含有原表中 序号 为奇数的元素，而B表中含有原表中 序号 为偶数的元素，且保持其相对顺序不变
template <typename DataType>
DataType f_2_3_10(Node<DataType> &A)
{
    Node<DataType> B = new Node<DataType>;  //初始化偶数链表，分配存储空间
    B->next = nullptr;                      //表 B 为空表，头结点后继为空
    int i = 0;                              //初始化序号计数器
    Node<DataType> *p = A->next;            //工作结点 p 赋值表 A 后继
    A->next = nullptr;                      //将表 A 置空，头结点后继为空
    Node<DataType> *ra = A, *rb = B;        //ra 和 rb 分别指向表 A 和表 B 的尾结点
    while (p != nullptr)
    {
        i++;
        if (i % 2 == 0)                     //元素序号为偶数
        {
            rb->next = p;                   //将结点 p 用尾插法插入表 B
            rb = p;
        }
        else
        {
            ra->next = p;                   //奇数序号元素用尾插法插入表 A
            ra = p;
        }
        p = p->next;                        //后移工作指针
    }
    ra->next = nullptr;                     //将表 a 尾结点指向空指针
    rb->next = nullptr;                     //将表 b 尾结点指向空指针
    return B;                               //返回序号为奇数的表 B，偶数表 A 为引用参数，可直接使用
}

//2.3.11 (medium) 设C={a1,b1,a2,b2,…，an,bn}为线性表，采用带头结点的单链表存放，设计一个就地算法，将其拆分为两个线性表，使得A={a1,a2,…,an}，B={bn,…,b2,b1}
template <typename DataType>
DataType f_2_3_11(Node<DataType> &A)
{
    Node<DataType> B = new Node<DataType>;  //初始化 B 链表
    B->next = nullptr;                      //链表 B 为空表
    Node<DataType> *p = A->next;            //工作指针
    Node<DataType> *ra = A;                 //新链表 A 的尾指针
    Node<DataType> *q;                      //用于保存指针 p 的后继结点
    while (p != nullptr)                    //一次循环处理两个结点
    {
        ra = p;                             //1 号位不移入表 B，后移
        p = p->next;                        //工作指针后移
        q = p->next;                        //保存待移出结点的后续结点，防止断链
        p->next = B->next;                  //头插法将操作结点插入链表 B
        B->next = p;
        ra->next = p->next;                 //链表 A 重新链接
        p = q;                              //工作指针后移
    }
    ra->next = nullptr;                     //结束循环后将表 A 尾指针指向空指针
    return B;                               //返回链表 B
}

//2.3.12 (medium) 在一个递增有序的线性表中，有数值相同的元素存在。若存储方式为单链表，设计算法去掉数值相同的元素，使表中不再有重复的元素，例如(7, 10, 10, 21, 30, 42, 42, 42, 51, 70)将变为(7, 10, 21, 30, 42, 51, 70)
template <typename DataType>
void f_2_3_12(Node<DataType> &L)
{
    Node<DataType> *p = L->next;    //工作指针
    Node<DataType> *pre = L;        //和工作指针做对比的基准指针
    while (p != nullptr)
    {
        if (p->data == pre->data)
        {
            pre->next = p->next;    //摘链
            delete(p);
            p = pre->next;          //后移工作指针，准备对比下一元素
        }
        else                        //若元素不相等
        {
            pre = p;                //后移工作指针和基准指针
            p = p->next;
        }
    }    
}

//2.3.14 (medium) 设A和B是两个单链表（带头结点），其中元素递增有序。设计一个算法从A和B中的公共元素产生单链表C，要求不破坏A，B的结点
template <typename DataType>
DataType f_2_3_14(Node<DataType> A, Node<DataType> B)
{
    Node<DataType> C = new Node<DataType>;              //初始化公共链表 C
    Node<DataType> *a = A->next, *b = B->next, *c = C;  //初始化表 A, B, C 的工作指针
    Node<DataType> *t;                                  //初始化临时存放公共元素的指针
    C->next = nullptr;                                  //单链表 C 置空
    while (a != nullptr && b != nullptr)
    {
        if (a->data < b->data)
            a = a->next;
        else if (a->data >b->data)
            b = b->next;
        else                                            //查找到公共元素
        {
            t = new Node<DataType>;                     //为临时存放公共结点的指针分配存储空间
            t->data = a->data;                          //复制公共结点数据到临时结点
            t->next = c->next;                          //尾插法插入新结点
            c->next = t;
            c = c->next;                                //后移工作指针
            a = a->next;
            b = b->next;
        }        
    }
    return C;
}

//2.3.17 (medium) 设计一个算法用于判断带头结点的循环双链表是否对称
template <typename DataType>
bool f_2_3_17(DNode<DataType> L)
{
    DNode<DataType> *p = L->next, *q = L->prior;    //两端工作指针
    while (p != q && q->next != p)                  //指向同一结点或相邻
    {
        if (p->data == q->data)                     //值相同则继续比较
        {
            p = p->next;
            q = q->prior;
        }
        else
            return false;
    }
    return true;
}

//2.3.18 (medium) 有两个循环单链表，链表头指针分别为 h1 和 h2，编写一个函数将链表 h2 链接到链表 h1 之后，要求链接后的链表仍保持循环链表形式
template <typename DataType>
void f_2_3_18(Node<DataType> &h1, Node<DataType> &h2)
{
    Node<DataType> *p = h1, *q = h2;    //记录 h1 和 h2 的尾结点
    while (p->next != h1)
        p = p->next;
    while (q->next != h2)
        q = q->next;
    p->next = h2;
    q->next = h1;
}

int main()
{
    int a[] = {1, 3, 5, 7, 9};
    int n = sizeof(a) / sizeof(a[0]);
    int x = 4;
    SeqList<int> A{a, 5};
    searchAndSwapOrInsert(A, n, x);
    A.PrintList();

    int r[11] = {1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 5};
    SeqList<int> L{r, 11};
    cout << "当前线性表的数据为：";
    L.PrintList();
    try
    {
        deleteSame(L);
        cout << "删除重复元素后数据为：";
        L.PrintList();
    }
    catch (const char *str)
    {
        cout << str << endl;
    }
    return 0;
}