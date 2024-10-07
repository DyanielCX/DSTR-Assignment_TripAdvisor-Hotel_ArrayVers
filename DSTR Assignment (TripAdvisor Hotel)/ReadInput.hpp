#ifndef READINPUT_HPP
#define READINPUT_HPP

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Structure for storing reviews and ratings
struct ReviewAndRating {
    string* review_arr;
    string* rating_arr;
};


class ReadFile {
public:
    // Read review & rating csv file function
    inline ReviewAndRating readCSV(const int lineNum) {
        ReviewAndRating CSV_input;
        ifstream file_read("tripadvisor_hotel_reviews.csv");

        if (file_read.is_open()) {
            CSV_input.review_arr = new string[lineNum];
            CSV_input.rating_arr = new string[lineNum];

            for (int i = 0; i < lineNum; i++) {
                string empty_1, review, empty_2, rating;

                getline(file_read, empty_1, '"');
                getline(file_read, review, '"');
                getline(file_read, empty_2, ',');
                getline(file_read, rating, '\n');

                CSV_input.review_arr[i] = review;
                CSV_input.rating_arr[i] = rating;
            }

            file_read.close();
        }
        else {
            cout << "ERROR: Unable to open tripadvisor_hotel_reviews.csv" << endl;
        }

        return CSV_input;
    }

    // Read positive word text file function
    inline string* readPositiveWords(const int lineNum) {
        string* posWords = new string[lineNum];
        ifstream file_read("positive-words.txt");

        if (file_read.is_open()) {
            for (int i = 0; i < lineNum; i++) {
                file_read >> posWords[i];
            }
            file_read.close();
        }
        else {
            cout << "ERROR: Unable to open positive-words.txt" << endl;
        }

        return posWords;
    }

    // Read negative word text file function
    inline string* readNegativeWords(const int lineNum) {
        string* negWords = new string[lineNum];
        ifstream file_read("negative-words.txt");

        if (file_read.is_open()) {
            for (int i = 0; i < lineNum; i++) {
                file_read >> negWords[i];
            }
            file_read.close();
        }
        else {
            cout << "ERROR: Unable to open negative-words.txt" << endl;
        }

        return negWords;
    }

    // Display all positive word
    inline void showPosWord(string* PosWord_Data, const int POS_WORDS) {
        for (int i = 0; i < POS_WORDS; i++) {
            cout << PosWord_Data[i] << endl;
        }
    }

    // Display all negative word
    inline void showNegWord(string* NegWord_Data, const int NEG_WORDS) {
        for (int i = 0; i < NEG_WORDS; i++) {
            cout << NegWord_Data[i] << endl;
        }
    }
};

#endif 
