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
        forest->push_back(S);
    }
    return forest->front();
}
HuffTree* minHChar(HuffForest* forest)
{
    
}
