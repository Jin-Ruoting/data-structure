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
    return 0;
}