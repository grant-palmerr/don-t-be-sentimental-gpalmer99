#ifndef NAIVEBAYESCLASSIFIER_H
#define NAIVEBAYESCLASSIFIER_H

#include "DSString.h"
#include "Trainer.h"
#include "Tweet.h"

class NaiveBayesClassifier {
   private:
    double probGood;   // probability that a given token belongs to a "good"
    double probBad;    // probaility that a given token belongs to a "bad"
    double priorGood;  // prior probability of a tweet being "good"
    double priorBad;   // prior probability of a tweet being "bad"

   public:
    NaiveBayesClassifier();                                        // default
    NaiveBayesClassifier(Trainer& trainer);                        // initializes probabilities based on a Trainer object
    void calculateTokenProbabilities(Trainer& trainer);            // calculates the liklihood a token is good or bad based on trainer
    DSString classifyTweet(const Tweet& tweet, Trainer& trainer);  // classifies a tweet
};

#endif
