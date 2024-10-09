#ifndef TERNARY_FUNCTION_HPP
#define TERNARY_FUNCTION_HPP

#include <sstream>
#include <algorithm>
#include <limits.h>
#include <string>
using namespace std;

class Ternary_fucn {
public:
    // Find index function
    inline int indexFind(int start, int lineNum, int input, int ar[]) {
        if (lineNum >= start) {

            // Set mid1 and mid2
            int mid1 = start + (lineNum - start) / 3;
            int mid2 = lineNum - (lineNum - start) / 3;

            // Check the user input is the mid or not
            if (ar[mid1] == input) {
                return mid1;
            }
            if (ar[mid2] == input) {
                return mid2;
            }

            // Check the input from other three segment
            if (input < ar[mid1]) {
                // Search the first segment
                return indexFind(start, mid1 - 1, input, ar);
            }
            else if (input > ar[mid2]) {
                // Search the first segment
                return indexFind(mid2 + 1, lineNum, input, ar);
            }
            else {
                // Search the middle segment
                return indexFind(mid1 + 1, mid2 - 1, input, ar);
            }
        }

        // Key not found
        return -1;
    }
};

#endif 