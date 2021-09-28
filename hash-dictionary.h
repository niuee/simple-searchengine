#ifndef HASHDICTIONARY
#define HASHDICTIONARY
// Implementation of a dictionary using a hash table

#include "dictionary.h"
#include <vector>

using std::vector;

class HashDictionary : public Dictionary {
    // Add any member variables you need
    vector<vector<dictionaryEntry> > hashTableDictionary;
    int tableSize;
public:
    // Constructor
    HashDictionary();

    // Add a record to the dictionary. Returns false if key already exists
    bool addRecord( KeyType key, DataType record);

    // Find a key in the dictionary and return corresponding record or NULL
    DataType findRecord( KeyType key);

    // Add other methods you may need
    int hash(KeyType key);
    
};

#endif
