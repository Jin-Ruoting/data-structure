#include <iostream>
#include <string>

#include "sequential stack.h"

using namespace std;

//括号匹配问题
class BracketMacher
{
public:
    BracketMacher(string str);
    ~BracketMacher();
    bool Match();
private:
    string str;
};

BracketMacher::BracketMacher(string str)
{
    this->str = str;
}

BracketMacher::~BracketMacher() {}

bool BracketMacher::Match()
{
    char S[10];
    int i, top = -1;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ')')
            if (top > -1)
                top--;
            else
                return false;
        else if (str[i] == '(')
            S[++top] = str[i];
    }
    if (top == -1)
        return false;
    else
        return true;
}

// 判断三种类型括号是否平衡的函数
bool areBracketsBalanced(char expr[])
{
    // 创建一个字符类型的栈
    SeqStack<char> s;
    char x;

    // 遍历表达式中的字符
    for (int i = 0; expr[i] != '\0'; i++)
    {
        // 如果遇到左括号，将其压入栈中
        if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{')
        {
            s.Push(expr[i]);
            continue;
        }

        // 如果遇到右括号，检查栈是否为空
        if (s.Empty())
            return false;

        // 检查栈顶元素是否与当前右括号匹配
        switch (expr[i])
        {
        case ')':
            x = s.GetTop();
            s.Pop();
            if (x == '{' || x == '[')
                return false;
            break;

        case ']':
            x = s.GetTop();
            s.Pop();
            if (x == '(' || x == '{')
                return false;
            break;

        case '}':
            x = s.GetTop();
            s.Pop();
            if (x == '(' || x == '[')
                return false;
            break;
        }
    }

    // 检查栈是否为空，如果为空，则表达式中的所有括号都已配对
    return (s.Empty());
}