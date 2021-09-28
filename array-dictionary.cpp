
// Implementation of a dictionary using an array and sequential search
// The array will be dynamically resized if necessary

#include <stdlib.h>
#include <string>
#include <list>
#include <vector>


#include "array-dictionary.h"


using std::string;
using std::list;
using std::vector;

// Constructor
ArrayDictionary::ArrayDictionary()
{
    // Add needed code
}

// Add a record to the dictionary. Returns false if key already exists
bool
ArrayDictionary::addRecord( KeyType key, DataType record)
{
    for(vector<dictionaryEntry>::iterator itr = dictionaryArray.begin(); itr != dictionaryArray.end(); itr++){
        if(!(*itr)._key.compare(key)){
            //don't add stuff
            return false;
        }
    }
    
    //key not found
    dictionaryEntry newEntry = {._key = key, ._data = record};
    dictionaryArray.push_back(newEntry);
    return true;
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
ArrayDictionary::findRecord( KeyType key)
{
    for(vector<dictionaryEntry>::iterator itr = dictionaryArray.begin(); itr != dictionaryArray.end(); itr++){
        if(!(*itr)._key.compare(key)){
            return (*itr)._data;
        }
    }
    return NULL;
}


