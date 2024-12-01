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

/*
since this program introduces a new header, gumbo, that I am unfamiliar with,
i am going to document every little thing about it for my clarity
*/

void parseTalentBuilds(const string& talentHTML) {
    regex talentStringRegex(R"(\[dragonflight-talent-calc=blizzard\\/([^\]]+)\])");
    regex talentTitleREgex(R"(\[tab name=\"([^\"]+)\"])");
    // this part serves as an identifier, knowing that the info we want
    // will be encoded in lines like these for export strings and titles

    smatch match;
    // smatch is class used to store matches from regex search in a string format

    string::const_iterator searchStart(talentHTML.cbegin());

    
    string currentTitle = "Untitled Build"; 
}



int main() {
    ifstream talentHTMLfile("optimalTalent.html");
    if (talentHTMLfile.is_open()) {
        string talentHTML ((istreambuf_iterator<char>(talentHTMLfile)), istreambuf_iterator<char>());
        /*  first part reads the file content as a sequence of characters,
            the second part means that it reaches the end, or reads the entire file
        */
        talentHTMLfile.close();
        cout << "optimalTalent.html data saved into talentHTML string var" << endl;
    } else {
        cerr << "Failed to open optimalTalent.html for opening" << endl;
    }
    
}
