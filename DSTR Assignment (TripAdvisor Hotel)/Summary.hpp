#ifndef SUMMARY_HPP
#define SUMMARY_HPP

#include <sstream>
#include <fstream>
#include <limits.h>
#include <string>
#include <chrono>
#include <iostream>
#include "ReadInput.hpp"
using namespace std;
using namespace chrono;

// Check word occurrences function - linear search
inline void CheckWordOcc(string curReview, string* wordList, int* wordFreq, int& totalCount, const int wordCount) {
    for (int j = 0; j < wordCount; j++) {
        if (curReview.find(wordList[j]) != string::npos) {
            wordFreq[j]++;
            totalCount++;
        }
    }
}

// Merge function to sort words based on frequency in descending order
inline void merge(string* wordArr, int* freqArr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Temporary arrays
    string* leftWords = new string[n1];
    string* rightWords = new string[n2];
    int* leftFreq = new int[n1];
    int* rightFreq = new int[n2];

    // Copy data into temporary arrays
    for (int i = 0; i < n1; i++) {
        leftWords[i] = wordArr[left + i];
        leftFreq[i] = freqArr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightWords[i] = wordArr[mid + 1 + i];
        rightFreq[i] = freqArr[mid + 1 + i];
    }

    // Merge the temp arrays back into wordArr and freqArr
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftFreq[i] >= rightFreq[j]) {  // Sort by frequency (descending)
            wordArr[k] = leftWords[i];
            freqArr[k] = leftFreq[i];
            i++;
        }
        else {
            wordArr[k] = rightWords[j];
            freqArr[k] = rightFreq[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of leftWords and leftFreq
    while (i < n1) {
        wordArr[k] = leftWords[i];
        freqArr[k] = leftFreq[i];
        i++;
        k++;
    }

    // Copy remaining elements of rightWords and rightFreq
    while (j < n2) {
        wordArr[k] = rightWords[j];
        freqArr[k] = rightFreq[j];
        j++;
        k++;
    }

    // Free the temporary arrays
    delete[] leftWords;
    delete[] rightWords;
    delete[] leftFreq;
}

// Merge Sort function to sort by word frequency in descending order
inline void mergeSort(string* wordArr, int* freqArr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(wordArr, freqArr, left, mid);
        mergeSort(wordArr, freqArr, mid + 1, right);
        merge(wordArr, freqArr, left, mid, right);
    }
}

// Display words and their frequencies, including words with 0 occurrences
inline void displayWordFreq(const string* wordList, const int* wordFreq, const int wordCount, const string& wordType) {
    cout << "\n" << wordType << " words in reviews (from max used to min used): \n";
    for (int i = 0; i < wordCount; i++) {
        cout << wordList[i] << " = " << wordFreq[i] << " times" << endl;  // Display words even if frequency is 0
    }
}

inline void findMinMaxUsedWords(const int* posWordFreq, const int* negWordFreq, const string* posWordList, const string* negWordList,
    const int POS_WORDS, const int NEG_WORDS, string*& minUsedWords, string*& maxUsedWords,
    int& minFreq, int& maxFreq, int& minWordCount, int& maxWordCount) {

    minFreq = INT_MAX;
    maxFreq = 0;

    minWordCount = 0;
    maxWordCount = 0;

    // Determine the max frequency across positive words
    for (int i = 0; i < POS_WORDS; i++) {
        if (posWordFreq[i] > maxFreq) {
            maxFreq = posWordFreq[i];
            maxWordCount = 1;
        }
        else if (posWordFreq[i] == maxFreq) {
            maxWordCount++;
        }

        // Handle words with 0 occurrences or the minimum frequency
        if (posWordFreq[i] == 0) {
            if (minFreq != 0) {
                minFreq = 0;
                minWordCount = 1;  // First word with 0 occurrences
            }
            else {
                minWordCount++;
            }
        }
        else if (posWordFreq[i] < minFreq) {
            minFreq = posWordFreq[i];
            minWordCount = 1;
        }
        else if (posWordFreq[i] == minFreq) {
            minWordCount++;
        }
    }

    // Determine the min/max frequency across negative words
    for (int i = 0; i < NEG_WORDS; i++) {
        if (negWordFreq[i] > maxFreq) {
            maxFreq = negWordFreq[i];
            maxWordCount = 1;
        }
        else if (negWordFreq[i] == maxFreq) {
            maxWordCount++;
        }

        // Handle words with 0 occurrences or the minimum frequency
        if (negWordFreq[i] == 0) {
            if (minFreq != 0) {
                minFreq = 0;
                minWordCount = 1;  // First word with 0 occurrences
            }
            else {
                minWordCount++;
            }
        }
        else if (negWordFreq[i] < minFreq) {
            minFreq = negWordFreq[i];
            minWordCount = 1;
        }
        else if (negWordFreq[i] == minFreq) {
            minWordCount++;
        }
    }

    // Allocate memory for the min and max used words based on the correct counts
    minUsedWords = new string[minWordCount];
    maxUsedWords = new string[maxWordCount];

    int minIndex = 0;
    int maxIndex = 0;

    // Populate the min and max used words arrays for positive words
    for (int i = 0; i < POS_WORDS; i++) {
        if (posWordFreq[i] == minFreq) {
            minUsedWords[minIndex++] = posWordList[i];
        }
        if (posWordFreq[i] == maxFreq) {
            maxUsedWords[maxIndex++] = posWordList[i];
        }
    }

    // Populate the min and max used words arrays for negative words
    for (int i = 0; i < NEG_WORDS; i++) {
        if (negWordFreq[i] == minFreq) {
            minUsedWords[minIndex++] = negWordList[i];
        }
        if (negWordFreq[i] == maxFreq) {
            maxUsedWords[maxIndex++] = negWordList[i];
        }
    }
}


