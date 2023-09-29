#include "Tweet.h"
#include "DSString.h"

// Default constructor
Tweet::Tweet() {
    sentiment = "";
    id = "";
    tweetText = ""; 
}

// Parameterized constructor
Tweet::Tweet(DSString newSentimentValue, DSString newIdValue, DSString newTweetValue) {
    sentiment = newSentimentValue;
    id = newIdValue;
    tweetText = newTweetValue;  
}

// Getters 
DSString Tweet::getId() const {
    return id;
}

DSString Tweet::getSentiment() const {
    return sentiment;
}

DSString& Tweet::getTweetText() {
    return tweetText;
}

// Setters 
void Tweet::setSentiment(const DSString& s) { 
    sentiment = s;
}

void Tweet::setId(const DSString& i) { 
    id = i;
}

void Tweet::setTweetText(const DSString& twt) {
    tweetText = twt;
}

