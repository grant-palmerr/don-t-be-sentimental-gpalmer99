#include "Tweet.h"

#include <vector>

#include "DSString.h"

// and default constructor
Tweet::Tweet() {
    sentiment = "";
    id = "";
    tweetText = "";
}

// parameterized constructor
Tweet::Tweet(DSString newSentimentValue, DSString newIdValue, DSString newTweetValue) {
    sentiment = newSentimentValue;
    id = newIdValue;
    tweetText = newTweetValue;
}

Tweet::Tweet(DSString idValue, DSString tweetValue) {
    sentiment = "-";
    id = idValue;
    tweetText = tweetValue;
}

// getters
DSString Tweet::getId() const {
    return id;
}

DSString Tweet::getSentiment() const {
    return sentiment;
}

DSString& Tweet::getTweetText() {
    return tweetText;
}

// setters
void Tweet::setSentiment(const DSString& s) {
    sentiment = s;
}

void Tweet::setId(const DSString& i) {
    id = i;
}

void Tweet::setTweetText(const DSString& twt) {
    tweetText = twt;
}

void Tweet::tokenizeTweet() {
    size_t start = 0;
    size_t end = 0;
    size_t length = tweetText.length();

    for (size_t i = 0; i < length; ++i) {
        char c = tweetText[i];

        // looking for spaces, newlines, and end of string length-1
        if (c == ' ' || c == '\n' || c == '\t' || i == length - 1) {
            end = i;
            if (i == length - 1) {
                end++;
            }
            DSString token = tweetText.substring(start, end - start);

            tokens.push_back(token);  // add to the tweet object's vector of tokens
            start = i + 1;            // continue from where we left off
        }
    }

    DSString token = tweetText.substring(start, length - start);
    tokens.push_back(token);
}

std::vector<DSString> Tweet::getTokens() {
    return tokens;
}
