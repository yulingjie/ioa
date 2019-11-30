#include <iostream>
int pow(int a, int n)
{
    int p = 1;
    int pw = a;
    while(n> 0)
    {
        if(n &1) p = p*pw;
        pw = pw*pw;
        n = n>>1; 
    }
    return p;
}
int main(int argc, char* argv[])
{
    std::cout<<pow(2,4)<<std::endl;
}
