#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ReadInput.hpp"
#include "DataRefresh_Menu.hpp"
using namespace std;

const int CSV_lines = 20491;    // Number of lines in the csv file
const int POS_WORDS = 2006;     // Number of positive words in the text file
const int NEG_WORDS = 4783;     // Number of negative words in the text file

int main() {
    int program;
    ReadFile fileReader;

    // Default data load
    ReviewAndRating Review_Data;
    string* PosWord_Data = nullptr;
    string* NegWord_Data = nullptr;

    Review_Data = fileReader.readCSV(CSV_lines);
    PosWord_Data = fileReader.readPositiveWords(POS_WORDS);
    NegWord_Data = fileReader.readNegativeWords(NEG_WORDS);

    // Main Menu
    while (true) {
        cout << "What do you want to do?" << endl;
        cout << "Choose your activities:" << endl;
        cout << "1. Refresh Data" << endl;
        cout << "2. Read Review" << endl;
        cout << "Enter number: ";
        cin >> program;

        switch (program) {
        case 1:
            refreshData(Review_Data, PosWord_Data, NegWord_Data, CSV_lines, POS_WORDS, NEG_WORDS);

            // Output review
            if (Review_Data.review_arr && Review_Data.rating_arr) {
                for (int i = 0; i < CSV_lines; i++) {
                    cout << i + 1 << " Review & Rating" << endl;
                    cout << "Rating: " << Review_Data.rating_arr[i] << endl;
                    cout << "Review: \n" << Review_Data.review_arr[i] << endl << endl;
                }
            }

            // Output positive word
            for (int i = 0; i < 10; i++) {
                cout << PosWord_Data[i] << endl;
            }

            // Output the words (for demonstration, let's print the first 10 words)
            for (int i = 0; i < 10; i++) {
                cout << NegWord_Data[i] << endl;
            }

            break;
        case 2:
            //countSentimentWord();
            break;
        default:
            cout << "Invalid option!" << endl;
            break;
        }
    }

    return 0;
}