#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ReadInput.hpp"
#ifndef DATAREFRESH_MENU_HPP
#define DATAREFRESH_MENU_HPP
using namespace std;

//const int CSV_lines = 20491;
//const int POS_WORDS = 2006;  // Number of positive words in the text file
//const int NEG_WORDS = 4783;  // Number of negative words in the text file

void refreshData(ReviewAndRating &Review_Data, string* &PosWord_Data, string* &NegWord_Data, const int CSV_lines, const int POS_WORDS, const int NEG_WORDS) {
    
    int program;
    ReadFile fileReader;
    //ReviewAndRating Review_Data;
    //string* PosWord_Data;
    //string* NegWord_Data;

    while (true) {
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
            break;

        case 2: // Read Positive Word Text File
            PosWord_Data = fileReader.readPositiveWords(POS_WORDS);
            break;

        case 3: // Read Negative Word Text File
            NegWord_Data = fileReader.readNegativeWords(NEG_WORDS);
            break;

        default:    // Re-prompt the user
            cout << "Invalid option!" << endl << endl;
            continue;
        }

        break;  // Back to main page
    }

    return;
}

#endif 