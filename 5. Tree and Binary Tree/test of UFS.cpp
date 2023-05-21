#include <iostream>

#include "union find set.h"

using namespace std;

int main()
{
    char str[6] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int flag[6];
    UnionFind UF{str, 6};
    UF.Union('a', 'b');
    UF.Union('a', 'c');
    UF.Union('d', 'e');
    for (int i = 0; i < 6; i++)
    {
        flag[i] = UF.Find(str[i]);
        cout << flag[i] << ":" << str[i] << endl;
    }

    return 0;
}