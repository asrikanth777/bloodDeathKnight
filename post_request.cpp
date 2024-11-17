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
    /* INI
    */
    return 0;   
}