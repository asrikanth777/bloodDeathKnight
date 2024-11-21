#include <iostream>
#include <string>
#include <curl/curl.h>
#include <fstream>


int main() {
    using namespace std;

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

    return 0;
}
