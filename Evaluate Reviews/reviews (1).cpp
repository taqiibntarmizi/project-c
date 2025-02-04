// <Nur Izzatul Adlina Adenan> 
// <Partner uniqname: mtaqi> 
// <Lab Section 025> 
// <November 12 2023>

//------------------------------------------------------
// AUTOGRADER INFO -- IGNORE BUT DO NOT REMOVE 
// test_cases: true
// feedback('all')
// c269759b-5ea7-4702-bff4-ebc05443d45d
//------------------------------------------------------


#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <functional>

#include "reviews.h"

using namespace std;

void readKeywordWeights(istream &input, vector<string> &keywords, vector<double> &weights) {
    string keyword;
    double weight;

    // add keywords and weights to respective vectors as they're read in from a file
    while(input >> keyword >> weight) {
      keywords.push_back(keyword);
      weights.push_back(weight);
   }
}

void readReview(istream &input, vector<string> &reviewWords) {
   string word;

   // add the words in a review to a vector as they're read in from a file
   while(input >> word) {
      reviewWords.push_back(word);
   }    
}

double wordWeight(const string &word, const vector<string> &keywords, const vector<double> &weights) {
    // for each word that matches a word in 'keywords', get its weight
   for(size_t i = 0; i < keywords.size(); ++i) {
      if(word == keywords.at(i)){
         return weights.at(i);
      }
   }

    // if the word is not in 'keywords', the word gets a 0.0 weight
    return 0.0;
}

double reviewScore(const vector<string> &reviewWords, const vector<string> &keywords, const vector<double> &weights) {

    // making a copy of the review
    vector<string> reviewCopy;

    for (size_t i=0; i < reviewWords.size(); ++i){
        reviewCopy.push_back(reviewWords.at(i)); 
    }

    // preprocessing the review
    preprocessReview(reviewCopy);
    
    // getting the word weights
    double score = 0;
    for (size_t i = 0; i < reviewCopy.size(); ++i){
        double weight = wordWeight(reviewCopy.at(i), keywords, weights);
        score += weight;
    }

   return score;
}










// -------------------- !!! *** DO NOT MODIFY ANY CODE BELOW THIS LINE *** !!! --------------------




// If you're curious, it's ok to look this code. But definitely don't change it!
// These are functions we intend for you to use in the rest of your code.






// Used as a helper function in preprocessReview.
static bool isNonAlphanumeric(char c) {
    // THIS FUNCTION IS ALREADY IMPLEMENTED FOR YOU. DO NOT CHANGE IT.
    return !isalnum(c);
}

// Preprocesses the individual words in a review by removing punctuation,
// converting all letters to lowercase, and replacing numbers (e.g. 100)
// by "<number>".
void preprocessReview(vector<string> &reviewWords) {
    // THIS FUNCTION IS ALREADY IMPLEMENTED FOR YOU. DO NOT CHANGE IT.

    for (int i = 0; i < int(reviewWords.size()); ++i) {
        // Create a reference to the word in the vector to use to change it.
        // A reference variable (just like a pass-by-reference parameter) will
        // refer to the original object, so our changes will show up in the vector.
        string &word = reviewWords.at(i);

        // Remove all non-alphanumeric characters (i.e. punctuation) from the word
        word.erase(remove_if(word.begin(), word.end(), isNonAlphanumeric), word.end());

        // Adjust all letters in the word to lowercase
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        // If the "word" is entirely numeric, change it to "<number>"
        if (all_of(word.begin(), word.end(), ::isdigit)) {
            word = "<number>";
        }
    }
}

// Generates the filename for the hotel review file corresponding
// to the given integer. It is presumed there will be no more than
// 100 reviews, numbered 0-99. It is required that 0 <= i && i <= 99.
string makeReviewFilename(int n) {
    // THIS FUNCTION IS ALREADY IMPLEMENTED FOR YOU. DO NOT CHANGE IT.
    int tensPlace = n / 10;
    int onesPlace = n % 10;
    return "review" + to_string(tensPlace) + to_string(onesPlace) + ".txt";
}