// Display word usage function
inline void displayWordUsage(const string* wordArray, int wordCount, int freq, const string& usageType) {
    cout << "\n" << usageType << " used words in the reviews: ";
    for (int i = 0; i < wordCount; i++) {
        cout << wordArray[i];
        if (i < wordCount - 1) {
            cout << ", ";
        }
    }
    cout << " (" << freq << " times)" << endl;
}

// Summary function
inline void summary(ReviewAndRating Review_Data, string* PosWord_Data, string* NegWord_Data, const int lineNum, const int POS_WORDS, const int NEG_WORDS) {
    cout << "\nProcessing the reviews... This might take some time. Please wait." << endl;
    auto start = high_resolution_clock::now();  // Start the timer

    // Arrays to store the frequency of each positive and negative word
    int* posWordFreq = new int[POS_WORDS]();
    int* negWordFreq = new int[NEG_WORDS]();
    int totalPosCount = 0;
    int totalNegCount = 0;

    // Process each review
    for (int i = 0; i < lineNum; i++) {
        string curReview = Review_Data.review_arr[i];
        transform(curReview.begin(), curReview.end(), curReview.begin(), ::tolower); // Case-insensitive

        // Check for occurrences of positive and negative words
        CheckWordOcc(curReview, PosWord_Data, posWordFreq, totalPosCount, POS_WORDS);
        CheckWordOcc(curReview, NegWord_Data, negWordFreq, totalNegCount, NEG_WORDS);
    }

    // Sort positive and negative words by frequency (descending)
    mergeSort(PosWord_Data, posWordFreq, 0, POS_WORDS - 1);
    mergeSort(NegWord_Data, negWordFreq, 0, NEG_WORDS - 1);

    // Title design
    cout << "\n \n";
    cout << "\033[0;34m"; // Set the text color to bright blue
    cout << "---------------------------------------" << endl;
    cout << "            Review Summary             " << endl;
    cout << "---------------------------------------" << endl;
    cout << "\033[0m";
    cout << "\n";

    // Display total counts of reviews, positive words, and negative words
    cout << "Total Reviews = " << lineNum << endl;
    cout << "Total Counts of positive words = " << totalPosCount << endl;
    cout << "Total Counts of negative words = " << totalNegCount << endl;

    // Display sorted word frequencies based on usage frequency
    displayWordFreq(PosWord_Data, posWordFreq, POS_WORDS, "Positive");
    displayWordFreq(NegWord_Data, negWordFreq, NEG_WORDS, "Negative");

    // Find max and min used words
    int minFreq = INT_MAX;
    int maxFreq = 0;
    int minWordCount = 0;
    int maxWordCount = 0;
    string* minUsedWords = nullptr;
    string* maxUsedWords = nullptr;

    findMinMaxUsedWords(posWordFreq, negWordFreq, PosWord_Data, NegWord_Data, POS_WORDS, NEG_WORDS, minUsedWords, maxUsedWords, minFreq, maxFreq, minWordCount, maxWordCount);

    // Display max & min used words
    displayWordUsage(maxUsedWords, maxWordCount, maxFreq, "Maximum");
    displayWordUsage(minUsedWords, minWordCount, minFreq, "Minimum");

    // Clean up dynamically allocated memory
    delete[] posWordFreq;
    delete[] negWordFreq;
    delete[] minUsedWords;
    delete[] maxUsedWords;

    auto end = high_resolution_clock::now();  // End the timer
    auto duration = duration_cast<seconds>(end - start);

    auto minutes = duration.count() / 60;  // Use auto to avoid narrowing warnings
    auto seconds = duration.count() % 60;

    // Display time taken
    cout << "\nTime taken: " << minutes << " minutes " << seconds << " seconds" << endl;
}

#endif
