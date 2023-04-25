#include <iostream>
#include <string>
#include "sequential stack.h"
#include "linked stack.h"

using namespace std;

/*
 *3.1.03 (medium)
 *假设以 I 和 O 分别表示入栈和出栈操作。栈的初态和终态均为空，入栈和出栈的操作顺序可表示为仅由 I 和 O 组成的序列，可以操作的序列称为合法序列，否则称为非法序列
 * 2) 通过对 1) 的分析，写出一个算法，判定所给的操作序列是否合法。若合法，返回 true，否则返回 false (假定被判定的操作序列已存入一维数组中)
 */
bool IsLegalSeq(string seq)
{
    SeqStack<char> stack;       // 创建字符类型的顺序栈

    for (int i = 0; i < seq.length(); i++)
    {
        if (seq[i] == 'I')
            stack.Push(seq[i]); // 入栈
        else if (seq[i] == 'O')
        {
            if (stack.Empty())
                return false;   // 栈为空时，无法执行出栈操作，非法操作序列
            stack.Pop();        // 出栈
        }
        else
            return false;       // 非法操作序列
    }

    if (stack.Empty())
        return true;            // 操作序列执行完毕后栈为空，合法操作序列
    else
        return false;           // 栈不为空，非法操作序列
}

int main()
{
    string seq = "IIIOOIOO";
    if (IsLegalSeq(seq))
        cout << "The sequence is legal." << endl;
    else
        cout << "The sequence is illegal." << endl;
    return 0;
}