#include "Tester.h"

void Tester::parseTestingData() {
    std::cout << "IN TESTING PARSER" << std::endl;

    FILE* file = fopen("/users7/cse/gpalmer/2341Projects/assignment-2-don-t-be-sentimental-gpalmer99/data/test_dataset_10k.csv", "r");

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
            // ADD PRINT STATEMENT BACK
            std::cout << "Column: " << columnName << std::endl;  // Debug print

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

void Tester::getTestingData() {
    std::cout << "IN PRINT" << std::endl;

    FILE* file2 = fopen("/users7/cse/gpalmer/2341Projects/assignment-2-don-t-be-sentimental-gpalmer99/data/test_dataset_10k.csv", "r");

    if (file2 == NULL) {
        std::cout << "Could not open file." << std::endl;
        return;
    } else {
        std::cout << "File opened successfully." << std::endl;
    }

    char line[1024];
    int lineCount = 0;

    // Loop to read each line
    while (fgets(line, 1024, file2) && lineCount <= 10) {
        // Initialize variables for this line
        bool insideQuotes = false;
        int startIndex = 0;
        int fieldIndex = 0;

        DSString id;
        DSString tweet;

        std::cout << "About to read in new field..." << std::endl;

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

                // Prepare for the next field
                fieldIndex++;
                startIndex = i + 1;
            }
        }

        // Print the extracted fields
        std::cout << "Current Line Count: " << lineCount << std::endl;

        // ADD PRINT STATEMENT BACK
        std::cout << "ID: " << id << ", Tweet: " << tweet << std::endl;
        //  Update line count
        populateTestingVector(id, tweet);

        lineCount++;
        std::cout << "Updated Line Count: " << lineCount << std::endl;
    }

    fclose(file2);
}

void Tester::populateTestingVector(DSString id, DSString tweet) {
    std::cout << "Received parameters - ID: " << id << ", Tweet: " << tweet << std::endl;

    // create a new tweet object with nessecary constructors and add it to the vector
    Tweet newTweet(id, tweet);
    testingTweets.push_back(newTweet);

    // debugging statements
    // ADD PRINT STATEMENT BACK
    std::cout << "Successfully populated vector. New size: " << testingTweets.size() << std::endl;
}

void Tester::cleanTestingVector() {
    std::cout << "Starting to clean the testing vector..." << std::endl;

    int counter = 0;  // To keep track of which tweet you're on
    for (Tweet& tweet : testingTweets) {
        // ADD PRINT STATEMENT BACK
        std::cout << "Processing tweet #" << counter << std::endl;

        // grab the current tweet text
        DSString currentTweetText = tweet.getTweetText();
        // ADD PRINT STATEMENT BACK
        std::cout << "Current tweet text: " << currentTweetText << std::endl;

        // clean the text
        currentTweetText = clean(currentTweetText);
        // ADD PRINT STATEMENT BACK
        std::cout << "Cleaned tweet text: " << currentTweetText << std::endl;

        tweet.setTweetText(currentTweetText);

        // push back into cleaned vector
        counter++;
    }
    // ADD PRINT STATEMENT BACK
    std::cout << "Finished cleaning the training vector. Now cleanvector is populated" << std::endl;
}

DSString Tester::clean(DSString& textToClean) {
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

    delete[] textArray;

    cleanedText = cleanedText.toLower();

    return cleanedText;
}

void Tester::tokenizeTestingTweets() {
    size_t counter = 0;
    for (Tweet& tweet : testingTweets) {
        tweet.tokenizeTweet();
        std::vector<DSString> testingTweetTokens = tweet.getTokens();  // Now returns vector of DSString objects

        // debugging rint tokens for each tweet
        // ADD PRINT STATEMENT BACK
        std::cout << "Tokens for tweet #" << (counter + 1) << "are: " << std::endl;

        for (std::vector<DSString>::const_iterator it = testingTweetTokens.begin(); it != testingTweetTokens.end(); ++it) {
            DSString tokenString = *it;
            // ADD PRINT STATEMENT BACK
            std::cout << "Token: " << tokenString << std::endl;
        }
        ++counter;
    }
    // ADD PRINT STATEMENT BACK
    std::cout << std::endl;
}