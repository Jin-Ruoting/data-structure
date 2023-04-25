#include <iostream>
#include "sequential stack.h"
#include "linked stack.h"

using namespace std;

/*
*3.1.03 (medium)
*假设以 I 和 O 分别表示入栈和出栈操作。栈的初态和终态均为空，入栈和出栈的操作顺序可表示为仅由 I 和 O 组成的序列，可以操作的序列称为合法序列，否则称为非法序列
* 2) 通过对 1) 的分析，写出一个算法，判定所给的操作序列是否合法。若合法，返回 true，否则返回 false (假定被判定的操作序列已存入一维数组中)
*/
template<typename DataType>
bool f_3_1_03(char A[])
{
    int t = 1;
    SeqStack<int> s{};
}