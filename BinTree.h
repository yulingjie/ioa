#include <iostream>
#include <queue>
#include <algorithm>
#ifndef __BIN_NODE_H__
#define __BIN_NODE_H__
// BinTree
#define BinNodePosi(T) BinNode<T>* 

template <typename T> struct BinNode{
    BinNodePosi(T) parent;
    BinNodePosi(T) lc;
    BinNodePosi(T) rc;
    T data;
    int height;
    int size(); 
    BinNode(T const & e, BinNodePosi(T) p)
        :data(e),parent(p),lc(NULL),rc(NULL)
    {

    }
    BinNodePosi(T) insertAsLC(T const&); // left child
    BinNodePosi(T) insertAsRC(T const&); // right child
    BinNodePosi(T) succ(); // 中序遍历下的当前节点的直接后继
    BinNodePosi(T) pred(); // 中序遍历下的当前节点的直接前驱
	template <typename VST> void travLevel(VST&  visit); // 层次遍历	
    template <typename VST> void travPre(VST &); // 先序遍历
    template <typename VST> void travIn(VST & ); // 中序遍历 
    template <typename VST> void travPost(VST &); // 后序遍历

	bool IsRChild(const BinNodePosi(T) node) { return node->parent != NULL && node->parent->rc == node; }
	bool IsLChild(const BinNodePosi(T) node) { return node->parent != NULL && node->parent->lc == node; }


};

template < typename T>
class BinTree{
    private:

        static int removeAt(BinNodePosi(T) x);

    protected:
        int _size;
    protected:
        BinNodePosi(T) _root;
        virtual int updateHeight(BinNodePosi(T) x);// update height for node x
        void updateHeightAbove(BinNodePosi(T) x); // update height for x and its ancestors
    public:
        BinTree():_root(NULL), _size(0){}
        BinTree(BinNodePosi(T) r):_root(r),_size(1){}
        int size() const {return _size;}
        bool empty () const {return !_root;}
        BinNodePosi(T) root() const {return _root;}
        BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const &);
        BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const &);
        BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T> * &S);
        BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &S);
        BinNodePosi(T) insertAsRoot(const T& x);
        virtual int remove(BinNodePosi(T) x);

        BinTree<T>* secede(BinNodePosi(T) x);
        template <typename VST> void travLevel(BinNodePosi(T) x, VST& v);
        template <typename VST> void travPrev(BinNodePosi(T) x, VST& v);
        template <typename VST> void travIn(BinNodePosi(T) x, VST& v);
        template <typename VST> void travPost(BinNodePosi(T) x, VST& v);
        template <typename VST> void travIn_I3(BinNodePosi(T) node, VST& visit);

        bool HasLChild(BinNode<T>& node)
        {
            return node.lc != NULL;
        }
        bool HasRChild(BinNode<T>& node)
        {
            return node.rc != NULL;
        }
};

template <typename T> BinNodePosi(T) BinNode<T>::insertAsLC(T const &e )
{
    return lc = new BinNode(e, this);
}
template <typename T> BinNodePosi(T) BinNode<T>::insertAsRC(T const & e)
{
    return rc = new BinNode(e, this);
}
template <typename T>
int BinNode<T>::size(){
    int s = 1;
    if (lc) s+= lc->size();
    if (rc) s += rc->size();
    return s;
}
template <typename T>
template <typename VST> void BinNode<T>::travPre(VST & vst)
{
    vst(data);
    if (lc != NULL)
    {
        lc->travPre(vst);
    }
    if(rc != NULL)
    {
        rc->travPre(vst);
    }
}
template <typename T>
template <typename VST> void BinNode<T>::travIn(VST& vst)
{
    if (lc != NULL)
    {
        lc->travIn(vst);
    }
    vst(data);
    if (rc != NULL)
    {
        rc->travIn(vst);
    }
}
template <typename T>
template <typename VST> void BinNode<T>::travPost(VST& vst)
{
    if (lc != NULL)
    {
        lc->travPost(vst);
    }
    if(rc != NULL)
    {
        rc->travPost(vst);
    }
    vst(data);
}
template <typename T> 
BinNodePosi(T) BinNode<T>::pred()
{
    BinNodePosi(T) s= this;
    if (lc != NULL)
    {
        s= lc;
        while(s->rc != NULL) s = s->rc;
    }
    else
    {
        while(IsLChild(s))
        {
            s = s->parent;
        }
        s = s->parent;
    }
}
template <typename T> BinNodePosi(T) BinNode<T>::succ(){
    BinNodePosi(T) s= this;
    if (rc != NULL)
    {
        s = rc;
        while(s->lc != NULL) s= s->lc;
    }
    else
    {
        while(IsRChild(s))
        {
            s= s->parent;
        }
        s = s->parent;
    }
    return s; // 可能是NULL
}


 template <typename T>
 template<typename VST> 
 void BinNode<T>::travLevel(VST& visit) // 层次遍历
 {
     std::queue<BinNodePosi(T) > Q;
     Q.push(this);
     while(!Q.empty())
     {
         BinNodePosi(T) x =Q.front();
         Q.pop();
         visit(x->data);
         if(x->lc != NULL) Q.push(x->lc);
         if(x->rc != NULL) Q.push(x->rc);
     }
 }

