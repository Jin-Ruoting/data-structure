using namespace std;

const int StackSize = 10;	 // 定义栈的大小
template <typename DataType> // 定义模板类SeqStack
class SeqStack
{
public:
	SeqStack();			   // 构造函数，初始化一个空栈
	~SeqStack();		   // 析构函数
	void Push(DataType x); // 入栈操作，将元素 x 入栈
	DataType Pop();		   // 出栈操作，将栈顶元素弹出
	DataType GetTop();	   // 取栈顶操作（并不删除）
	bool Empty();		   // 判断栈是否为空
private:
	DataType data[StackSize]; // 存放栈元素的数组
	int top;				  // 栈顶元素在数组中的下标
};

// 构造函数，初始化一个空栈
template <typename DataType>
SeqStack<DataType>::SeqStack()
{
	top = -1;
}

// 析构函数
template <typename DataType>
SeqStack<DataType>::~SeqStack() {}

// 入栈操作，将元素 x 入栈
template <typename DataType>
void SeqStack<DataType>::Push(DataType x)
{
	if (top == StackSize - 1)
		throw "上溢";
	data[++top] = x;
}

// 出栈操作，将栈顶元素弹出
template <typename DataType>
DataType SeqStack<DataType>::Pop()
{
	if (top == -1)
		throw "下溢";
	return data[top--];
}

// 取栈顶操作（并不删除）
template <typename DataType>
DataType SeqStack<DataType>::GetTop()
{
	if (top == -1)
		throw "下溢";
	return data[top];
}

// 判断栈是否为空
template <typename DataType>
bool SeqStack<DataType>::Empty()
{
	if (top == -1)
		return true;
	return false;
}

const int MaxLen = 100; // 根据实际问题具体定义

// 两栈共享空间的顺序栈C++实现 : 如果需要同时使用具有相同数据类型的两个栈的时候，可以采用一个数组，让一个栈的栈底在该数组的起始端，另一个栈的栈底在数组的结尾，有利于节省空间。
typedef int DataType;
class BothSeqStack
{
public:
	BothSeqStack();				  // 构造函数，将两个栈分别初始化
	~BothSeqStack();			  // 析构函数
	void Push(int s, DataType x); // 入栈函数，将元素 x 压入栈 s
	DataType Pop(int s);		  // 出栈操作，对栈 i 执行出栈操作
	DataType GetTop(int s);		  // 取栈 i 的栈顶元素
	int Empty(int s);			  // 判断栈 i 是否为空
private:
	DataType data[MaxLen]; // 存放两个栈元素的数组
	int lsTop;			   // lsTop 是左栈顶指针
	int rsTop;			   // lsTop 是右栈顶指针
};

// 构造函数----顺序栈的初始化，初始化一个空的顺序栈只需将栈顶指针 top 置为-1
BothSeqStack::BothSeqStack()
{
	lsTop = -1;
	rsTop = MaxLen;
}

// 析构函数----顺序栈的销毁，顺序栈是静态存储分配，在顺序栈变量退出作用域时自动释放顺序栈所占存储单元。因此，顺序栈无需销毁，析构函数为空
BothSeqStack::~BothSeqStack() {}

// 入栈算法：①入左栈: s=1;  ②入右栈: s=2; 且x为入栈元素
void BothSeqStack::Push(int s, DataType x)
{
	if (rsTop == lsTop + 1)
		throw "栈满";
	if (s == 1) 			// 入左栈
		data[++lsTop] = x;
	else if (s == 2) 		// 入右栈
		data[--rsTop] = x;
	else
		cout << "该栈不存在！\n" << endl;
}

// 出栈算法：①出左栈：s=1; ②出右栈：s=2; 且x为入栈元素  成功返回1 否则返回0
DataType BothSeqStack::Pop(int s)
{
	DataType x;
	if (s == 1) 			// 出左栈
	{
		if (lsTop == -1)
			throw "栈已空！\n";
		x = data[lsTop--];
	}
	else if (s == 2) 		// 出右栈
	{
		if (rsTop == MaxLen)
			throw "栈已空！\n";
		x = data[rsTop--];
	}
	return x;
}

// 取栈操作----取栈顶元素只是将 lsTop 或 rsTop 位置的栈顶元素取出并返回，并不修改栈顶位置。
DataType BothSeqStack::GetTop(int s)
{
	DataType x;
	if (s == 1) 			// 左栈
	{
		if (lsTop == -1)
			throw "栈已空！\n";
		else
			x = data[lsTop];
	}
	else if (s == 2) 		// 右栈
	{
		if (rsTop == MaxLen)
			throw "栈已空！\n";
		else
			x = data[rsTop];
	}
	return x;
}

// 判断栈是否为空
int BothSeqStack::Empty(int s)
{
	if (s == 1) 			// 左栈
		if (lsTop == -1)
			return 1;
		else if (s == 2) 	// 右栈
			if (rsTop == MaxLen)
				return 1;
	return 0;
}