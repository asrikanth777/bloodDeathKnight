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
    
    string buildHTMLstring;
    ifstream buildHTMLfile("optimalBuild.html");
    string htmlLine;
    vector<string> equipBody;
    vector<string> itemIDnumber;
    int matchCount = 0;

    while (getline(buildHTMLfile, htmlLine)) {
        if (htmlLine.find("WH.markup.printHtml") != string::npos) { // CHANGE THIS LATER!!!!!!
            cout << "found line" << endl;
            regex buildRegex("\\[copy=\\\\\"([^\"]*)\\\\\"\\]([A-Za-z0-9]+)\\[\\\\/copy\\]"); 
            smatch matches;


            for (sregex_iterator it(htmlLine.begin(), htmlLine.end(), buildRegex), end; it != end; ++it) {
                matchCount++;

                cout << it->str(0) << endl;    // Full match
                cout << it->str(1) << endl;    // Capture group 1 (build title)
                cout << it->str(2) << endl;    // Capture group 2 (export string)

                string equip_body = it->str(1);
                string item_id = it->str(2);

                equipBody.push_back(equip_body);
                itemIDnumber.push_back(item_id);

                cout << "build Tree Title: " << equip_body << endl;
                cout << "Export String: " << item_id << endl;
                cout << "-------------------------------" << endl;
            }
        }
    }

    int overwriteCounter = 0;
    cout << "match count: " << matchCount << endl;
    ofstream buildTableSheet("build_table.txt");
    if (buildTableSheet.is_open()){
        buildTableSheet << "updated builds" << endl;
        for (overwriteCounter = 0; overwriteCounter < matchCount; overwriteCounter++) {
            buildTableSheet << buildTitles[overwriteCounter] << " : " << exportStrings[overwriteCounter] << endl;
        }
        buildTableSheet.close();
        cout << "build Builds are uploaded to build_builds.txt" << endl;
    } else {
        cerr << "Failed to open build_builds.txt for writing" << endl;
    }
    
    

    return 0;



}
