#include <iostream>
#include <string>
#include <curl/curl.h>
#include <fstream>

using namespace std;

size_t ReturnTokenData(void* contents, size_t size, size_t nmemb, void* userp) {
    ((string*)userp) ->append((char*)contents, size * nmemb);
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
        string playerURL =  "https://us.api.blizzard.com/profile/wow/character/area-52/Purplenascar"
                            "?access_token=" + accesstoken;
        curl_easy_setopt(curlFetch, CURLOPT_URL, playerURL.c_str());
        curl_easy_setopt(curlFetch, CURLOPT_WRITEFUNCTION, ReturnTokenData);
        curl_easy_setopt(curlFetch, CURLOPT_WRITEDATA, &returnData);

        resFetch = curl_easy_perform(curlFetch);

        if (resFetch != CURLE_OK) {
            cerr << "Request failed: " << curl_easy_strerror(resFetch) << endl;
        } else {
            cout << "Character Data: " << returnData << endl;
        }


    }

    return 0;
}
