#include "NaiveBayesClassifier.h"

#include <cmath>

//tried to incporoate naive bayes classification to classify my tweets 

NaiveBayesClassifier::NaiveBayesClassifier(Trainer& trainer) {
    // intialize prior probabilities
    priorGood = (double)trainer.getNumGoodTweets() / (trainer.getNumGoodTweets() + trainer.getNumBadTweets());
    priorBad = 1.0 - priorGood;

    // and initialize token probabilities
    calculateTokenProbabilities(trainer);
}

void NaiveBayesClassifier::calculateTokenProbabilities(Trainer& trainer) {
    // calculates probabilities here based on the tokenMap in Trainer
    int totalGoodTokens = 0;
    int totalBadTokens = 0;

    // goes through getting the total number of good and bad tokens
    for (const auto& pair : trainer.tokenMap) {
        const Token& token = pair.second;
        totalGoodTokens += token.getGoodCount();
        totalBadTokens += token.getBadCount();
    }

    // calculate the probabilities based off training data
    for (auto& pair : trainer.tokenMap) {
        Token& token = pair.second;

        // find probability this token is in "good" tweets
        // token good count / respect of total # of good tokens
        double probTokenGood = (double)token.getGoodCount() / totalGoodTokens;

        // find probability this token is in "bad" tweets
        double probTokenBad = (double)token.getBadCount() / totalBadTokens;

        // store these probabilities a Token object
        token.setProbGood(probTokenGood);
        token.setProbBad(probTokenBad);
    }
}

DSString NaiveBayesClassifier::classifyTweet(const Tweet& tweet, Trainer& trainer) {
    Tweet mutableTweet = tweet;  // copy tweet to tokenize
    mutableTweet.tokenizeTweet();
    std::vector<DSString> tweetTokens = mutableTweet.getTokens();  // vector of tokens of current tweet we are classifying

    // initialize probabilities with prior probabilities
    double probTweetGood = log(priorGood);
    double probTweetBad = log(priorBad);

    // loop through each token in the tweet
    for (const DSString& token : tweetTokens) {
        auto it = trainer.tokenMap.find(token);
        if (it != trainer.tokenMap.end()) {
            // see if that token is found in the training data
            const Token& trainingToken = it->second;
            probTweetGood += log(trainingToken.getProbGood());
            probTweetBad += log(trainingToken.getProbBad());
        }
        // if token doesn't exist in training data ignore
    }

    // if prob of one or another is greater add that classification to that tweet
    if (probTweetGood > probTweetBad) {
        return "4";  // good tweet
    } else {
        return "0";  // bad tweet
    }
}