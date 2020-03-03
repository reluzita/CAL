/*
 * Partioning.cpp
 */

#include "Partitioning.h"


int s_recursive(int n,int k)
{
   if(k == 1 || k == n)
       return 1;
   return s_recursive(n-1, k-1) + k*s_recursive(n-1, k);
}

int s_dynamic(int n,int k)
{
	int c[k];

	for (int i = 0; i < n; i++) {
	    int maxj;
	    if(k-1 > i)
	        maxj = i;
	    else
	        maxj = k - 1;
	    for (int j = maxj; j >= 0; j--) {
	        if ( j == 0 || j == i )
	            c[j] = 1;
	        else
	            c[j] = c[j-1] + (j+1)*c[j];
	    }
	}

	return c[k-1];
}


int b_recursive(int n)
{
    int res = 0;
    for (int k = 1; k <= n; k++)
        res += s_recursive(n, k);
    return res;
}

int b_dynamic(int n)
{
    int res = 0;
    for (int k = 1; k <= n; k++)
        res += s_dynamic(n, k);
    return res;
}


