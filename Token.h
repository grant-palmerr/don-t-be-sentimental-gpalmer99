#ifndef TOKEN_H
#define TOKEN_H

#include "DSString.h"

class Token {
    private:
    DSString tokenString;
    int goodCount;
    int badCount;

    public:
    //constructor
    Token(const DSString& str);

    //getters
    int getGoodCount() const;

    int getBadCount() const;

    DSString getTokenString() const;
    

    //other methods
    void incGood();
    void incBad();
    
};

#endif