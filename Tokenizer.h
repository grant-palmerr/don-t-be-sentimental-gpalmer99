#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Token.h"
#include "Tweet.h"

#include <vector>

class Tokenizer {
    void tokenizeTweet(std::vector<Tweet> cleanedTweets);
};

#endif