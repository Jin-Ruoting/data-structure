#include <iostream>
#include <string>
#include "sequential stack.h"
#include "linked stack.h"
#include "singly linked list.h"

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

/*

该方法需要传入数组长度 len，需要注意 sizeof() 会计算数组末尾的 '/0'，边界条件应为 len - 1

bool IsLegalSeq(char* seq, int len)
{
    SeqStack<char> s;  //创建一个空栈
    for(int i = 0; i < len - 1; i++)  //遍历操作序列
    {
        if(seq[i] == 'I')  //入栈操作
            s.Push(seq[i]);
        else if(seq[i] == 'O')  //出栈操作
        {
            if(s.Empty())  //栈为空，无法出栈
                return false;
            else
                s.Pop();  //出栈
        }
        else  //非法操作
            return false;
    }
    if(s.Empty())  //操作序列执行完毕后栈为空，操作序列合法
        return true;
    else  //操作序列执行完毕后栈非空，操作序列非法
        return false;
}
*/


// 3.1.04 (medium) 设单链表的表头指针为 L，结点结构由 data 和 next 两个域构成，其中 data 域为字符型。试设计算法判断该链表的全部 n 个字符是否中心对称。例如 xyx、xyyx 都是中心对称
bool is_symmetric(LinkList<char> *L, int n)
{
    SeqStack<char> s;
    Node<char> *p = L->GetFirst()->next;
    for (int i = 0; i < n / 2; i++)
    {
        s.Push(p->data);        // 将前半部分元素入栈
        p = p->next;
    }
    if (n % 2 == 1)             // 如果 n 为奇数，则跳过中间的结点
        p = p->next;
    while (p != nullptr)
    {
        if (p->data != s.Pop()) // 依次与栈顶元素比较
            return false;
        p = p->next;
    }
    return true;
}

// 3.1.05 (medium) 设有两个栈 s1、s2 都采用顺序栈方式，并共享一个存储区 [0,…,maxsize-1]，为了尽量利用空间，减少移除的可能，可采用栈顶相向、迎面增长的存储方式。试设计 s1、s2 有关入栈和出栈的操作算法
//见 sequential stack.h 中 class BothSeqStack

int main()
{
    //3.1.03
    string seq = "IIIOOIOO";
    int len = sizeof(seq) / sizeof(char); // 序列长度
    if (IsLegalSeq(seq))
        // if(IsLegalSeq(seq, len))
        cout << "The sequence is legal." << endl;
    else
        cout << "The sequence is illegal." << endl;
    
    //3.1.04
    char c[] = {'x', 'y', 'y', 'x'};
    int n = sizeof(c) / sizeof(char);
    LinkList<char> L{n, c};
    if (is_symmetric(&L, n))
        cout << "该链表是中心对称的" << endl;
    else
        cout << "该链表不是中心对称的" <<endl;

    //3.1.05
    int x;
	BothSeqStack S{};                   // 定义顺序栈遍历 S
	S.Push(1,4);
	cout<<S.GetTop(1)<<endl;
	S.Push(1,5);
	cout<<S.GetTop(1)<<endl;
	S.Push(2,8);
	cout<<S.GetTop(2)<<endl;
	S.Push(2,9);
	cout<<S.GetTop(2)<<endl;

    return 0;
}