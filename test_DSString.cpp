#include <algorithm>
#include <iostream>
#include <vector>

#include "DSString.h"
#include "NaiveBayesClassifier.h"
#include "Tester.h"
#include "Trainer.h"

int main() {
    Trainer trainer;  // TRAINER OBJECT
    Tester tester;    // TESTER OBJECT

    DSString myString = "Hello, World!";
    std::cout << myString << "\n";

    // this uses the one argument constructor in DSString and then the inherited operator=
    myString = "Good bye!";
    std::cout << myString << "\n";

    std::cout << "substr: " << myString.substring(5, 3) << "\n";

    DSString a = "test";
    DSString b = a;
    std::cout << "b:" << b << std::endl;
    std::cout << "test" << std::endl;
    std::cout << std::boolalpha;
    std::cout << (a == b) << "\n";

    // use initialization list (see DSVector.h)
    std::vector<DSString> strings = {
        DSString("bbb"),
        DSString("aaa"),
        DSString("ddd"),
        DSString("eee"),
        DSString("ccc")};

    // find strings
    for (const auto &s : strings)
        std::cout
            << s << "\n";

    std::cout << "found ddd: " << (std::find(strings.begin(), strings.end(), DSString("ddd")) != strings.end()) << "\n";
    std::cout << "found zzz: " << (std::find(strings.begin(), strings.end(), DSString("zzz")) != strings.end()) << "\n";

    // sorting
    std::sort(strings.begin(), strings.end());

    for (const auto &s : strings)
        std::cout
            << s << "\n";

    //needed for maps to work
    std::cout << "found ddd: " << binary_search(strings.begin(), strings.end(), DSString("ddd")) << "\n";
    std::cout << "found zzz: " << binary_search(strings.begin(), strings.end(), DSString("zzz")) << "\n";

    std::cout << "---------END OF DSSTRING TESTS---------" << std::endl;;

    //          TRAINING:
    trainer.parseTrainData();
    trainer.getTrainingData();
    trainer.cleanTrainingVector();
    trainer.tokenizeAndMapTweets();
    
    trainer.filterBasicTokensFromMap(); //improves initial accuracy of 68% to 72%
    //     decided to filter function based on accuracy
    //     //trainer.filterStopWordsFromMap();

    //          TESTING:
    NaiveBayesClassifier classifier(trainer); //Classifier object
    tester.parseTestingData();
    tester.openSentimentFile();
    tester.mapTestingSentiments();
    tester.getTestingData();
    tester.cleanTestingVector();
    std::vector<Tweet> testingTweets = tester.getTestingTweets();

    int correctCount = 0;

    for (const Tweet &tweet : testingTweets) {
        DSString result = classifier.classifyTweet(tweet, trainer);
        DSString actualSentiment = tweet.getSentiment();

        // Debugging print statements
        // ADD DEBUG STATEMENT IN
        // std::cout << "Predicted: " << result << ", Actual: " << actualSentiment << std::endl;

        if (result == actualSentiment) {
            correctCount++;
            // ADD DEBUG STATEMENT IN
            // std::cout << "Correct Count: " << correctCount << std::endl;
        } else {
            // ADD DEBUG STATEMENT IN
            // std::cout << "Mismatch! Predicted: " << result << ", Actual: " << actualSentiment << std::endl;
        }
    }

    //          ACCURACY:
    double accuracy = (double)correctCount / testingTweets.size();
    std::cout << "Accuracy: " << accuracy << std::endl;
    
    return 0;
}
