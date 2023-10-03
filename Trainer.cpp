#include "Trainer.h"

#include <stdio.h>

#include <iostream>
#include <vector>

#include "DSString.h"
#include "Tweet.h"

void Trainer::parseTrainData() {

    FILE* file = fopen("/users7/cse/gpalmer/2341Projects/assignment-2-don-t-be-sentimental-gpalmer99/data/train_dataset_20k.csv", "r");

    if (file == NULL) {
        std::cout << "could not open the file." << std::endl;
        return;
    } else {
        std::cout << "the file opens successfully." << std::endl;
    }

    char header[1024];
    fgets(header, 1024, file);
    std::cout << "Header: " << header << std::endl;  // Debug print

    int columnINDEX = 0;
    int startINDEX = 0;

    DSString sentimentStr = "Sentiment"; //look for these in header
    DSString idStr = "id";
    DSString tweetStr = "Tweet";

    int headerLength = 0;
    while (header[headerLength] != '\0') {
        headerLength++;
    }

    for (int i = 0; i < headerLength; i++) {
        if (header[i] == ',' || header[i] == '\0' || header[i] == '\n') {
            DSString columnName = DSString(header).substring(startINDEX, i - startINDEX);
            // ADD PRINT STATEMENT BACK
            // std::cout << "Column: " << columnName << std::endl;  // Debug print

            if (columnName == sentimentStr) {
                SID = columnINDEX;
            } else if (columnName == idStr) {
                IDID = columnINDEX;
            } else if (columnName == tweetStr) {
                TWID = columnINDEX;
            }

            columnINDEX++;
            startINDEX = i + 1;
        }
    }

    fclose(file);

}

void Trainer::getTrainingData() {
    //std::cout << "IN PRINT" << std::endl;

    FILE* file2 = fopen("/users7/cse/gpalmer/2341Projects/assignment-2-don-t-be-sentimental-gpalmer99/data/train_dataset_20k.csv", "r");

    if (file2 == NULL) {
        std::cout << "Could not open file." << std::endl;
        return;
    } else {
        std::cout << "File opened successfully." << std::endl;
    }

    char line[1024];
    int lineCount = 0;

    //  loop in and read each line
    while (fgets(line, 1024, file2)) {
        // initialize start, if its in quotes, and field index
        bool insideQuotes = false;
        int startIndex = 0;
        int fieldIndex = 0;

        DSString sentiment;
        DSString id;
        DSString tweet;


        for (int i = 0; line[i] != '\0'; i++) {
            // if a quote is found
            if (line[i] == '\"') {
                insideQuotes = !insideQuotes;
            }

            // find either newline or endl
            if ((line[i] == ',' && !insideQuotes) || line[i] == '\n') {
                DSString field = DSString(line).substring(startIndex, i - startIndex);

                // assign the field based on its index
                if (fieldIndex == SID) {
                    sentiment = field;
                } else if (fieldIndex == IDID) {
                    id = field;
                } else if (fieldIndex == TWID) {
                    tweet = field;
                }

                // Prepare for the next field
                fieldIndex++;
                startIndex = i + 1;
            }
        }
        populateTrainingVector(sentiment, id, tweet);

        lineCount++;
    }

    fclose(file2);
}

void Trainer::populateTrainingVector(DSString sentiment, DSString id, DSString tweet) {
    
    // create a new tweet object with nessecary constructors and add it to the vector
      if (sentiment == "4") { // 4 means a good tweet
        numGoodTweets++;
    } else {
        numBadTweets++; // i guess i am assuming only 0 and 4 are in the dataset
    }

    Tweet newTweet(sentiment, id, tweet); //create new object using param constructor
    trainingTweets.push_back(newTweet); //

    // debugging statement
    // std::cout << "Successfully populated vector. New size: "
    // << trainingTweets.size() << std::endl;
}

// debugging method
void Trainer::testTrainer() {
    for (std::vector<Tweet>::iterator it = trainingTweets.begin(); it != trainingTweets.end(); ++it) {
        std::cout << "Sentiment: " << it->getSentiment() << ", ID: " << it->getId() << ", Tweet: " << it->getTweetText() << std::endl;
    }
}

// modifying vector in place so not making a large copy and instead reutnring void
void Trainer::cleanTrainingVector() {
//cleans the tweets for tokenization

    int counter = 0;  // keep track of which tweet is getting processed
    for (Tweet& tweet : trainingTweets) {

        // grab the current tweet text
        DSString currentTweetText = tweet.getTweetText();
 
        // clean the text
        currentTweetText = clean(currentTweetText);

        tweet.setTweetText(currentTweetText); //since its a reference it modifies the tweet itself and uses the cleanedtweet instead

        // push back into cleaned vector
        counter++;
    }
  
}

