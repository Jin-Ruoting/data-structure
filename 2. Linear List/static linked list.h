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