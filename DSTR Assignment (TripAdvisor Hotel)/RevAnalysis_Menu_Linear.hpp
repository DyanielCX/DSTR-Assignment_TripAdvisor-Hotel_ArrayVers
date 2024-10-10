#ifndef REVANALYSIS_MENU_HPP
#define REVANALYSIS_MENU_HPP

#include <iostream>
#include "RevAnalysisCalc.hpp"
#include "ReadInput.hpp"
using namespace std;

void display_POS_NEG(string* foundPosWords, string* foundNegWords, int posCount, int negCount);
string Define_AnlysOutput(double sentimentScore, string curRating);


inline void countSentimentWord(ReviewAndRating Review_Data, string* PosWord_Data, string* NegWord_Data, const int lineNum, const int POS_WORDS, const int NEG_WORDS) {
    AnalysisCalc calculator;

        int reviewNum = 0;
        do {
            // Title design
            cout << "\n \n \n";
            cout << "\033[0;34m"; // Set the text color to bright blue
            cout << "---------------------------------------" << endl;
            cout << "            Review Analysis            " << endl;
            cout << "           (Linear Algorithm)          " << endl;
            cout << "---------------------------------------" << endl;
            cout << "\033[0m";
            cout << "\n";

            cout << "There are total " << lineNum << " reviews \n";
            cout << "Select review from 1 to " << lineNum << " for analysis. Enter 0 back to main" << endl;
            cout << "Enter review number: ";
            cin >> reviewNum;
            cout << "\n";

            auto start = high_resolution_clock::now();    // Start the timer

            if (reviewNum > 0 && reviewNum <= lineNum) {
                string curReview = Review_Data.review_arr[reviewNum - 1];
                string curRating = Review_Data.rating_arr[reviewNum - 1];

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


// Display posWord negWord function
inline void display_POS_NEG(string* foundPosWords, string* foundNegWords, int posCount, int negCount) {
    
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
}

// Define analysis output function
inline string Define_AnlysOutput(double sentimentScore, string curRating) {
    string AnlysOutput;
    try {
        double Rating = stod(curRating);

        if (sentimentScore > Rating) {
            AnlysOutput = "The analysis indicates a more positive sentiment than the user�s personal rating.";
        }
        else if (sentimentScore == Rating) {
            AnlysOutput = "The user�s rating aligns with the sentiment score generated by the analysis.";
        }
        else {
            AnlysOutput = "The analysis reflects a more negative sentiment compared to the user's higher rating.";
        }
    }
    catch (const std::invalid_argument& e) {
        AnlysOutput = "Invalid rating format. Cannot compare with sentiment score.";
    }

    return AnlysOutput;
}

#endif 