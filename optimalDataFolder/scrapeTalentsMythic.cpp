#include <iostream>
#include <string>
#include <curl/curl.h>
#include "json.hpp"
using json = nlohmann::json;
#include <fstream>
#include <sstream>
#include <gumbo.h>


using namespace std;

size_t FetchOptimalTalentMythicData(void* contents, size_t size, size_t nmemb, void* userp) {
    ((string*)userp) ->append((char*)contents, size * nmemb);
    // cout << "Appending Data: " << string((char*)contents, size * nmemb) << endl;
    return size * nmemb;
}

int main() {
    CURL* curlOptimalTalentMythic;
    CURLcode resOptimalTalentMythic;
    string returnDataOptimalTalentMythic;
    string OptimalTalentMythicURL = "https://www.wowhead.com/guide/classes/death-knight/blood/talent-builds-pve-tank";

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curlOptimalTalentMythic = curl_easy_init();

    if (curlOptimalTalentMythic) { 
        curl_easy_setopt(curlOptimalTalentMythic, CURLOPT_URL, OptimalTalentMythicURL);
        curl_easy_setopt(curlOptimalTalentMythic, CURLOPT_WRITEFUNCTION, FetchOptimalTalentMythicData);
        curl_easy_setopt(curlOptimalTalentMythic, CURLOPT_WRITEDATA, &returnDataOptimalTalentMythic);

        resOptimalTalentMythic = curl_easy_perform(curlOptimalTalentMythic);

        if (resOptimalTalentMythic != CURLE_OK) {
                cerr << "Request failed: " << curl_easy_strerror(resOptimalTalentMythic) << endl;
        } else {
            cout << "Response: " << returnDataOptimalTalentMythic << endl;
        }
    }

}
