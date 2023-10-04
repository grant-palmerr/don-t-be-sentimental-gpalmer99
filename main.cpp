#include <iostream>
#include <chrono>

#include "Analyzer.h"

int main(int argc, char** argv) {
    if (argc > 1) {
//include to test runtime
        //auto start = std::chrono::high_resolution_clock::now();

        Analyzer analysis;

        
        analysis.Train(argv[1]);

        //auto end = std::chrono::high_resolution_clock::now();
        //auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        //std::cout << "Analysis Executation time: " << duration << " ms" << std::endl;

        //uto start1 = std::chrono::high_resolution_clock::now();
        analysis.ClassifyAndEvaluate(argv[2], argv[3], argv[4], argv[5]);
        //auto end1 = std::chrono::high_resolution_clock::now();
        //auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end1-start1).count();
        //std::cout << "Classification Executation time: " << duration2 << " ms" << std::endl;

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
