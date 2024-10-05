#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Define a structure for review and rating
struct ReviewAndRating{
	string* review_arr;
	string* rating_arr;
};

class ReadFile {
private:
	

public:
	//Read CSV file funtion
	ReviewAndRating readCSV(const int lineNum);

    //Read Positive text file function
    string* readPositiveWords(const int lineNum);

    //Read Negative text file function
    string* readNegativeWords(const int lineNum);
};

ReviewAndRating ReadFile::readCSV(const int lineNum) {
	ReviewAndRating CSV_input;

    ifstream file_read("tripadvisor_hotel_reviews.csv");

    if (file_read.is_open()) {
        const int lineNum = 20491;
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

        for (int i = 0; i < lineNum; i++) {
            cout << i + 1 << " Review & Rating" << endl;
            cout << "Rating: " << CSV_input.rating_arr[i] << endl;
            cout << "Review: \n" << CSV_input.review_arr[i] << endl << endl;
        }

        file_read.close();
    }
    else {
        cout << "ERROR: tripadvisor_hotel_reviews.csv open fail" << endl;
    }

    return CSV_input;
}

string* ReadFile::readPositiveWords(const int lineNum) {
    
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

string* ReadFile::readNegativeWords(const int lineNum) {

    string* negWords = new string[lineNum];
    ifstream file_read("negative-words.txt");

    if (file_read.is_open()) {
        for (int i = 0; i < lineNum; i++) {
            file_read >> negWords[i];
        }
        file_read.close();
    }
    else {
        cout << "ERROR: Unable to open positive-words.txt" << endl;
    }

    return negWords;
}