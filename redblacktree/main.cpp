#include <gtest/gtest.h>
#include "redblacktree.h"
#include <vector>
#include <iostream>

class RedBlackTreeTest:public ::testing::Test
{
    protected:
        void SetUp() override{

            std::vector<int> vec = {1,2,3};
            for(int i = 0; i < vec.size(); ++i)
            {
                BinNode<int> * node = BinTree<int>::make_node(vec[i]);

                _rb.insert(node);
            }

            std::vector<int> vec_delete_case3 = {1,2,3,10,8};
            for(int i =0; i < vec_delete_case3.size(); ++i)
            {
                BinNode<int>* node = BinTree<int>::make_node(vec_delete_case3[i]);
                _rb_delete_case3.insert(node);
            }

            {
                std::vector<int> vec = {1,2,3,10,8,9,11};
                for(int i =0; i < vec.size(); ++i)
                {
                    BinNode<int>* node = BinTree<int>::make_node(vec[i]);
                    _rb_delete_fixup.insert(node);
                }
            }
        }


        BinTree<int> _rb;
        BinTree<int> _rb_delete_case3;
        BinTree<int> _rb_delete_fixup;
};
TEST_F(RedBlackTreeTest, DFS)
{
    _rb.bfs();

    EXPECT_EQ(0,0);
}
TEST_F(RedBlackTreeTest, LEFT_ROTATE)
{
    BinNode<int> * r = _rb.root(); 
    _rb.LeftRotate(r);
    _rb.bfs();
    EXPECT_EQ(0,0);
}
TEST_F(RedBlackTreeTest, RIGHT_ROTATE)
{
    _rb.RightRotate(_rb.root());
    _rb.bfs();
    EXPECT_EQ(0,0);
}
TEST_F(RedBlackTreeTest, InsertFixupCase1)
{
    _rb.insert(BinTree<int>::make_node(10));
    _rb.bfs();
    EXPECT_EQ(0,0);
}
TEST_F(RedBlackTreeTest, InsertFixupCase2And3)
{
    _rb.insert(BinTree<int>::make_node(10));
    _rb.insert(BinTree<int>::make_node(8));

    _rb.bfs();
    EXPECT_EQ(0,0);
}

TEST_F(RedBlackTreeTest, DeleteNoFixUp)
{
    BinNode<int>* node = _rb_delete_case3.search(8);
    _rb_delete_case3.deletenode(node);

    _rb_delete_case3.bfs();
    EXPECT_EQ(0,0);
}
TEST_F(RedBlackTreeTest, DeleteFixupDirectly)
{

    _rb_delete_fixup.bfs();
    // delete 9
    BinNode<int>* node = _rb_delete_fixup.search(9);
    _rb_delete_fixup.deletenode(node);
    _rb_delete_fixup.bfs();
    // no need to fixup

}
TEST_F(RedBlackTreeTest, DeleteFixup)
{
    _rb_delete_fixup.bfs();
    // delete 3
    BinNode<int>* node = _rb_delete_fixup.search(3);
    _rb_delete_fixup.deletenode(node);
    _rb_delete_fixup.bfs();
}
int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

