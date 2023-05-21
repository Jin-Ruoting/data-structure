// 数组元素的结点结构定义
struct ElemType
{
    char data;      // 假定并查集的元素为字符型
    int parent;     // 游标，该元素的双亲在数组中的下标
};

const int MaxSize = 100;        // 集合元素最大数量

// 并查集类的定义
class UnionFind
{
public:
    UnionFind(char ch[], int n);
    ~UnionFind();
    int Find(char x);
    void Union(char x, char y);
private:
    ElemType elem[MaxSize];     // 双亲表示法存储
    int length;                 // 集合的元素个数
};

// 构造函数，每个元素构成一个子集
UnionFind::UnionFind(char ch[], int n)
{
    length = n;
    for (int i = 0; i < length; i++)
    {
        elem[i].parent = -1;    // 将 parent 初始化为 -1
        elem[i].data = ch[i];   // 将 n 个元素存储到 data 域
    }    
}

// 析构函数，采用静态存储分配，为空
UnionFind::~UnionFind() {}

// 查找元素 x 所在子树的根结点下标
int UnionFind::Find(char x)
{
    int i;
    for (i = 0; i < length; i++)    // 查找 x 的双亲，直到根结点
        if (elem[i].data == x)
            break;
    while (elem[i].parent != -1)    // 查找元素所在树的根结点的下标
        i = elem[i].parent;
    return i;
}

// 合并元素 x 和 y 所在子集
void UnionFind::Union(char x, char y)
{
    int vex1 = Find(x);             // 查找元素 x 所在集合根结点下标
    int vex2 = Find(y);             // 查找元素 y 所在集合根结点下标
    if (vex1 != vex2)
        elem[vex2].parent = vex1;   // 合并
}