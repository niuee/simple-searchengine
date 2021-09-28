
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>


#include "search-engine.h"


using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::list;

#define BILLION 1E9

SearchEngine::SearchEngine( int port, DictionaryType dictionaryType):
  MiniHTTPD(port)
{
    
    ifstream wifs("word.txt", std::ifstream::in);
    string read = "";
    string word = "";
    string indices = "";
    string indexNumber = "";
    switch (dictionaryType) {
        case ArrayDictionaryType:
            _wordToURLList = new ArrayDictionary();
            break;
        case HashDictionaryType:
            _wordToURLList = new HashDictionary();
            break;
        case BinarySearchDictionaryType:
            _wordToURLList = new BinarySearchDictionary();
            break;
        default:
            break;
    }
    
    list<int> * indexList = new list<int>();
    if(wifs.is_open()){
        while(getline(wifs,read)){
            int i = 0;
            bool wordRead = false;
            word = "";
            indexNumber = "";
            indexList = new list<int>();
            while(i < read.length()){
                if(read[i] != ' '){
                    if(!wordRead){
                        word = word + read[i];
                        i++;
                        continue;
                    }
                    else{
                        indexNumber = indexNumber + read[i];
                        if(i == read.length() - 1){
                            if(atoi(indexNumber.c_str())){
                                indexList->push_back(atoi(indexNumber.c_str()));
                            }
                            indexNumber = "";
                        }
                        i++;
                        continue;
                    }
                }
                else{
                    if(!wordRead){
                        wordRead = true;
                    }
                    else{
                        indexList->push_back(atoi(indexNumber.c_str()));
                        indexNumber = "";
                    }
                    i++;
                    continue;
                }
            }
//            for(list<int>::iterator itr = indexList->begin(); itr != indexList->end(); itr++){
//                cout<<(*itr)<<endl;
//            }
            _wordToURLList->addRecord(word.c_str(), indexList);
        }
        wifs.close();
    }
    
    
//    if(wifs.is_open()){
//        while(getline(wifs,read)){
//            if(!read.compare("Word: ")){
//                getline(wifs, word);
//            }
//            else if(!read.compare(0, 7, "Indices")){
//                indexList = new list<int>();
//                getline(wifs, indices);
//                for(int i = 0; i < indices.length(); i++){
//                    if(indices[i] == ',' || indices[i] == '.'){
//                        indexList->push_back(atoi(indexNumber.c_str()));
//                        indexNumber = "";
//                    }
//                    else if(indices[i] == ' '){
//                        continue;
//                    }
//                    else{
//                        indexNumber = indexNumber + indices[i];
//                    }
//                }
//                _wordToURLList->addRecord(word.c_str(), indexList);
//            }
//            else{
//                //
//            }
//        }
//        wifs.close();
//    }// end of reading the wordList.txt
    
    
    
//    list<int> * testing = (list<int> *)_wordToURLList->findRecord("Us");
//    for(list<int>::iterator testItr = testing->begin(); testItr != testing->end(); testItr++){
//        cout<<(*testItr)<<endl;
//    }
    
    
//    ifstream uifs("url.txt", std::ifstream::in);
//    string url = "";
//    string title = "";
//    string description = "";
//    if(uifs.is_open()){
//        while(getline(uifs, read)){
//            if(!read.compare(0, 4, "Url:")){
//                getline(uifs, url);
//            }
//            else if(!read.compare(0, 6, "Title:")){
//                getline(uifs, title);
//            }
//            else if(!read.compare(0, 12, "Description:")){
//                getline(uifs, description);
//                urlDescription newDescriptionEntry = {.title = title, .description = description, .url = url};
//                urlList.push_back(newDescriptionEntry);
//            }
//        }
//        uifs.close();
//    }// end of reading url list (_urlArray index)
//    for(vector<urlDescription>::iterator itr = urlList.begin(); itr != urlList.end(); itr++){
//        cout<<(*itr).title<<endl;
//        cout<<(*itr).description<<endl;
//        cout<<(*itr).url<<endl;
//    }
    
    
    ifstream uifs("url.txt", std::ifstream::in);
    string url = "";
    string title = "";
    string description = "";
    int readNumber = 0;
    bool indexRead = false;
    enum readingType{
        urlReading,
        descriptionReading,
    };
    readingType currentReading = urlReading;
    urlDescription newDescriptionEntry;
    int i = 0;
    
    url = "";
    description = "";
    indexNumber = "";
    if(uifs.is_open()){
        while(getline(uifs, read)){
            if(read.empty()){
                continue;
            }
            
            switch (currentReading) {
                case urlReading:
                    i = 0;
                    indexRead = false;
                    while(i < read.length()){
                        if( 48 <= read[i] && read[i] <= 57 && !indexRead){
                            indexNumber = indexNumber + read[i];
                            i++;
                        }
                        else if (read[i] == ' ' && !indexRead){
			    indexRead = true;
                            i++;
                            continue;
                        }
                        else{
                            url = url + read[i];
                            i++;
                            continue;
                        }
                    }
                    currentReading = descriptionReading;
		    std::cout<<"URL: "<<url<<std::endl;
                    break;
                case descriptionReading:
                    newDescriptionEntry.url = url;
                    newDescriptionEntry.description = read;
                    urlList.push_back(newDescriptionEntry);
                    url = "";
                    description = "";
                    currentReading = urlReading;
		    std::cout<<"Description: "<<read<<endl;
                    break;
                default:
                    break;
            }
            
            
        }
        uifs.close();
    }// end of reading url list (_urlArray index)
//    for(vector<urlDescription>::iterator itr = urlList.begin(); itr != urlList.end(); itr++){
        //cout<<"URL: "<<(*itr).url<<endl;
        //cout<<"Description: "<<(*itr).description<<endl;
//    }
    
    indexList = NULL;
    delete indexList;
    
    sumSearchTime = 0;
    searchNumber = 0;
}

