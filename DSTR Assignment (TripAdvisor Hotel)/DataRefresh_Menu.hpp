#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ReadInput.hpp"
using namespace std;

const int CSV_lines = 20491;
const int POS_WORDS = 2006;  // Number of positive words in the text file
const int NEG_WORDS = 4783;  // Number of negative words in the text file

struct DataRefreshed {
    ReviewAndRating Review_Data;
    string* PosWord_Data;
    string* NegWord_Data;
};

void refreshData() {
    
    int program;
    ReadFile fileReader;
    ReviewAndRating Review_Data;
    string* PosWord_Data;
    string* NegWord_Data;

    cout << "What do you want to do?" << endl;
    cout << "Choose your activities:" << endl;
    cout << "1. Read CSV" << endl;
    cout << "2. Read positive words" << endl;
    cout << "3. Read negative words" << endl;
    cout << "Enter number: ";
    cin >> program;

    switch (program) {
    case 1: // Read CSV File
        Review_Data = fileReader.readCSV(CSV_lines);

        // Output the results
        if (Review_Data.review_arr && Review_Data.rating_arr) {
            for (int i = 0; i < CSV_lines; i++) {
                cout << i + 1 << " Review & Rating" << endl;
                cout << "Rating: " << Review_Data.rating_arr[i] << endl;
                cout << "Review: \n" << Review_Data.review_arr[i] << endl << endl;
            }

            // Clean up the dynamically allocated memory
            delete[] Review_Data.review_arr;
            delete[] Review_Data.rating_arr;
        }
        break;
    case 2: // Read Positive Word Text File
         PosWord_Data = fileReader.readPositiveWords(POS_WORDS);

         // Output the words (for demonstration, let's print the first 10 words)
         for (int i = 0; i < POS_WORDS; i++) {
             cout << PosWord_Data[i] << endl;
         }

         // Clean up the dynamically allocated memory
         delete[] PosWord_Data;

        break;
    case 3: // Read Negative Word Text File
        NegWord_Data = fileReader.readNegativeWords(NEG_WORDS);

        // Output the words (for demonstration, let's print the first 10 words)
        for (int i = 0; i < NEG_WORDS; i++) {
            cout << NegWord_Data[i] << endl;
        }

        // Clean up the dynamically allocated memory
        delete[] NegWord_Data;
        break;
    default:
        cout << "Invalid option!" << endl << endl;
        refreshData();
    }
    return;
}