#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ReadInput.hpp"
#include "DataRefresh_Menu.hpp"
#include "RevAnalysis_Menu.hpp"
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

    // Logo
    cout << "\n";
    cout << "\033[1;31m";  // Set the text color to bright red
    cout << "*************************************************************" << endl;
    cout << "*          T R I P A D V I S O R   H O T E L                *" << endl;
    cout << "*                                                           *" << endl;
    cout << "*     /$$$$$$$$        /$$            /$$$$$$        /$$    *" << endl;
    cout << "*    |__  $$__/       |__/           /$$__  $$      | $$    *" << endl;
    cout << "*       | $$  /$$$$$$  /$$  /$$$$$$ | $$  \\ $$  /$$$$$$$    *" << endl;
    cout << "*       | $$ /$$__  $$| $$ /$$__  $$| $$$$$$$$ /$$__  $$    *" << endl;
    cout << "*       | $$| $$  \\__/| $$| $$  | $$| $$__  $$| $$  | $$    *" << endl;
    cout << "*       | $$| $$      | $$| $$  | $$| $$  | $$| $$  | $$    *" << endl;
    cout << "*       | $$| $$      | $$| $$$$$$$/| $$  | $$|  $$$$$$$    *" << endl;
    cout << "*       |__/|__/      |__/| $$____/ |__/  |__/ \\_______/    *" << endl;
    cout << "*                         | $$                              *" << endl;
    cout << "*                         | $$                              *" << endl;
    cout << "*                         |__/                              *" << endl;
    cout << "*                                                           *" << endl;
    cout << "*     Your Trusted Source for Genuine Hotel Reviews!        *" << endl;
    cout << "*************************************************************" << endl;
    cout << "\033[0m";

    // Main Menu
    while (true) {
        // Title design
        cout << "\n";
        cout << "\033[1;36m";  // Sets the text color to bright cyan
        cout << "******************************" << endl;
        cout << "*         MAIN MENU          *" << endl;
        cout << "******************************" << endl;
        cout << "\033[0m";
        cout << "\n";

        cout << "What do you want to do?" << endl;
        cout << "Choose your activities:" << endl;
        cout << "1. Data Refresh" << endl;
        cout << "2. Review Analysis" << endl;
        cout << "3. Read Positive Word" << endl;
        cout << "4. Read Negative Word" << endl;
        cout << "Enter number: ";
        cin >> program;
        

        switch (program) {
        case 1:
            cout << endl;
            refreshData(Review_Data, PosWord_Data, NegWord_Data, CSV_lines, POS_WORDS, NEG_WORDS);
            break;
        case 2:
            countSentimentWord(Review_Data, PosWord_Data, NegWord_Data, CSV_lines, POS_WORDS, NEG_WORDS);
            break;
        case 3:
            // Output positive word
            for (int i = 0; i < POS_WORDS; i++) {
                cout << PosWord_Data[i] << endl;
            }
            cout << endl;
            break;
        case 4:
            // Output Negative word
            for (int i = 0; i < NEG_WORDS; i++) {
                cout << NegWord_Data[i] << endl;
            }
            cout << endl;
            break;
        default:
            cout << "Invalid option!" << endl;
            break;
        }
    }

    return 0;
}