void
SearchEngine::dispatch( FILE * fout, const char * documentRequested)
{
    struct timespec requestStart, requestEnd;
    clock_gettime(CLOCK_REALTIME, &requestStart);
    
    vector<string> searchWords;
    std::string word = "";
    std::string search = documentRequested;
    
    list<int> * iListCollective;
    list<int> * iListCurrent;
    list<int> iListCurrentM;
    list<int> iListCollectiveM;
    
    if (strcmp(documentRequested, "/")==0) {
        // Send initial form
        fprintf(fout, "<TITLE>CS251 Search</TITLE>\r\n");
        fprintf(fout, "<CENTER><H1><em>Boiler Search</em></H1>\n");
        fprintf(fout, "<H2>\n");
        fprintf(fout, "<FORM ACTION=\"search\">\n");
        fprintf(fout, "Search:\n");
        fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
        fprintf(fout, "</H2>\n");
        fprintf(fout, "</FORM></CENTER>\n");
        return;
    }
    
    if(!search.compare(0, 13, "/search?word=")){
        search = search.substr(13, search.length() - 13);
        cout<<"Search String: "<<search<<endl;
        for(int i = 0; i < search.length(); i++){
            if(search[i] == '+' && !word.empty()){
                searchWords.push_back(word);
                cout<<"Word is: "<<word<<endl;
                word = "";
            }
            else if(i == search.length() - 1 && !word.empty() && search[i] != '+'){
                word = word + search[i];
                searchWords.push_back(word);
                cout<<"Word is: "<<word<<endl;
                word = "";
            }
            else{
                if(search[i] == '+'){
                    continue;
                }
                else{
                    word = word + search[i];
                }
            }
        }
        
        
        if(searchWords.empty()){
            return;
        }
        else{
            std::cout<<"Starting word: "<<(*searchWords.begin())<<endl;
            string findWord = (*searchWords.begin());
            iListCollective = (list<int> *)_wordToURLList->findRecord(findWord.c_str());
            searchWords.erase(searchWords.begin());
            if(iListCollective == NULL){
                fprintf(fout, "<HR><H2>\n");
                fprintf(fout, "No Results<H2>\n");
                fprintf(fout, "<HR><H2>\n");
                fprintf(fout, "<FORM ACTION=\"search\">\n");
                fprintf(fout, "Search:\n");
                fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
                fprintf(fout, "</H2>\n");
                fprintf(fout, "</FORM>\n");
                return;
            }
            iListCollectiveM = *iListCollective;
        }
//        string findString = "Us";
//        list<int> * findList = (list<int> *)_wordToURLList->findRecord(findString.c_str());
//        for(list<int>::iterator findItr = iListCollective->begin(); findItr != iListCollective->end(); findItr++){
//            cout<<(*findItr)<<endl;
//        }
        
       
       
        for(vector<string>::iterator itr = searchWords.begin(); itr != searchWords.end(); itr++){
            iListCurrentM.clear();
            string findString = (*itr);
            iListCurrent = (list<int> *) _wordToURLList->findRecord(findString.c_str());
            
            
            
            
            if(iListCurrent != NULL){
                
                iListCurrentM = *iListCurrent;
                
                list<int>::iterator itrCurrentList = iListCurrentM.begin();
                
                list<int>::iterator itrCollectiveList = iListCollectiveM.begin();
                
                
                while(itrCurrentList != iListCurrentM.end() && itrCollectiveList != iListCollectiveM.end()){
                    
                   
                    if((*itrCollectiveList) == (*itrCurrentList)){
                        std::advance(itrCollectiveList, 1);
                        std::advance(itrCurrentList, 1);
                    }
                    else if ((*itrCollectiveList) > (*itrCurrentList)){
                        std::advance(itrCurrentList, 1);
                        if(itrCurrentList == iListCurrentM.end()){
                            itrCollectiveList = iListCollectiveM.erase(itrCollectiveList);
                        }
                    }
                    else{
                        itrCollectiveList = iListCollectiveM.erase(itrCollectiveList);
                    }
                }
                //cout<<(*itrCollectiveList)<<endl;
                if(itrCollectiveList != iListCollectiveM.end()){
                    iListCollectiveM.erase(itrCollectiveList, iListCollectiveM.end());
                }
                
            }
        }//end of the for loop for processing all the words in the find request sent
        
        if(iListCollectiveM.empty()){
            fprintf(fout, "<HR><H2>\n");
            fprintf(fout, "No Results<H2>\n");
            fprintf(fout, "<HR><H2>\n");
            fprintf(fout, "<FORM ACTION=\"search\">\n");
            fprintf(fout, "Search:\n");
            fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
            fprintf(fout, "</H2>\n");
            fprintf(fout, "</FORM>\n");
            return;
        }
        clock_gettime(CLOCK_REALTIME, &requestEnd);
        double searchTime = ( requestEnd.tv_sec - requestStart.tv_sec )+ ( requestEnd.tv_nsec - requestStart.tv_nsec ) / BILLION;
        printf( "%lf\n", searchTime );
        sumSearchTime += searchTime;
        searchNumber += 1;
        for(list<int>::iterator displayItr = iListCollectiveM.begin(); displayItr != iListCollectiveM.end(); displayItr++){
            fprintf(fout, "<div>");
            fprintf(fout, "%d",(*displayItr));
            fprintf(fout, " ");
            fprintf(fout, "<a href=\"");
            fprintf(fout, "%s\"> ", urlList[(*displayItr)].url.c_str());
            fprintf(fout, "%s </a>", urlList[(*displayItr)].url.c_str()); //modified here
            fprintf(fout, "<p> %s </p>", urlList[(*displayItr)].description.c_str());
            fprintf(fout, "</div>");
            
        }
        fprintf(fout, "<p> The search take: %.5f s.</p>", searchTime);
        fprintf(fout, "<p> The average search time is: %.5f s.</p>", (sumSearchTime / searchNumber));
        
        
        
        // Add search form at the end
        fprintf(fout, "<HR><H2>\n");
        fprintf(fout, "<FORM ACTION=\"search\">\n");
        fprintf(fout, "Search:\n");
        fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
        fprintf(fout, "</H2>\n");
        fprintf(fout, "</FORM>\n");
        word = "";
        return;
    }
    else{
        fprintf(fout, "<TITLE>CS251 Search</TITLE>\r\n");
        fprintf(fout, "<CENTER><H1><em>Boiler Search</em></H1>\n");
        fprintf(fout, "<H2>\n");
        fprintf(fout, "<FORM ACTION=\"search\">\n");
        fprintf(fout, "Search:\n");
        fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
        fprintf(fout, "</H2>\n");
        fprintf(fout, "</FORM></CENTER>\n");
        cout<<"Other Request"<<endl;
        return;
    }

    // TODO: The words to search in "documentRequested" are in the form
    // /search?word=a+b+c
    //
    // You need to separate the words before search
    // Search the words in the dictionary and find the URLs that
    // are common for al the words. Then print the URLs and descriptions
    // in HTML. Make the output look nicer.

    // Here the URLs printed are hardwired
}

void
printUsage()
{
  const char * usage =
    "Usage: search-engine port (array | hash | bsearch)\n"
    "  It starts a search engine at this port using the\n"
    "  data structure indicated. Port has to be larger than 1024.\n";

  fprintf(stderr, "%s", usage);
}

int main(int argc, char ** argv)
{
  if (argc < 3) {
    printUsage();
    return 1;
  }

  // Get port
  int port;
  sscanf( argv[1], "%d", &port);

  // Get DictionaryType
  const char * dictType = argv[2];
  DictionaryType dictionaryType;
  if (!strcmp(dictType, "array")) {
    dictionaryType = ArrayDictionaryType;
  }
  else if (!strcmp(dictType, "hash")) {
    dictionaryType = HashDictionaryType;
  }
  else if (!strcmp(dictType, "bsearch")) {
    dictionaryType = BinarySearchDictionaryType;
  }
  else {
    printUsage();
    return 0;
  }
  
  SearchEngine httpd(port, dictionaryType);
  
  httpd.run();

  return 0;
}
