#include "singly linked list.h"

template <typename DataType>
class LinkQueue
{
public:
    LinkQueue();
    ~LinkQueue();
    void EnQueue(DataType x);
    DataType DeQueue();
    DataType GetHead();
    bool Empty();
private:
    Node<DataType> *front, *rear;
};

// 构造函数，初始化空的链队列
template <typename DataType>
LinkQueue<DataType>::LinkQueue()
{
    Node<DataType> *s = nullptr;
    s = new Node<DataType>;
    s->next = nullptr;
    front = rear = s;       // 将队头指针和队尾指针都指向头结点 s
}

// 析构函数，释放链队列的存储空间
template <typename DataType>
LinkQueue<DataType>::~LinkQueue()
{    
    while (front != rear)
    {
        Node<DataType> *p = front;
        front = front->next;
        delete p;
    }    
}

// 入队操作，在链表尾部插入元素 x
template <typename DataType>
void LinkQueue<DataType>::EnQueue(DataType x)
{
    Node<DataType> *s = nullptr;
    s = new Node<DataType>;     // 申请结点 s
    s->data = x;
    s->next = nullptr;
    rear->next = s;             // 将结点插入到队尾
    rear = s;
}

//出队操作，将链表头部的结点删除并返回数据元素
template <typename DataType>
DataType LinkQueue<DataType>::DeQueue()
{
    DataType x;
    Node<DataType> *p = nullptr;
    if (rear == front)
        throw "下溢";
    p = front->next;
    x = p->data;            // 暂存队头元素
    front->next = p->next;  //摘链
    if (p->next == nullptr) //队列长度为 1
        rear = front;       //置空
    delete p;
    return x;
}

// 取链队列的队头元素
template <typename DataType>
DataType LinkQueue<DataType>::GetHead()
{
    return front->next->data;
}

// 判断链队列是否为空
template <typename DataType>
bool LinkQueue<DataType>::Empty()
{
    if (front == rear)
        return true;
    return false;
}