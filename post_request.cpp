#include <iostream>
#include <string>
#include <curl/curl.h>

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
    CURLE_OK (request worked), everything else means it failed 
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
        string POSTfields = "grant_type=client_credentials&client_id=" + clientID + "&client_secret" + clientSECRET;
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
        

        
        
               
        
    }
    return 0;   
}