#ifndef __AVL_H__
#define __AVL_H__
#include "BST.h"

#define Balanced(x) (stature( (x).lc) == stature( (x).rc))
#define BalFac(x) (stature((x).lc) - stature((x).rc))
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))

#define tallerChild(x) ( \
        stature ((x)->lc) > stature( (x)->rc) ? (x)->lc: ( \
        stature ((x)->lc) < stature( (x)->rc) ? (x)->rc: ( \
            IsLChild( *(x) ) ? (x)->lc: (x)->rc \
            ) \
            )\
            )
template<typename T>
class AVL: public BST<T>
{
    public:
        BinNodePosi(T) insert(const T& e)
        {
            BinNodePosi(T) & x = search(e); 
            if(x) return x;
            BinNodePosi(T) xx = x = new BinNode<T>(e, this->_hot);
            this->_size ++;
            for(BinNodePosi(T) g =this-> _hot; g; g = g->parent)
            {
                if(!AvlBalanced(*g)){

                    FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g))); 
                    break;
                }
                else
                {
                    updateHeight(g);
                }
            }
            return xx;
        }

        bool remove(const T& e)
        {
            BinNodePosi(T) & x = search(e);
            if(!x) return false;
            removeAt(x, this->_hot); 
            this->_size--;
            for(BinNodePosi(T) g = this->_hot; g; g= g->parent){
                if(!AvlBalanced(*g))
                {
                   g = FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
                }

                updateHeight(g);
            }
            return true;
        }
    private:
       
        BinNodePosi(T) rotateAt(BinNodePosi(T) v)
        {
            BinNodePosi(T) p = v->parent;
            BinNodePosi(T) g = p->parent;
            if(IsLChild(*p))
            {
                if(IsLChild(*v)) // zig
                {
                    p->parent = g->parent;
                    return connect34(v, p,g, v->lc, v->rc, p->rc, g->rc);
                }
                else // zig-zag
                {
                    v->parent = g->parent;
                    return connect34(p,v,g,p->lc, v->lc, v->rc, g->rc);
                }
            }
            else
            {
                if(IsRChild(*v))
                {
                    p->parent = g->parent;
                    return connect34(g,p,v,g->lc, p->lc, v->lc, v->rc);
                }
                else
                {
                    v->parent = g->parent;
                    return connect34(g,v,p,g->lc,v->lc, v->rc, p->rc);
                }
            }
        }

};


#endif /* ifndef __AVL_H__

 */
