#include <gtest/gtest.h>
#include <cstring>
#include "BM.h"



TEST(BMTest, SuffixLengthTest)
{
	const char* pat = "abcbcabc";
	int patlen = strlen(pat);
	EXPECT_EQ(patlen,8);
	
	int s0 = suffix_length(pat, patlen, 0);
	EXPECT_EQ(s0,0);
	int s1 = suffix_length(pat,patlen,1);
	EXPECT_EQ(s1,0);
	int s2 = suffix_length(pat, patlen,2);
	EXPECT_EQ(s2,3);
	
	int s3 = suffix_length(pat, patlen,3);
	EXPECT_EQ(s3,0);
	
	int s4 = suffix_length(pat,patlen,4);
	EXPECT_EQ(s4, 2);
	
	int s5 = suffix_length(pat, patlen, 5);
	EXPECT_EQ(s5,0);
	
	int s6 = suffix_length(pat, patlen, 6);
	EXPECT_EQ(s6,0);
}
TEST(BMTest, MakeDeltaTest)
{
	int delta1[256];
	const char* pat = "abcbcabc";
	int patlen = strlen(pat);
	
	make_delta1(pat, patlen, delta1);
	int delta_c = delta1[(int)'c'];
	EXPECT_EQ(delta_c , 0);
	
	int delta_b = delta1[(int)'b'];
	EXPECT_EQ(delta_b,1);
	
	int delta_a = delta1[(int)'a'];
	EXPECT_EQ(delta_a,2);
	
	int delta_o = delta1[(int)'o'];
	EXPECT_EQ(delta_o, 8);
}
TEST(BMTest, MakeDelta2Test)
{
	const char* pat = "abcbcabc";
	int patlen = strlen(pat);
	int* delta2 = new int[patlen];
	make_delta2(pat, patlen, delta2);
	int delta_7 = delta2[7];
	EXPECT_EQ(delta_7,1);
	int delta_6 = delta2[6];
	EXPECT_EQ(delta_6,2);
	int delta_5 = delta2[5];
	EXPECT_EQ(delta_5,5);
	
	for(int i = 0; i < patlen; ++i)
	{
		std::cout<<" "<<delta2[i];
	}
	std::cout<<std::endl;
}
TEST(BMTest, MatchTest)
{
	const char* pat = "abcbcabc";
					       //"abcbcabc"
	const char* txt = "dsdfgabcbcabcdspsd";
	
	int rt = match(txt,strlen(txt),pat, strlen(pat));
	EXPECT_EQ(rt,5);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
}