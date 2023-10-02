#include "NaivesBayesClassifier.h"

#include <cmath>

NaiveBayesClassifier::NaiveBayesClassifier(Trainer& trainer) {
    // initialize probabilities based on the Trainer object
    calculateTokenProbabilities(trainer);
}

void NaiveBayesClassifier::calculateTokenProbabilities(Trainer& trainer) {
    // Calculate probabilities here based on the tokenMap in Trainer
    // For example, you can set probGood and probBad based on the counts of good and bad tweets
    int totalGoodTokens = 0;
    int totalBadTokens = 0;

    // goes through getting the total number of good and bad tokens
    for (const auto& pair : trainer.tokenMap) {
        const Token& token = pair.second;
        totalGoodTokens += token.getGoodCount();
        totalBadTokens += token.getBadCount();
    }

    // calculate the probabilities
    for (auto& pair : trainer.tokenMap) {
        Token& token = pair.second;

        // find probability this token is in "good" tweets
        // token good count / respect of total # of good tokens
        double probTokenGood = (double)token.getGoodCount() / totalGoodTokens;

        // find probability this token is in "bad" tweets
        double probTokenBad = (double)token.getBadCount() / totalBadTokens;

        // store these probabilities in Token object
        token.setProbGood(probTokenGood);
        token.setProbBad(probTokenBad);
    }
}

DSString NaiveBayesClassifier::classifyTweet(const Tweet& tweet) {
   //nothing
    return DSString(); 
}