// cleaning method to clean my tweets from special characters, unnessecary punctuation, and non alphanum
DSString Trainer::clean(DSString& textToClean) {
    char* textArray = new char[textToClean.length() + 1];

    size_t j = 0;                       // index where the next cleaned character will be written
    size_t len = textToClean.length();  // get curr length

    for (size_t i = 0; i < len; ++i) {
        char currentChar = textToClean[i];
        //  if the character is alphanumeric or a space
        if (isalnum(currentChar) || isspace(currentChar)) {
            textArray[j++] = currentChar;
        }
        // Check if it's an apostrophe and not at the start of a word
        else if (currentChar == '\'' && (i == 0 || isalnum(textToClean[i - 1]))) {
            textArray[j++] = currentChar;
        }
        // Check if it's a punctuation and at the end of a word
        else if ((currentChar == '!' || currentChar == '?') &&
                 (i == len - 1 || isspace(textToClean[i + 1]))) {
            textArray[j++] = currentChar;
        }
    }

    // make sure j is in bounds before setting a null-terminator
    if (j == len) {
        textArray[len] = '\0';
    } else {
        textArray[j] = '\0';
        j = len - 1;  // update j to be in bounds
    }

    DSString cleanedText(textArray);

    delete [] textArray;

    cleanedText = cleanedText.toLower(); //set all text tolower

    return cleanedText;
}

void Trainer::print() {
    // print tweet object members
    size_t counter = 0;
    for (Tweet& tweet : trainingTweets) {
        DSString currentTweetText = tweet.getTweetText();
        DSString currentTweetID = tweet.getId();
        DSString currentTweetSentiment = tweet.getSentiment();
  
        ++counter;
    }
}

void Trainer::tokenizeAndMapTweets() {
    for (Tweet& tweet : trainingTweets) {
        tweet.tokenizeTweet();
        std::vector<DSString> tweetTokens = tweet.getTokens();  // returns vector of DSString objects
        DSString sentiment = tweet.getSentiment();

        // debugging print tokens for each tweet
        // std::cout << "Tokens for tweet with sentiment " << sentiment << " are: " << std::endl;

        for (std::vector<DSString>::const_iterator it = tweetTokens.begin(); it != tweetTokens.end(); ++it) {
            DSString tokenString = *it; //dereference
            if (tokenMap.find(tokenString) != tokenMap.end()) {
                // element exists, update counts in tokenMap
                if (sentiment == "4") {
                    tokenMap[tokenString].incGood();
                } else {
                    tokenMap[tokenString].incBad();
                }
            } else {
                // element doesn't exist, add to tokenMap
                Token newToken(tokenString);
                if (sentiment == "4") {
                    newToken.incGood();
                } else {
                    newToken.incBad();
                }
                tokenMap[tokenString] = newToken;
            }
        }
    }
}

std::vector<Tweet>& Trainer::getTrainingTweets() {
    return trainingTweets;
}

// print the contents of the tokenMap for debugging
void Trainer::printTokenMap() {
    std::cout << "Printing Token Map:" << std::endl;

    // iterate through the map and print each key/val pair
    for (const auto& pair : tokenMap) {
        const DSString& tokenString = pair.first;
        const Token& token = pair.second;

        std::cout << "Token: " << tokenString << ", Good Count: " << token.getGoodCount() << ", Bad Count: " << token.getBadCount() << std::endl;
    }
}

// this removes space, number, and good+bad count <=0 tokens if they exist,
void Trainer::filterBasicTokensFromMap() {
    // iterate through the map
    for (auto it = tokenMap.begin(); it != tokenMap.end();) {
        const DSString& tokenString = it->first;
        Token& token = it->second;

        // get rid of spaces
        if (tokenString == " ") {
            it = tokenMap.erase(it);
            continue;
        }

        // get rid of tokens with goodCount + badCount <= 1
        if (token.getGoodCount() + token.getBadCount() <= 1) {
            it = tokenMap.erase(it);
            continue;
        }

        //if good count and bad count are the same
        if(token.getGoodCount() == token.getBadCount()) {
            it = tokenMap.erase(it);
            continue;
        }

        ++it;  // and we only increment if no erase happened
    }
}

//for debugging
void Trainer::printTokenProbabilities() {
    std::cout << "Printing Token Probabilities:" << std::endl;

    for (const auto& pair : tokenMap) {
        const DSString& tokenString = pair.first;
        const Token& token = pair.second;

        std::cout << "Token: " << tokenString 
                  << ", ProbGood: " << token.getProbGood() 
                  << ", ProbBad: " << token.getProbBad() << std::endl;
    }
}

//getters for probabilities
int Trainer::getNumGoodTweets() {
    return numGoodTweets;
}

int Trainer::getNumBadTweets() {
    return numBadTweets;
}