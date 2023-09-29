#ifndef TOKEN_H
#define TOKEN_H

#include "DSString.h"

class Token {
   private:
    int good;
    int bad;
    float ratioGOODtoBAD;
    DSString token;

   public:
    Token();
    Token(int good, int bad, float ratio, DSString token);
};

#endif