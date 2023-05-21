#include "Huffman.h"

int main()
{
    int w[] = {2, 3, 4, 5};
    HuffmanTree T{w, 4};
    T.Print();
    
    return 0;
}
