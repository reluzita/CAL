/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>

string calcSum(int* sequence, int size)
{
    string res;
	for (int m = 1; m <= size; m++) {
	    int sum = INT_MAX;
	    int index = 0;
	    for(int i = 0; i <= size - m; i++) {
	        int s = 0;
	        for(int k = i; k < i + m; k++)
	            s += sequence[k];
	        if (s < sum) {
                sum = s;
                index = i;
            }
	    }
	    res += to_string(sum) + "," + to_string(index) + ";";
	}
	return res;
}

