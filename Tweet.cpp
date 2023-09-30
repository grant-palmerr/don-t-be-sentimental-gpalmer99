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
            //looking to see if a a tweet reaches a newline, space, tab, etc.
            if (c == ' ' || c == '\n' || c == '\t' || i == length - 1) {
                end = i;
                if (i == length - 1) {
                    end++;
                }
                DSString token = tweetText.substring(start, end - start);
                // have had issues with my tokenizer sometimes leaving addtional spaces so added an addtional check for a  trailing space and remove it if its there
            if (token[token.length() - 1] == ' ') {
                token = token.substring(0, token.length() - 1);
            }
                tokens.push_back(token); //add it to that tweet objects vector of tokens 
                start = i + 1;  // continue from where we left off and do it again
            }
        }
}

std::vector<DSString> Tweet::getTokens()
{
    return tokens;
}

