#include "Token.h"

Token::Token(const DSString& str) {
    tokenString = str;
    goodCount = 0;
    badCount = 0;

}

void Token::incGood() 
{ 
    ++goodCount; 
}

void Token::incBad() 
{ 
    ++badCount; 
}

int Token::getGoodCount() const 
{ 
    return goodCount; 
}

int Token::getBadCount() const 
{ 
    return badCount; 
}

DSString Token::getTokenString() const 
{ 
    return tokenString; 
}
