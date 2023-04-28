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