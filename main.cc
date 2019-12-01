#include "BinTree.h"
#include <iostream>
#include "List.h"

template <typename T>
struct Visit
{
    void operator() (T data)
    {
        std::cout<<data;
        std::cout<<" ";
    }
};
void testBinTree()
{
    BinNodePosi(int) r = new BinNode<int>(1,NULL);    
    BinTree<int>* t = new BinTree<int>(r);
    BinNodePosi(int) l1 = t->insertAsLC(r, 2);
    BinNodePosi(int) r1 = t->insertAsRC(r,3);
     t->insertAsLC(l1,4);
     t->insertAsRC(l1,5);
     t->insertAsLC(r1, 6);
     t->insertAsRC(r1,7);
    Visit<int> v;
    t->travIn(r,v);
    std::cout << std::endl;
    t->travPrev(r, v);
    std::cout << std::endl;
    t->travPost(r, v);

}
void testList()
{
    List<int> l;
    l.insertAsFirst(1);
    l.insertAsLast(2);
    Visit<int> v;
    l.traverse(v);
}
int main(int argc, char* argv[])
{
    testList();

}
