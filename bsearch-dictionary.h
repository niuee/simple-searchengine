#ifndef BSEARCHDICTIONARY_H
#define BSEARCHDICTIONARY_H
// Implementation of a dictionary using an array and binary search
// The class inherits from ArrayDictionary
#include <vector>
#include "array-dictionary.h"


class BinarySearchDictionary : public ArrayDictionary {
  // Add any member variables you need

public:
    // Constructor
    BinarySearchDictionary();

    // No need for addRecord since it will use the one in ArrayDictionary

    // Find a key in the dictionary and return corresponding record or NULL
    // Use binary search
    DataType findRecord( KeyType key);

    // Sort array using heap sort.
    void sort();

    // Add other methods you may need
    void downHeap(vector<dictionaryEntry> * array);
    void upHeap(vector<dictionaryEntry> * array);
    void swap();
    
    int getLChild(int parent);
    int getRChild(int parent);
    int getParent(int child);
};


#endif

