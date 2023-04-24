const int StackSize = 10;       //定义栈的大小
template<typename DataType>     //定义模板类SeqStack
class SeqStack
{
public:
    SeqStack();                 //构造函数，初始化一个空栈
    ~SeqStack();                //析构函数
    void Push(DataType x);      //入栈操作，将元素 x 入栈
    DataType Pop();             //出栈操作，将栈顶元素弹出
    DataType GetTop();          //取栈顶操作（并不删除）
    bool Empty();                //判断栈是否为空
private:
    DataType data[StackSize];   //存放栈元素的数组
    int top;                    //栈顶元素在数组中的下标
};

//构造函数，初始化一个空栈
template<typename DataType>
SeqStack<DataType>::SeqStack()
{
    top = -1;
}

//析构函数
template<typename DataType>
SeqStack<DataType>::~SeqStack() {}

//入栈操作，将元素 x 入栈
template<typename DataType>
void SeqStack<DataType>::Push(DataType x)
{
    if (top == StackSize - 1)
        throw "上溢";
    data[++top] = x;
}

//出栈操作，将栈顶元素弹出
template<typename DataType>
DataType SeqStack<DataType>::Pop()
{
    if (top == -1)
        throw "下溢";
    return data[top--];
}

//取栈顶操作（并不删除）
template<typename DataType>
DataType SeqStack<DataType>::GetTop()
{
    if (top == -1)
        throw "下溢";
    return data[top];
}

//判断栈是否为空
template<typename DataType>
bool SeqStack<DataType>::Empty()
{
    if (top == -1)
        return true;
    return false;
}