#ifndef __BST_H__
#define __BST_H__
#include <iostream>
#include "BinTree.h"

template <typename K, typename V>
struct Entry{
    K key;
    V value;
    Entry(K k,V v): key(k), value(v)
    {
    }
    bool operator < (Entry<K,V> const& e) {return key < e.key;}
    bool operator > (Entry<K,V> const& e) {return key > e.key;}
    bool operator ==(Entry<K,V> const& e) {return key == e.key;}
    bool operator !=(Entry<K,V> const& e) {return key != e.key;}
};

template <typename T>
static BinNodePosi(T) & searchIn(BinNodePosi(T) & v, const T& e, BinNodePosi(T) & hot);
template <typename T> 
class BST: public BinTree<T>
{

    protected:
        BinNodePosi(T)& FromParentTo(BinNode<T>& g)
        {
            if(g.parent == NULL) return this->_root;
            if(g.parent->lc == &g) return g.parent->lc;
            if(g.parent->rc == &g) return g.parent->rc;
        }
    protected:
        BinNodePosi(T) _hot;
        BinNodePosi(T) connect34(BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
                BinNodePosi(T) T0, BinNodePosi(T) T1,BinNodePosi(T) T2, BinNodePosi(T) T3)
        {
            a->lc = T0; if(T0) T0->parent = a;
            a->rc = T1; if(T1) T1->parent = a; updateHeight(a);
            c->lc = T2; if(T2) T2->parent = c;
            c->rc = T3; if(T3) T3->parent = c; updateHeight(c);
            b->lc = a; a->parent =b;
            b->rc = c; c->parent = b;
            updateHeight(b);
            return b;
        }
        BinNodePosi(T) rotateAt(BinNodePosi(T) x);
        BinNodePosi(T) zig(BinNodePosi(T) x)
        {
           BinNodePosi(T) c =  FromParentTo(*x) =x->lc;
            x->lc = c->rc;
            c->rc = x;
        }
        BinNodePosi(T) zag(BinNodePosi(T) x)
        {
            BinNodePosi(T) c= FromParentTo(*x) = x->rc;
            x->rc = c->lc;
            c->lc = x;
        }
    public:
        virtual BinNodePosi(T) insert(const T& e)
        {
            BinNodePosi(T) & x= search(e);
            if(!x)
            {
                x = new BinNode<T>(e, _hot);
                this->_size++;
                updateHeightAbove(x);
            }
            return x;
           
        }
        virtual bool remove(const T& e)
        {
            BinNodePosi(T) & x = search(e);
            if(!x) return false;
            removeAt(x, _hot);
            this->_size --;
            updateHeightAbove(_hot);
            return true;

        }
        virtual BinNodePosi(T) & search(const T& e)
        {
            return searchIn(this->_root, e,_hot = NULL);
        }

    protected:
        static BinNodePosi(T) removeAt(BinNodePosi(T) & x, BinNodePosi(T) & hot)
        {
            BinNodePosi(T) w = x;
            BinNodePosi(T) succ = NULL;
            if(!HasLChild(*x))
            {
                succ = x = x->rc;
            }
            else if(!HasRChild(*x))
            {
                succ = x = x->lc;
            }
            else{
                w = w->succ();
                std::swap(x->data, w->data);
                BinNodePosi(T) u = w->parent;
                ((u == x) ? u->rc : u->lc ) = succ = w->rc;
            }
            hot = w->parent;
            if(succ) succ->parent = hot;
            release(w->data);
            release(w);
            return succ;
        }

       
};
template <typename T>
static BinNodePosi(T) & searchIn(BinNodePosi(T) & v, const T& e, BinNodePosi(T) & hot)
{
    if(!v || (e == v->data)) return v;
    hot = v;
    return searchIN(((e < v->data) ? v->lc : v->rc), e, hot);
}

#endif /* ifndef __BST_H__


          }; */
