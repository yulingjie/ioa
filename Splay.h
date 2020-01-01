#include "BST.h"

template<typename T>
class Splay: public BST<T>
{
    protected:
        BinNodePosi(T) splay(BinNodePosi(T) v);
    public:
        BinNodePosi(T) & search(const T& e);
        BinNodePosi(T) insert(const T&);
        bool remove(const T& e);
    private:
    
};
template <typename NodePosi> inline
void attachAsLChild(NodePosi p, NodePosi lc)
{
    p->lc = lc;
    if(lc) lc->parent = p;
}
template <typename NodePosi> inline
void attachAsRChild(NodePosi p, NodePosi rc)
{
    p->rc = rc;
    if(rc) rc->parent = p;
}
template <typename T>
BinNodePosi(T) Splay<T>::splay(BinNodePosi(T) v)
{
    if(!v) return NULL; 
    BinNodePosi(T) p;
    BinNodePosi(T) g;
    while((p = v->parent) && (g=p->parent)){
        BinNodePosi(T) gg=g->parent;
        if(IsLChild(*p))
        {
            if(IsLChild(*v))
            {
                //zig-zig
                // zig g then zig p
                zig(g);
                zig(p);

            }
            else
            {
                // zag -zig
                // zag p then zig g
                zag(p);
                zig(g);
            }
        }
        else if(IsRChild(*p))
        {
            if(IsRChild(*v))
            {
                // zag -zag
                // zag g then zag p
                zag(g);
                zag(p);
            }
            else
            {
                // zig p then zag g
                zig(p);
                zag(g);

            }

        }
        if(!gg) v->parent = NULL;
        else
        {
            (g == gg->lc) ? attachAsLChild(gg, v) : attachAsRChild(gg,v);
        }
        updateHeight(g);
        updateHeight(p);
        updateHeight(v);
    }
    if(p= v-> parent){
        if(IsLChild(*v)) {
            attachAsLChild(p, v->rc);
            attachAsRChild(v,p);
        }
        else
        {
            attachAsRChild(p, v->lc);
            attachAsLChild(v,p);
        }
        updateHeight(p);
        updateHeight(v);
    }
    v->parent = NULL;
    return v;
}

template<typename T>
BinNodePosi(T) & Splay<T>::search(const T& e)
{
    BinNodePosi(T) p = searchIn(this->_root, e, this->hot = NULL);
    this->_root = splay(p? p:this->_hot);
    return this->_root;
}
template<typename T>
BinNodePosi(T)  Splay<T>::insert(const T& e)
{
    if(!this->_root) {

        this->_size ++;
        return this->_root = new BinNode<T> (e);
    }
    if(e == search(e)->data) return this->_root;

}
