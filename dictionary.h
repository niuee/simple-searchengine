#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
// Abstract class for a string dictionary

// KeyType is a string
typedef const char * KeyType;

// DataType is void *
typedef void * DataType;


struct dictionaryEntry{
    std::string _key;
    DataType _data;
};

class Dictionary {
public:
    // Add a record to the dictionary. Returns false if key already exists
    virtual bool addRecord( KeyType key, DataType record) = 0;
    
    // Find a key in the dictionary and return corresponding record or NULL
    virtual DataType findRecord( KeyType key) = 0;
};

#endif

