
// Implementation of a dictionary using a hash table

#include <stdlib.h>
#include <string>
#include <vector>


#include "hash-dictionary.h"


using std::string;
using std::vector;

// Constructor
HashDictionary::HashDictionary()
{
  // Add needed code
    tableSize = 2053;
    hashTableDictionary.resize(2053);
}

// Add a record to the dictionary. Returns false if key already exists
bool
HashDictionary::addRecord( KeyType key, DataType record)
{
    // Add needed code
    int hashcode = hash(key);
    for(vector<dictionaryEntry>::iterator itr = hashTableDictionary[hashcode].begin(); itr != hashTableDictionary[hashcode].end(); itr++){
        if(!(*itr)._key.compare(key)){
            return false;
        }
    }
    dictionaryEntry newEntry = {._key = key, ._data = record};
    hashTableDictionary[hashcode].push_back(newEntry);
    return true;
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
HashDictionary::findRecord( KeyType key)
{
    int hashcode = hash(key);
    for(vector<dictionaryEntry>::iterator itr = hashTableDictionary[hashcode].begin(); itr != hashTableDictionary[hashcode].end(); itr++){
        if(!(*itr)._key.compare(key)){
            return (*itr)._data;
        }
    }
    
    return NULL;
}

int
HashDictionary::hash(KeyType key){
    string hashString = key;
    unsigned int hsum = 0;
    for(int i = 0; (unsigned)i < hashString.length(); i++){
        hsum += (unsigned) hashString[i];
    }
    return hsum % tableSize;
}

