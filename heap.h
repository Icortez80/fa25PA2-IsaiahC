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
        data[pos] = idx;

        upheap(pos, weightArr);
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index********COMPLETED
        // Replace root with last element, then call downheap()
        if (weightArr[size] == 0 ) return -1;

        int smallest = data[0];
        data[0] = data[size-1];
        size--;

        downheap(0, weightArr);
        return smallest;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent********COMPLETED
        while (pos > 0) {
            int parentPos = (pos - 1) / 2;
            if (weightArr[data[pos]] < weightArr[parentPos]) {
                swap(data[pos], weightArr[parentPos]);
                pos = parentPos;
            }else {
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
            if (left < size && weightArr[data[left]] < weightArr[smallest]) {
                smallest = left;
            }
            if (right < size && weightArr[data[right]] < weightArr[smallest]) {
                smallest = right;
            }
            if (smallest == pos) {
                break;
            }
                swap(data[pos], data[smallest]);
                pos = smallest;

        }
    }
};

#endif