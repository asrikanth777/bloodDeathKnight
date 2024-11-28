#include <iostream>
#include <string>
#include <curl/curl.h>
#include "json.hpp"
using json = nlohmann::json;
#include <fstream>
#include <sstream>

using namespace std;

int main() {
    string playerDATApath = "playerDATA.json";
    json playerData;
 
    ifstream playFile(playerDATApath);
    if (playFile.is_open()) {
        try {
            playFile >> playerData;
            playFile.close();
        } catch (json::parse_error& e) {
            cerr << "return data JSON file parsing error" << e.what() << endl;
        }
    } else {
        cerr << "Couldn't open API response data stored JSON file: " << playerDATApath << endl;
    }

    cout << "This is the the completed JSON object" << endl;
    cout << playerData << endl;

    int     characterID = playerData["id"];
    string  characterName = playerData["name"];
    string  characterFaction = playerData["faction"]["type"];
    string  characterRace = playerData["race"]["name"];
    string  characterClass = playerData["character_class"]["name"];
    string  characterClassSpec = playerData["active_spec"]["name"];
    string  characterRealm = playerData["realm"]["name"];
    int     characterLevel = playerData["level"];
    int     characterAchievementPoints = playerData["achievement_points"];
    int     characterItemLevel = playerData["equipped_item_level"];



    /* this is to 
    cout << characterID << endl;
    cout << characterFaction << endl;
    cout << characterName << endl;
    */

    return 0;
}
