//定义单链表结构体
/*
template <typename DataType>
struct Node
{
    DataType data;
    Node<DataType> *next;
};
*/
#include "singly linked list.h"

//带头结点的栈链类
template<typename DataType>
class LinkStack
{
public:
    LinkStack();
    ~LinkStack();
    void Push(DataType x);
    DataType Pop();
    DataType GetTop();
    bool Empty();
private:
    Node<DataType> *top;
};

//链栈类 LinkStack 的构造函数，初始化一个空栈链
template<typename DataType>
LinkStack<DataType>::LinkStack()
{
    top = new Node<DataType>;   //生成头结点
    top->next = nullptr;        //头结点的指针域置空
}

//链栈类 LinkStack 的析构函数，释放栈链各结点的存储空间
template<typename DataType>
LinkStack<DataType>::~LinkStack()
{
    Node<DataType> *p;
    while (top != nullptr)      //遍历链栈，释放每一个结点
    {
        p = top;                //暂存被释放结点
        top = top->next;        //top 指向被释放节点的下一个结点
        delete p;
    }    
}

//链栈类 LinkStack 的入栈操作，将元素 x 入栈
template<typename DataType>
void LinkStack<DataType>::Push(DataType x)
{
    Node<DataType> *s = nullptr;
    s = new Node<DataType>;
    s->data = x;
    s->next = top;
    top = s;
}

//栈链类 LInkStack 的出栈操作，将栈顶元素出栈并返回元素的数据域
template<typename DataType>
DataType LinkStack<DataType>::Pop()
{
    Node<DataType> *p = nullptr;
    DataType x;
    if (top == nullptr)
        throw "下溢";
    p = top;            //暂存结点
    top = top->next;    //摘链
    x = p->data;
    delete p;
    return x;
}

//栈链类 LinkStack 的非破坏性取栈顶元素操作
template<typename DataType>
DataType LinkStack<DataType>::GetTop()
{
    if (top == nullptr)
        throw "空栈";
    return top->data;
}

//栈链类  LinkStack 的判空操作
template<typename DataType>
bool LinkStack<DataType>::Empty()
{
    if (top == nullptr)
        return true;
    return false;
}