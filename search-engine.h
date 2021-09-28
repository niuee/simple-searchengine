#include <vector>
#include <string>


#include "minihttpd.h"
#include "dictionary.h"
#include "array-dictionary.h"
#include "bsearch-dictionary.h"
#include "hash-dictionary.h"

// Types of dictionaries used
enum DictionaryType {
  ArrayDictionaryType,
  HashDictionaryType,
  AVLDictionaryType,
  BinarySearchDictionaryType
};

struct urlDescription{
    std::string title;
    std::string description;
    std::string url;
};

// Inherits from MiniHTTPD
class SearchEngine : public MiniHTTPD {
    Dictionary * _wordToURLList;
    std::vector<urlDescription> urlList;
    double sumSearchTime;
    double searchNumber;
    // Add any other member variables you need
public:
    // Constructor for SearchEngine
    SearchEngine( int port, DictionaryType dictionaryType);

    // Called when a request arrives
    void dispatch( FILE * out, const char * requestLine );
    
};



