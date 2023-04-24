#include <iostream>
#include "sequential list.h"

using namespace std;

template <typename DataType>
void deleteSame(SeqList<DataType> &L)
{
    if (L.Length() == 0)
        throw "该表为空";
    int i = 0, j = 1;
    for (; j < L.Length(); j++)
        if (L.Data(i) != L.Data(j))
            L.ChangeData(++i, L.Data(j));
    L.ChangeLength(i + 1);
}

template <typename DataType>
void merge(SeqList<DataType> A, SeqList<DataType> B, SeqList<DataType> &C)
{
    if (A.Length() + B.Length() > C.MaxSize)
        throw "新表最大长度过短！";
    int i = 0, j = 0, k = 0;
    while (i < A.Length() && j < B.Length())
    {
        if (A.Data(i) <= B.Data(j))
            C.ChangeData(k++, A.Data(i++));
        else
            C.ChangeData(k++, B.Data(j++));
    }
    while (i < A.Length())
        C.ChangeData(k++, A.Data(i++));
    while (j < B.Length())
        C.ChangeData(k++, B.Data(j++));
    C.ChangeLength(k);
    C.PrintList();
}

// 二分查找元素x在有序线性表a中的位置
template <typename DataType>
int binarySearch(SeqList<DataType> &a, int n, int x)
{
    int low = 0, high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (a.Data(mid) == x)
            return mid;
        else if (a.Data(mid) < x)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1; // 没有找到
}

// 将线性表a中下标为i和i+1的元素交换
template <typename DataType>
void swap(SeqList<DataType> &a, int i)
{
    DataType temp = a.Data(i);
    a.ChangeData(i, a.Data(i + 1));
    a.ChangeData(i + 1, temp);
}

// 在有序顺序表a中查找元素x，若找到则将其与后继元素交换，否则插入x并保持有序
template <typename DataType>
void searchAndSwapOrInsert(SeqList<DataType> &a, int n, int x)
{
    int index = binarySearch(a, n, x);
    if (index != -1)
    {
        // 找到了x，将其与后继元素交换
        if (index < n - 1)
        {
            swap(a, index);
        }
    }
    else
    {
        // 没有找到x，插入x并保持有序
        int i = n - 1;
        while (i >= 0 && a.Data(i) > x)
        {
            a.ChangeData(i + 1, a.Data(i));
            i--;
        }
        a.ChangeLength(n + 1);
        a.ChangeData(i + 1, x);
    }
}

int main()
{
    int a[] = {1, 3, 5, 7, 9};
    int n = sizeof(a) / sizeof(a[0]);
    int x = 4;
    SeqList<int> A{a, 5};
    searchAndSwapOrInsert(A, n, x);
    A.PrintList();

    int r[11] = {1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 5};
    SeqList<int> L{r, 11};
    cout << "当前线性表的数据为：";
    L.PrintList();
    try
    {
        deleteSame(L);
        cout << "删除重复元素后数据为：";
        L.PrintList();
    }
    catch (const char *str)
    {
        cout << str << endl;
    }
    return 0;
}