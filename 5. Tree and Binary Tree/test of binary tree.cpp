#include "Binary Tree.h"

#include <iostream>

using namespace std;

// 5.2.05 (medium) 已知一颗二叉树按顺序存储结构进行存储，设计一个算法，求编号分别为 i 和 j 的两个结点的最近的公共祖先结点的值
template <typename DataType>
DataType GetLowestCommonAncestor(SeqBiTree<DataType>& tree, int i, int j)
{
    i = i - 1;                              // 将结点编号转换为数组下标
    j = j - 1;
    int index_i = i * 2 + 1;                // 结点 i 左儿子的下标
    int index_j = j * 2 + 1;                // 结点 j 左儿子的下标
    while (index_i != 0 && index_j != 0)    // 寻找结点 i 和结点 j 的共同祖先，直到它们的祖先相同或达到根节点
    {
        index_i = (index_i - 1) / 2;        // 父节点的下标
        index_j = (index_j - 1) / 2;
    }
    if (i == j)                             // 如果结点 i 和结点 j 相同，那么他们自己就是它们的共同祖先
        return tree.data[i];
    while (index_i != index_j)              // 如果结点 i 和结点 j 的共同祖先不是它们自己，那么它们的共同祖先就是它们祖先中的最近公共祖先
    {
        if (index_i > index_j)
            index_i = (index_i - 1) / 2;
        else
            index_j = (index_j - 1) / 2;
    }
    return tree.data[index_i];
}
template <typename DataType>
DataType Comm_Ancestor(SeqBiTree<DataType> T,int i, int j)
{
    if (T.data[i] != '\0' && T.data[j] != '\0') // 结点存在
    {
        while (i != j)                          // 两个编号不同时循环
        {
            if (i > j)
                i = i/2;                        // 向上找 i 的祖先
            else
                j = j/2;                        // 向上找 j 的祖先
        }
        return T.data[i];
    }    
}

int main()
{
    SeqBiTree<char> tree = {{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}, 26};
    int i = 2;
    int j = 8;
    char ancestor = GetLowestCommonAncestor(tree, i, j);
    cout << "The lowest common ancestor of node " << i << " and node " << j << " is " << ancestor << endl;

    return 0;
}