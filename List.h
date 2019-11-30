#ifndef __LIST_H__
#define __LIST_H__
#include <iostream>
#define Posi(T) ListNode<T>* 
template <typename T>
struct ListNode{
    T data;
    Posi(T) pred;
    Posi(T) succ;
    ListNode() {}
    ListNode(T e, Posi(T) p = NULL, Posi(T) s = NULL)
        :data(e), pred(p), succ(s) {}
    Posi(T) insertAsPred(T const& e);
    Posi(T) insertAsSucc(T const& e);


};
template <typename T>
Posi(T) ListNode<T>::insertAsPred(T const& e)
{
    Posi(T) x = new ListNode(e ,pred, this);
    pred->succ = x;
    pred = x;
    return x;
}
template <typename T>
Posi(T) ListNode<T>::insertAsSucc(T const& e)
{
    Posi(T) x = new ListNode(e, this, succ);
    succ->pred = x;
    succ = x;
    return x;
}
#define ListNodePosi(T) Posi(T)

template<typename T> 
class List{
    private:
        int _size;
        Posi(T) header;
        Posi(T) trailer;
    private:
        void init();
        void copyNodes(Posi(T) p, int n);
    protected:
    public:
        
        ~List();
        List(List<T> const& L);
        List(List<T> const& L, int r, int n);
        int size() const;
        Posi(T) first() const ;
        Posi(T) last() const;
        Posi(T) insertAsFirst(T const& e);
        Posi(T) insertAsLast(T const& e);
        Posi(T) insertA(Posi(T) p, T const& e);// insert after
        Posi(T) insertB(Posi(T) p, T const& e);// insert before
        T remove(Posi(T) p);
        Posi(T) find(T const& e) const;
        Posi(T) find(T const& e, int n, Posi(T) p) const;// 在节点p的n个真前驱中，找到等于e的最后者
        int clear();
        int deduplicate();
        void traverse(void(*visit)(T& ));
        template <typename VST>
        void traverse(VST& visit);
        int uniquify();
};

template <typename T> 
void List<T>::init()
{
    header = new ListNode<T>();
    trailer = new ListNode<T>();
    header->succ = trailer;
    header->pred = NULL;
    trailer->pred = header;
    trailer->succ = NULL;
    _size = 0;
}
template <typename T>
void List<T>::copyNodes(Posi(T) p, int n)
{
    init();
    while(n--)
    {
        insertAsLast(p->data);
        p= p->succ;
    }
}

template <typename T>
List<T>::List(List<T> const& L)
{
    copyNodes(L.first(), L._size);
}
template <typename T>
List<T>::List(List<T> const& L, int r, int n)
{
    copyNodes(L[r],n);
}

template <typename T>
Posi(T) List<T>::find(T const& e, int n, Posi(T) p) const
{
    while (0 < n--)
    {
        if (e == (p=p->pred)->data)
            return p;
    }
    return NULL;
}
template <typename T>
Posi(T) List<T>::find(T const& e) const
{
    return find(e, _size, trailer);
}
template <typename T>
Posi(T) List<T>::insertB( Posi(T) p, T const& e)
{
    _size++;
    return p->insertAsPred(e);
}
template <typename T>
T List<T>::remove( Posi(T) p)
{
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--;
    return e;
}
template <typename T>
List<T>::~List()
{
    clear();
    delete header;
    delete trailer;
}
template <typename T>
int List<T>::clear()
{
    int oldSize = _size;
    while(0 < _size){
        remove(header->succ);
    }
    return oldSize;
}
template <typename T>
int List<T>::deduplicate()
{
    if(_size < 2) return 0;
    int oldSize = _size;
    Posi(T) p = first(); 
    int r = 1;
    while(trailer != (p=p->succ))
    {
        Posi(T) q = find(p->data,r,p);
        if (q )
        {
            remove(q);
        }
        else
        {
            ++r;
        }
    }
    return oldSize - _size;
}
template <typename T>
void List<T>::traverse(void (*visit)(T &))
{
    Posi(T) p = header;
    while((p = p->succ) != trailer) visit(p->data);
}
template <typename T>
template <typename VST>
void List<T>::traverse(VST& visit)
{
    Posi(T) p = header;
    while((p = p->succ) != trailer) visit(p->data);
}
template <typename T>
int List<T>::uniquify(){
}
#endif
