#define CATCH_CONFIG_MAIN
#include <string>
#include <utility>
#include <vector>
#include <cstdlib>
#include <time.h>

#include <catch.hpp>
#include <input.hpp>
#include <graph.hpp>

using namespace std;

#define RANDOMIZED_TEST_NUM 100

/*
 * Tests if two input words are read correctly from a file.
 */
TEST_CASE( "Input words", "[words]" )
{
    pair<string, string> words = getWords("../inputFiles/words.txt");
    REQUIRE( words.first  == "CAT"  );
    REQUIRE( words.second == "BAR" );
}

/*
 * Tests if dictionary of words is read correctly from a file.
 */
TEST_CASE( "Input dictionary", "[dict]" )
{
    vector<string> dictionary = getDictionary("../inputFiles/dict.txt");
    REQUIRE( dictionary.size() == 14 );
    REQUIRE( dictionary[0] == "CAT" );
    REQUIRE( dictionary[dictionary.size() - 1] == "TOT" );

    vector<string> emptyDictionary = getDictionary("../inpuFiles/emptyDict.txt");
    REQUIRE( emptyDictionary.size() == 0 );
}

/*
 * Tests if getting word replacements works correctly.
 */
TEST_CASE( "Word replacements", "[repl]" )
{
    vector<string> v1 = {"AT0", "CT1", "CA2"};
    REQUIRE( getStringReplacements("CAT") == v1 );
    vector<string> v2 = {"0"};
    REQUIRE( getStringReplacements("K") == v2);
}

/*
 * Tests if underlying data structure works correctly. File dict.txt is used as a source of dictionary words.
 */
TEST_CASE( "Graph construction and neighbors", "[graph]" )
{
    vector<string> dictionary = getDictionary("../inputFiles/dict.txt");
    unordered_map<string, vector<string> > replMap;
    getReplMapFromDictionary(dictionary, replMap);

    // Tests if a word replacement maps to correct vector of strings.
    vector<string> v1 = {"CAT", "FAT", "BAT"};
    REQUIRE( replMap["AT0"] == v1 );

    // Tests if getting neigbors of a word in a graph works correctly.
    SECTION( "Neighbors checking" )
    {
        vector<string> nbrs = getNeighbors("CAT", replMap);
        set<string> nbrsSet(nbrs.begin(), nbrs.end());
        set<std::string> trueNbrsSet = {"FAT", "BAT", "CAR"};
        REQUIRE( nbrsSet == trueNbrsSet );

        vector<string> nbrs2 = getNeighbors("ROSE", replMap);
        set<string> nbrsSet2(nbrs2.begin(), nbrs2.end());
        set<std::string> trueNbrsSet2 = {"ROPE", "ROLE", "POSE"};
        REQUIRE( nbrsSet2 == trueNbrsSet2 );
    }

    // Tests if getting paths from one word to another works correctly.
    // Paths must be correct and minimal.
    SECTION( "Path checking" )
    {
        vector<string> path = getPath("CAT", "BAR", replMap);
        vector<string> truePath = {"CAT", "BAT", "BAR"};
        REQUIRE( path == truePath );

        vector<string> path2 = getPath("LOT", "BAT", replMap);
        vector<string> truePath2 = {};
        REQUIRE( path2 == truePath2 );

        vector<string> path3 = getPath("LOT", "TOT", replMap);
        vector<string> truePath3 = {"LOT", "TOT"};
        REQUIRE( path3 == truePath3 );

        vector<string> path4 = getPath("POPE", "ROSE", replMap);
        vector<string> truePath4 = {"POPE", "ROPE", "ROSE"};
        REQUIRE( path4 == truePath4 );
    }
}

/*
 * Helper function to determine if two strings differ by a single character.
 */
bool diffByOne(string const &s1, string const &s2)
{
    if (s1.length() != s2.length())
    {
        return false;
    }

    int numOfDiffs = 0;

    for (int i = 0; i < s1.length() && numOfDiffs < 2; i++)
    {
        if (s1[i] != s2[i])
            numOfDiffs++;
    }

    if (numOfDiffs > 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/*
 * Randomized test takes RANDOMIZED_TEST_NUM pairs of words from a big dictionary (BigDict.txt),
 * finds a path from one to another and checks if the path is correct. The path is correct iff
 * consecutive strings in the path differ by a single character. This test doesn't check if a path
 * is minimal.
 */
TEST_CASE( "Final randomized test on a big dictionary", "[final]" )
{
    vector<string> dictionary = getDictionary("../inputFiles/BigDict.txt");
    unordered_map<string, vector<string> > replMap;
    getReplMapFromDictionary(dictionary, replMap);

    srand(time(NULL));

    for (int i = 0; i < RANDOMIZED_TEST_NUM; i++)
    {
        int pos1 = rand() % dictionary.size();
        int pos2 = rand() % dictionary.size();
        while (pos2 == pos1)
            pos2 = rand() %  1000;

        vector<string> path = getPath(dictionary[pos1], dictionary[pos2], replMap);
        if (path.size() == 0)
            continue;
        bool diffByOneCondition = true;

        for (int j = 0; j < path.size() - 1 && diffByOneCondition; ++j)
        {
            if (!diffByOne(path[j], path[j+1]))
                diffByOneCondition = false;
        }
        REQUIRE( diffByOneCondition == true );
    }
}
