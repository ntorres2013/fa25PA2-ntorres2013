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
//        Case 1: Heap is empty, nothing to remove
        if(size == 0)
        {
            cout << "Heap is empty" << endl;
            return -1; // placeholder
        }

//        Case 2: Heap has one single node, pop node and heap becomes empty
        if(size == 1)
        {
            size = 0;
            return data[0];
        }

//        Case 3: Heap is not empty, pop element
        int returnElement = data[0];
        size--;
        data[0] = data[size];       // Last element goes to root of heap
        downheap(0, weightArr);
        return returnElement;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
//        Case 1: Heap has only has the root as its only node
        if(pos == 0)
        {
            return;
        }

//        Case 2: Heap has multiple nodes
        while(pos > 0)
        {
            int parent = (pos - 1) / 2;

            if(weightArr[data[pos]] < weightArr[data[parent]])
            {
                swap(data[pos], data[parent]);
                pos = parent;
            }
            else
            {
                break;
            }
        }

    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
//        Case 1: Heap is empty or has one singular node
        if(size <= 1)
        {
            return;
        }

//        Case 2: Heap has multiple nodes
        while(true)
        {
            int left  = 2 * pos + 1;
            int right = 2 * pos + 2;
            int smallest = pos;

            // Check if left child exists and is smaller
            if (left < size && weightArr[data[left]] < weightArr[data[smallest]])
            {
                smallest = left;
            }

            // Check if right child exists and is smaller
            if (right < size && weightArr[data[right]] < weightArr[data[smallest]])
            {
                smallest = right;
            }

            // If parent is already smaller than both children, stop
            if (smallest == pos)
            {
                break;
            }

            // Otherwise, swap with smaller child and continue down
            swap(data[pos], data[smallest]);
            pos = smallest; // move down one level
        }
    }
};

#endif
