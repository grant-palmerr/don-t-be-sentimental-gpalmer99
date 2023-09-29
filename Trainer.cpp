#include <stdio.h>
#include <iostream>
#include <vector>

#include "DSString.h"
#include "Tweet.h"
#include "Trainer.h"

void Trainer::parseTrainData() {
    std::cout << "IN PARSER" << std::endl;

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
            std::cout << "Column: " << columnName << std::endl;  // Debug print

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

    std::cout << "Sentiment Index: " << SID << std::endl;
    std::cout << "ID Index: " << IDID << std::endl;
    std::cout << "Tweet Index: " << TWID << std::endl;
}

void Trainer::printTrainingData() {
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
    while (fgets(line, 1024, file2) && lineCount < 7) {
        // Initialize variables for this line
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
        // Print the extracted fields
        // std::cout << "Sentiment: " << sentiment << ", ID: " << id << ", Tweet: " << tweet << std::endl;
        // Update line count
        populateTrainingVector(sentiment, id, tweet);

        lineCount++;
    }
}


void Trainer::populateTrainingVector(DSString sentiment, DSString id, DSString tweet) {
    Tweet newTweet(sentiment, id, tweet);
    trainingTweets.push_back(newTweet);
}

void Trainer::testTrainer() {
    for (std::vector<Tweet>::iterator it = trainingTweets.begin(); it != trainingTweets.end(); ++it) {
        std::cout << "Sentiment: " << it->getSentiment() << ", ID: " << it->getId() << ", Tweet: " << it->getTweetText() << std::endl;
    }
}

DSString Trainer::clean(DSString& textToClean) {
    size_t j = 0;  // Position where the next cleaned character will be written
    size_t len = textToClean.length();  // Get the current length

    for (size_t i = 0; i < len; ++i) {
        char currentChar = textToClean[i];
        // Check if the character is alphanumeric or a space
        if (isalnum(currentChar) || isspace(currentChar)) {
            textToClean[j++] = currentChar;
        }
        // Check if it's an apostrophe and not at the start of a word
        else if (currentChar == '\'' && (i == 0 || isalnum(textToClean[i-1]))) {
            textToClean[j++] = currentChar;
        }
        // Check if it's a punctuation and at the end of a word
        else if ((currentChar == '.' || currentChar == '!' || currentChar == '?') && 
                 (i == len - 1 || isspace(textToClean[i+1]))) {
            textToClean[j++] = currentChar;
        }
    }

    // Ensure j is in bounds before setting null-terminator
    if (j < len) {
        textToClean[j] = '\0';
    } else {
        textToClean[len - 1] = '\0';
        j = len - 1;  // Update j to be in bounds
    }

    // set length of the DSString object
    textToClean.setLength(j);

    textToClean = textToClean.toLower();

    return textToClean;


}

// modifying vector in place so not making a large copy and instead reutnring void

void Trainer::cleanTrainingVector() {
    std::cout << "Starting to clean the training vector..." << std::endl;

    int counter = 0;  // To keep track of which tweet you're on
    for (Tweet& tweet : trainingTweets) 
    {
        std::cout << "Processing tweet #" << counter << std::endl;

        // grab the current tweet text
        DSString currentTweetText = tweet.getTweetText();
        std::cout << "Current tweet text: " << currentTweetText << std::endl;


        // clean the text
        clean(currentTweetText);
        
        std::cout << "Cleaned tweet text: " << currentTweetText << std::endl;

        tweet.setTweetText(currentTweetText);

    //push back into cleaned vector 
        counter++;
    }

    std::cout << "Finished cleaning the training vector. Now cleanvector is populated" << std::endl;
}

void Trainer::print() 
{
size_t counter = 0;
for(Tweet& tweet : trainingTweets) 
{
    DSString currentTweetText = tweet.getTweetText();
    std::cout << "Tweet #: " << counter << ": " << currentTweetText << std::endl;
    ++counter;
}
}
