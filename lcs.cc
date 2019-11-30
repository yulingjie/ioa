#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int lcs_recur(const std::string& A, const std::string& B,
        const std::string::const_iterator ate,
        const std::string::const_iterator bte,
        std::string&rt);
int lcs_dp(const std::string&A, const std::string& B,std::string & rt);
int main(int argc, char*argv[])
{
    if(argc == 1)
    {
        std::cout<<argv[0]<<std::endl; 
    }
    std::string A = "immaculate";
    std::string B = "computer";
    std::string rt;
    //int len = lcs_recur(A,B,A.cend() -1,B.cend() -1,rt);
    int len = lcs_dp(A,B,rt);
    std::cout<<"len = "<<len <<" rt = "<<rt<<std::endl;
}
int lcs_dp(const std::string&A, const std::string& B, std::string &rt)
{
    
    /*std::vector<std::vector<int>> dp;
    for(size_t i =0; i <=A.length(); ++i)
    {
        std::vector<int> vec(B.length() ,0); 
        dp.push_back(vec);
        
    }
    */
    std::vector<int> dpp(B.length() +1, 0);
    std::vector<int> dpn(B.length() +1 ,0);
    std::vector<int>* pCur = &dpp;
    std::vector<int>* pNext = &dpn;
    int len = 0;
    for(int i = 0; i < (int)A.length(); ++i)
    {
        for(int j =0; j < (int)B.length(); ++j)
        {
            int j_index = j+1;
            if(A[i] == B[j])
            {
                (*pNext)[j_index] = (*pCur)[j_index-1] + 1;
                if((*pNext)[j_index] > len)
                {
                    len = (*pNext)[j_index];
                    rt += A[i];
                }
            }
            else
            {
                (*pNext)[j_index] =std::max((*pCur)[j_index],(*pNext)[j_index-1]);
            }
        }
        std::swap(pNext,pCur);
    }
    return rt.length();
    // find str
     
    /*
    int m = A.length(); 
    int n = B.length();
    int len = dp[m][n];
    std::string str="";
    while(m != 0 && n!=0)
    {
        if(n >0 && dp[m][n-1] == dp[m][n])
        {
            n--;
        }
        else if( m > 0 && dp[m-1][n] == dp[m][n])
        {
            m--;
        }
        else
        {
            str += A[m-1];
            m--;
            n--;
        }
        if(m <0 || n <0) break;
    }
    for(std::string::const_iterator ite = str.cend() -1;
            ite >= str.cbegin(); --ite)
    {
        rt += *ite;
    }

    return len;
    */
}
int lcs_recur(const std::string& A, const std::string&B, 
        const std::string::const_iterator ate,
        const std::string::const_iterator bte,
        std::string& rt)
{
    if(A.length() == 0 || B.length() == 0)
    {
        rt = "";
        return 0;
    }
    if(*ate == *bte)
    {
        int len = 0;
        if(ate > A.cbegin() && bte > B.cbegin())
        {
            len = lcs_recur(A,B,ate-1, bte-1,rt);
        }
        rt += *ate;
        return len + 1;
    }
    if(*ate != *bte)
    {
        int lenA = 0, lenB = 0;
        std::string rtA = "";
        std::string rtB = "";
        if(ate > A.cbegin())
        {
            lenA = lcs_recur(A,B,ate-1,bte, rtA);
        }
        if(bte > B.cbegin())
        {
            lenB = lcs_recur(A,B,ate,bte-1,rtB);
        }
        if(lenA >= lenB)
        {
            rt = rtA;
            return lenA;
        }
        else 
        {
            rt = rtB;
            return lenB;
        }
        /*else
          {
          std::cerr<<"error same len "<<lenA<<std::endl;
          return lenA;
          }
          */
    }

}

