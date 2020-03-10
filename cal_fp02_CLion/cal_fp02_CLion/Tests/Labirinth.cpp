/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;



Labirinth::Labirinth(int values[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j] = values[i][j];
}


void Labirinth::initializeVisited()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			visited[i][j] = false;
}




void  Labirinth::printLabirinth()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << labirinth[i][j] << " ";

		cout << endl;
	}
}


bool Labirinth::findGoal(int x, int y)
{
    visited[x][y] = true;
	if (labirinth[x][y] == 2)
	    return true;
	else if (labirinth[x][y] == 0)
	    return false;
	bool found = false;
	for (int i = 0; i < 4; i++) {
	    switch(i) {
	        case 0:
	            if(x - 1 >= 0) {
	                if(!visited[x-1][y]) {
                        found = findGoal(x - 1, y);
                        if (found)
                            return true;
                    }
                }
	            break;
            case 1:
                if(x + 1 < 10) {
                    if(!visited[x+1][y]) {
                        found = findGoal(x + 1, y);
                        if (found)
                            return true;
                    }
                }
                break;
            case 2:
                if(y - 1 >= 0) {
                    if(!visited[x][y - 1]) {
                        found = findGoal(x, y - 1);
                        if (found)
                            return true;
                    }
                }
                break;
            case 3:
                if(y + 1 < 10) {
                    if(!visited[x][y + 1]) {
                        found = findGoal(x, y + 1);
                        if (found)
                            return true;
                    }
                }
                break;
	    }
	}
	visited[x][y] = false;
	return false;
}


