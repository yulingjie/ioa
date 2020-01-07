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

template<class T,class Node>
class BinTree
{
    public:
class BinNode
{
    public:
        BinNode (const Node& data)
            :_data(data)
        {
            _color = BLACK;
            _lc = NULL;
            _rc = NULL;
            _p = NULL;
        }
        virtual ~BinNode (){}

        int & color() {return _color;}
        Node*& lc(){return _lc;}
        Node*& rc(){return _rc;}
        Node*& p(){return _p;}

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


    public:

        static Node* nil;
    public:
        BinTree()
        {
            _root = nil;
        }
        void insert(Node* node);
        Node* search(const T & t) const;

        void deletenode(Node* z);
        void dfs();
        void bfs();
        Node* root(){return _root;}
        void LeftRotate(Node* x) {left_rotate(x);}
        void RightRotate(Node* x){right_rotate(x);}
    protected:
        virtual void left_rotate(Node* x);

        virtual void right_rotate(Node* x);
    private:
        Node* search_recur(Node* node, const T& t) const;
        void insert_fixup(Node* node);
        void transplant(Node* u, Node* v);
        Node* minimum(Node* node);

        void delete_fixup(Node* x);

        void dfs_recur(Node* node);

    protected:
        Node* _root;
    public:
        static Node* make_node(const T& t)
        {
            Node* node = new Node(t);
            node->color() = RED;

            node->lc() = nil;
            node->rc() = nil;
            node->p() = nil;

            return node;
        }

};


template<class T>
class RedBlackTree:public BinTree<T,BinNode<T>>
{
};

template<class T,class Node>
Node* BinTree<T,Node>::nil = new Node(-1);

template<class T,class Node>
Node* BinTree<T,Node>::search(const T& t) const
{
    return search_recur(_root, t);
}
template<class T,class Node>
Node* BinTree<T,Node>::search_recur(Node* node, const T& t) const
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
    template<class T,class Node>
void BinTree<T,Node>::dfs()
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
    template <class T,class Node>
void BinTree<T,Node>::bfs()
{
    if (_root == nil) return;
    std::queue<Node* > q;
    q.push(_root);
    int cur = 1;
    int next =0;
    while(q.size() > 0)
    {
        Node* node = q.front();

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

    template<class T,class Node>
void BinTree<T,Node>::dfs_recur(Node* node)
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

    template<class T,class Node>
Node* BinTree<T,Node>::minimum(Node* node)
{

    while(node->lc() != nil)
    {
        node = node->lc();
    }
    return node;


}

    template<class T,class Node>
void BinTree<T,Node>::transplant(Node* u, Node* v)
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
    template<class T,class Node>
void BinTree<T,Node>::deletenode(Node* z)
{
    Node* y = z;
    Node* x= nil;
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

    template<class T,class Node>
void BinTree<T,Node>::delete_fixup(Node* x)
{
    Node * w;
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
    template<class T,class Node>
void BinTree<T,Node>::left_rotate(Node* x)
{
    Node* y = x->rc();
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
    template<class T,class Node>
void BinTree<T,Node>::right_rotate(Node* y)

{

    Node* x = y->lc();
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
    template<class T,class Node>
void BinTree<T,Node>::insert_fixup(Node* z)
{
    Node* y;
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

    template<class T,class Node>
void BinTree<T,Node>::insert(Node* node)
{
    Node* y = nil;
    Node* x= _root;;
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
