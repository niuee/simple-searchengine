#ifndef ADICTIONARY_H
#define ADICTIONARY_H
// Implementation of a dictionary using an array and sequential search
// The array will be dynamically resized if necessary
#include <string>
#include <list>
#include <vector>
#include "dictionary.h"

using std::string;
using std::list;
using std::vector;


class ArrayDictionary : public Dictionary {
    // Add any member variables you need
protected:
    vector<dictionaryEntry> dictionaryArray;
  
public:
    // Constructor
    ArrayDictionary();

    // Add a record to the dictionary. Returns false if key already exists
    bool addRecord( KeyType key, DataType record);

    // Find a key in the dictionary and return corresponding record or NULL
    // Use sequential search
    DataType findRecord( KeyType key);

    // Add other methods you may need
};

#endif
