#ifndef TOKEN_H
#define TOKEN_H

#include "DSString.h"

class Token {
   private:
    DSString tokenString;  // token itself
    int goodCount;         // # of times token appears in a GOOD tweet
    int badCount;          // # of times token appears in a BAD tweet
    double probGood;       // probability of token being in a GOOD tweet
    double probBad;        // probability of token being in a BAD tweet

   public:
    // constructor
    Token();
    Token(const DSString& str);

    // getters
    int getGoodCount() const;

    int getBadCount() const;

    double getProbGood() const;

    double getProbBad() const;

    DSString getTokenString() const;

    // other methods
    void incGood();
    void incBad();

    // setters
    void setProbGood(double prob);
    void setProbBad(double prob);
};

#endif