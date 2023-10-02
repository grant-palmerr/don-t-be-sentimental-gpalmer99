#ifndef TRAINER_H
#define TRAINER_H

#include <map>
#include <set>
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
    std::set<

    void parseTrainData();

    // training
    void getTrainingData();
    void populateTrainingVector(DSString sentiment, DSString id, DSString tweetTEXT);
    void cleanTrainingVector();
    DSString clean(DSString& uncleanedText);

    // tests
    void testTrainer();
    void print();

    // tokenizers
    void tokenizeAndMapTweets();
    void tokenizeTweets();
    std::vector<Tweet>& getTrainingTweets();

    // map members
    void filterBasicTokensFromMap(); //filters map tokens from current tokenMap
    void filterStopWordsFromMap(); //gets rid of stop words to see if accuracy is better
    void printTokenMap(); // print map contents
    void printFilteredTokens(); //testing tokens that appear > 200 times 

    
};

#endif