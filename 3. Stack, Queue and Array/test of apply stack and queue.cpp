#include <iostream>

#include "application of stack and queue.h"

using namespace std;

int main()
{
    string str;
    cout<<"请输入一组括号：";
    cin>>str;
    BracketMacher M{str};
    int k = M.Match();
    if (k == 0)
        cout<<"正确匹配\n";
    else if (k == 1)
        cout<<"多左括号\n";
    else
        cout<<"多右括号\n";

    // 读取算术表达式
    char expr[100];
    cout << "Enter an expression: ";
    cin >> expr;

    // 调用判断括号平衡的函数
    if (areBracketsBalanced(expr))
        cout << "Brackets are balanced\n";
    else
        cout << "Brackets are not balanced\n";

    // 返回 0 表示程序正常结束
    return 0;
}