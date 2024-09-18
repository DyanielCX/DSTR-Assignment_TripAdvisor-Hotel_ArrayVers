#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
    // read csv file
    ifstream csv_ipt("tripadvisor_hotel_reviews.csv");

    if (!csv_ipt.is_open()) {
        cout << "ERROR: File Open" << endl;
    }

    string empty_1;
    string review;
    string empty_2;
    string rating;

    // get data from csv file
   for (int i=0; i < 10; i++) {
        getline(csv_ipt, empty_1, '"');
        getline(csv_ipt, review, '"');
        getline(csv_ipt, empty_2, ',');
        getline(csv_ipt, rating, '\n');

        cout << "Review: \n" << review << endl;
        cout << "Rating: " << rating << endl << endl;

        //test convert str to int
        int rating_int = stoi(rating);
        rating_int = rating_int + 1;
        cout << "Rating in str: " << rating << endl;
        cout << "Rating in int (+1): " << rating_int << endl << endl;
    }

    csv_ipt.close();
}