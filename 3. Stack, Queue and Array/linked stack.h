template<typename DataType>
class LinkStack
{
private:
    Node<DataType> *top;
public:
    LinkStack();
    ~LinkStack();
    void Push(DataType x);
    DataType Pop();
    DataType GetTop();
    int Empty();
};

template<typename DataType>
LinkStack<DataType>::LinkStack()
{
}

template<typename DataType>
LinkStack<DataType>::~LinkStack()
{
}
