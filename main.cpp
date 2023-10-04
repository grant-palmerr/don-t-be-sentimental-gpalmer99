#include <iostream>

#include "Analyzer.h"

int main(int argc, char** argv) {
    if (argc > 1) {
        Analyzer analysis;

        analysis.Train(argv[1]);
        analysis.ClassifyAndEvaluate(argv[2], argv[3], argv[4], argv[5]);

        // argv [1] = "data/train_dataset_20k.csv"
        // argv [2] = "data/test_dataset_10k.csv"
        // argv [3] = "data/test_dataset_sentiment_10k.csv"
        // argv [4] = "results.csv"
        // argv [5] = "accuracy.txt"

        // paste in terminal when you run
        //./sentiment data/train_dataset_20k.csv data/test_dataset_10k.cv data/test_dataset_sentiment_10k.cv results.cs accuracy.txt
        // I need to enter //./sentiment ../ return (0):
    }

    return 0;
}

// Comments:

// name of file opened successfully
// training comment..
// testing comment..
// writing to file..

// remove lines in files
