#include<iostream>
int power(int a,int n)
{
    int pow = 1; int p =a;
    while( 0 < n){
        if( n & a) pow *= p;
        n >>=1; p*=p;
    }
    return pow;
}
int main(int argc, char* argv[])
{
   int rt =  power(3,10);
    std::cout<<"rt = "<<rt<<std::endl;
}
