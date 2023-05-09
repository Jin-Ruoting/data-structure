#include <iostream>

#include "pattern matching.h"

using namespace std;

int main()
{
    const char *str1 = "bacbbacabadababacambabacadbacabacasdsd";
    const char *str2 = "bacabaca";
    for (auto i : getNext(str2))
        cout << i<<" ";
    cout << endl
         << "start index is: " << KMP(str1, str2) << endl;
    return 0;
}