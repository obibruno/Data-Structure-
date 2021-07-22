//
//  Heap.cpp
//  Phase3
//
//  Created by Obi Bruno Da Silva Ndubueze on 4/9/21.

#ifndef CDA_CPP
#define CDA_CPP
#include "CDA.cpp"
#endif

#include <stdio.h>
using namespace std;

template<class keytype>

class Heap
{
    private:
        
        CDA<keytype> minHeap;
    
        int parent(int index)
        {
            return (index - 1)/2;
        }
        int lChild(int index)
        {
            return (2 * index) + 1;
        }
        int rChild(int index)
        {
            return (2 * index) + 2;
        }
    
        void swap(keytype &a, keytype &b)
        {
            keytype temp;
            temp = a;
            a = b;
            b = temp;
        }
    
        void MinHeapify(int i)
        {
            int left = lChild(i);
            int right = rChild(i);
            int smallest = i;
            if (left < minHeap.Length() && minHeap[left] < minHeap[i])
                smallest = left;
            if (right < minHeap.Length() && minHeap[right] < minHeap[smallest])
                smallest = right;
            if (smallest != i)
            {
                swap(minHeap[i], minHeap[smallest]);
                MinHeapify(smallest);
            }
    }
    public:
        //Default Constructor;
        Heap(){}
        //Constructor
        Heap(keytype k[], int s)
        {
            for (int i = 0; i < s; i++)
            {
                minHeap.AddEnd(k[i]);
            }
            for (int i = s/2; i >= 0; i--)
            {
                MinHeapify(i);
            }
        }
    
        keytype peekKey()
        {
            return minHeap[0];
        }
    
        keytype extractMin()
        {
            keytype temp = minHeap[0];
            swap(minHeap[0], minHeap[minHeap.Length() - 1]);
            minHeap.DelEnd();
            MinHeapify(0);
            return temp;
        }
    
        void insert(keytype k)
        {
            minHeap.AddEnd(k);
            
            int currentI = minHeap.Length() - 1; // current index location
            
            // Fix the min heap property if it is violated
            while (currentI > 0 && minHeap[parent(currentI)] > minHeap[currentI])
            {
                swap(minHeap[currentI], minHeap[parent(currentI)]);
                currentI = parent(currentI);
            }
        }
        
        void printKey()
        {
            for (int i = 0; i < minHeap.Length(); i++)
            {
                cout << minHeap[i] << " ";
            }
            cout << endl;
        }
};
