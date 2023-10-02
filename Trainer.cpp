#include "Trainer.h"

#include <stdio.h>

#include <iostream>
#include <vector>

#include "DSString.h"
#include "Tweet.h"

void Trainer::parseTrainData() {
    std::cout << "IN TRAINING PARSER" << std::endl;

    FILE* file = fopen("/users7/cse/gpalmer/2341Projects/assignment-2-don-t-be-sentimental-gpalmer99/data/train_dataset_20k.csv", "r");

    if (file == NULL) {
        std::cout << "Could not open file." << std::endl;
        return;
    } else {
        std::cout << "File opens successfully." << std::endl;
    }

    char header[1024];
    fgets(header, 1024, file);
    std::cout << "Header: " << header << std::endl;  // Debug print

    int columnINDEX = 0;
    int startINDEX = 0;

    DSString sentimentStr = "Sentiment";
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
    // ADD PRINT STATEMENT BACK
    /*std::cout << "Sentiment Index: " << SID << std::endl;
    std::cout << "ID Index: " << IDID << std::endl;
    std::cout << "Tweet Index: " << TWID << std::endl;*/
}

void Trainer::getTrainingData() {
    std::cout << "IN PRINT" << std::endl;

    FILE* file2 = fopen("/users7/cse/gpalmer/2341Projects/assignment-2-don-t-be-sentimental-gpalmer99/data/train_dataset_20k.csv", "r");

    if (file2 == NULL) {
        std::cout << "Could not open file." << std::endl;
        return;
    } else {
        std::cout << "File opened successfully." << std::endl;
    }

    char line[1024];
    int lineCount = 0;

    // Loop to read each line
    while (fgets(line, 1024, file2)) {
        // Initialize variables for this line
        bool insideQuotes = false;
        int startIndex = 0;
        int fieldIndex = 0;

        DSString sentiment;
        DSString id;
        DSString tweet;

        // std::cout << "About to read in new field..." << std::endl;

        for (int i = 0; line[i] != '\0'; i++) {
            // if a quote is found
            if (line[i] == '\"') {
                insideQuotes = !insideQuotes;
            }

            // std::cout << "IN FOR LOOP, LINE COUNT: " << line[i] << std::endl;

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

        // Print the extracted fields
        // std::cout << "Current Line Count: " << lineCount << std::endl;

        // ADD PRINT STATEMENT BACK
        // std::cout << "Sentiment: " << sentiment << ", ID: " << id << ", Tweet: " << tweet << std::endl;
        //  Update line count
        populateTrainingVector(sentiment, id, tweet);

        lineCount++;
        // std::cout << "Updated Line Count: " << lineCount << std::endl;
    }

    fclose(file2);
}

void Trainer::populateTrainingVector(DSString sentiment, DSString id, DSString tweet) {
    // ADD PRINT STATEMENT BACK
    // std::cout << "Received parameters - Sentiment: " << sentiment << ", ID: " << id << ", Tweet: " << tweet << std::endl;

    // create a new tweet object with nessecary constructors and add it to the vector
    Tweet newTweet(sentiment, id, tweet);
    trainingTweets.push_back(newTweet);

    // debugging statements
    // ADD PRINT STATEMENT BACK
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
    // ADD PRINT STATEMENT BACK
    // std::cout << "Starting to clean the training vector..." << std::endl;

    int counter = 0;  // To keep track of which tweet you're on
    for (Tweet& tweet : trainingTweets) {
        // ADD PRINT STATEMENT BACK
        // std::cout << "Processing tweet #" << counter << std::endl;

        // grab the current tweet text
        DSString currentTweetText = tweet.getTweetText();
        // ADD PRINT STATEMENT BACK
        // std::cout << "Current tweet text: " << currentTweetText << std::endl;

        // clean the text
        currentTweetText = clean(currentTweetText);
        // ADD PRINT STATEMENT BACK
        // std::cout << "Cleaned tweet text: " << currentTweetText << std::endl;

        tweet.setTweetText(currentTweetText);

        // push back into cleaned vector
        counter++;
    }
    // ADD PRINT STATEMENT BACK
    // std::cout << "Finished cleaning the training vector. Now cleanvector is populated" << std::endl;
}

// cleaning method to clean my tweets from special characters, unnessecary punctuation, and non alphanum
DSString Trainer::clean(DSString& textToClean) {
    char* textArray = new char[textToClean.length() + 1];

    size_t j = 0;                       // Position where the next cleaned character will be written
    size_t len = textToClean.length();  // Get the current length

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

    // Ensure j is in bounds before setting null-terminator
    if (j == len) {
        textArray[len] = '\0';
    } else {
        textArray[j] = '\0';
        j = len - 1;  // Update j to be in bounds
    }

    DSString cleanedText(textArray);

    delete [] textArray;

    cleanedText = cleanedText.toLower();

    return cleanedText;
}

void Trainer::print() {
    // print tweet object members
    size_t counter = 0;
    for (Tweet& tweet : trainingTweets) {
        DSString currentTweetText = tweet.getTweetText();
        DSString currentTweetID = tweet.getId();
        DSString currentTweetSentiment = tweet.getSentiment();
        // ADD PRINT STATEMENT BACK
        /*std::cout << "Tweet #: " << counter << " TEXT: " << currentTweetText << std::endl;
                std::cout << "Tweet #: " << counter << " ID: " << currentTweetID << std::endl;
                std::cout << "Tweet #: " << counter << " SENTIMENT: " << currentTweetSentiment << std::endl;*/
        ++counter;
    }
}

void Trainer::tokenizeAndMapTweets() {
    for (Tweet& tweet : trainingTweets) {
        tweet.tokenizeTweet();
        std::vector<DSString> tweetTokens = tweet.getTokens();  // Now returns vector of DSString objects
        DSString sentiment = tweet.getSentiment();

        // debugging rint tokens for each tweet
        // ADD PRINT STATEMENT BACK
        // std::cout << "Tokens for tweet with sentiment " << sentiment << " are: " << std::endl;

        for (std::vector<DSString>::const_iterator it = tweetTokens.begin(); it != tweetTokens.end(); ++it) {
            DSString tokenString = *it;
            // ADD PRINT STATEMENT BACK
            // std::cout << "Processing token: " << tokenString << std::endl;

            // Uncomment your map code here and add debugging prints
            // ADD PRINT STATEMENT BACK
            // std::cout << "About to insert into map..." << std::endl;
            if (tokenMap.find(tokenString) != tokenMap.end()) {
                // element exists, update counts
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
            // ADD PRINT STATEMENT BACK
            // std::cout << "Successfully inserted into map." << std::endl;
        }
    }
    // ADD PRINT STATEMENT BACK
    // std::cout << std::endl;
}

std::vector<Tweet>& Trainer::getTrainingTweets() {
    return trainingTweets;
}

// print the contents of the tokenMap
void Trainer::printTokenMap() {
    std::cout << "Printing Token Map:" << std::endl;

    // Iterate through the map and print each key-value pair
    for (const auto& pair : tokenMap) {
        const DSString& tokenString = pair.first;
        const Token& token = pair.second;

        std::cout << "Token: " << tokenString << ", Good Count: " << token.getGoodCount() << ", Bad Count: " << token.getBadCount() << std::endl;
    }
}

void Trainer::printFilteredTokens() {
    std::cout << "------------------------------------------------" << std::endl;

    std::cout << "Printing Filtered Tokens:" << std::endl;

    // Iterate through the map and print each key-value pair
    for (const auto& pair : tokenMap) {
        const DSString& tokenString = pair.first;
        const Token& token = pair.second;

        // Check if goodCount or badCount > 200
        if (token.getGoodCount() > 200 || token.getBadCount() > 200) {
            std::cout << "Token: " << tokenString
                      << ", Good Count: " << token.getGoodCount()
                      << ", Bad Count: " << token.getBadCount() << std::endl;
        }
    }
}

// removes space tokens if they exist,
// removes numbers if they exist
// removes tokens whose good+bad count <= 0 (they only appear once)

void Trainer::filterBasicTokensFromMap() {
    // Iterate through the map
    for (auto it = tokenMap.begin(); it != tokenMap.end();) {
        const DSString& tokenString = it->first;
        Token& token = it->second;

        // Remove spaces
        if (tokenString == " ") {
            it = tokenMap.erase(it);
            continue;
        }

        // Remove tokens with goodCount + badCount <= 1
        if (token.getGoodCount() + token.getBadCount() <= 1) {
            it = tokenMap.erase(it);
            continue;
        }

        //if good count and bad count are the same
        if(token.getGoodCount() == token.getBadCount()) {
            it = tokenMap.erase(it);
            continue;
        }

        ++it;  // Only increment if no erase happened
    }
}

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
