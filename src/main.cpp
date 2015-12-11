#include <iostream>
#include <fstream>
#include <utility>

#include <input.hpp>
#include <graph.hpp>


using namespace std;

int main( int argc, char* argv[] )
{
    if (argc < 3)
    {
        cout << "Please provide two file names as parameters." << endl;
        return 0;
    }

    string inputWordsFile = argv[1];
    string dictionaryFile = argv[2];
    pair<string, string> words = getWords(inputWordsFile);
    vector<string> dictionary = getDictionary(dictionaryFile);
    unordered_map<string, vector<string> > replMap = getReplMapFromDictionary(dictionary);
    vector<string> path = getPath(words.first, words.second, replMap);
    
    for (auto it = path.begin(); it != path.end(); it++)
    {
        cout << *it << endl;
    }

    return 0;
}
