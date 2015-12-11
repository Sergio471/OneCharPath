#include <string>
#include <vector>
#include <utility>

using namespace std;

/*
 * Reads from a file and returns a pair of two input words for which path is to be found.
 */
pair<string, string> getWords(string const &fileName);

/*
 * Reads from a file and returns a vector of dictionary words.
 */
vector<string> getDictionary(string const &fileName);
