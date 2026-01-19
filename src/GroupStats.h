#ifndef GroupStats_h
#define GroupStats_h

#include <vector>

template <typename ElemType, typename KeyType, typename FuncType>
struct GrouInfo
{
    KeyType KeyType;
    size_t count;
    ElemType minElem;
    ElemType maxElem;
    FuncType funcType;
    double avg;
};



template <typename T>
T groupStats(arr, n, keyFunc, valueFunc)
{
    ;
};

#endif // GroupStats_h
