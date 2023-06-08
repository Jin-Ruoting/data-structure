// 图的存储结构

const int MaxSize = 10;         // 图中最多顶点个数
// 邻接矩阵存储的类定义
template <typename DataType>
class MGraph
{
public:
    MGraph(DataType a[], int n, int e);
    ~MGraph();
private:
    DataType vertex[MaxSize];   // 存放图中顶点的数组
    int edge[MaxSize][MaxSize]; // 存放图中边的数组
    int vertexNum,edgeNum;      // 图的顶点数和边数
};

// 构造函数，建立无向图邻接矩阵
template <typename DataType>
MGraph<DataType>::MGraph(DataType a[], int n, int e)
{
    int i, j, k;
    vertexNum = n;
    edgeNum = e;
    for (i = 0; i < vertexNum; i++)     // 存储顶点
        vertex[i] = a[i];
    for (i = 0; i < vertexNum; i++)     // 初始化邻接矩阵
        for (j = 0; j < vertexNum; j++)
            edge[i][j] = 0;
    for (k = 0; k < vertexNum; k++)     // 依次输入每一条边
    {
        std::cin >> i >> j;                  // 输入边依附的两个顶点的编号
        edge[i][j] = 1;
        edge[j][i] = 1;
    }
}

// 析构函数
template <typename DataType>
MGraph<DataType>::~MGraph() {}

// 邻接表的存储结构

// 定义边表结点
struct EdgeNode
{
    int adjvex;     // 邻接点域
    EdgeNode *next;
};
// 定义顶点表结点
template <typename DataType>
struct VertexNode
{
    DataType vertex;
    EdgeNode *firstEdge;
};


//const int MaxSize = 10;
// 邻接表的实现
template <typename DataType>
class ALGraph
{
public:
    ALGraph(DataType a[], int n, int e);
    ~ALGraph();
private:
    VertexNode<DataType> adjlist[MaxSize];  // 存放顶点表的数组
    int vertexNum, edgeNum;                 // 图的顶点数和边数
};

// 构造函数，建立有向图邻接表
template <typename DataType>
ALGraph<DataType>::ALGraph(DataType a[], int n, int e)
{
    int i, j, k;
    EdgeNode *s = nullptr;              // 边表结点 s
    vertexNum = n;
    edgeNum = e;
    for (i = 0; i < vertexNum; i++)     // 输入顶点信息，初始化顶点表
    {
        adjlist[i].vertex = a[i];
        adjlist[i].firstEdge = nullptr;
    }
    for (k = 0; k < edgeNum; k++)       // 依次输入每一条边
    {
        std::cin >> i >> j;                  // 输入边所依附的两个顶点的编号
        s = new EdgeNode;               // 生成一个边表节点 s
        s->adjvex = j;
        s->next = adjlist[i].firstEdge; // 将结点 s 插入表头
        adjlist[i].firstEdge = s;
    }
}

// 析构函数，释放所有边表结点的存储空间
template <typename DataType>
ALGraph<DataType>::~ALGraph()
{
    EdgeNode *p = nullptr, *q = nullptr;
    for (int i = 0; i < vertexNum; i++)
    {
        p = q = adjlist[i].firstEdge;
        while (p != nullptr)
        {
            p = p->next;
            delete q;
            q = p;
        }        
    }    
}
