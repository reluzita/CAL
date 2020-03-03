/*
 * Factorial.cpp
 */

#include "Factorial.h"

int factorialRecurs(int n)
{
	if (n == 1)
	    return 1;
	else
	    return factorialRecurs(n-1)*n;
}

int factorialDinam(int n)
{
	int res = 1;
	for(int i = 1; i <= n; i++)
	    res *= i;
	return res;
}
