#ifndef TRAINER_H
#define TRAINER_H

#include <map>
#include <vector>

#include "DSString.h"
#include "Token.h"
#include "Tweet.h"

class Trainer {
   private:
    std::vector<Tweet> trainingTweets;

    int SID = -1;   // comma sentiment id location of sentiment in CSV
    int IDID = -1;  // comma id location of id in CSV
    int TWID = -1;  // comma id of tweet location in CSV

   public:

    std::map<DSString, Token> tokenMap;

    void parseTrainData();

    // tests
    void getTrainingData();
    void print();

    void populateTrainingVector(DSString sentiment, DSString id, DSString tweetTEXT);
    void cleanTrainingVector();
    void testTrainer();
    DSString clean(DSString& uncleanedText);
    void tokenizeTweets();
    std::vector<Tweet>& getTrainingTweets();
    
};

#endif