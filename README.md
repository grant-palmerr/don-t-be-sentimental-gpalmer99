# Project: Don't Be Sentimental!

**My Project Emphasizes Programming Aspects Like:** 

* Implementing a custom string class (DSString) that uses dynamic memory allocation and requires the implementation of the rule-of-three.
* Practice debugging and memory leak detection using Valgrind and VS Code Debugger.
* Use of STL container (vectors, maps, etc.)
* Analyzing the programs runtime complexity.
* Write a program with a command line interface.
* Designing, implementing, and testing a small system.

## Introduction
Have you ever read a tweet and thought, “Gee, what a positive outlook!” or “Wow, why so negative, friend?”  Can computers make the same determination?  They can surely try!

In Machine Learning, the task of assigning a **label** to a data item is called **classification** (putting things into different classes or categories).  The more specific name for what we’re going to do is sentiment analysis because you’re trying to determine the “sentiment” or attitude based on the words in a tweet.  The goal of the project is to build a sentiment classifier! Aren’t you excited??  ( ← That would be positive sentiment!)

In my project, I am given a set of tweets called the **training data set** that are already pre-classified by humans as **positive** or **negative** based on their content.  My project analyzes the frequency of occurrences of words in the tweets to develop a classification scheme, specifically I use a "naive" version of Bayes Thereom called [**Naive Bayes Classification**](https://en.wikipedia.org/wiki/Naive_Bayes_classifier).  I use this to then classify another set of tweets called the **testing data set** and **predict** if each tweet has positive sentiment or negative sentiment.

## Building a Classifier
The goal in classification is to assign a class label to each element of a data set, positive or negative in our case.  Of course, I would want this done with the highest accuracy possible.  At a high level, the process to build a classifier (and many other machine learning models) has two major steps:

1. Training Phase
   - Input is a set of tweets with each tweet’s associated sentiment value.  This is the training data set.
   - Example: Assume you have 10 tweets and each is pre-classified with positive or negative sentiment.  How might you go about analyzing the words in these 10 tweets to find words more commonly associated with negative sentiment and words more commonly associated with positive sentiment?
   - The result of the training step is a list of words (token class) that have an associated positive or negative sentiment with them depending on which type of tweet they appeared in more frequently. 

2. Testing Phase
   - In the testing phase, for a set of tweets called the testing data set, I predict the sentiment by using the list or lists of words extracted during the training phase.
   - Behind the scenes, I technically already know the sentiment of each of the tweets in the testing data set.  We’ll call this the actual sentiment or ground truth.  I then compare your predicted sentiment to the known sentiment for each of the testing tweets. My classifier is not 100% perfect, some of the predictions will be correct; some will be wrong.  The percentage correct is the accuracy.

## The Data
The data set we will be using in this project comes from real tweets posted around 11-12 years ago.  The original data was retrieved from Kaggle at https://www.kaggle.com/kazanova/sentiment140.  I’ve pre-processed it into the file format we are using for this project.  For more information, please see  Go, A., Bhayani, R. and Huang, L., 2009. Twitter sentiment classification using distant supervision. CS224N Project Report, Stanford, 1(2009), p.12.

**The preprocessed dataset can is already included in the data folder in the project repo.**

## Input files
There are 3 different input files:
* Training Data
* Testing Data Tweet (no sentiment column)
* Testing Ground Truth (id and sentiment for testing data for you to compare against).

The training data file is formatted as a comma-separated-values (CSV) file containing a list of tweets, each one on a separate line.  Each line of the data files include the following fields:
* Sentiment value (negative = 0, positive = 4, numbers in between are not used),
* the tweet id,
* the date the tweet was posted
* Query status (you can ignore this column)
* the twitter username that posted the tweet
* the text of the tweet itself

The testing data set is broken into two files:
* A CSV file containing formatted just like the training data EXCEPT no Sentiment column
* A CSV file containing tweet ID and sentiment for the testing dataset (so you can compare your predictions of sentiment to the actually sentiment ground truth)

Below are two example tweets from the training dataset:
```
4,1467811594,Mon Apr 06 22:20:03 PDT 2009,NO_QUERY,peruna_pony,"Beat TCU"
0,1467811595,Mon Apr 06 22:22:03 PDT 2009,NO_QUERY,the_frog,"Beat SMU"
```

Here is a tweet from the testing dataset:
```
1467811596,Mon Apr 06 22:20:03 PDT 2009,NO_QUERY,peruna_pony,"SMU > TCU"
```

The sentiment file for that testing tweet would be:
```
4, 1467811596
```

## Running your Program: Training and Testing
The program takes 5 command line arguments in this order:
1. training data set filename - the file with the training tweets
2. testing data set filename - tweets that your program will classify
3. testing data set sentiment filename - the file with the classifications for the testing tweet data
4. classifier results file name - see Output Files section below
5. classifier accuracy and errors file name - see Output Files section below

Example: In the build folder executing this command in the terminal should work.
```
./sentiment data/train_dataset_20k.csv data/test_dataset_10k.csv data/test_dataset_sentiment_10k.csv results.csv accuracy.txt
```

Note that `CMake` installs a copy of the data directory in the `build` directory and that is why you can directly
use `data` in the path for the files above.


### Output Files
The program produces two output files. The first file contains your classifier's
results for all tweets in the testing dataset in the same format as the sentiment file:
```
4, 1467811596
...
```

The second file is be organized as follows:
* The first line of the output file will contain the accuracy, a single floating point number with exactly 3 decimal places of precision.  See the section “How good is your classifier” below to understand Accuracy.
* The remaining lines of the file will contain for each tweet that your algorithm incorrectly classified your prediction,
the ground truth and the Tweet ID. This could be useful information as you tweak your algorithm to increase efficiency.

Example of the testing data tweet classifications file:
```
0.500
4, 1, 2323232323
1, 3, 1132553423
...
```


## Implementation Requirements

### DSString
I need strings to represent tweets and individual words.
For this project, I had to implement my own custom string class (`DSString`). **I do not use the STL string class or any other available string class from the Internet for this exercise. These are only used to interface to other code (e.g., to read from a file).**

**I did not use c-string functions (in headers `<string.h>` or `<cstring>`) in my string class** since they use C memory management with lots of pointers. The only exception is that you can use `strlen()` and `strcpy()` in your constructor or assignment operator when you convert a c-string into a DSString. Otherwise all other string operations (tokenize, etc.) were implemented myself by manipulating the character array. 

The program exclusively uses DSString class for strings. 

### Tokenizer For Breaking Tweets into Words

I had to design and implement an own algorithm to do this. I did not use the existing c-string tokenizer (`strtok()`) or STL solutions (`std::stringstream`).

### Classifier

Classifier Explanation

### Process
Training and testing of a classification algorithm was an iterative process.  I had to develop a training algorithm, test it, evaluate its performance, tweak the algo, retrain, retest, etc.  But how do I know how good my classifier actually worked? To do this I use **accuracy**.

$$\text{Accuracy} = \frac{(\text{total number of correctly classified tweets from test dataset})}{(\text{total number of tweets in the test data set})}  $$ 

**My algorithm performs with a 74% Accuracy!**

Note that if your classifier produces an accuracy close to 50% is is not performing better than random guessing. A classifier needs to reach at least 52% to demonstrate that it is working.

The Ways I Improved Accuracy:

### Stop words
You may look into using [stop words](https://en.wikipedia.org/wiki/Stop_word).

### Stemming
Happy, happier, and happiest all come from the same root word of happy. Finding a common word stem is called [stemming.](https://en.wikipedia.org/wiki/Stemming).  You might explore the use of a stemming library to help get to the root word.
Words that appear frequently in both positive and negative tweets are useless for determining sentiment. You can look for a C++ stemming library. If you have to convert `DSString` into `std::string` to use the library then you can do that.

### Character Encoding
Some tweets might have interesting characters in them that aren’t part of the ASCII character set.  You might look into [character encoding](https://www.joelonsoftware.com/2003/10/08/the-absolute-minimum-every-software-developer-absolutely-positively-must-know-about-unicode-and-character-sets-no-excuses/) and the `wchar_t` data type (instead of `char`) if this becomes a problem.

### Converting Counts into Probabilities
[Naive Bayes classifiers](https://en.wikipedia.org/wiki/Naive_Bayes_classifier) are a family of simple "probabilistic classifiers" based on applying Bayes' theorem. You can try to implement this strategy.










