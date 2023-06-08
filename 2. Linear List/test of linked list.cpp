#include <iostream>
#include "singly linked list.h"
#include "double linked list.h"
#include "static linked list.h"

using namespace std;

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
    cout<<a<<endl;
    return 0;
}