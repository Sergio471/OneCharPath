/*
 * This is the core functionality of the program. To find a minimal path from one word to another, a graph is used.
 * In the graph, each node is a string. There is an edge between two nodes iff strings of those nodes differ by
 * a single character. The solution is to find the shortest path from one node to another in this graph.
 * Since weights of all edges equal to 1, BFS can be used to find the shortest path.
 *
 * To construct a graph, it is possible to iterate over all pairs of words, check if they differ by a single character,
 * and if they do, link them with an edge. However, the time complexity of such an approach is O(N^2) where N is the
 * number of words in a dictionary, which can be too big.
 * A better approach is to construct an underlying data structure which maps string replacements to  strings from which
 * the replacements were constructed. Replacements are constructed in such a way that two words which differ by a single
 * character share a single word replacement. This allows to get O(N*W) time complexity where W is the average length of
 * words from a dictionary.
 */

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <queue>

using namespace std;

/*
 * Returns a vector of string replacements of a given string.
 *
 * String replacements are constructed according to the rule:
 * 1. Pick a character, remove it from the string.
 * 2. Shift all remaining characters to the left.
 * 3. Append the position number of the removed character.
 * Example: "CAT" -> {"AT0", "CT1", "CA2"}
 */
vector<string> getStringReplacements(string const &s);

/*
 * Returns a replacement map constructed from a dictionary of words.
 * It maps string replacements to strings from which they constructed.
 * The data structure makes it easier to look up words, which differ
 * from a given word by a single character.
 */
void getReplMapFromDictionary(vector<string> &dict, unordered_map<string, vector<string> > &graph);

/*
 * Returns a collection words which differ from a given word s by a single character.ui
 */
vector<string> getNeighbors(string const &s, unordered_map<string, vector<string> > &replMap);

/*
 * Returns a correct minimal path from the string start to the string end.
 * The function uses Breadth First Search under the hood to find the shortest path.
 */
vector<string> getPath(string const &start, string const &end, unordered_map<string, vector<string> > &graph);
