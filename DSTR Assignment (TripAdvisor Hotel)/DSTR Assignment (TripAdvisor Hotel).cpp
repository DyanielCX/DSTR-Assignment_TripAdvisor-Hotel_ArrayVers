#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

const int POS_WORDS = 2006;  // Number of positive words in the text file
const int NEG_WORDS = 4783;  // Number of negative words in the text file

void readfile();
void readCSV();
void readPositiveWords();
void readNegativeWords();
void countSentimentWord();

int main() {
    int program;

    cout << "What do you want to do?" << endl;
    cout << "Choose your activities:" << endl;
    cout << "1. Read File" << endl;
    cout << "2. Read Review" << endl;
    cout << "Enter number: ";
    cin >> program;

    switch (program) {
    case 1:
        readfile();
        break;
    case 2:
        countSentimentWord();
        break;
    default:
        cout << "Invalid option!" << endl;
        break;
    }
    return 0;
}

void readfile() {
    int program;

    cout << "What do you want to do?" << endl;
    cout << "Choose your activities:" << endl;
    cout << "1. Read CSV" << endl;
    cout << "2. Read positive words" << endl;
    cout << "3. Read negative words" << endl;
    cout << "Enter number: ";
    cin >> program;

    switch (program) {
    case 1:
        readCSV();
        break;
    case 2:
        readPositiveWords();  // Now prints all positive words
        break;
    case 3:
        readNegativeWords();  // Now prints all negative words
        break;
    default:
        cout << "Invalid option!" << endl;
        break;
    }
    return;
}

void readCSV() {
    ifstream csv_read("tripadvisor_hotel_reviews.csv");

    if (csv_read.is_open()) {
        const int lineNum = 20491;
        string* review_arr = new string[lineNum];
        string* rating_arr = new string[lineNum];

        for (int i = 0; i < lineNum; i++) {
            string empty_1, review, empty_2, rating;

            getline(csv_read, empty_1, '"');
            getline(csv_read, review, '"');
            getline(csv_read, empty_2, ',');
            getline(csv_read, rating, '\n');

            review_arr[i] = review;
            rating_arr[i] = rating;
        }

        for (int i = 0; i < lineNum; i++) {
            cout << i + 1 << " Review & Rating" << endl;
            cout << "Rating: " << rating_arr[i] << endl;
            cout << "Review: \n" << review_arr[i] << endl << endl;
        }

        delete[] review_arr;
        delete[] rating_arr;
    }
    else {
        cout << "ERROR: tripadvisor_hotel_reviews.csv open fail" << endl;
    }

    csv_read.close();
}

// Modified function to print positive words
void readPositiveWords() {
    ifstream file("positive-words.txt");
    int count = 0;

    if (file.is_open()) {
        string word;
        cout << "Positive words loaded from file:\n";
        while (file >> word && count < POS_WORDS) {
            cout << word << endl;  // Print each word
            count++;
        }
        file.close();
    }
    else {
        cout << "ERROR: Unable to open positive-words.txt" << endl;
    }
}

// Modified function to print negative words
void readNegativeWords() {
    ifstream file("negative-words.txt");
    int count = 0;

    if (file.is_open()) {
        string word;
        cout << "Negative words loaded from file:\n";
        while (file >> word && count < NEG_WORDS) {
            cout << word << endl;  // Print each word
            count++;
        }
        file.close();
    }
    else {
        cout << "ERROR: Unable to open negative-words.txt" << endl;
    }
}

// Function to count and collect occurrences of positive/negative words in a review
void countOccurrences(const string& review, string* wordList, int wordCount, string* foundWords, int& count) {
    stringstream ss(review);
    string word;
    while (ss >> word) {
        for (int i = 0; i < wordCount; i++) {
            if (word == wordList[i]) {
                foundWords[count] = word;  // Store matched word
                count++;
            }
        }
    }
}

// Function to calculate the sentiment score
double calculateSentimentScore(int posCount, int negCount) {
    int N = posCount + negCount;
    if (N == 0) return 3;  // Neutral if no positive/negative words found

    int rawScore = posCount - negCount;
    int minRawScore = -N;
    int maxRawScore = N;
    double normalizedScore = (rawScore - minRawScore) / (double)(maxRawScore - minRawScore);
    return 1 + 4 * normalizedScore;
}

void countSentimentWord() {
    string* posWords = new string[POS_WORDS];
    string* negWords = new string[NEG_WORDS];

    // Load positive and negative words into arrays
    ifstream posFile("positive-words.txt");
    ifstream negFile("negative-words.txt");

    if (posFile.is_open() && negFile.is_open()) {
        for (int i = 0; i < POS_WORDS; i++) posFile >> posWords[i];
        for (int i = 0; i < NEG_WORDS; i++) negFile >> negWords[i];
    }
    posFile.close();
    negFile.close();

    ifstream csv_read("tripadvisor_hotel_reviews.csv");

    if (csv_read.is_open()) {
        const int lineNum = 20491;
        string* review_arr = new string[lineNum];
        string* rating_arr = new string[lineNum];

        for (int i = 0; i < lineNum; i++) {
            string empty_1, review, empty_2, rating;

            getline(csv_read, empty_1, '"');
            getline(csv_read, review, '"');
            getline(csv_read, empty_2, ',');
            getline(csv_read, rating, '\n');

            review_arr[i] = review;
            rating_arr[i] = rating;
        }

        int reviewNum = 0;
        do {
            cout << "There are total " << lineNum << " reviews \n";
            cout << "Enter number (1 to " << lineNum << ") to read review, or 0 to exit: ";
            cin >> reviewNum;

            if (reviewNum > 0 && reviewNum <= lineNum) {
                string curReview = review_arr[reviewNum - 1];
                string curRating = rating_arr[reviewNum - 1];

                cout << "\nReview #" << reviewNum << ":\n";
                cout << "Rating: " << curRating << endl;
                cout << "Review: \n" << curReview << endl;

                // Dynamically allocate arrays to store found positive and negative words
                string* foundPosWords = new string[POS_WORDS];
                string* foundNegWords = new string[NEG_WORDS];
                int posCount = 0, negCount = 0;

                // Count and collect positive and negative words
                countOccurrences(curReview, posWords, POS_WORDS, foundPosWords, posCount);
                countOccurrences(curReview, negWords, NEG_WORDS, foundNegWords, negCount);

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
                double sentimentScore = calculateSentimentScore(posCount, negCount);
                cout << "\nSentiment score (1 - 5) is " << sentimentScore << ", thus the rating should be equal to " << round(sentimentScore) << " (Neutral).\n";

                // Clean up dynamically allocated memory for found words
                delete[] foundPosWords;
                delete[] foundNegWords;

            }
            else if (reviewNum != 0) {
                cout << "Invalid review number! Please enter a number between 1 and " << lineNum << "." << endl;
            }
        } while (reviewNum != 0);

        delete[] review_arr;
        delete[] rating_arr;
    }
    else {
        cout << "ERROR: tripadvisor_hotel_reviews.csv open fail" << endl;
    }

    delete[] posWords;
    delete[] negWords;
    csv_read.close();
}
