#ifndef __UNION_FIND_H__
#define __UNION_FIND_H__ 
#include <vector>
template<typename Tk>
struct UnionFindNode{
    int root;
    Tk data;
    int parent;
    UnionFindNode(Tk& d)
        :data(d),parent(-1),root(-1)
    {
    }
};
template<typename Tk>
class UnionFind
{
    public:
        int Find(const UnionFindNode<Tk>& node)
        {
           while(node.parent != -1) 
           {
               node = vec[node.parent]; 
           }
           return node->root;
        }
        void Union(UnionFindNode<Tk>& x, UnionFindNode<Tk>& y)
        {
            if(Find(x) != Find(y))
            {
                vec[y->root]->parent = x->root;
            }
        }
    private:
        std::vector<UnionFindNode<Tk>* > vec;
};
#endif /* ifndef __UNION_FIND_H__ */
