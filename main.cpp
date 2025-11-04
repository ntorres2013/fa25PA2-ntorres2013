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
    buildFrequencyTable(freq, "../input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("../input.txt", codes);

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

//    Case 1: There are no symbols
    if(nextFree == 0)
    {
        cout << "No symbols found" << endl;
        return -1; // placeholder
    }

//    Case 2: There is only one singular symbol (root)
    if(nextFree == 1)
    {
        return 0;
    }

//    Case 3: Normal case. Create a MinHeap object.
    MinHeap heap;

//    Push all leaf node indices into the heap.
    for(int i = 0; i < nextFree; i++)
    {
        heap.push(i, weightArr);
    }

    while (heap.size > 1)       // While heap size is greater than 1
    {
//        Pop the 2 smallest nodes
        int first = heap.pop(weightArr); // First smallest node
        int second = heap.pop(weightArr); // Second smallest node

        // Create a new internal parent node at index nextFree
        if (nextFree >= MAX_NODES)
        {
            return -1;
        }

        leftArr[nextFree] = first;        // left
        rightArr[nextFree] = second;       // right
        weightArr[nextFree] = weightArr[first] + weightArr[second];     // Combined weight
        charArr[nextFree] = '\0';  // null character

        // Push new parent index back into heap and increment nextFree
        heap.push(nextFree, weightArr);
        nextFree++;
    }

    // Return the index of the last remaining node (root)
    int root = heap.pop(weightArr);
    return root;
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
//    Case 1: No tree
    if(root == -1)
    {
        cout << "No tree to traverse" << endl;
        return;
    }

//    Case 2: Only one singular symbol. One-node-tree
    if (leftArr[root] == -1 && rightArr[root] == -1)
    {
        if (charArr[root] >= 'a' && charArr[root] <= 'z')
        {
            codes[charArr[root] - 'a'] = "0";
        }
        return;
    }

    // Case 3: Normal case — iterative DFS with a stack
    // Each stack entry holds (nodeIndex, pathBitsSoFar)
    stack<pair<int, string>> st;
    st.push({root, ""});

    while (!st.empty()) {
        auto [node, path] = st.top();
        st.pop();

        bool isLeaf = (leftArr[node] == -1 && rightArr[node] == -1);

        if (isLeaf) {
            // Assign code to the leaf character
            // (If path == "" this would be the single-node case, already handled.)
            char c = charArr[node];
            if (c >= 'a' && c <= 'z') {
                codes[c - 'a'] = path;
            }
        } else {
            // Push right first, then left — so left is processed first (optional)
            if (rightArr[node] != -1) {
                st.push({ rightArr[node], path + "1" });
            }
            if (leftArr[node] != -1) {
                st.push({ leftArr[node],  path + "0" });
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
