#ifndef NAIVEBAYESCLASSIFIER_H
#define NAIVEBAYESCLASSIFIER_H

#include "Trainer.h"
#include "DSString.h"
#include "Tweet.h"

class NaiveBayesClassifier {
private:
    double probGood;
    double probBad;

public:
    NaiveBayesClassifier(Trainer& trainer);  //initializes probabilities based on a Trainer object
    void calculateTokenProbabilities(Trainer& trainer);
    DSString classifyTweet(const Tweet& tweet);
};

#endif
