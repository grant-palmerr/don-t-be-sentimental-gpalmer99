#include "Token.h"

Token::Token() {
    tokenString = "";
    goodCount = 0;
    badCount = 0;
    probGood = 0.0;
    probBad = 0.0;
}

Token::Token(const DSString& str) {
    tokenString = str;
    goodCount = 0;
    badCount = 0;
    probGood = 0.0;
    probBad = 0.0;
}

void Token::incGood() {
    ++goodCount;
}

void Token::incBad() {
    ++badCount;
}

int Token::getGoodCount() const {
    return goodCount;
}

int Token::getBadCount() const {
    return badCount;
}

DSString Token::getTokenString() const {
    return tokenString;
}

void Token::setProbGood(double prob) {
    probGood = prob;
}

void Token::setProbBad(double prob) {
    probBad = prob;
}

double Token::getProbGood() const {
    return probGood;
}

double Token::getProbBad() const {
    return probBad;
}
