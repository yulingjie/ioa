#include "BinTree.h"
#include <iostream>
template <typename T>
struct Visit
{
    void operator() (T data)
    {
        std::cout<<data;
        std::cout<<" ";
    }
};
int main(int argc, char* argv[])
{
    BinNodePosi(int) r = new BinNode<int>(1,NULL);    
    BinTree<int>* t = new BinTree<int>(r);
    BinNodePosi(int) l1 = t->insertAsLC(r, 2);
    BinNodePosi(int) r1 = t->insertAsRC(r,3);
    BinNodePosi(int) l1l1 = t->insertAsLC(l1,4);
    BinNodePosi(int) l1r1 = t->insertAsRC(l1,5);
    BinNodePosi(int) r1l1 = t->insertAsLC(r1, 6);
    BinNodePosi(int) r1r1 = t->insertAsRC(r1,7);
    Visit<int> v;
    t->travIn(r,v);
	std::cout << std::endl;
	t->travPrev(r, v);
	std::cout << std::endl;
	t->travPost(r, v);
}
