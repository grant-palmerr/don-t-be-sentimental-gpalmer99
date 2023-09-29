#include <iostream>

#include "DSString.h"
#include "Tweet.h"
#include "Trainer.h"
#include "Token.h"

Token::Token() {
    good = 0;
    bad = 0;
    ratioGOODtoBAD = good/bad;
    token = "";
}

Token::Token(int goodDataOccurances, int badDataOccurances, float ratio, DSString string)
{
    good = goodDataOccurances;
    bad = badDataOccurances;
    ratioGOODtoBAD = ratio;
    token = string;
}

