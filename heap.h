//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[])
    {
        // TODO: insert index at end of heap, restore order using upheap()
//        Case 1: Heap is full
        if(size >= 64)
        {
            cout << "Heap is full" << endl;
            return;
        }

//        Case 2: Heap is empty, index getting pushed becomes the root
        if(size == 0)
        {
            data[0] = idx;
            size++;
            return;
        }

//        Case 3: Heap is not empty, push at the end and upheap
        data[size] = idx;
        upheap(size, weightArr);
        size++;
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        return -1; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
    }
};

#endif
