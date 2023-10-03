#include "Tester.h"

#include <cmath>

#include "Trainer.h"

void Tester::parseTestingData(const char* filePath1) {
    std::cout << "IN TESTING PARSER" << std::endl;

    FILE* file = fopen(filePath1, "r");

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

    DSString idStr = "id";
    DSString tweetStr = "Tweet";

    int headerLength = 0;
    while (header[headerLength] != '\0') {
        headerLength++;
    }

    for (int i = 0; i < headerLength; i++) {
        if (header[i] == ',' || header[i] == '\0' || header[i] == '\n') {
            DSString columnName = DSString(header).substring(startINDEX, i - startINDEX);

            if (columnName == idStr) {
                IDID = columnINDEX;
            } else if (columnName == tweetStr) {
                TWID = columnINDEX;
            }

            columnINDEX++;
            startINDEX = i + 1;
        }
    }

    fclose(file);

    std::cout << "ID Index: " << IDID << std::endl;
    std::cout << "Tweet Index: " << TWID << std::endl;
}

void Tester::getTestingData(const char* filePath1) {
    std::cout << "Retrieving Testing Data" << std::endl;

    FILE* file2 = fopen(filePath1, "r");

    if (file2 == NULL) {
        std::cout << "Could not open file." << std::endl;
        return;
    } else {
        std::cout << "File opened successfully." << std::endl;
    }

    char line[1024];
    int lineCount = 0;

    // loop through to read each line
    while (fgets(line, 1024, file2)) {
        // and then initiailize variables for this line
        bool insideQuotes = false;
        int startIndex = 0;
        int fieldIndex = 0;

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
                if (fieldIndex == IDID) {
                    id = field;
                } else if (fieldIndex == TWID) {
                    tweet = field;
                }

                // increment for the next field, replace starting pos
                fieldIndex++;
                startIndex = i + 1;
            }
        }

        populateTestingVector(id, tweet);  // then we add that tweet to the testing vector passing only the two used parameters

        lineCount++;
    }

    fclose(file2);
}

void Tester::populateTestingVector(DSString id, DSString tweet) {
    // keeping for future debugging
    // std::cout << "Received parameters - ID: " << id << ", Tweet: " << tweet << std::endl;

    // find the sentiment of the id corresponding in sentimentIDmap and use that to set as the field for sentiment for the testing tweet object
    DSString sentiment;
    if (idSentimentMap.find(id) != idSentimentMap.end()) {
        sentiment = idSentimentMap[id];
    } else {
        sentiment = "-";  // default value if not found
    }

    // use parameterized constructor w all 3 parameters to create Tweet object
    Tweet newTweet(sentiment, id, tweet);
    testingTweets.push_back(newTweet);

    // keeping for future debugging
    // std::cout << "Successfully populated vector. New size: " << testingTweets.size() << std::endl;
}

void Tester::cleanTestingVector() {
    std::cout << "Starting to clean the testing vector..." << std::endl;

    int counter = 0;  // keep track of which tweet
    for (Tweet& tweet : testingTweets) {
        // grab the current tweet text
        DSString currentTweetText = tweet.getTweetText();

        // clean the text
        currentTweetText = clean(currentTweetText);

        tweet.setTweetText(currentTweetText);

        // push back into cleaned vector
        counter++;
    }

    std::cout << "Finished cleaning the training vector. Now cleanvector is populated" << std::endl;
}

DSString Tester::clean(DSString& textToClean) {
    char* textArray = new char[textToClean.length() + 1];

    size_t j = 0;                       // position where the next cleaned character will be written
    size_t len = textToClean.length();  // get the current length

    for (size_t i = 0; i < len; ++i) {
        char currentChar = textToClean[i];
        //  if the character is alphanumeric or a space
        if (isalnum(currentChar) || isspace(currentChar)) {
            textArray[j++] = currentChar;
        }
        // if it's an apostrophe and not at the start of a word
        else if (currentChar == '\'' && (i == 0 || isalnum(textToClean[i - 1]))) {
            textArray[j++] = currentChar;
        }
        // if it's a punctuation and at the end of a word
        else if ((currentChar == '!' || currentChar == '?') &&
                 (i == len - 1 || isspace(textToClean[i + 1]))) {
            textArray[j++] = currentChar;
        }
    }

    // make sure j is in bounds before setting null-terminator
    if (j == len) {
        textArray[len] = '\0';
    } else {
        textArray[j] = '\0';
        j = len - 1;  // update j bounds
    }

    DSString cleanedText(textArray);

    delete[] textArray;

    cleanedText = cleanedText.toLower();  // return the cleaned tweet

    return cleanedText;
}

