#include <iostream>
#include <string>
#include <curl/curl.h>
#include "json.hpp"
using json = nlohmann::json;
#include <fstream>
#include <sstream>

using namespace std;

int main() {
    string playerDATApath = "playerDATA.txt";
    stringstream playerDATAbuffer;
    string playerDATAcontent;
    json playerData;

    ifstream playFile(playerDATApath);
    if (playFile.is_open()) {
        playerDATAbuffer << playFile.rdbuf();
        playerDATAcontent = playerDATAbuffer.str();
        playFile.close();
    } else {
        cerr << "Error: Couldn't open file" << playerDATApath << endl;
    }

    try {
        playerData = json::parse(playerDATAcontent);
    } catch (json::parse_error& e) {
        cerr << "JSON parsing error: " << e.what() << endl;
    }
}