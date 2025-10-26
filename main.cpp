//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {

    // 1. Create a MinHeap object.
    MinHeap mHeap;

    // 2. Push all leaf node indices into the heap.
    //indices ==>(0 -> nextFree-1)
    for (int i=0; i < nextFree; ++i) {
        mHeap.push(i, weightArr);
    }

    // 3. While the heap size is greater than 1:
    while (mHeap.size > 1) {

        //    - Pop two smallest nodes( Either Left or Right)
        int left = mHeap.pop(weightArr);
        int right = mHeap.pop(weightArr);

        //    - Create a new parent node with combined weight
        int newParent = nextFree++;
        weightArr[newParent] = weightArr[left] + weightArr[right];

        //    - Set left/right pointers
        leftArr[newParent] = left;
        rightArr[newParent] = right;

        //    - Push new parent index back into the heap
        mHeap.push(newParent, weightArr);
    }

        // 4. Return the index of the last remaining node (root)
        return mHeap.pop(weightArr);

}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    //if heap is empty
    if (root == -1) {
        cout << "Empty Heap - no tree to generate codes." << endl;
        return;
    }

    // Use stack<pair<int, string>> to simulate DFS traversal.

    //Element -> (node index, current binary code)
    stack<pair<int, string>> codesStack;
    codesStack.push({root, ""});
    //Loop until all nodes are processed
    while (!codesStack.empty()) {
        //Get the top element
        pair<int, string> current = codesStack.top();
        codesStack.pop();

        //node index
        int node = current.first;

        //Current binary code path
        string code = current.second;

    //If the leaf node -> record the code
        if (leftArr[node] == -1 && rightArr[node] == -1) {
            if (charArr[node] >= 'a' && charArr[node] <= 'z') {
                codes[charArr[node] - 'a'] = code;
            }
        }
        else
            {
            //Transvering Right and Left Children
            // Left edge adds '0', right edge adds '1'.

            //Allows right -> left to processed first
            //Right edge adds '1'
            if (rightArr[node] != -1) {
                codesStack.push(make_pair(rightArr[node], code + "1"));
            }

            //Left edge adds '0'
            if (leftArr[node] != -1) {
                codesStack.push(make_pair(leftArr[node], code + "0"));
            }
        }
    }

}




// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}