void Tester::openSentimentFile(const char* filePath2) {
    // gets the indicies of the commas for file for future processing

    std::cout << "Opening data/test_dataset_sentiment_10k.csv" << std::endl;

    FILE* file = fopen(filePath2, "r");

    if (file == NULL) {
        std::cout << "Could not open file." << std::endl;
        return;
    } else {
        std::cout << "File opens successfully." << std::endl;
    }

    char header[1024];
    fgets(header, 1024, file);
    std::cout << "Header: " << header << std::endl;  // make sure header reads in correctly

    int columnINDEX = 0;
    int startINDEX = 0;

    DSString sentimentString = "Sentiment";
    DSString idString = "id";

    int headerLength = 0;
    while (header[headerLength] != '\0') {
        headerLength++;
    }

    for (int i = 0; i < headerLength; i++) {
        if (header[i] == ',' || header[i] == '\0' || header[i] == '\n') {
            DSString columnName = DSString(header).substring(startINDEX, i - startINDEX);
            // keeping for future debugging
            // std::cout << "Column: " << columnName << std::endl;  // Debug print

            if (columnName == sentimentString) {
                sentimentCOMMA = columnINDEX;
            } else if (columnName == idString) {
                idCOMMA = columnINDEX;
            }

            columnINDEX++;
            startINDEX = i + 1;
        }
    }

    fclose(file);

    std::cout << "Sentiment Index: " << sentimentCOMMA << std::endl;
    std::cout << "ID Index: " << idCOMMA << std::endl;
}

void Tester::mapTestingSentiments() {
    // make a map to hold the id and sentiment pairs

    // Open the file
    FILE* file = fopen("/users7/cse/gpalmer/2341Projects/assignment-2-don-t-be-sentimental-gpalmer99/data/test_dataset_sentiment_10k.csv", "r");
    if (file == NULL) {
        std::cout << "Could not open file." << std::endl;
        return;
    }

    // skipping the header line since we already know
    char header[1024];
    fgets(header, 1024, file);

    // read in each line
    char line[1024];
    while (fgets(line, 1024, file)) {
        int fieldIndex = 0;
        int startIndex = 0;
        DSString id;
        DSString sentiment;

        // parse the line how we did in trainer
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == ',' || line[i] == '\n') {
                DSString field = DSString(line).substring(startIndex, i - startIndex);

                // assign the field based on its index
                if (fieldIndex == idCOMMA) {
                    id = field;
                } else if (fieldIndex == sentimentCOMMA) {
                    sentiment = field;
                }

                // prepare for the next field
                fieldIndex++;
                startIndex = i + 1;
            }
        }

        // and then lastly populate the map w the key val pair
        idSentimentMap[id] = sentiment;
    }

    fclose(file);

    // Keeping for future debugging
    std::cout << "Final Size of idSentimentMap: " << idSentimentMap.size() << std::endl;

    // update sentiments in testingTweets with the map sentiments comparing the ids
    for (Tweet& tweet : testingTweets) {
        DSString id = tweet.getId();
        if (idSentimentMap.find(id) != idSentimentMap.end()) {
            tweet.setSentiment(idSentimentMap[id]);

        } else {
            std::cout << "ID not found in map: " << id << std::endl;  // Debugging statement
        }
    }
}

std::vector<Tweet> Tester::getTestingTweets() const {
    return testingTweets;
}

void Tester::printIdSentimentMap() {
    std::cout << "Printing ID-Sentiment Map:" << std::endl;

    // Iterate through the map and print each key-value pair
    for (const auto& pair : idSentimentMap) {
        std::cout << "ID: " << pair.first << ", Sentiment: " << pair.second << std::endl;
    }
}
