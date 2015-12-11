#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <queue>

#include "graph.hpp"

using namespace std;

vector<string> getStringReplacements(string const &s)
{
    vector<string> replacements;

    for (int i = 0; i < s.size(); i++)
    {
        string repl = s.substr(0, i) + s.substr(i + 1, s.size() - i - 1) + to_string(i);
        replacements.push_back(repl);
    }

    return replacements;
}

unordered_map<string, vector<string> > getReplMapFromDictionary(vector<string> &dict)
{
    unordered_map<string, vector<string> > graph;
    
    for (auto &w : dict)
    {
        vector<string> replacements = getStringReplacements(w);
        for (auto &r : replacements)
        {
            graph[r].push_back(w);
        }
    }

    return graph;
}

vector<string> getNeighbors(string const &s, unordered_map<string, vector<string> > &graph)
{
    vector<string> nbrs;
    vector<string> replacements = getStringReplacements(s);
    
    for (auto &r : replacements)
    {
        vector<string> candidateNbrs = graph[r];
        for (auto &cNbr : candidateNbrs)
        {
            if (cNbr != s)
            {
                nbrs.push_back(cNbr);
            }
        }
    }
    
    return nbrs;
}

vector<string> getPath(string const &start, string const &end, unordered_map<string, vector<string> > &graph)
{
    queue<string> q;
    q.push(start);
    unordered_set<string> visited;
    visited.insert(start);

    // Maps a node to the path to this node
    unordered_map<string, vector<string> > paths;
    paths[start].push_back(start);

    while (!q.empty())
    {
        string cur = q.front();
        q.pop();
        vector<string> nbrs = getNeighbors(cur, graph);
        
        for (auto &nbr : nbrs)
        {
            if (visited.find(nbr) != visited.end())
                continue;
            else
                visited.insert(nbr);
            if (nbr == end)
            {
                vector<string> &path = paths[cur];
                path.push_back(nbr);
                return path;
            }
            q.push(nbr);

            vector<string> pathToNbr(paths[cur].begin(), paths[cur].end());
            pathToNbr.push_back(nbr);
            paths[nbr] = pathToNbr;
        }
    }

    return vector<string>();
}
