#ifndef TWEET_H
#define TWEET_H

#include "DSString.h"
#include "Token.h"
#include <vector>

class Tweet {
   
    private:
        std::vector<Token> tokens; //the tweet but tokenized
        std::vector<Token> tokensNOSTOP; //the tweet but tokenized and stop words removed
        DSString sentiment; //holds sentiment of tweet
        DSString id; //hold id of tweet
        DSString tweetText; //holds text of tweet

    public:
        // constructors
        Tweet();
        Tweet(DSString sentiment, DSString id, DSString tweet);

        // setters 
        void setSentiment(const DSString& s);
        void setId(const DSString& i);
        void setTweetText(const DSString& t);

        // getters 
        DSString getSentiment() const;
        DSString getId() const;
        DSString& getTweetText();
        std::vector<Token> getTokens();

        //other added methods
        void tokenizeTweet(); //takes in a tweet and turns it into tokens

};

#endif