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
        cin >> i >> j;                  // 输入边依附的两个顶点的编号
        edge[i][j] = 1;
        edge[j][i] = 1;
    }
}

// 析构函数
template <typename DataType>
MGraph<DataType>::~MGraph() {}
