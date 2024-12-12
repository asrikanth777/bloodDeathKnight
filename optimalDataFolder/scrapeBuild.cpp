#include <iostream>
#include <string>
#include <curl/curl.h>
#include "json.hpp"
using json = nlohmann::json;
#include <fstream>
using namespace std;

size_t ReturnOptimalBuildData(void* contents, size_t size, size_t nmemb, void* userp) {
    ((string*)userp) ->append((char*)contents, size * nmemb);
    // cout << "Appending Data: " << string((char*)contents, size * nmemb) << endl;
    return size * nmemb;
}

int main() {
    CURL* curlOptimalBuild;
    CURLcode resOptimalBuild;
    string returnOptimalBuildHTML;

    curlOptimalBuild = curl_easy_init();
    if (curlOptimalBuild) {
        string wowheadBuildURL = "https://www.icy-veins.com/wow/blood-death-knight-pve-tank-gear-best-in-slot?";
        curl_easy_setopt(curlOptimalBuild, CURLOPT_URL, wowheadBuildURL.c_str());
        cout << "Requesting URL: " << wowheadBuildURL << endl;

        curl_easy_setopt(curlOptimalBuild, CURLOPT_WRITEFUNCTION, ReturnOptimalBuildData);
        curl_easy_setopt(curlOptimalBuild, CURLOPT_WRITEDATA, &returnOptimalBuildHTML);

        resOptimalBuild = curl_easy_perform(curlOptimalBuild);

        long responseCodeOptimalBuild;
        curl_easy_getinfo(curlOptimalBuild, CURLINFO_RESPONSE_CODE, &responseCodeOptimalBuild);
        cout << "Response Code: " << responseCodeOptimalBuild << endl;

        if (resOptimalBuild != CURLE_OK) {
            cerr << "Request Failed: " << curl_easy_strerror(resOptimalBuild) << endl;
        } else {
            cout << "Character Data: " << returnOptimalBuildHTML << endl;
        }

        ofstream optimalBuildFile("optimalBuild.html");
        if (optimalBuildFile.is_open()) {
            optimalBuildFile << returnOptimalBuildHTML;
            optimalBuildFile.close();
            cout << "HTML response for Wowhead Optimal Builds has been saved to optimalBuild.html" << endl;
        } else {
            cerr << "Failed to open optimalBuild.html for writing" << endl;
        }

        curl_easy_cleanup(curlOptimalBuild);
        curl_global_cleanup();

    }

    return 0;
}
