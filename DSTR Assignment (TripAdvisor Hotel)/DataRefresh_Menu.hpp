#ifndef DATAREFRESH_MENU_HPP
#define DATAREFRESH_MENU_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ReadInput.hpp"
using namespace std;


inline void refreshData(ReviewAndRating &Review_Data, string* &PosWord_Data, string* &NegWord_Data, const int CSV_lines, const int POS_WORDS, const int NEG_WORDS) {
    
    int program;
    ReadFile fileReader;

    while (true) {
        // Title design
        cout << "\n";
        cout << "\033[0;34m"; // Set the text color to bright blue
        cout << "---------------------------------------" << endl;
        cout << "            Data Refresh              " << endl;
        cout << "---------------------------------------" << endl;
        cout << "\033[0m";
        cout << "\n";

        cout << "Choose the data that you want to refresh" << endl;
        cout << "1. Review & Rating" << endl;
        cout << "2. Positive words" << endl;
        cout << "3. Negative words" << endl;
        cout << "Enter number: ";
        cin >> program;


        switch (program) {
        case 1: // Refresh CSV File
            Review_Data = fileReader.readCSV(CSV_lines);
            cout << "<-- The review & rating array is refreshed -->" << endl << endl;
            break;

        case 2: // Refresh Positive Word Text File
            PosWord_Data = fileReader.readPositiveWords(POS_WORDS);
            cout << "<-- The positive word array is refreshed -->" << endl << endl;
            break;

        case 3: // Refresh Negative Word Text File
            NegWord_Data = fileReader.readNegativeWords(NEG_WORDS);
            cout << "<-- The positive word array is refreshed -->" << endl << endl;
            break;

        default:    // Re-prompt the user option
            cout << "Invalid option!" << endl << endl;
            continue;
        }

        break;  // Back to main page
    }

    return;
}

#endif 