#include <iostream>
#include <vector>
std::vector<int>::iterator bubble(std::vector<int>::iterator lo, std::vector<int>::iterator hi);
void bubbleSort(std::vector<int>::iterator lo, std::vector<int>::iterator hi)
{
    while(lo < (hi=bubble(lo,hi)));
}
std::vector<int>::iterator bubble(std::vector<int>::iterator lo, std::vector<int>::iterator hi)
{
    std::vector<int>::iterator ite = lo;
    while(++lo < hi)
    {
        if(*(lo-1) > *lo)
        {
            ite = lo;
            std::swap(*(lo-1),*lo);
        }
    }
    return ite;
}

int main(int argc,char* argv[])
{
    std::vector<int> vec={1,2,5,2,3,4,2,6,2,18,53,99,2,333};
    bubbleSort(vec.begin(),vec.end());
    for(std::vector<int>::iterator ite = vec.begin(); ite != vec.end();++ite)
    {
        std::cout<<*ite <<" ";
    }
    std::cout<<std::endl;
}
