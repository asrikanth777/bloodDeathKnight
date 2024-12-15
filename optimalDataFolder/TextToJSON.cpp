#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <utility>
#include <cstring>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

// Struct for an item
struct item {
    string gearType;
    string itemName;
    string itemDropLoc;

    json to_json() const {
        return json{
            {"Gear Type", gearType},
            {"Item Name", itemName},
            {"Item Drop Location", itemDropLoc}
        };
    }
};

// Struct for a build
struct build {
    string buildDescription;
    vector<item> items;

    json to_json() const {
        json items_json = json::array();
        for (const auto& item : items) {
            items_json.push_back(item.to_json());
        }
        return json{
            {"Build Description", buildDescription},
            {"Items", items_json}
        };
    }
};

vector<build> parseTxtFile (const string& filename) {
    ifstream buildTextFile (filename);
    if (!buildTextFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
    }

    vector<build> allBuilds;
    build currentBuild;
    item currentItem;
    string line;
    
    while (getline(buildTextFile, line)) {
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);
    }
}

int main() {


}