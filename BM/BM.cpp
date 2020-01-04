
#include <iostream>
#include <algorithm>



void make_delta1(const char* pat, int patlen, int* delta1)
{	
	for(int i = 0; i < 256; ++i)
	{
		delta1[i] = patlen;
	}
	for(int i = 0; i < patlen; ++i)
	{
		delta1[(int)pat[i]] = patlen - i -1; // we start index from zero	
	}
}

int suffix_length(const char* pat, int patlen,int pos)
{
	int i = 0;
	while( i <= pos 
			&& pat[pos-i] == pat[patlen-i-1])
	{
			++i;
			
	}
	return i;
}



void make_delta2(const char* pat, int patlen, int* delta2)
{	
	// 默认正在p处不匹配时，直接移动到+1的位置进行新的匹配，
	// 最慢的
	// 默认值
	for(int p = 0; p < patlen; ++p)
	{
		delta2[p] = patlen - p ;
	}
	for(int p = 0; p < patlen-1;++p)
	{
		int slen = suffix_length(pat, patlen, p);
		
		if(p - slen < 0 || pat[p-slen] != pat[patlen-slen])
		{
			delta2[patlen-slen -1] = patlen - p -1 + slen;
			//std::cout<<" set delta2 "<<patlen-slen -1 << " = "<<patlen-p-1 + slen<<std::endl;
		}
	}

}

int match(const char* txt, int txtLen, const char* pat, int patlen)
{
		
		int delta1[256];
		make_delta1(pat, patlen, delta1);
		
		int* delta2 = new int[patlen];
		make_delta2(pat, patlen, delta2);
		
		int j = patlen-1;
		int i = patlen - 1;
		while( i < txtLen)
		{
			int j = patlen-1;
			//std::cout<<" i = "<<i<<" j = "<<j<<std::endl;
			while( j >= 0)
			{
				//std::cout<<" compare "<<txt[i] << " and "<<pat[j]<<std::endl;
				if(txt[i] == pat[j])
				{
					j--;
					i--;
				}
				else{
					break;
				}
			}
			if(j <0)
			{
				return i + 1;
			}
			//std::cout<<" delta1 = "<<delta1[txt[i]] << " delta2 = "<<delta2[j]<<std::endl;
			i = i + std::max(delta1[txt[i]],delta2[j]);
		}
		return -1;
}