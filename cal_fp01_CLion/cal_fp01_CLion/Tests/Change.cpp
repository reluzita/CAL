/*
 * Change.cpp
 */

#include "Change.h"

string calcChange(int m, int numCoins, int *coinValues)
{
    int minCoins[m + 1];
    int lastCoin[m + 1];
    for (int i = 0; i <= m; i++) {
        if(i < coinValues[0])
            minCoins[i] = 0;
        else
            minCoins[i] = INT_MAX;
        lastCoin[i] = 0;
    }

    if(coinValues[0] > m && m != 0)
        return "-";
    for (int i = 0; i < numCoins; i++) {
        for (int k = coinValues[i]; k <= m; k++) {
            if(minCoins[k - coinValues[i]] + 1 < minCoins[k]) {
                minCoins[k] = 1 + minCoins[k - coinValues[i]];
                lastCoin[k] = i;
            }
        }
    }

    string res;
    for (int i = m; i > 0; i-= coinValues[lastCoin[i]]) {
        res += to_string(coinValues[lastCoin[i]]) + ";";
    }
    return res;
}


