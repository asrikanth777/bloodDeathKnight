#include <iostream>
#include <string>
#include <curl/curl.h>
#include "json.hpp"
#include <fstream>
#include <gumbo.h>
#include <map>
#include <vector>
#include <utility>
#include <regex>


using namespace std;
using json = nlohmann::json;

void searchForTitles(GumboNode* node, ofstream& talentOutputFile) {
    if (node->type != GUMBO_NODE_ELEMENT) {
        return;
    }
}

/*
since this program introduces a new header, gumbo, that I am unfamiliar with,
i am going to document every little thing about it for my clarity
*/

int main() {
    
    string talentHTMLstring;
    ifstream talentHTMLfile("optimalTalent.html");
    if (talentHTMLfile.is_open()) {
        talentHTMLstring = std::string((std::istreambuf_iterator<char>(talentHTMLfile)), std::istreambuf_iterator<char>());
        /*  first part reads the file content as a sequence of characters,
            the second part means that it reaches the end, or reads the entire file
        */
        talentHTMLfile.close();
        cout << "optimalTalent.html data saved into talentHTML string var" << endl;
        cout << talentHTMLstring.substr(0,100) << endl;
    } else {
        cerr << "Failed to open optimalTalent.html for opening" << endl;
    }
    
    /*

    regex talentRegex(R"(\[copy=\"([^\"]+)\"]([^\[]+)\[\/copy\])");
    // this part serves as an identifier, knowing that the info we want

    ofstream talentOutputFile("talent_builds.txt");
    if (!talentOutputFile.is_open()) {
        cerr << "Failed to open talent_builds.txt for writing builds!" << endl;
    }

    cout << "talent_builds.txt should be open" << endl;

    auto matchesBegin = sregex_iterator(talentHTMLstring.begin(), talentHTMLstring.end(), talentRegex);
    auto matchesEnd = sregex_iterator();

    cout << "should start going through html file here" << endl;

    int matchCount = 0;

    for (sregex_iterator it = matchesBegin; it != matchesEnd; ++it) {
        smatch match = *it;
        matchCount++;

        string talentTitle = match[1];
        cout << "talent title is " << talentTitle << endl;
        string exportString = match[2];

        cout << "variables overwritten" << endl;



        talentOutputFile << "Talent Build Title : " << talentTitle << endl;
        talentOutputFile << "Export String: " << exportString << endl;
        talentOutputFile << "---------------------------------------" << endl;
    }

    cout << "Total matchess found: " << matchCount << endl;


    cout << "Talent Builds have been written into 'talent_builds.txt'. " << endl;

    */

    return 0;



}
