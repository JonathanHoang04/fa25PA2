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
        //Overflow Condition
        //Since max size is 64
        if (size >= 64) {
            cout <<endl;
            cout << "Heap Overflow! No more elements.";
            cout << endl;
            return;
        }

        //Places new index at the end of the heap
        data[size] = idx;

        // Restore heap property
        upheap(size, weightArr);

        //Increase size of heap
        size++;

    }

    int pop(int weightArr[]) {

        //Underflow Condition
        //If the heap is empty
        if (size ==0) {
            cout << endl;
            cout << "Heap Underflow! There is no index in the heap";
            return 0;
        }

        // Replace root with last element, then call downheap()

        int minimumIdx = data[0]; //Initializes smallest index in heap
        data[0] = data[size - 1]; // Move last leaf to become the new root of the heap tree
        size--; //Decrease Heap size

        //Calls DownHeap
        downheap(0, weightArr);

        //Gives the user lowest index from heap
        return minimumIdx;

    }

    //Called After inserting a new index
    void upheap(int pos, int weightArr[]) {
        // swap child upward while smaller than parent

        //Parent Index
        int parent = (pos - 1)/2;

        //Base Case stop if when @ root
        if (pos == 0) {
            return;
        }

        //IF The noded just added (pos) < parent then swap and recursion
        if (weightArr[data[pos]] < weightArr[data[parent]]) {
            //Swap pos and parent
            swap(data[pos], data[parent]);
            //Recursion call to upheap to ensure the new parent(pos) follows minheap
            upheap(parent, weightArr);
        }




    }

    //After Removal in the Heap
    void downheap(int pos, int weightArr[]) {

            int left = 2 * pos + 1; //Left
            int right = 2 * pos + 2; // Right
            int i = pos; //The current pos or small it is looking at while comparing



            //Compare With left Child First
            if (left < size && weightArr[data[left]] < weightArr[data[i]]) {
                //If the left child exists and has a smaller weight than current smallest(i[pos]), update smallest being
                //to be left child
                i = left;
            }

            if (right < size && weightArr[data[right]] < weightArr[data[i]]) {
                //If the right child exist and has a smaller weight than the current smallest(i[pos]), update smallest
                //to be right child
                i = right;
            }

        //IF the smallest has changed to left or right child
            if (i != pos) {
                //Swap with the Parent with the smaller child
                swap(data[pos], data[i]);

                //continue the downheap recursively
                downheap(i, weightArr);
                }
        else {
            return; //Base Case if there is no child is smaller and stop recursion
        }
    }
};

#endif