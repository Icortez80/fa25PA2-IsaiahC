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

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()*****COMPLETED
        size++;
        int pos = size - 1;
        //place new value onto the end of the heap
        data[pos] = idx;

        //call upheap to determine proper placement
        upheap(pos, weightArr);
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index********COMPLETED
        // Replace root with last element, then call downheap()
        if (size == 0 ) return -1;//if heap is empty return

        //grab first element
        int smallest = data[0];
        //move the most bottom value to the top
        data[0] = data[size-1];
        size--;

        //call downheap to find proper placement for this node
        downheap(0, weightArr);
        //return smallest value from heap
        return smallest;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent********COMPLETED
        while (pos > 0) {
            int parentPos = (pos - 1) / 2;
            //we use the indice from data and find its weight through weightArr[]
             if (weightArr[data[pos]] < weightArr[data[parentPos]]){
                 //if the child node is less than the parent then we swap them
                swap(data[pos], data[parentPos]);
                 //change the position index and loop
                pos = parentPos;
            }else {
                //if no changes need to be made return
                return;
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child*********COMPLETED
        while (true) {
            int left = 2 * pos + 1;
            int right = 2 * pos + 2;
            int smallest = pos;
            //if the left child is smaller than the smallest then set left to smallest
            if (left < size && weightArr[data[left]] < weightArr[smallest]) {
                smallest = left;
            }
            //if the right child is smaller than the smallest then set right to smallest
            if (right < size && weightArr[data[right]] < weightArr[smallest]) {
                smallest = right;
            }
            //if the smallest is equal to smallest position then stop
            if (smallest == pos) {
                break;
            }
                //swap smallest node into its right position
                swap(data[pos], data[smallest]);
                pos = smallest;

        }
    }

    //debug function
    void displayHeap() {
        //cout << "size: " << this->size << "\n";
        cout << "Building min heap: ";
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

#endif