#ifndef __RED_BLACK_TREE_H__
#define __RED_BLACK_TREE_H__ 1
#include <iostream>
#include <queue>

const int RED = 0;
const int BLACK = 1;
const int BLACK_BLACK= 3;
const int BLACK_RED = 4;
template<class T>
class BinNode
{
public:
    BinNode (const T& data)
        :_data(data)
    {
        _color = BLACK;
        _lc = NULL;
        _rc = NULL;
        _p = NULL;
    }
    virtual ~BinNode (){}

    int & color() {return _color;}
    BinNode*& lc(){return _lc;}
    BinNode*& rc(){return _rc;}
    BinNode*& p(){return _p;}

    T& data(){return _data;}

private:
private:
    /* data */
    int _color;
    BinNode* _lc;
    BinNode* _rc;
    BinNode* _p;
    T _data;
};

template<class T>
class BinTree
{
    public:

        static BinNode<T>* nil;
    public:
        BinTree()
        {
            _root = nil;
        }
        void insert(BinNode<T>* node);
        BinNode<T>* search(const T & t) const;

        void deletenode(BinNode<T>* z);
        void dfs();
        void bfs();
        BinNode<T>* root(){return _root;}
        void LeftRotate(BinNode<T>* x) {left_rotate(x);}
        void RightRotate(BinNode<T>* x){right_rotate(x);}

    private:
        BinNode<T>* search_recur(BinNode<T>* node, const T& t) const;
        void insert_fixup(BinNode<T>* node);
        void left_rotate(BinNode<T>* x);
        void right_rotate(BinNode<T>* x);
        void transplant(BinNode<T>* u, BinNode<T>* v);
        BinNode<T>* minimum(BinNode<T>* node);

        void delete_fixup(BinNode<T>* x);

        void dfs_recur(BinNode<T>* node);
        
    private:
        BinNode<T>* _root;
    public:
        static BinNode<T>* make_node(const T& t)
        {
            BinNode<T>* node = new BinNode<T>(t);
            node->color() = RED;

            node->lc() = nil;
            node->rc() = nil;
            node->p() = nil;

            return node;
        }

};


template<class T>
BinNode<T>* BinTree<T>::nil = new BinNode<T>(-1);

template<class T>
BinNode<T>* BinTree<T>::search(const T& t) const
{
    return search_recur(_root, t);
}
template<class T>
BinNode<T>* BinTree<T>::search_recur(BinNode<T>* node, const T& t) const
{
    if(node == nil) return nil;
    if(node->data() == t) return node;
    if(node->data() < t)
    {
        return search_recur(node->rc(),t);
    }
    if (node->data() > t)
    {
        return search_recur(node->lc(),t);
    }
    return nil;

}
template<class T>
void BinTree<T>::dfs()
{
    dfs_recur(_root);
}
static const char* getColor(int color)
{
    if (color == RED)
    {
        return "red";
    }
    else if(color == BLACK)
    {
        return "black";
    }
    else if(color == BLACK_BLACK)
    {
        return "black_black";
    }
    else if(color == BLACK_RED)
    {
        return "black_red";
    }
    return "";
}
template <class T>
void BinTree<T>::bfs()
{
    if (_root == nil) return;
    std::queue<BinNode<T>* > q;
    q.push(_root);
    int cur = 1;
    int next =0;
    while(q.size() > 0)
    {
        BinNode<T>* node = q.front();

        q.pop();
        std::cout<<node->data() << " "<<getColor(node->color())<<"    ";


        if(node->lc() != NULL)
        {
            q.push(node->lc());
            next ++;
        }
        if(node->rc() != NULL)
        {
            q.push(node->rc());
            next += 1;
        }

        cur--;
        if(cur <=0)
        {
            std::cout<<std::endl;
            cur = next;
            next = 0;
        }
    }
    std::cout<<std::endl;
}

    template<class T>
void BinTree<T>::dfs_recur(BinNode<T>* node)
{
    if(node->lc() != nil)
    {
        dfs_recur(node->lc());
    }
    if(node->rc() != nil)
    {
        dfs_recur(node->rc());
    }
    std::cout<<" "<<node->data()<<" ";
}

    template<class T>
BinNode<T>* BinTree<T>::minimum(BinNode<T>* node)
{

    while(node->lc() != nil)
    {
        node = node->lc();
    }
    return node;


}

    template<class T>
void BinTree<T>::transplant(BinNode<T>* u, BinNode<T>* v)
{
    if(u->p() == nil)
    {
        _root = v;
    }
    else if(u == u->p()->lc())
    {
        u->p()->lc() = v;
    }
    else
    {
        u->p()->rc() = v;
    }
    v->p() = u->p();
}
    template<class T>
void BinTree<T>::deletenode(BinNode<T>* z)
{
    BinNode<T>* y = z;
    BinNode<T>* x= nil;
    int y_original_color = y->color();
    if (z->lc() == nil)
    {
        x = z->rc();
        transplant(z,z->rc());
    }
    else if(z->rc() == nil)
    {
        x = z->lc();
        transplant(z,z->lc());
    }
    else
    {
        y = minimum(z->rc());
        y_original_color = y->color();
        x = y->rc();
        if(y->p() == z)
        {
            x->p() = y;
        }
        else
        {
            transplant(y,y->rc());
            y->rc() = z->rc();
            y->rc()->p() = y;
        }
        transplant(z,y);
        y->lc() = z->lc();
        y->lc()->p() = y;
        y->color() = z->color();
    }
    if(y_original_color == BLACK)
    {
        std::cout<<"delete_fixup "<<x->data()<<std::endl;
        delete_fixup(x);
    }

}

    template<class T>
