#include <iostream>
#include <string>
#include <curl/curl.h>
#include "json.hpp"
using json = nlohmann::json;
#include <fstream>
using namespace std;

size_t ReturnOptimalTalentData(void* contents, size_t size, size_t nmemb, void* userp) {
    ((string*)userp) ->append((char*)contents, size * nmemb);
    // cout << "Appending Data: " << string((char*)contents, size * nmemb) << endl;
    return size * nmemb;
}

int main() {
    CURL* curlOptimalTalent;
    CURLcode resOptimalTalent;
    string returnOptimalTalentHTML;

    curlOptimalTalent = curl_easy_init();
    if (curlOptimalTalent) {
        string wowheadURL = "https://www.wowhead.com/guide/classes/death-knight/blood/talent-builds-pve-tank";
        curl_easy_setopt(curlOptimalTalent, CURLOPT_URL, wowheadURL.c_str());
        cout << "Requesting URL: " << wowheadURL << endl;

        curl_easy_setopt(curlOptimalTalent, CURLOPT_WRITEFUNCTION, ReturnOptimalTalentData);
        curl_easy_setopt(curlOptimalTalent, CURLOPT_WRITEDATA, &returnOptimalTalentHTML);

        resOptimalTalent = curl_easy_perform(curlOptimalTalent);

        long responseCodeOptimalTalent;
        curl_easy_getinfo(curlOptimalTalent, CURLINFO_RESPONSE_CODE, &responseCodeOptimalTalent);
        cout << "Response Code: " << responseCodeOptimalTalent << endl;

        if (resOptimalTalent != CURLE_OK) {
            cerr << "Request Failed: " << curl_easy_strerror(resOptimalTalent) << endl;
        } else {
            cout << "Character Data: " << returnOptimalTalentHTML << endl;
        }

        ofstream optimalTalentFile("optimalTalent.html");
        if (optimalTalentFile.is_open()) {
            optimalTalentFile << returnOptimalTalentHTML;
            optimalTalentFile.close();
            cout << "HTML response for Wowhead Optimal Talents has been saved to optimalTalent.html" << endl;
        } else {
            cerr << "Failed to open optimalTalent.html for writing" << endl;
        }

        curl_easy_cleanup(curlOptimalTalent);
        curl_global_cleanup();

    }

    return 0;
}
