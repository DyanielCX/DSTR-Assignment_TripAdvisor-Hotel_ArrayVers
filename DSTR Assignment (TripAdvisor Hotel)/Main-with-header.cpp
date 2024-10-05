#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

const int CSV_lines = 20491;    // Number of lines in the csv file
const int POS_WORDS = 2006;     // Number of positive words in the text file
const int NEG_WORDS = 4783;     // Number of negative words in the text file


int main() {
    int program;

    while (true) {
        cout << "What do you want to do?" << endl;
        cout << "Choose your activities:" << endl;
        cout << "1. Refresh Data" << endl;
        cout << "2. Read Review" << endl;
        cout << "Enter number: ";
        cin >> program;

        switch (program) {
        case 1:
            //readfile();
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