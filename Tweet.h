#ifndef TWEET_H
#define TWEET_H

#include "DSString.h"

class Tweet {
   
    private:
        DSString sentiment;
        DSString id;
        DSString tweetText;

    public:
        // Constructors
        Tweet();
        Tweet(DSString sentiment, DSString id, DSString tweet);

        // Setter methods
        void setSentiment(const DSString& s);
        void setId(const DSString& i);
        void setTweetText(const DSString& t);

        // Getter methods
        DSString getSentiment() const;
        DSString getId() const;
        DSString& getTweetText();
};

#endif
