
// Implementation of a dictionary using an array and binary search
// It will inherit from the ArrayDictionary
#include <stdlib.h>
#include <string>
#include <list>
#include <iostream>
#include <vector>
#include "bsearch-dictionary.h"

using std::list;
using std::cout;
using std::endl;

// Constructor
BinarySearchDictionary::BinarySearchDictionary()
{
  // Add needed code
    
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
BinarySearchDictionary::findRecord( KeyType key)
{
    // Ue binary search
    // Add needed code
    sort();
    for(vector<dictionaryEntry>::iterator sItr = dictionaryArray.begin(); sItr != dictionaryArray.end(); sItr++){
        cout<<(*sItr)._key<<endl;
    }
    int left = 0;
    int right = dictionaryArray.size() - 1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(dictionaryArray[mid]._key.compare(key) < 0){
            left = mid + 1;
        }
        else if(!dictionaryArray[mid]._key.compare(key)){
            return dictionaryArray[mid]._data;
        }
        else{
            right = mid - 1;
        }
    }
    return NULL;
}

// Sort array using heap sort.
void
BinarySearchDictionary::sort()
{
    
    // Add needed code
    vector<dictionaryEntry> heapArray;
    heapArray.clear();
    for(vector<dictionaryEntry>::iterator itr = dictionaryArray.begin(); itr != dictionaryArray.end(); itr++){
        heapArray.push_back((*itr));
        upHeap(&heapArray);
    }
    dictionaryArray.clear();
    vector<dictionaryEntry>::iterator itrR = heapArray.begin();
    //Problem is here; after removing the first element (which is the min) need to take the last element in the vector and place it at the front
    while(itrR != heapArray.end()){
        dictionaryArray.push_back((*itrR));
        dictionaryEntry endEntry = heapArray.back();
        heapArray.front() = endEntry;
        heapArray.pop_back();
        itrR = heapArray.begin();
        downHeap(&heapArray);
    }
}

void
BinarySearchDictionary::upHeap(vector<dictionaryEntry> * array){
    int upHeapIndex = array->size() - 1;
    int parent = getParent(upHeapIndex);
    while(parent >= 0 && (array->at(upHeapIndex))._key.compare( array->at(parent)._key) < 0){
        dictionaryEntry temp = array->at(upHeapIndex);
        array->at(upHeapIndex) = array->at(parent);
        array->at(parent) = temp;
	upHeapIndex = parent;
        parent = getParent(upHeapIndex);
    }
}

void
BinarySearchDictionary::downHeap(vector<dictionaryEntry> * array){
    int downHeapIndex = 0;
    int lChild = getLChild(downHeapIndex);
    int rChild = getRChild(downHeapIndex);
    int smallerIndex;
    while(lChild < array->size()){
        if(rChild < array->size() && (array->at(rChild))._key.compare((array->at(lChild))._key) <  0){
            smallerIndex = rChild;
        }
        else{
            smallerIndex = lChild;
        }
        if((array->at(downHeapIndex))._key.compare((array->at(smallerIndex))._key) < 0){
            break;
        }
        else{
            dictionaryEntry temp = array->at(downHeapIndex);
            (*array)[downHeapIndex] = array->at(smallerIndex);
            (*array)[smallerIndex] = temp;
            downHeapIndex = smallerIndex;
            lChild = getLChild(downHeapIndex);
            rChild = getRChild(downHeapIndex);
        }
    }
}

int
BinarySearchDictionary::getLChild(int parent){
    return 2*parent + 1;
}


int
BinarySearchDictionary::getRChild(int parent){
    return 2*parent + 2;
}


int
BinarySearchDictionary::getParent(int child){
    return (child - 1) / 2;
}

