#include <string>
#include <fstream>
#include <vector>

#include <input.hpp>

using namespace std;

pair<string, string> getWords(string const &fileName)
{
    ifstream inputFile(fileName);
    pair<string, string> words;
    inputFile >> words.first >> words.second;

    return words;
}

vector<string> getDictionary(string const &fileName)
{
    ifstream inputFile(fileName);
    vector<string> dictionary;
    string buf;
    while (getline(inputFile, buf))
    {
        dictionary.push_back(buf);
    }

    return dictionary;
}
