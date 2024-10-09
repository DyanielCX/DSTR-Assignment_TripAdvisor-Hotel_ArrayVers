#ifndef REVANALYSIS_MENU_TERNARY_HPP
#define REVANALYSIS_MENU_TERNARY_HPP

#include <iostream>
#include "Ternary_Function.hpp"
#include "RevAnalysis_Menu_Linear.hpp"
#include "RevAnalysisCalc.hpp"
#include "ReadInput.hpp"
using namespace std;


inline void countSentimentWord_Ternary(ReviewAndRating Review_Data, string* PosWord_Data, string* NegWord_Data, const int lineNum, const int POS_WORDS, const int NEG_WORDS) {
    AnalysisCalc calculator;
    Ternary_fucn tenFucn;

    int reviewNum = 0;
    do {
        // Title design
        cout << "\n \n \n";
        cout << "\033[0;34m"; // Set the text color to bright blue
        cout << "---------------------------------------" << endl;
        cout << "            Review Analysis            " << endl;
        cout << "          (Ternary Algorithm)          " << endl;
        cout << "---------------------------------------" << endl;
        cout << "\033[0m";
        cout << "\n";

        cout << "There are total " << lineNum << " reviews \n";
        cout << "Select review from 1 to " << lineNum << " for analysis. Enter 0 back to main" << endl;
        cout << "Enter review number (rating): ";
        cin >> reviewNum;
        cout << "\n";

        auto start = high_resolution_clock::now();    // Start the timer

        if (reviewNum > 0 && reviewNum <= lineNum) {

            // Create indices array for sorted ratings to allow review search by index
            int* indices = new int[lineNum];
            for (int i = 0; i < lineNum; i++) {
                indices[i] = i + 1;
            }

            // Use ternary search to find the review number in the sorted ratings array
            int foundIndex = tenFucn.indexFind(0, lineNum - 1, reviewNum, indices);

            if (foundIndex != -1) {
                string curReview = Review_Data.review_arr[foundIndex];
                string curRating = Review_Data.rating_arr[foundIndex];

                cout << "\033[1;33m";
                cout << "\nReview #" << reviewNum << "\n";
                cout << "\033[0m";
                cout << curReview << endl;

                string* foundPosWords = new string[POS_WORDS];
                string* foundNegWords = new string[NEG_WORDS];
                int posCount = 0, negCount = 0;

                // Count and collect positive and negative words
                calculator.countOccurrences(curReview, PosWord_Data, POS_WORDS, foundPosWords, posCount);
                calculator.countOccurrences(curReview, NegWord_Data, NEG_WORDS, foundNegWords, negCount);

                // Calculate sentiment score
                double sentimentScore = calculator.calculateSentimentScore(posCount, negCount);

                // Display positive & negative words + sentiment score
                display_POS_NEG(foundPosWords, foundNegWords, posCount, negCount);
                cout << "\nSentiment score (1 - 5) is " << sentimentScore << ", thus the rating should be equal to " << round(sentimentScore) << " (Neutral).\n \n" << endl;

                // Display review analysis conclusion
                string AnlysOutput = Define_AnlysOutput(sentimentScore, curRating);

                cout << "\033[1;33m";
                cout << "#------ Analysis Conclusion ------#" << endl;
                cout << "\033[0m";
                cout << "Sentiment Score(1-5) = " << round(sentimentScore) << endl;
                cout << "Rating given by user = " << curRating << endl;
                cout << "\nAnalysis output: \n \n" << AnlysOutput << endl;

                // Clean up dynamically allocated memory for found words
                delete[] foundPosWords;
                delete[] foundNegWords;
            }
            else {
                cout << "Review number not found!" << endl;
            }

        }
        else if (reviewNum != 0) {
            cout << "Invalid review number! Please enter a number between 1 and " << lineNum << "." << endl;
        }

        // Display time used for review analysis
        auto end = high_resolution_clock::now();      // End the timer
        auto duration = duration_cast<milliseconds>(end - start);
        int milliseconds = duration.count() % 1000;

        cout << "\nTime taken: " << milliseconds << " milliseconds " << endl;

    } while (reviewNum != 0);
}

#endif
