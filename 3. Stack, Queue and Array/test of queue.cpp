#include <iostream>

#include "linked queue.h"
#include "sequential queue.h"

using namespace std;

// 3.2.01 (easy) 若希望循环队列中的元素都能得到利用，则需设置一个标志域 tag，并以 tag 的值为 0 或 1 来区分队头指针 front 和队尾指针 rear 相同时的队列状态是“空”还是“满”。试编写与此结构相应的入队和出队算法

//进队时置 tag 为 1，出队时置 tag 为 0，因为只有入队操作可能导致队满，也只有出队操作可能导致队空，初始化队列时置 tag = 0; front = rear = 0;

// 带 tag 标志位的入队算法
template <typename DataType>
void EnQueue(CirQueue<DataType> &Q, DataType x)
{
    int tag;                            // tag 标志区分队列状态，此处 tag 应为 CirQueue 类的成员，为方便实现在这里临时设置变量
    if (Q.front == Q.rear && tag == 1)
        throw "队满";
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % QueueSize;
    tag = 1;                            // 置 tag 标志为 1，只有经过入队操作后队列才有可能为满
}
// 带 tag 标志位的出队算法
template <typename DataType>
DataType DeQueue(CirQueue<DataType> &Q)
{
    int tag;
    if (Q.front == Q.rear && tag == 0)
        throw "队空";
    DataType x = Q.data[Q.front];
    Q.front = (Q.front + 1) % QueueSize;
    tag = 0;
}

/*
* 3.2.04 [2019] 
* 请设计一个队列，要求满足：
* 初始时队列为空；
* 入队时，允许增加队列占用空间；
* 出队后，出队元素所占用的空间可重复使用，即整个队列所占用的空间只增不减；
* 入队操作和出队操作的时间复杂度始终保持为 O(1)。
* 请回答下列问题：
* 1) 该队列是应选择链式存储结构，还是应选择顺序存储结构？
* 2) 画出队列的初始状态，并给出判断队空和队满的条件。
* 3) 画出第一个元素入队后的队列状态。
* 4) 给出入队操作和出队操作的基本过程。
*/

//链式、初始化头结点和尾结点