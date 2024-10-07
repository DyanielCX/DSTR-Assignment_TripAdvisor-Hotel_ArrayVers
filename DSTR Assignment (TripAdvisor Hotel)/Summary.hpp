#ifndef SUMMARY_HPP
#define SUMMARY_HPP

#include <sstream>
#include <fstream>
#include <algorithm>
#include <limits.h>
#include <string>
#include <chrono>
#include <iostream>
#include "ReadInput.hpp"
using namespace std;
using namespace chrono;

inline void summary(ReviewAndRating Review_Data, string* PosWord_Data, string* NegWord_Data, const int lineNum, const int POS_WORDS, const int NEG_WORDS) {
    cout << "\nProcessing the reviews... This might take some time. Please wait." << endl;
    auto start = high_resolution_clock::now();  // Start the timer

    // Sort the word lists for binary searching
    sort(PosWord_Data, PosWord_Data + POS_WORDS);
    sort(NegWord_Data, NegWord_Data + NEG_WORDS);


    // Arrays to store the frequency of each positive and negative word
    int* posWordFreq = new int[POS_WORDS]();
    int* negWordFreq = new int[NEG_WORDS]();

    int totalPosCount = 0;
    int totalNegCount = 0;

    // Process each review
    for (int i = 0; i < lineNum; i++) {
        string curReview = Review_Data.review_arr[i];

        // Convert review to lowercase for case-insensitive matching
        transform(curReview.begin(), curReview.end(), curReview.begin(), ::tolower);

        // Check for occurrences of positive words
        for (int j = 0; j < POS_WORDS; j++) {
            if (curReview.find(PosWord_Data[j]) != string::npos) {
                posWordFreq[j]++;
                totalPosCount++;
            }
        }

        // Check for occurrences of negative words
        for (int j = 0; j < NEG_WORDS; j++) {
            if (curReview.find(NegWord_Data[j]) != string::npos) {
                negWordFreq[j]++;
                totalNegCount++;
            }
        }
    }

    // Title design
    cout << "\n \n";
    cout << "\033[0;34m"; // Set the text color to bright blue
    cout << "---------------------------------------" << endl;
    cout << "            Review Summary             " << endl;
    cout << "---------------------------------------" << endl;
    cout << "\033[0m";
    cout << "\n";

    // Display total counts of positive and negative words
    cout << "Total Reviews = " << lineNum << endl;
    cout << "Total Counts of positive words = " << totalPosCount << endl;
    cout << "Total Counts of negative words = " << totalNegCount << endl;

    // Display frequency of each positive word used
    cout << "\nFrequency of each positive word in reviews:\n";
    for (int i = 0; i < POS_WORDS; i++) {
        if (posWordFreq[i] > 0) {
            cout << PosWord_Data[i] << " = " << posWordFreq[i] << " times" << endl;
        }
    }

    // Display frequency of each negative word used
    cout << "\nFrequency of each negative word in reviews:\n";
    for (int i = 0; i < NEG_WORDS; i++) {
        if (negWordFreq[i] > 0) {
            cout << NegWord_Data[i] << " = " << negWordFreq[i] << " times" << endl;
        }
    }

    // Find the minimum and maximum used words
    int minFreq = INT_MAX;
    int maxFreq = 0;
    int minWordCount = 0;  // Counter for minimum-used words
    int maxWordCount = 0;  // Counter for maximum-used words

    // Search through positive words
    for (int i = 0; i < POS_WORDS; i++) {
        if (posWordFreq[i] > 0 && posWordFreq[i] < minFreq) {
            minFreq = posWordFreq[i];
            minWordCount = 1;
        }
        else if (posWordFreq[i] == minFreq) {
            minWordCount++;
        }

        if (posWordFreq[i] > maxFreq) {
            maxFreq = posWordFreq[i];
            maxWordCount = 1;
        }
        else if (posWordFreq[i] == maxFreq) {
            maxWordCount++;
        }
    }

    // Search through negative words
    for (int i = 0; i < NEG_WORDS; i++) {
        if (negWordFreq[i] > 0 && negWordFreq[i] < minFreq) {
            minFreq = negWordFreq[i];
            minWordCount = 1;
        }
        else if (negWordFreq[i] == minFreq) {
            minWordCount++;
        }

        if (negWordFreq[i] > maxFreq) {
            maxFreq = negWordFreq[i];
            maxWordCount = 1;
        }
        else if (negWordFreq[i] == maxFreq) {
            maxWordCount++;
        }
    }

    // Arrays to store all the minimum and maximum used words
    string* minUsedWords = new string[minWordCount];
    string* maxUsedWords = new string[maxWordCount];
    int minIndex = 0;
    int maxIndex = 0;

    // Add the minimum and maximum used positive words to the arrays
    for (int i = 0; i < POS_WORDS; i++) {
        if (posWordFreq[i] == minFreq) {
            minUsedWords[minIndex++] = PosWord_Data[i];
        }
        if (posWordFreq[i] == maxFreq) {
            maxUsedWords[maxIndex++] = PosWord_Data[i];
        }
    }

    // Add the minimum and maximum used negative words to the arrays
    for (int i = 0; i < NEG_WORDS; i++) {
        if (negWordFreq[i] == minFreq) {
            minUsedWords[minIndex++] = NegWord_Data[i];
        }
        if (negWordFreq[i] == maxFreq) {
            maxUsedWords[maxIndex++] = NegWord_Data[i];
        }
    }

    // Display maximum used words
    cout << "\nMaximum used words in the reviews: ";
    for (int i = 0; i < maxWordCount; i++) {
        cout << maxUsedWords[i];
        if (i < maxWordCount - 1) {
            cout << ", ";
        }
    }
    cout << " (" << maxFreq << " times)" << endl;

    // Display minimum used words
    cout << "\nMinimum used words in the reviews: ";
    for (int i = 0; i < minWordCount; i++) {
        cout << minUsedWords[i];
        if (i < minWordCount - 1) {
            cout << ", ";
        }
    }
    cout << " (" << minFreq << " times)" << endl;

    // Clean up dynamically allocated memory
    delete[] posWordFreq;
    delete[] negWordFreq;
    delete[] minUsedWords;
    delete[] maxUsedWords;

    auto end = high_resolution_clock::now();  // End the timer
    auto duration = duration_cast<seconds>(end - start);

    int minutes = duration.count() / 60;
    int seconds = duration.count() % 60;

    cout << "\nTime taken: " << minutes << " minutes " << seconds << " seconds" << endl;
}

#endif 