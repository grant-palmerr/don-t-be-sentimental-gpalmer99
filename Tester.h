#ifndef TESTER_H
#define TESTER_H

#include <vector>

#include "Tweet.h"

class Tester {
   private:
    std::vector<Tweet> testingTweets;

    int IDID = -1;  // comma id location of id in CSV
    int TWID = -1;  // comma id of tweet location in CSV

   public:

    void parseTestingData();  // getting comma indexes from test_dataset
    void getTestingData();
    void populateTestingVector(DSString id, DSString tweet);
    void cleanTestingVector();
    DSString clean(DSString& dirtyText);
    void tokenizeTestingTweets();

};

#endif