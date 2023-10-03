#ifndef ANALYZER_H
#define ANALYZER_H

#include "Analyzer.h"
#include "DSString.h"
#include "NaiveBayesClassifier.h"
#include "Tester.h"
#include "Trainer.h"

class Analyzer {
   public:
    Trainer trainer;
    Tester tester;
    NaiveBayesClassifier classifier;

    void Train(const char* filePath);
    void ClassifyAndEvaluate(const char* filePath1, const char* filePath2, const char* resultsFile, const char* accuracyFile);
};

#endif