///////////////////////////////////////////////////////////////////////////////

#define stature(p) ((p) ? (p)->height : -1)

template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x){
    return x->height = 1+
        std::max( stature(x->lc), stature(x->rc));
}
template <typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
    while(x)
    {
        updateHeight(x); x = x->parent;
    }
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(const T &x)
{
    _root = new BinNode<T>(x,NULL);
    _size = 1;
    return _root;
}
template <typename T> 
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const & e){
        _size++; x->insertAsRC(e);
        updateHeightAbove(x);
        return x->rc;
    }
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const & e)
{
    _size ++; x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lc;
}
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T> * &S){
    if ((x->rc = S->root)) x->rc->parent = x;
    _size += S->_size;
    updateHeightAbove(x);
    S->_root = NULL;
    S->_size = 0;
    delete S; 
    S = NULL;
    return x;
}
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T> * &S){
    if((x->lc = S->root)) x->lc->parent = x;
    _size += S->_size;
    updateHeightAbove(x);
    S->_root = NULL;
    S->_size = 0;
    delete S;
    S = NULL;
    return x;
}
template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x)
{
    BinNodePosi(T) p = x->parent ;
    if (p->lc == x)
    {
        p->lc = NULL;
    }
    else if(p->rc == x)
    {
        p->rc = NULL;
    }
    updateHeightAbove(x->parent);
    int n = removeAt(x); _size -= n;
    return n;
}
template <typename T>  int BinTree<T>::removeAt(BinNodePosi(T) x)
{
    if(!x) return 0;
    int n = 1 + removeAt(x->lc) + removeAt(x->rc);
    release(x->data); release(x); return n;
}
template <typename T> BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x)
{
    BinNodePosi(T) p = x->parent;
    if(p->lc == x) {
        p->lc = NULL;
    }
    else if(p->rc == x)
    {
        p->rc = NULL;
    }
    updateHeightAbove(x->parent);
    BinTree<T> *S = new BinTree<T>();
    S->_root = x;
    x->parent = NULL;
    S->_size = x->size();
    _size -= S->_size;
    return S;
}
template <typename T> 
template <typename VST>
void BinTree<T>::travIn(BinNodePosi(T) x, VST& visit)
{
    x->travLevel(visit);
}
template <typename T>
template <typename VST>
void BinTree<T>::travPrev(BinNodePosi(T) x, VST& visit)
{
    x->travPre(visit);
}
template <typename T>
template <typename VST>
void BinTree<T>::travPost(BinNodePosi(T) x, VST& visit)
{
    x->travPost(visit);
}
template <typename T>
template <typename VST>
void BinTree<T>::travLevel(BinNodePosi(T) x, VST& visit)
{
    x->travLevel(visit);
}
template <typename T>
template <typename VST>
void BinTree<T>::travIn_I3(BinNodePosi(T) node, VST& visit)
{
    bool backtrack = false;
    while(true)
    {
        if(!backtrack && HasLChild(*node))
        {
            node = node->lc;
        }
        else
        {
            visit(node->data);
            if(HasRChild(*node)){
                node = node->rc;
                backtrack = false;
            }
            else{
                if(!(node = node->succ())) break;
                backtrack = true;
            }
        }
    }
}
#endif
