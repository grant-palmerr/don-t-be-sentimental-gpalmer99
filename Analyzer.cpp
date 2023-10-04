#include "Analyzer.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "DSString.h"
#include "NaiveBayesClassifier.h"
#include "Tester.h"
#include "Trainer.h"

void Analyzer::Train(const char* filePath) {
    //          TRAINING:
    trainer.parseTrainData(filePath);
    trainer.getTrainingData(filePath);
    trainer.cleanTrainingVector();
    trainer.tokenizeAndMapTweets();
    trainer.filterBasicTokensFromMap();  // improves initial accuracy of 68% to 72%
    //     decided to filter function based on accuracy
    //     trainer.filterStopWordsFromMap();
}

void Analyzer::ClassifyAndEvaluate(const char* filePath1, const char* filePath2, const char* resultsFile, const char* accuracyFile) {
    //          CLASSIFYING:
    Tester tester;
    NaiveBayesClassifier classifier(trainer);  // Classifier object
    tester.parseTestingData(filePath1);
    tester.openSentimentFile(filePath2);
    tester.mapTestingSentiments(filePath2);
    tester.getTestingData(filePath1);
    tester.cleanTestingVector();

    std::cout << "Results File: " << resultsFile << std::endl;
    std::cout << "Accuracy File: " << accuracyFile << std::endl;

    //           EVALUATING:
    std::vector<Tweet> testingTweets = tester.getTestingTweets();
    int correctCount = 0;

    FILE* resultsFp = fopen(resultsFile, "w");
    bool inFile = true;
    if (resultsFp == nullptr) {
        std::cout << "Could not open results file for writing.\n";
        inFile = false;
        return;
    }

    // iterate through tweets to classify and write results
    for (const Tweet& tweet : testingTweets) {
        DSString result = classifier.classifyTweet(tweet, trainer);
        DSString actualSentiment = tweet.getSentiment();

        // write ID of tweet and predicted sentiment
        fprintf(resultsFp, "%s, %s\n", tweet.getId().c_str(), result.c_str());

        // check how many are correct
        if (result == actualSentiment) {
            correctCount++;
        }
    }

    if (inFile == true) {
        std::cout << "Output results.csv file successfully!" << std::endl;
    }

    // close
    fclose(resultsFp);

    // calculate accuracy
    double numInDataSet = static_cast<double>(testingTweets.size());
    double accuracy = (correctCount / numInDataSet) * 100;

    // write  to file
    FILE* accuracyFp = fopen(accuracyFile, "w");
    if (accuracyFp != nullptr) {
        fprintf(accuracyFp, "%.3f\n", accuracy);

        // write incorrect classifications
        for (const Tweet& tweet : testingTweets) {
            DSString result = classifier.classifyTweet(tweet, trainer);
            DSString actualSentiment = tweet.getSentiment();
            if (result != actualSentiment) {
                fprintf(accuracyFp, "%s, %s, %s\n", result.c_str(), actualSentiment.c_str(), tweet.getId().c_str());
            }
        }

        std::cout << "Output accuracy.csv file successfully!" << std::endl;

        // close
        fclose(accuracyFp);
    } else {
        std::cout << "Could not open accuracy file for writing.\n";
    }
}