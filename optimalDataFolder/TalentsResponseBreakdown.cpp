#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <utility>
#include <regex>


using namespace std;



/*
since this program introduces a new header, gumbo, that I am unfamiliar with,
i am going to document every little thing about it for my clarity
*/

int main() {
    
    string talentHTMLstring;
    ifstream talentHTMLfile("optimalTalent.html");
    string htmlLine;
    vector<string> talentTitles;
    vector<string> exportStrings;
    int matchCount = 0;

    while (getline(talentHTMLfile, htmlLine)) {
        if (htmlLine.find("WH.markup.printHtml") != string::npos) {
            cout << "found line" << endl;
            regex talentRegex("\\[copy=\\\\\"([^\"]*)\\\\\"\\]([A-Za-z0-9]+)\\[\\\\/copy\\]"); 
            smatch matches;


            for (sregex_iterator it(htmlLine.begin(), htmlLine.end(), talentRegex), end; it != end; ++it) {
                matchCount++;

                cout << it->str(0) << endl;    // Full match
                cout << it->str(1) << endl;    // Capture group 1 (talent title)
                cout << it->str(2) << endl;    // Capture group 2 (export string)

                string talent_title = it->str(1);
                string export_string = it->str(2);

                talentTitles.push_back(talent_title);
                exportStrings.push_back(export_string);

                cout << "Talent Tree Title: " << talent_title << endl;
                cout << "Export String: " << export_string << endl;
                cout << "-------------------------------" << endl;
            }
        }
    }

    int overwriteCounter = 0;
    cout << "match count: " << matchCount << endl;
    ofstream talentBuildSheet("talent_builds.txt");
    if (talentBuildSheet.is_open()){
        talentBuildSheet << "updated talents" << endl;
        for (overwriteCounter =0; overwriteCounter < matchCount; overwriteCounter++) {
            talentBuildSheet << talentTitles[overwriteCounter] << " : " << exportStrings[overwriteCounter] << endl;
        }
        talentBuildSheet.close();
        cout << "Talent Builds are uploaded to talent_builds.txt" << endl;
    } else {
        cerr << "Failed to open talent_builds.txt for writing" << endl;
    }
    
    

    return 0;



}
