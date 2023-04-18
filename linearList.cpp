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
        cout << data[i] << "\t";
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

//双链表
template <typename DataType>
struct DulNode
{
    DataType data;
    DulNode<DataType> *prior, *next;
};


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