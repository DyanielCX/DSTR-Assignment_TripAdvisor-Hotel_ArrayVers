#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

const int POS_WORDS = 2006; 
const int NEG_WORDS = 4783;

void readCSV();
void readPositiveWords();
void readNegativeWords();

int main() {
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
        readPositiveWords();
        break;
    case 3:
        readNegativeWords();
        break;
    default:
        cout << "Invalid option!" << endl;
        break;
    }

    return 0;
}

void readCSV() {
    cout << "test" << endl;
    // Read csv file
    ifstream csv_read("tripadvisor_hotel_reviews.csv");

    if (csv_read.is_open()) {
        
        // Create vector
        const int lineNum = 20491;
        /*string review_arr[lineNum][2];*/
        vector<pair<string, string>> review_arr;

        // Get data from csv file
        for (int i = 0; i < lineNum; i++) {
            string empty_1;
            string review;
            string empty_2;
            string rating;

            getline(csv_read, empty_1, '"');
            getline(csv_read, review, '"');
            getline(csv_read, empty_2, ',');
            getline(csv_read, rating, '\n');

            cout << "Review: \n" << review << endl;
            cout << "Rating: " << rating << endl << endl;

            // Insert review and rating into the vector
            review_arr.push_back(make_pair(review, rating));
        }

        // Test print all the review and rating
        for (int i = 0; i < lineNum; i++) {
            string curReview = review_arr[i].first;
            string curRating = review_arr[i].second;

            cout << i+1 << " Review & Rating" << endl;
            cout << "Rating: " << curRating << endl;
            cout << "Review: \n" << curReview << endl << endl;
        }

        ////test convert str to int
        //int rating_int = stoi(rating);
        //rating_int = rating_int + 1;
        //cout << "Rating in str: " << rating << endl;
        //cout << "Rating in int (+1): " << rating_int << endl << endl;
    }else {
        cout << "ERROR: tripadvisor_hotel_reviews.csv open fail" << endl;
    }

    csv_read.close();
}

void readPositiveWords() {
    ifstream file("positive-words.txt"); // Opens the positive words file
    string words[POS_WORDS]; // Create a fixed-size array for storing positive words
    int count = 0;

    if (file.is_open()) {
        string word;
        // Reading positive words from the file into the array
        while (file >> word && count < POS_WORDS) {
            words[count] = word; // Store each word in the array
            count++;
        }
        file.close();

        // Output the positive words stored in the array
        cout << "Positive words loaded into fixed-size array:" << endl;
        for (int i = 0; i < count; i++) {
            cout << words[i] << endl;
        }
    }
    else {
        cout << "Unable to open file." << endl;
    }
}

void readNegativeWords() {
    ifstream file("negative-words.txt");
    string words[NEG_WORDS]; // Fixed-size array
    int count = 0;

    if (file.is_open()) {
        string word;
        while (file >> word && count < NEG_WORDS) {
            words[count] = word; // Store each word in the array
            count++;
        }
        file.close();

        // Output the array content
        cout << "Negative words loaded into fixed-size array:" << endl;
        for (int i = 0; i < count; i++) {
            cout << words[i] << endl;
        }
    }
    else {
        cout << "Unable to open file." << endl;
    }
}