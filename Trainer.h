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
    int numGoodTweets = 0; //total # of tweets w 4 sentiment in training data
    int numBadTweets = 0; //total # of tweets w 0 sentiment in training data

   public:

    std::map<DSString, Token> tokenMap; //holds all training tokens 

    void parseTrainData(); // parse the testing data CSV

    // training
    void getTrainingData(); // get the testing data from the CSV file
    void populateTrainingVector(DSString sentiment, DSString id, DSString tweetTEXT); // populates the trainingTweets with Tweet objects from trainingData
    void cleanTrainingVector(); // Clean the tweet texts in the trainingTweets vector
    DSString clean(DSString& yuckyText); //Takes in a dirty string a returns the cleaned version

    // testing methods 
    void testTrainer();
    void print();

    // tokenizers
    void tokenizeAndMapTweets(); 
    void tokenizeTweets();
    std::vector<Tweet>& getTrainingTweets();

    // map members
    void filterBasicTokensFromMap(); //filters map tokens from current tokenMap
    //void filterStopWordsFromMap(); //gets rid of stop words to see if accuracy is better
    void printTokenMap(); // print map contents 
    void printTokenProbabilities();

//getters for probability class
    int getNumGoodTweets();
    int getNumBadTweets();

    
};

#endif