// 图的存储结构

const int MaxSize = 10;         // 图中最多顶点个数
int visited[MaxSize] = {0};     // 全局数组变量 visited 初始化
// 邻接矩阵存储的类定义
template <typename DataType>
class MGraph
{
public:
    MGraph(DataType a[], int n, int e);
    ~MGraph();
    void DFTraverse(int v);
    void BFTraverse(int v);
private:
    DataType vertex[MaxSize];   // 存放图中顶点的数组
    int edge[MaxSize][MaxSize]; // 存放图中边的数组
    int vertexNum,edgeNum;      // 图的顶点数和边数
};

// 构造函数，输入顶点的数据信息 a[n]，顶点个数 n，边的个数 e，建立无向图邻接矩阵
template <typename DataType>
MGraph<DataType>::MGraph(DataType a[], int n, int e)
{
    int i, j, k;
    vertexNum = n;                      // 存储图的顶点个数
    edgeNum = e;                        // 存储图的边的个数
    for (i = 0; i < vertexNum; i++)     // 将顶点信息存储在一维数组 vertex 中
        vertex[i] = a[i];
    for (i = 0; i < vertexNum; i++)     // 初始化邻接矩阵 edge
        for (j = 0; j < vertexNum; j++)
            edge[i][j] = 0;
    for (k = 0; k < vertexNum; k++)     // 依次输入每一条边
    {
        std::cin >> i >> j;             // 输入边依附的两个顶点的编号
        edge[i][j] = 1;
        edge[j][i] = 1;
    }
}

// 析构函数
template <typename DataType>
MGraph<DataType>::~MGraph() {}

// 深度优先遍历图，输入顶点的编号 v
template <typename DataType>
void MGraph<DataType>::DFTraverse(int v)
{
    std::cout << vertex[v];                     // 访问顶点 v
    visited[v] = 1;                             // 修改顶点 v 的标志 visited[i] = 1
    for (int j = 0; j < vertexNum; j++)         // 遍历 v 的邻接点 j
        if (edge[v][j] == 1 && visited[j] == 0) // 结点存在且未被访问
            DFTraverse(j);                      // 递归执行深度优先算法
}

// 广度优先遍历图，输入顶点的编号 v
template <typename DataType>
void MGraph<DataType>::BFTraverse(int v)
{
    int w, j, Q[MaxSize];       // 采用顺序队列
    int front = -1, rear = -1;  // 初始化队列 Q
    std::cout << vertex[v];     // 访问顶点 v
    visited[v] = 1;             // 修改访问标志位
    Q[++rear] = v;              // 顶点 v 入队列 Q
    while (front != rear)       // 队列非空
    {
        w = Q[++front];         // 将队头元素出队并送到 v 中
        for (j = 0; j < vertexNum; j++)
            if (edge[w][j] == 1 && visited[j] == 0)
            {
                std::cout << vertex[j];
                visited[j] = 1;
                Q[++rear] = j;
            }
    }
}

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


// 邻接表的实现
template <typename DataType>
class ALGraph
{
public:
    ALGraph(DataType a[], int n, int e);
    ~ALGraph();
    void DFTraverse(int v);
    void BFTraverse(int v);
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
        std::cin >> i >> j;             // 输入边所依附的两个顶点的编号
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

// 深度优先遍历图，输入顶点的序号 v
template <typename DataType>
void ALGraph<DataType>::DFTraverse(int v)
{
    int j;
    EdgeNode *p = nullptr;
    std::cout << adjlist[v].vertex;
    visited[x] = 1;
    p = adjlist[v].firstEdge;       // 工作指针 p 指向顶点 v 的边表
    while (p != nullptr)            // 依次搜索顶点 v 的邻接点 j
    {
        j = p->adjvex;
        if (visited[j] == 0)
            DFTraverse(j);
        p = p->next;
    }    
}

// 广度优先遍历图，输入顶点的编号 v
template <typename DataType>
void ALGraph<DataType>::BFTraverse(int v)
{
    int w, j, Q[MaxSize];           // 采用顺序队列
    int front = -1, rear = -1;      // 初始化队列
    EdgeNode *p = nullptr;          // 初始化工作指针 p
    std::cout << adjlist[v].vertex;
    visited[v] = 1;
    Q[++rear] = v;                  // 被访问顶点入队
    while (front = rear)            // 当队列非空时
    {
        w = Q[++front];
        p = adjlist[w].firstEdge;   // 工作指针 p 指向顶点 v 的边表
        while (p != nullptr)
        {
            j = p->adjvex;
            if (visited[j] == 0)
            {
                std::cout << adjlist[j].vertex;
                visited[j] = 1;
            }
            p = p->next;
        }        
    }    
}