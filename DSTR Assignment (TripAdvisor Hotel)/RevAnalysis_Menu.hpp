#ifndef REVANALYSIS_MENU_HPP
#define REVANALYSIS_MENU_HPP


#include <iostream>
#include "RevAnalysisCalc.hpp"
#include "ReadInput.hpp"
using namespace std;

void countSentimentWord(ReviewAndRating Review_Data, string* PosWord_Data, string* NegWord_Data, const int lineNum, const int POS_WORDS, const int NEG_WORDS) {
    AnalysisCalc calculator;

        int reviewNum = 0;
        do {
            cout << "There are total " << lineNum << " reviews \n";
            cout << "Enter number (1 to " << lineNum << ") to read review, or 0 to exit: ";
            cin >> reviewNum;

            if (reviewNum > 0 && reviewNum <= lineNum) {
                string curReview = Review_Data.review_arr[reviewNum - 1];
                string curRating = Review_Data.rating_arr[reviewNum - 1];

                cout << "\nReview #" << reviewNum << ":\n";
                cout << "Rating: " << curRating << endl;
                cout << "Review: \n" << curReview << endl;

                // Dynamically allocate arrays to store found positive and negative words
                string* foundPosWords = new string[POS_WORDS];
                string* foundNegWords = new string[NEG_WORDS];
                int posCount = 0, negCount = 0;

                // Count and collect positive and negative words
                calculator.countOccurrences(curReview, PosWord_Data, POS_WORDS, foundPosWords, posCount);
                calculator.countOccurrences(curReview, NegWord_Data, NEG_WORDS, foundNegWords, negCount);

                // Display positive words
                cout << "\nPositive Words = " << posCount << ":\n";
                for (int i = 0; i < posCount; i++) {
                    cout << "- " << foundPosWords[i] << endl;
                }

                // Display negative words
                cout << "\nNegative Words = " << negCount << ":\n";
                for (int i = 0; i < negCount; i++) {
                    cout << "- " << foundNegWords[i] << endl;
                }

                // Calculate and display sentiment score
                double sentimentScore = calculator.calculateSentimentScore(posCount, negCount);
                cout << "\nSentiment score (1 - 5) is " << sentimentScore << ", thus the rating should be equal to " << round(sentimentScore) << " (Neutral).\n";

                // Clean up dynamically allocated memory for found words
                delete[] foundPosWords;
                delete[] foundNegWords;

            }
            else if (reviewNum != 0) {
                cout << "Invalid review number! Please enter a number between 1 and " << lineNum << "." << endl;
            }
        } while (reviewNum != 0);
}

#endif 