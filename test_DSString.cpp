#include <iostream>
#include <vector>
#include <algorithm>

#include "DSString.h"
#include "Trainer.h"
#include "NaivesBayesClassifier.h"

int main()
{  
    Trainer trainer;//TRAINER TEST
    
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
        DSString("ccc")
    };

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
            
    std::cout << "END OF TESTS" << std::endl;
    // now we can do more efficient search
    std::cout << "PARSING CSV FILE" << std::endl;
    trainer.parseTrainData();
    std::cout << "PARSING DONE NOW PRINTING...." << std::endl;
    trainer.getTrainingData();
    trainer.cleanTrainingVector();
//     trainer.print();
     trainer.tokenizeAndMapTweets();
    trainer.printTokenMap();
    trainer.printFilteredTokens();

    trainer.filterBasicTokensFromMap();
    //keep or remove based on accuracy
    //trainer.filterStopWordsFromMap();
    trainer.printTokenMap();
    //sets probabilities for tokens
    NaiveBayesClassifier classifier(trainer);
    classifier.calculateTokenProbabilities(trainer);
    trainer.printTokenProbabilities();
    
    std::cout << "found ddd: " << binary_search(strings.begin(), strings.end(), DSString("ddd")) << "\n";
    std::cout << "found zzz: " << binary_search(strings.begin(), strings.end(), DSString("zzz")) << "\n";

    return 0;
}

