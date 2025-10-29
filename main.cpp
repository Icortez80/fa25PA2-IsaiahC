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
    //DUBUG LINES
    // cout << "freq[]: ";
    // for (int fre : freq) {
    //     if (fre > 0) {
    //         cout << fre << " ";
    //     }
    // }
    // cout << endl;

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    //debug line
    //cout << "nextFree: " << nextFree << endl;

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    //debug line
    //cout << "root: " << root;
    //cout << endl;

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

void debugFunction(MinHeap heap) {
    cout << "\nleftArr: ";
    for(int left: leftArr) {
        if (left != 0) {
            cout << left << " ";
        }
    }
    cout << "\nrightArr: ";
    for(int right: rightArr) {
        if (right != 0) {
            cout << right << " ";
        }
    }
    cout << endl;

    cout << "charArr: " << charArr << "\n";
    cout << "weightArr: ";
    for(int wght: weightArr) {
        if (wght > 0) {
            cout << wght << " ";
        }
    }
    cout << endl;
    heap.displayHeap();
}

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
    cout << endl;
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
    // TODO:
    // 1. Create a MinHeap object.
        MinHeap heap = MinHeap();
    // 2. Push all leaf node indices into the heap.
    for (int i = 0; i < 26; ++i) {
        if (weightArr[i] > 0) {
            heap.push(i, weightArr);
        }
    }
    //debug line
    //heap.displayHeap();

    // 3. While the heap size is greater than 1:
    //    - Pop two smallest nodes
    //    - Create a new parent node with combined weight
    //    - Set left/right pointers
    //    - Push new parent index back into the heap
    // 4. Return the index of the last remaining node (root)
    int parent = nextFree;
    while (heap.size > 1) {
        int temp1 = heap.pop(weightArr);
        int temp2 = heap.pop(weightArr);
        parent = nextFree++;

        if (weightArr[temp1] <= weightArr[temp2]) {
            leftArr[parent] = temp1;
            rightArr[parent] = temp2;
        }else {
            leftArr[parent] = temp2;
            rightArr[parent] = temp1;
        }

        weightArr[parent] = weightArr[temp1] + weightArr[temp2];
        charArr[parent] = '\0';
        heap.push(parent, weightArr);
    }

    //debug line
    //debugFunction(heap);

    return parent = heap.pop(weightArr);
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // Use stack<pair<int, string>> to simulate DFS traversal.
    stack<pair<int, string>> code;
    code.push(make_pair(root, ""));

    while (!code.empty()) {
        pair<int, string> topPair = code.top();
        code.pop();

        int node = topPair.first;
        string path = topPair.second;

        // If this node is a leaf, record its code
        if (leftArr[node] == -1 && rightArr[node] == -1) {
            int idx = charArr[node] - 'a';
            codes[idx] = path;
            //debug lines
            // if (charArr[node] != '\0') {
            //     cout << charArr[node] << " : " << path << endl;
            // }
        }
        else {
            if (rightArr[node] != -1)
                code.push({ rightArr[node], path + "1" });
            if (leftArr[node] != -1)
                code.push({ leftArr[node], path + "0" });
        }
    }

}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    //debug
    // cout << "codes[]: ";
    // for (int i = 0; i < 26; ++i) {
    //     cout << codes[i] << " ";
    // }
    // cout << endl;
    //end debug


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
