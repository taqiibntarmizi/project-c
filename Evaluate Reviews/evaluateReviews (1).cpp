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


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "reviews.h"

using namespace std;

const double SCORE_LIMIT_TRUTHFUL = 3;
const double SCORE_LIMIT_DECEPTIVE = -3;

// this function returns the index of the element with the highest value in a vector
int ind_max(const vector<double> &vec) {

  //returns -1 if vector is empty
  if (vec.empty()) {
    return -1; 
  }

  // assume the first element is the largest
  int index_of_max = 0; 

  // iterate through vector, looking for any values bigger than the one we have
  for (size_t i = 0; i < vec.size(); ++i) {
    if (vec.at(i) > vec.at(index_of_max)){
      index_of_max = i;
    }
  }
  return index_of_max;
}


// this function returns the index of the element with the smallest value in a vector
int ind_min(const vector<double> &vec) {

  // return -1 if the vector is empty
  if (vec.empty()) {
    return -1; 
  }

  // assume the first element is the smallest
  int index_of_min = 0; 

  // iterate through vector, looking for any values smaller than the one we have
  for (size_t i = 0; i < vec.size(); ++i) {
    if (vec.at(i) < vec.at(index_of_min)){
      index_of_min = i;
    }
  }
  return index_of_min;
}


// this function returns the number of elements in a vector that matches a given string type
int sum(const vector<string> &vec, string category) {

  int sum = 0;
  for (size_t i = 0; i < vec.size(); ++i) {
    if(vec.at(i) == category){
        ++sum;
    }
  }
  return sum;
}


int main(){
    //open file input stream
    ifstream keywordsIn("keywordWeights.txt");

    //if cannot be opened, output to cout
    if(!keywordsIn.is_open()){
        cout << "Error: keywordWeights.txt could not be opened.";
        return 1;
    }

    //read keywords and weights into parallel vectors
    vector<string> keywords;
    vector<double> weights;
    readKeywordWeights(keywordsIn, keywords, weights);

    //initializing some variables that we will need to use inside and outside the 'for' loop
    vector<double> review_scores;
    vector<string> review_categories;
    int truthful_count = 0;
    int deceptive_count = 0;
    int uncat_count = 0;
    int i_highest = 0;
    int i_lowest = 0;

    //for each hotel review
    for(int i = 0; 0 <= i && i <= 99; ++i){
        //create the filename (turns it into .txt file)
        string review = makeReviewFilename(i);

        //open a filestream to the file
        ifstream reviewIn(review);

        //if it cannot open, exit the loop
        if(!reviewIn.is_open()){
            break;
        }

        //read each word from the review into a string vector
        vector<string> reviewWords;
        readReview(reviewIn, reviewWords);

        //calculate the review's score
        double review_score = reviewScore(reviewWords, keywords, weights);

        //determine the review's category
        string review_category;
        if (review_score > SCORE_LIMIT_TRUTHFUL){
            review_category = "truthful";
        } else if (review_score < SCORE_LIMIT_DECEPTIVE) {
            review_category = "deceptive";
        } else {
            review_category = "uncategorized";
        }

        //add the scores and categories to a vector of each (the indices correspond to each other)
        review_scores.push_back(review_score);
        review_categories.push_back(review_category);

        //get the indices of the highest and lowest scores
        i_highest = ind_max(review_scores);
        i_lowest = ind_min(review_scores);

        reviewIn.close();
    }

    //reading out to report.txt
    ofstream reportOut("report.txt");

    //using the sum function to get the total number of each review type
    truthful_count = sum(review_categories, "truthful");
    deceptive_count = sum(review_categories, "deceptive");
    uncat_count = sum(review_categories, "uncategorized");

    //header
    reportOut << "review score category" << endl;

    //individual reviews and scores
    int i = 0;
    for (size_t j = 0; j < review_scores.size(); ++j){
        reportOut << j << " " << review_scores.at(j) << " " << review_categories.at(j) << endl;
        i = j;
    }

    //final summaries
    reportOut << endl;
    reportOut << "Number of reviews: " << i + 1 << endl;
    reportOut << "Number of truthful reviews: " << truthful_count << endl;
    reportOut << "Number of deceptive reviews: " << deceptive_count << endl;
    reportOut << "Number of uncategorized reviews: " << uncat_count << endl;

    reportOut << endl;
    reportOut << "Review with highest score: " << i_highest << endl;
    reportOut << "Review with lowest score: " << i_lowest;

    reportOut.close();
}

