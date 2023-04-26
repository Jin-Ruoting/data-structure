const int QueueSize = 100;      // 队列规模
// 循环队列类
template <typename DataType>
class CirQueue
{
public:
    CirQueue();
    ~CirQueue();
    void EnQueue(DataType x);
    DataType DeQueue();
    DataType GetHead();
    bool Empty();
private:
    DataType data[QueueSize];   // 存放队列元素的数组
    int front, rear;            // 游标，队头和队尾指针
};

// 构造函数，初始化一个空的循环队列
template <typename DataType>
CirQueue<DataType>::CirQueue()
{
    rear = front = QueueSize - 1;
}

// 析构函数，自动释放内存单元，无需手动销毁
template <typename DataType>
CirQueue<DataType>::~CirQueue() {}

// 入队操作，将元素 x 入队
template <typename DataType>
void CirQueue<DataType>::EnQueue(DataType x)
{
    if ((rear + 1) % QueueSize == front)
        throw "上溢";
    rear = (rear + 1) % QueueSize;      // 队尾指针循环 +1
    data[rear] = x;                     // 在队尾插入元素
}

// 出队操作，返回队头元素
template <typename DataType>
DataType CirQueue<DataType>::DeQueue()
{
    if (rear == front)
        throw "下溢";
    int x = front;                      // 存储队头下标
    front = (front + 1) % QueueSize;    // 队头指针循环 +1
    return data[x];                     // 返回出队前队头元素
}

// 读取队头元素操作
template <typename DataType>
DataType CirQueue<DataType>::GetHead()
{
    if (rear == front)
        throw "下溢";
    return data[(front + 1) % QueueSize];   // 不修改队头指针
}

// 判空操作
template <typename DataType>
bool CirQueue<DataType>::Empty()
{
    if (front == rear)  //队空
        return true;
    return false;
}