void BinTree<T>::delete_fixup(BinNode<T>* x)
{
    BinNode<T> * w;
    while( x != _root && x->color() == BLACK)
    {
        if(x == x->p()->lc())
        {
            w = x->p()->rc();
            if(w->color() == RED) // case 1
            {
                w->color() = BLACK;
                x->p()->color() = BLACK;
                left_rotate(x->p());
                w = x->p()->rc();
            }
            if(w->lc()->color() == BLACK && w->rc()->color() == BLACK)
            {
                w->color() = RED;
                x = x->p();
            }
            else
            {
                if(w->rc()->color() == BLACK)
                {
                    w->lc()->color() = BLACK;
                    w->color() = RED;
                    right_rotate(w);
                    w = x->p()->rc();
                }
                w->color() = x->p()->color();
                x->p()->color()  = BLACK;
                w->rc()->color() = BLACK;
                left_rotate(x->p());
                x = _root;
            }
        }
        else
        {
            w = x->p()->lc();
            if(w->color() == RED)
            {
                w->color() = BLACK;
                x->p()->color() = RED;
                right_rotate(x->p());
                w = x->p()->lc();
            }
            if(w->lc()->color() == BLACK && w->rc()->color() == BLACK)
            {
                w->color() = RED;
                x = x->p();
            }
            else
            {
                if(w->lc()->color() == BLACK)
                {
                    w->rc()->color() = BLACK;
                    w->color() = RED;
                    left_rotate(w);
                    w = x->p()->lc();
                }
                w->color() = x->p()->color();
                x->p()->color() = BLACK;
                w->lc()->color() = BLACK;
                right_rotate(x->p());
                x = _root;
            }
        }
    }
    x->color() =BLACK;
}
    template<class T>
void BinTree<T>::left_rotate(BinNode<T>* x)
{
    BinNode<T>* y = x->rc();
    x->rc() = y->lc();
    if(y->lc() != nil)
    {
        y->lc()->p() = x;
    }
    y->p() = x->p();
    if(x->p() == nil)
    {
        _root = y;
    }
    else if (x == x->p()->lc())
    {
        x->p()->lc() = y;
    }
    else if(x == x->p()->rc())
    {
        x->p()->rc() = y;
    }
    y->lc() = x;
    x->p() = y;
}
template<class T>
void BinTree<T>::right_rotate(BinNode<T>* y)
{

    BinNode<T>* x = y->lc();
    y->lc()  = x->rc();
    if(x->rc() != nil)
    {
        x->rc()->p() = y;
    }
    x->p() = y->p();
    if(y->p() == nil)
    {
        _root = x;
    }
    else if(y == y->p()->lc())
    {
        y->p()->lc() = x;
    }
    else if(y == y->p()->rc())
    {
        y->p()->rc() =x;
    }
    x ->rc() = y;
    y->p() = x;
}
    template<class T>
void BinTree<T>::insert_fixup(BinNode<T>* z)
{
    BinNode<T>* y;
    while(z->p()->color() == RED)
    {
        if(z->p() == z->p()->p()->lc())
        {
            y = z->p()->p()->rc();
            if (y->color() == RED)
            {
                z->p()->color() = BLACK;
                y->color() = BLACK;
                z->p()->p()->color() = RED;
                z = z->p()->p();
            }
            else
            {
                if(z == z->p()->rc())
                {
                    z = z->p();
                    left_rotate(z);
                }
                z->p()->color() = BLACK;
                z->p()->p()->color() = RED;
                right_rotate(z->p()->p());
            }
        }
        else
        {
            //std::cout<<"case 2'"<<std::endl;
            y = z->p()->p()->lc();
            if (y ->color() == RED)
            {
                z->p()->color() = BLACK;
                y->color() = BLACK;
                z->p()->p()->color() = RED;
                z = z->p()->p();
            }
            else
            {
                if (z == z->p()->lc())
                {
                    z = z->p();
                    right_rotate(z);
                    //std::cout<<"right_rotate for case 2"<<std::endl;
                    //bfs();
                }
                z->p()->color() = BLACK;
                z->p()->p()->color() = RED;
                left_rotate(z->p()->p());
            }
        }
    }
    _root->color() = BLACK;
}

    template<class T>
void BinTree<T>::insert(BinNode<T>* node)
{
    BinNode<T>* y = nil;
    BinNode<T>* x= _root;;
    while (x != nil)
    {
        y = x;
        if(node->data() < x->data())
        {
            x = x->lc();
        }
        else
        {
            x = x->rc();
        }
    }
    node->p() = y;
    if (y == nil )
    {
        _root = node;
    }
    else if(node->data() < y->data())
    {
        y->lc() = node;
    }
    else
    {
        y->rc() = node;
    }
    node->lc() = nil;
    node->rc() = nil;
    node->color() = RED;
    //std::cout<<"before insert_fixup "<<std::endl;
    //bfs();
    //std::cout<<"==================="<<std::endl;
    insert_fixup(node);
}


#endif /* ifndef __RED_BLACK_TREE_H__
*/
