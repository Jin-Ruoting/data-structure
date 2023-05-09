#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

// BF 算法进行模式匹配
int BF(char S[], char T[])
{
    int start = 0;                              // 主串从下标 0 开始第一趟匹配
    int i = 0, j = 0;                           // 设置比较的起始下标
    while ((S[i] != '\0') && (T[j] != '\0'))
    {
        if (S[i] == T[j])
        {
            i++;
            j++;
        }
        else                                    // i 和 j 分别回溯
        {
            start++;
            i = start;
            j = 0;
        }
    }
    if (T[j] == '\0')
        return start + 1;                       // 返回本趟匹配的起始位置 + 1
    else
        return 0;
}

// KMP 算法中求 next 数组的函数
vector<int> getNext(const char *str)
{
    int len = strlen(str);                  // 字符串长度
    vector<int> next(len, 0);               // 保存结果，next[0]=0
    for(int i = 1; i < len; i++)
    {
        int k = next[i - 1];                // k 表示需要比较的位置，初始值为 next[i - 1]
        while(k > 0 && str[i] != str[k])    // 比较，若不相等则继续分割，直到相等或为0(即不含相同部分)
            k = next[k - 1];
        if(str[i] == str[k])                // 若相等，则 next[i] = k + 1，否则为0，其中 k 为索引
            k++;
        next[i] = k;                        // 更新 next[i]
    }
    return next;
}

// KMP 算法进行模式匹配
int KMP(const char *str1, const char *str2)
{
    vector<int> next = getNext(str2);           // 获得 str2 的 next 数组
    int k = 0;                                  // 记录当前已匹配 str2 的索引
    int res = -1;                               // 保存匹配的字符串起始位置，若不存在，返回-1
    for(int i = 0; i < (int)strlen(str1); i++)  // 第 i 轮匹配
    {
        while(k > 0 && str1[i] != str2[k])      // str1的第i个与str2的第k个字符进行比较，若不同，则k=next[k-1]，直到k为0或相等为止
            k = next[k - 1];
        if(str1[i] == str2[k])                  // 若相等，更新k
            k++;
        if(k == (int)strlen(str2))              // 若找到完全匹配
        {
            res = i - k + 1;                    // 保存匹配的字符串起始位置，此时根据需要可用容器保存多个结果
            k = next[k - 1];                    // 进行下一轮匹配，此处根据需要可去掉
        }
    }
    return res;
}