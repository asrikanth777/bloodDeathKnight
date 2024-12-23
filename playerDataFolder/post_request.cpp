#include <iostream>
#include <string>
#include <curl/curl.h>
#include "json.hpp"
using json = nlohmann::json;


//this is to save access token info so it doesnt have to be copy pasted
#include <fstream>

/*
this is to automate the part that accesses my application to get
an access token that helps me receive data about my character

the token allowes me to make requests to Blizzard's API without
needing to manually provide client_id and client_secret every time

this is done by writing a POST request to Blizzard's OAuth token endpoint with
- grant_type=client_credentials
- clientid
- clientsecret

Diagram : client (with id and secret) -> access token -> api -> char data
*/

using namespace std;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    /* void* contents = pointer to chunk of data received
       size_t size = size of element in contents
       size_t nmemb = number of elements in contents
       (size * nmemb should equal the total amount of data given)
       void* userp = directs where data should go to (like giving an address)
    */
   ((string*)userp) ->append((char*)contents, size * nmemb);
   //changes pointer type for userp to string to better handle data
   /* this adds on to userp the data pulled from contents : 
   changes void* contents to char* contents to handle strings
   second part indicates length, which is size * nmemb
   */

   return size * nmemb; //make sure we have all the data needed

   /* this function is basically like a kitchen
    chef -> WriteCallback()
    ingredients -> contents
    proportions -> size and nmemb
    waiter -> userp
    chef is given ingredients and proportions, it makes the food and double checks that
    it is correct meal, then it is given to waiter, and he is later given direction
    on where to give it to
   */
}



int main() {
    // Building the request with libcurl to handle HTTP requests

    // the "username" and "password" to use the client that pulls my character data
    string clientID = "2b9689144d51429f8322b860870d6547";
    string clientSECRET = "qdujUTCiyHIZMxa8qSh216azvOxtSo8k";

    CURL* curl; //pointer to curl object that libcurl uses for the http request
    /*  CURL = data structure that holds info about the request
        CURL* = pointer that gives location of that data structure
    */

    CURLcode  res; //enum to represent outcomes of libcurl function call, like return 0
    /* res is variable that stores request's result, and its value indicates of execution
    was successful
    CURLE_OK (request worked), anything else means it failed 
    */
    string readBuffer; //stores response data received from server request

    curl_global_init(CURL_GLOBAL_DEFAULT); 
    //  global_init() allows libcurl to be used globally in the program
    //  global_default sets up the normal settings for libcurl's resources to be used
    
    curl = curl_easy_init();
    // sets up CURL object to store information from the HTTP request, like getting a bucket before turning on the faucet

    if (curl) {
        // this is to setup URL we are reaching to
        curl_easy_setopt(curl, CURLOPT_URL, "https://us.battle.net/oauth/token");
        /*
        curl -> where information will be stored for handling the http request
        CURLOPT_URL -> the option of request we are using, which is a url
        https://.... -> the URL we are accessing, which is the OAuth token endpoint provided by blizzard to get an access token
        */



        // here we set up our headers, prompting the server about what we are asking for
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
        /* this is like sending an email to the server
        curl_slist is like the subject of the email, and the headers variable is like the box that you write in, the subject line (points to it).
        we then start writing bits of our subject line (appending to curl_slist through headers)
        */
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        // so now that we have our completed header, we are telling libcurl that here is our header that we custom wrote, which var headers points to  



        // now we set up the body of our message, with our credentials to obtain access token  
        string POSTfields = "grant_type=client_credentials&scope=wow.profile&client_id=" + clientID + "&client_secret=" + clientSECRET;
        // this is setting up the request we are sending, the exact client, and the "password for it"
        // its like showing an invitation at the door, with the party address, and our name

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, POSTfields.c_str()); // c_str just makes it from c++ string (std::string) to const char*



        // set the callback function to handle response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        /*  1st part passes data received to the WriteCallback(), which breaks down the info received accordingly
            2nd part shows where the newly processed data should go to, which is readBuffer

            this is so that when data comes in streams, the chunks are appended accordingly, almost like making nachos
            you have ur chips first, then sauce, then topppings, and then the product is then handed to you */

        

        res = curl_easy_perform(curl);
        // handles the actual execution of requesting info from the url given and sending data
        // the response it gets indicates whether it was successful or not

        if (res != CURLE_OK) {
            cerr << "Request failed: " << curl_easy_strerror(res) << endl; //converts teh CURLcode enum value to a readable error message
        } else {
            cout << "Response: " << readBuffer << endl; 

            // Parsing through response to get the access token to put into text file
            // ADD COMMENTARY TONIGHT!!!!!!
            try {
                // turns the string response into a json object, making it easy to separate by field
                json responseJson = json::parse(readBuffer);
                string accessToken = responseJson["access_token"];
                // pulls out the specific response in access_token and puts it into a string



                // creates a text file named accessTOKEN
                ofstream tokenFile("accessTOKEN.txt");

                // if the text file is open, then it is over written with accessToken and closed so it can be used later
                if (tokenFile.is_open()) {
                    tokenFile << accessToken;
                    tokenFile.close();
                    cout << "Access token has been saved to accessTOKEN.txt" << endl;
                } else {
                    // this is if the text file doesnt open or isn't created correctly
                    cerr << "Failed to open accessTOKEN.txt for writing." << endl;
                }
            } catch (json::parse_error& e) {
                // triggers if readbuffer is not a valid response (like if it is giving an error response)
                cerr << "Failed to parse response: " << e.what() << endl;
            } catch (json::out_of_range& e) {
                // triggers if readbuffer doesn't have the access token
                cerr << "Expected field not found in response: " << e.what() << endl;
            } 
        }

        // Clean up
        
        curl_easy_cleanup(curl);
        // frees up the resources that curl used, making that memory reusable
        curl_global_cleanup();
        // does the same thing, but cleans up the resources globally, and anything outside of the initial request

    }
    return 0;   
    // IT WORKS YESSSSSSSSSSS
}

// When compiling, dont forget to write libcurl
// g++ -o post_request post_request.cpp -lcurl