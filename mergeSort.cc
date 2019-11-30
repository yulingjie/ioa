#include <iostream>
#include <vector>

void merge(std::vector<int>::iterator lo,
        std::vector<int>::iterator mi,
        std::vector<int>::iterator hi);
void mergeSort(std::vector<int>::iterator lo, std::vector<int>::iterator hi)
{
    if (hi - lo < 2) return;
    auto mi = (lo - hi) /2 + lo;
    mergeSort(lo,mi);
    mergeSort(mi,hi);
}
