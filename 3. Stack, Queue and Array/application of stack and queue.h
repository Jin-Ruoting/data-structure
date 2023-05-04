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

/* 3.3.2 表达式求值
* 【问题】 表达式求值是编译程序的一个基本问题。设运算符有 +、-、*、/、# 和圆括号，其中 # 为表达式的定界符，对于任意给定的表达式进行求值运算，给出求值结果。
* 【想法】 表达式求值需要根据运算符的优先级来确定计算顺序。
* 因此，在求值过程中需要保存优先级较低的运算符以及没有参与计算的运算对象，并将当前运算符与已经扫描过的、尚未计算的运算符进行比较，以确定哪个运算符以及哪两个运算对象参与计算。
* 这需要两个栈来辅助完成：运算对象栈 OPND 和运算符栈 OPTR。
* 【算法】 设函数Compute 实现表达式求值，简单起见，假设运算对象均为一位十进制数，且表达式不存在语法错误，算法用伪代码描述如下：
     算法：Computer(str)
    输入：以字符串 str 存储的算数表达式
    输出：该表达式的值
        1. 将栈 OPND 初始化为空，将栈 哦普通人初始化为表达式的定界符 #；
        2. 从左至右扫描表达式的每一个字符执行下述操作：
            2.1 若当前字符是运算对象，则入栈 OPND；
            2.2 若当前字符是运算符且优先级比栈 OPTR 的栈顶运算符的优先级高，则入栈 OPTR，处理下一个字符；
            2.3 若当前字符是运算符且优先级比栈 OPTR 的栈顶运算符的优先级低，则从栈 OPND 出栈两个运算对象，从栈 OPTR 中出栈一个运算符进行运算，并将运算结果入栈 OPND，继续处理当前字符；
            2.4 若当前字符是运算符且优先级与栈 OPTR 的栈顶运算符的优先级相同，则将栈 OPTR 的栈顶运算符出栈，处理下一个字符；
        3. 输出栈 OPND 中的栈顶元素，即表达式的运算结果；
*/

// 将函数 Compute 定义为类 Expression 的成员函数，类 Expression 的成员变量 str 储存表达式，成员函数 Comp 比较当前扫描到的运算符和运算符栈 OPTR 的栈顶元素的优先级。主函数首先接收从键盘键入的表达式，然后定义对象变量 E，构造函数将该表达式加上定界符 '#'，再调用函数 Compute 计算表达式的值
class Expression
{
public:
    Expression(string str);
    ~Expression();
    int Compute();
private:
    int Comp(char str1, char str2);
    string str;
};

// 构造函数，接收键盘输入并加上定界符
Expression::Expression(string str)
{
    this->str = str + "#";
}

// 析构函数
Expression::~Expression() {}

// 计算表达式 str 的值
int Expression::Compute()
{
    char OPND[100];                         // 运算对象栈
    char OPTR[100];                         // 运算符栈
    OPTR[0] = '#';                          // 栈 OPTR 初始化为界定符
    int top1 = -1, top2 = 0;                // 初始化栈 OPND 和 OPTR
    int i, k, x, y, z, op;
    for (i = 0; str[i] != '\0';)            // 遍历每一个字符
    {
        if (str[i] >= 48 && str[i] <= 57)   // 0 的 ASCII 码为 48
            OPND[++top1] = str[i++] - 48;   // 将字符转换为数字压栈
        else
        {
            k = Comp(str[i], OPTR[top2]);
            if (k == 1)                     // str[i] 的优先级高
                OPTR[++top2] = str[i++];    // 将 str[i] 压入运算符栈
            else if (k == 1)                // str[i] 的优先级低
            {
                y = OPND[top1--];           // 从运算对象栈出栈两个元素
                x = OPND[top1--];
                op = OPTR[top2--];          // 从运算符栈出栈一个元素
                switch (op)                 // op 为运算符，进行对应的运算
                {
                case '+':
                    z = x + y;
                    break;
                case '-':
                    z = x - y;
                    break;
                case '*':
                    z = x * y;
                    break;
                case '/':
                    z = x / y;
                    break;
                default:
                    break;
                }
                OPND[++top1] = z;           // 运算结果入运算对象栈
            }
            else                            // str[i] 与运算符栈的栈顶元素优先级相同
            {
                top2--;                     // 匹配 str[i]，扫描下一个字符
                i++;
            }
        }
    }
    return OPND[top1];                      // 运算对象栈的栈顶元素即为运算结果
}

// 比较 str1 和 str2 的优先级，1 表示 str1 高；0 表示相同；-1 表示 str1 低
int Expression::Comp(char str1, char str2)
{
    switch (str1)
    {
    case '+':
    case '-':
        if (str2 == '(' || str2 == '#')
            return 1;
        else
            return -1;
        break;
    case '*':
    case '/':
        if (str2 == '*' || str2 == '/')
            return -1;
        else
            return 1;
        break;
    case '(':
        return 1;
        break;
    case ')':
        if (str2 == '(')
            return 0;
        else
            return -1;
        break;
    default:
        break;
    }
}

// 3.3.01 (medium) 假设一个算数表达式中包含圆括号、方括号和花括号 3 种类型的括号，编写一个算法来判别表达式种的括号是否配对，以字符 "\0" 作为算术表达式的结束符
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