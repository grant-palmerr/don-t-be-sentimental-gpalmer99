#ifndef TWEET_H
#define TWEET_H

#include <vector>

#include "DSString.h"
#include "Token.h"

class Tweet {
   private:
    std::vector<DSString> tokens;  // the tweet but tokenized
    DSString sentiment;            // holds sentiment of tweet
    DSString id;                   // hold id of tweet
    DSString tweetText;            // holds text of tweet

   public:
    // constructors
    Tweet();
    // constructor for training tweets
    Tweet(DSString sentiment, DSString id, DSString tweet);
    // constructor for testing tweets
    Tweet(DSString id, DSString tweet);

    // setters
    void setSentiment(const DSString& s);
    void setId(const DSString& i);
    void setTweetText(const DSString& t);

    // getters
    DSString getSentiment() const;
    DSString getId() const;
    DSString& getTweetText();
    std::vector<DSString> getTokens();

    // other added methods
    void tokenizeTweet();  // takes in a tweet and turns it into tokens
};

#endif