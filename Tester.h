#ifndef TESTER_H
#define TESTER_H

#include <map>
#include <vector>

#include "NaiveBayesClassifier.h"
#include "Tweet.h"

class Tester {
   private:
    std::vector<Tweet> testingTweets;  // vector to hold testing tweets

    // comma positions for CSV parsing
    int IDID = -1;            // comma id location of id in CSV
    int TWID = -1;            // comma id of tweet location in CSV
    int sentimentCOMMA = -1;  // comma id tweet location in CSV
    int idCOMMA = -1;

   public:
    std::map<DSString, DSString> idSentimentMap;  // Map to hold tweet ID and its sentiment

    void parseTestingData(const char* filePath1);             // parse the testing data CSV to get the column indices
    void getTestingData(const char* filePath1);               // get the actual testing data from the CSV file
    void populateTestingVector(DSString id, DSString tweet);  // populates the testingTweets vector with Tweet objects from testingData
    void cleanTestingVector();                                // Clean the tweet texts in the testingTweets vector
    DSString clean(DSString& dirtyText);                      // returns a cleaned version of DSString ready for tokenizing
    void tokenizeTestingTweets();                             // tokenize the cleaned tweet for processing
    void openSentimentFile(const char* filePath2);            // open the sentiment file and get the column indices
    void mapTestingSentiments();                              // Map tweet IDs to their sentiments
    void printIdSentimentMap();                               // prints map

    std::vector<Tweet> getTestingTweets() const;  // returns testing tweets
};

#endif