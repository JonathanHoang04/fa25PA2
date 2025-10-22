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

        //Places new index at the end of the heap
        data[size] = idx;

        // Restore heap property
        upheap(size, weightArr);

        //Increase size of heap
        size++;

    }

    int pop(int weightArr[]) {

        if (size ==0) {
            return 0; //If the heap is empty
        }

        // Replace root with last element, then call downheap()

        int minimumIdx = data[0]; //Initializes smallest index in heap
        data[0] = data[size - 1]; // Move last leaf to become the new root of the heap tree
        size--; //Decrease Heap size

        //Calls DownHeap
        downheap(0, weightArr);

        //Gives the user lowest index from heap
        return minimumIdx;



        return -1; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent


    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child

        //Continue Looping until the heap property is restored
        while (true) {
            int left = 2 * (pos+1); //Left
            int right = 2*(pos+2); // Right
            int i = pos; //The current Parent


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

            if (i != pos) {
                //Swap with the Parent with the smaller child
                swap(data[pos], data[i]);

                //Make the "old" smallest to the child's position
                pos = i;

            }
            else
            {
                break; //The base condtion if the child is smaller than stop the loop
            }
        }
};

#endif