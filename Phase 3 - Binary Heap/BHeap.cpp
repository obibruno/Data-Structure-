//
//  BHeap.cpp
//  Phase3
//
//  Created by Obi Bruno Da Silva Ndubueze on 4/9/21.
//
#ifndef CDA_CPP
#define CDA_CPP
#include "CDA.cpp"
#endif

#include <stdio.h>


using namespace std;

template<class keytype>

class BHeap
{
    private:
        struct Node
        {
            Node * sibling;
            Node * parent;
            Node* child;
            int degree;
            keytype k;
            
            Node(keytype key)
            {
                degree = 0;
                k = key;
                parent = sibling = child = NULL;
            }
        };
        
        CDA<Node*> minHeap;
        int min;
        keytype minK;
    
        void DestructTrees(CDA<Node*> heap)
        {
            
        }
    
        Node* mergeTrees(Node* tree1, Node* tree2)
        {
            if (tree1->k < tree2->k) {
                tree2->parent = tree1;
                tree2->sibling = tree1->child;
                tree1->child = tree2;
                tree1->degree++;
                return tree1;
            }
            else {
                tree1->parent = tree2;
                tree1->sibling = tree2->child;
                tree2->child = tree1;
                tree2->degree++;
                return tree2;
            }
        }
        
        // Source geekforgeeks.org/implementation-binomial-heap/ *some adjustments were made to fit CDA
        // This function perform union
        CDA<Node*> BinomialUnion(CDA<Node *> heap1, CDA<Node *> heap2)
        {
            // new heap after merging heap1 & heap2
            CDA<Node *> newHeap;
            //it1 & it2 are iterators
            int it1 = 0;
            int it2 = 0;
            while (it1 != heap1.Length() && it2 != heap2.Length())
            {
                // heap1->degree <= heap2->degree
                if (heap1[it1]->degree <= heap2[it2]->degree)
                {
                    newHeap.AddEnd(heap1[it1]);
                    it1++;
                }
                //heap1->degree > heap2->degree
                else
                {
                    newHeap.AddEnd(heap2[it2]);
                    it2++;
                }
            }
            
            // if there remains some elements in heap1
            // binomial heap
            while (it1 != heap1.Length())
            {
                newHeap.AddEnd(heap1[it1]);
                it1++;
            }

            // if there remains some elements in l2
            // binomial heap
            while (it2 != heap2.Length())
            {
                newHeap.AddEnd(heap2[it2]);
                it2++;
            }
            return newHeap;
            
        }
    
        void preorder(Node *tree)
        {
            if (tree == NULL)
                    return;
              
            cout << tree->k << " ";
            preorder(tree->child);
            preorder(tree->sibling);
        }
        
        CDA<Node *> adjust(CDA<Node *> newHeap)
        {
            //check if the heap is empty or only has one tree
            if (newHeap.Length() <= 1)
            {
                return newHeap;
            }
            int prev_x = 0;
            int x = 0; //smallest order trees are at the end
            int next_x = 1;

            while (next_x <= newHeap.Length() - 1)
            {
                //check if the orders of x and next-x are the same(CASE 1).
                if (newHeap[x]->degree == newHeap[next_x]->degree) 
                {
                    //case 2 x is the first of three roots with the same degree.
                    if (next_x + 1 < newHeap.Length() && newHeap[next_x + 1]->degree == newHeap[x]->degree)
                    {
                        prev_x = x;
                    }
                    else //Case 3 and 4 After all the pointers move down one position in the root list
                    {
                        Node *temp = mergeTrees(newHeap[x], newHeap[next_x]); //creates a node of the next order
                        newHeap = del(newHeap, x);
                        newHeap[x] = temp;
                        x--; //minus an index as merge occurred
                        next_x--;
                    }
                }
                x++;
                next_x++;
            }

            return newHeap;
        }
        CDA<Node *> del(CDA<Node *> heap, int val)
        {
            CDA<Node*> tempH;
            //deletes index val from the array
            
            
            if (val == 0)
            {
                heap.DelFront();
            }
            else
            {
                for (int i = val; i < heap.Length() - 1; i++)
                {
                    heap[i] = heap[i + 1];
                }
                heap.DelEnd();
            }
            return heap;
        }
        int minValue()
        {
            int min = 0;
            for (int i = 1; i < minHeap.Length(); i++)
            {
                if (minHeap[i]->k < minHeap[min]->k)
                    min = i;
            }
            return min;
        }
        CDA<Node*> removeMin(Node *minK)
        {
            //removes the minimum node from the tree and returns the children trees only
            CDA<Node *> newHeap(minK->degree);
            Node *tempH = minK->child;
            Node *leftOver;
            int degreeV =minK->degree;

            while (tempH)
            {
                leftOver = tempH;
                tempH = tempH->sibling;
                leftOver->sibling = NULL;
                degreeV--;
                leftOver->degree = degreeV;
                newHeap[degreeV] = leftOver; // sibling will always be smaller - addfront
            }
            return newHeap;
        }
    public:
        BHeap()
        {
            min = -1;
        };
        BHeap(keytype k[], int s)
        {
            min = -1;
            for (int i = 0; i < s; i++)
            {
                insert(k[i]);
            }
        }
        ~BHeap()
        {
            
        }
        keytype peekKey()
        {
            int min = minValue();
            return minHeap[min]->k;
        }
        void insert(keytype k)
        {
            CDA<Node*> tempH;
            tempH.AddEnd(new Node(k));
            
            tempH = BinomialUnion(tempH, minHeap);
            tempH = adjust(tempH);
            minHeap = tempH;
        }
        
        keytype extractMin()
        {
            int min = minValue();
            keytype minK = minHeap[min]->k;
            CDA<Node *> newHeap;
            CDA<Node *> leftOver;
            leftOver = removeMin(minHeap[min]);
            newHeap= del(minHeap, min);
            newHeap = BinomialUnion(newHeap, leftOver);
            newHeap = adjust(newHeap);

            minHeap = newHeap;
            return minK;
        }
        
        void merge(BHeap<keytype> &H2)
        {
            minHeap = BinomialUnion(minHeap, H2.minHeap);
            minHeap = adjust(minHeap);
        }
        
        void printKey()
        {
            for (int i = 0; i < minHeap.Length(); i++) {
                cout << "B" << minHeap[i]->degree << endl;
                preorder(minHeap[i]);
                cout << endl << endl;
            }
        }
};
