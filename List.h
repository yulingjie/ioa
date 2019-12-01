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
        ListNodePosi(T) header;
        ListNodePosi(T) trailer;
    private:
        void init();
        void copyNodes(Posi(T) p, int n);
    protected:
    public:
       List(); 
        ~List();
        List(List<T> const& L);
        List(List<T> const& L, int r, int n);
        int size() const;
        ListNodePosi(T) first() const ;
        ListNodePosi(T) last() const;
        ListNodePosi(T) insertAsFirst(T const& e);
        ListNodePosi(T) insertAsLast(T const& e);
        ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e);// insert after
        ListNodePosi(T) insertB(ListNodePosi(T) p, T const& e);// insert before
        T remove(ListNodePosi(T) p);
        ListNodePosi(T) find(T const& e) const;
        ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const;// 在节点p的n个真前驱中，找到等于e的最后者
        int clear();
        int deduplicate();
        void traverse(void(*visit)(T& ));
        template <typename VST>
        void traverse(VST& visit);
        int uniquify();
        ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const;
        bool valid(ListNodePosi(T) p) const;
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
List<T>::List()
{
    init();
}
template <typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n)
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
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const
{
    while (0 < n--)
    {
        if (e == (p=p->pred)->data)
            return p;
    }
    return NULL;
}
template <typename T>
ListNodePosi(T) List<T>::find(T const& e) const
{
    return find(e, _size, trailer);
}
template <typename T>
ListNodePosi(T) List<T>::insertB( ListNodePosi(T) p, T const& e)
{
    _size++;
    return p->insertAsPred(e);
}
template <typename T>
ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p, T const& e)
{
    _size ++;
    return p->insertAsSucc(e);
}
template <typename T>
T List<T>::remove( ListNodePosi(T) p)
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
    ListNodePosi(T) p = first(); 
    int r = 1;
    while(trailer != (p=p->succ))
    {
        ListNodePosi(T) q = find(p->data,r,p);
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
    ListNodePosi(T) p = header;
    while((p = p->succ) != trailer) visit(p->data);
}
template <typename T>
template <typename VST>
void List<T>::traverse(VST& visit)
{
    ListNodePosi(T) p = header;
    while((p = p->succ) != trailer) visit(p->data);
}
template <typename T>
int List<T>::uniquify(){
    if(_size < 2) return 0;
    int oldSize = _size;
    ListNodePosi(T) p = first();
    ListNodePosi(T) q;
    while(trailer != (q=p->succ))
    {
        if(p->data != q->data) p = q;
        else
        {
            remove(q);
        }
    }
    return oldSize - _size;
}
template <typename T>
ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const
{
    do{
        p = p->pred;
        n--;
    }while((-1<n) && (e < p->data));
}
template <typename T>
ListNodePosi(T) List<T>::insertAsLast(const T& e) 
{
    return insertB(trailer,e);
}
template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(const T& e)
{
    return insertA(header, e);
}
template <typename T>
bool List<T>::valid(ListNodePosi(T) p) const
{
    return p != NULL;
}

#endif
