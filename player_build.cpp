#include <iostream>
#include <string>
#include <curl/curl.h>
#include "json.hpp"
using json = nlohmann::json;
#include <fstream>
#include <sstream>

using namespace std;

size_t FetchEquipmentData(void* contents, size_t size, size_t nmemb, void* userp) {
    ((string*)userp) ->append((char*)contents, size * nmemb);
    // cout << "Appending Data: " << string((char*)contents, size * nmemb) << endl;
    return size * nmemb;
}



int main() {
    string accesstoken;
    ifstream tokenFile("accessTOKEN.txt");

    // if tokenfile is available, it takes the text in the file and writes it into accesstoken
    // the error code is self explanatory
    if (tokenFile.is_open()) {
        getline(tokenFile, accesstoken);
        tokenFile.close();
        cout << "Access token loaded: " << accesstoken << endl;
    } else {
        cerr << "Failed to open accessTOKEN.txt to read for token" << endl;
    }

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

    string playerEquipmentURL = playerData["equpment"]["href"];

    CURL* curlEquip;
    CURLcode resEquip;
    string returnDataEquip;


    curlEquip = curl_easy_init();
    if (curlEquip) {
        curl_easy_setopt(curlEquip, CURLOPT_URL, playerEquipmentURL.c_str());
        cout << "Requesting URL: " << playerEquipmentURL << endl;

        struct curl_slist* equipHeaders = NULL;
        string authHeaderEquip = "Authorization: Bearer " + accesstoken;
        equipHeaders = curl_slist_append(equipHeaders, authHeaderEquip.c_str());
        curl_easy_setopt(curlEquip, CURLOPT_HTTPHEADER, equipHeaders);

        curl_easy_setopt(curlEquip, CURLOPT_WRITEFUNCTION, FetchEquipmentData);
        curl_easy_setopt(curlEquip, CURLOPT_WRITEDATA, &returnDataEquip);

        resEquip = curl_easy_perform(curlEquip);

        long responseCodeEquip;
        curl_easy_getinfo(curlEquip, CURLINFO_RESPONSE_CODE, &responseCodeEquip);
        cout << "Response Code: " << responseCodeEquip << endl;

        if (resEquip != CURLE_OK) {
            cerr << "Request failed: " << curl_easy_strerror(resEquip) << endl;
        } else {
            cout << "Equipment Data: " << endl;
            cout << returnDataEquip << endl;
        }

        try {
            json EquipJson = json::parse(returnDataEquip);
            ofstream EquipDataFile("PlayerEquipmentData.json");
            if (EquipDataFile.is_open()) {
                EquipDataFile << EquipJson;
                EquipDataFile.close();
                cout << "Player Equipment Data has been saved to PlayerEquipmentData.json" << endl;
            } else {
                cerr << "Failed to open PlayerEquipmentData.json for writing " << endl;
            }
        } catch (json::parse_error& e) {
            cerr << "Failed to upload correctly. " << endl;
        }

        curl_easy_cleanup(curlEquip);
        curl_global_cleanup();

        
    }
    
    return 0;
}