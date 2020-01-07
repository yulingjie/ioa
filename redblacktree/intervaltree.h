#ifndef __INTERVAL_TREE_H__
#define __INTERVAL_TREE_H__ 1

#include <algorithm>
#include "redblacktree.h"

// use low as BinNode key
class IntervalNode
{
    public:

        IntervalNode(int noop)
            :_low(noop),_high(noop),_max(noop),_lc(NULL),_rc(NULL),_p(NULL)
        {

        }
        IntervalNode(int low, int high)
            :_low(low),_high(high),_max(high),_lc(NULL),_rc(NULL),_p(NULL)
        {
        }

        IntervalNode*& lc() {return _lc;}
        IntervalNode*& rc() {return _rc;}
        IntervalNode*& p() {return _p;}
        int & color() {return _color;}

        int& data() {return _low;}

        int& low() {return _low;}
        int& high() {return _high;}

        int& max() {return _max;}
        bool overlap(IntervalNode* i)
        {
            return  _low <= i->high() && _high >= i->low();
        }
    private:
        int _low;

        int _high;

        int _max;

        int _color;
        IntervalNode* _lc;
        IntervalNode* _rc;
        IntervalNode* _p;
};

class IntervalTree:public BinTree<int,IntervalNode>
{
    public:
        IntervalTree()
        {
        }
    public:
        static IntervalNode* make_node(int low, int high)
        {
            IntervalNode* node = new IntervalNode(low,high);
            node->color() = RED;

            node->lc() = nil;
            node->rc() = nil;
            node->p() = nil;

            return node;
 
        }
    public:
        IntervalNode* IntervalSearch(IntervalNode* i)
        {
           IntervalNode* x =this-> _root; 
           while( x != nil && ! x->overlap(i))
           {
               if(x->lc() != nil && x->lc()->max() > i->low())
               {
                    x= x->lc();
               }
               else
               {
                   x = x->rc();
               }
                       
           }
           return x;
        }
    protected:
        void left_rotate(IntervalNode* x) override
        {
            IntervalNode* y = x->rc();
            IntervalNode* y_lc = y->lc();
            IntervalNode* y_rc = x->rc();
            BinTree<int,IntervalNode>::left_rotate(x);
            int x_max = x->high();
            if( x->lc() != nil)
            {
                x_max = std::max(x_max, x->lc()->max());
            }
            if ( y_lc != nil)
            {
                x_max = std::max(x_max, y_lc->max());
            }
            x->max() = x_max;

            int y_max = y->high();
            y_max = std::max(y_max,x_max);
            if(y_rc != nil)
            {
                y_max = std::max(y_max,y_rc->max());
            }
            y_rc->max() = y_max;
        }
        void right_rotate(IntervalNode* y)  override
        {
            IntervalNode* x = y->lc();
            IntervalNode* x_lc = x->lc();
            IntervalNode* x_rc = x->rc();
            BinTree<int,IntervalNode>::right_rotate(y);
            int y_max = y->high();
            if (x_rc != nil)
            {
                y_max = std::max(x_rc->max(),y_max);
            }
            if(y->rc() != nil)
            {
                y_max = std::max(y->rc()->max(),y_max);
            }
            y->max() = y_max;
            int x_max = x->high();
            x_max = std::max(x_max, y_max);
            if(x_lc != nil)
            {
                x_max = std::max(x_lc->max(), x_max);
            }
            x->max() = x_max;
        }
};

#endif /* ifndef __INTERVAL_TREE_H__ */
