#include <iostream>
#include <string>
#include <curl/curl.h>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

size_t ReturnTokenData(void* contents, size_t size, size_t nmemb, void* userp) {
    ((string*)userp) ->append((char*)contents, size * nmemb);
    // cout << "Appending Data: " << string((char*)contents, size * nmemb) << endl;
    return size * nmemb;
}

/*
for the above function, it is exactly like WriteCallback in post_request.cpp
the only difference is that it is handling data received from the api now
instead of response data for getting access token
*/


int main() {
    // recreating variables from post_request.cpp used to pull accesstoken data and write into file
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

    CURL* curlFetch;
    CURLcode resFetch;
    string returnData;

    curlFetch = curl_easy_init();
    if (curlFetch) {

        // creating URL
        string playerURL =  "https://us.api.blizzard.com/profile/wow/character/area-52/purplenascar?namespace=profile-us&locale=en_US";
        curl_easy_setopt(curlFetch, CURLOPT_URL, playerURL.c_str());
        cout << "Requesting URL: " << playerURL << endl;


        // designing headers
        struct curl_slist* fetchHeaders = NULL;
        string authHeader = "Authorization: Bearer " + accesstoken;
        fetchHeaders = curl_slist_append(fetchHeaders, authHeader.c_str());
        curl_easy_setopt(curlFetch, CURLOPT_HTTPHEADER, fetchHeaders);

        // sends resopnse through tokendata function and sends that info to returnData
        curl_easy_setopt(curlFetch, CURLOPT_WRITEFUNCTION, ReturnTokenData);
        curl_easy_setopt(curlFetch, CURLOPT_WRITEDATA, &returnData);


        // performs inquiry
        resFetch = curl_easy_perform(curlFetch);

        // this is to handle diff response codes like 401 and 404
        long responseCode;
        curl_easy_getinfo(curlFetch, CURLINFO_RESPONSE_CODE, &responseCode);
        cout << "Response Code: " << responseCode << endl;

        if (resFetch != CURLE_OK) {
            cerr << "Request failed: " << curl_easy_strerror(resFetch) << endl;
        } else {
            cout << "Character Data: " << returnData << endl;
        }

        // now to store the strings returned into a text file that can be parsed through later
        try {
            json returnJson = json::parse(returnData);

            ofstream playerDataFile("playerDATA.json");
            if (playerDataFile.is_open()) {
                playerDataFile << returnJson;
                playerDataFile.close();
                cout << "Player Data has been saved to playerDATA file" << endl;
            } else {
                cerr << "Failed to open playerDATA.txt for writing" << endl;
            }
        } catch (json::parse_error& e) {
            cerr << "Failed to upload correctly. " << endl;
        }


        /*figure out how to store character data here*/

        curl_easy_cleanup(curlFetch);
        curl_global_cleanup();


    }

    return 0;
}
