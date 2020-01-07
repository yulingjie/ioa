#include <gtest/gtest.h>
#include "intervaltree.h"
#include <vector>
#include <iostream>

class IntervalTreeTest:public ::testing::Test
{
    
    protected:
        void SetUp() override {

            {
                std::vector<int> vec = {0,3,6,10,5,8,15,23,8,9,16,21,25,30,17,19,26,26,19,20};
                //std::vector<int> vec = {0,3};
                for(int i = 0; i < vec.size(); )
                {
                    IntervalNode* node = IntervalTree::make_node(vec[i],vec[i+1]);
                    i += 2;
                    _it.insert(node);
                }
            }

            {
                std::vector<int> vec = {16,21,8,9,25,30};
                for(int i = 0;i < vec.size();)
                {
                    IntervalNode* node = IntervalTree::make_node(vec[i],vec[i+1]);
                    i += 2;
                    _it_rotate.insert(node);
                }
            }
        }

        IntervalTree _it;
        IntervalTree _it_rotate;
};

TEST_F(IntervalTreeTest,InsertTest)
{
    _it.bfs();
    EXPECT_EQ(0,0);
}
TEST_F(IntervalTreeTest, SearchTest)
{
    IntervalNode* node = _it_rotate.search(8);
   EXPECT_EQ(node->high(),9); 
}

TEST_F(IntervalTreeTest, LeftRotateTest)
{
    _it_rotate.bfs();
    IntervalNode* node = _it_rotate.search(16);
    _it_rotate.LeftRotate(node);
    _it_rotate.bfs();
    EXPECT_EQ(0,0);
}
TEST_F(IntervalTreeTest, RightRotateTest)
{
   _it_rotate.bfs();
   IntervalNode* node = _it_rotate.search(16);
   _it_rotate.RightRotate(node);
   _it_rotate.bfs();
   EXPECT_EQ(0,0);
}
TEST_F(IntervalTreeTest, IntervalSearchTest)
{
   _it.bfs(); 
   IntervalNode* node = IntervalTree::make_node(22,25);
   IntervalNode* rt = _it.IntervalSearch(node);
   EXPECT_EQ(rt->low(),15);
   EXPECT_EQ(rt->high(),23);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
