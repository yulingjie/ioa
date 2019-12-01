#include <list>
#include "Huffman.h"

HuffTree* minHChar(HuffForest* forest);

HuffTree* generateTree(HuffForest* forest)
{
    while( 1 < forest->size())
    {
        HuffTree* T1 = minHChar(forest);
        HuffTree* T2 = minHChar(forest);
        HuffTree* S = new HuffTree();
        S->insertAsRoot(HuffChar('^',T1->root()->data.weight
                    + T2->root()->data.weight));
        S->attachAsLC(S->root(), T1);
        S->attachAsRC(S->root(), T2);
        forest->insertAsLast(S);
    }
    return forest->first()->data;
}
HuffTree* minHChar(HuffForest* forest)
{
   ListNodePosi(HuffTree*) p = forest->first();
   ListNodePosi(HuffTree*) minChar = p;
    int minWeight = p->data->root()->data.weight;
    while(forest->valid(p=p->succ))
    {
        if(minWeight > p->data->root()->data.weight){
            minWeight = p->data->root()->data.weight;
            minChar = p;
        }
    }
    return forest->remove(minChar);
}
