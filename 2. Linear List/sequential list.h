using namespace std;

const int MaxSize = 100;

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
    DataType Data(int i);
    void ChangeLength(int i);
    void ChangeData(int i, DataType x);
private:
    DataType data[MaxSize];
    int length;
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
DataType SeqList<DataType>::Data(int i)
{
    return data[i];
}

template <typename DataType>
void SeqList<DataType>::ChangeLength(int i)
{
    length = i;
}

template <typename DataType>
void SeqList<DataType>::ChangeData(int i, DataType x)
{
    data[i] = x;
}