#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
	int size, numMoves = 0;
	ifstream placein;
	placein.open("outofplace.in");
	
	placein >> size;

	int tempHeights[size+2], correctHeights[size+2];
	heights[0] = 0;
	for (int i = 0; i < size; i++)
	{
		placein >> heights[i+1];
	}
	heights[size+1] = 1000001;
	
	for (int i = 0; i < size+2; i++)
	{
		correctHeights[i] = heights[i];
	}
	sort(correctHeights, correctHeights + size+2);
	
	bool checkBreak;
	int tempInt;
	for (int i = 1; i < size+1; i++)
	{
	    for (int j = 1; j < size+1; j++)
	    {
    		if (heights[i-1] > heights[i])
    		{
    			tempInt = heights[i-1];
    			heights[i-1] = heights[i];
    			heights[i] = tempInt;
    			i--;
    			numMoves++;
    		}
    		else if (heights[i+1] < heights[i])
    		{
    			tempInt = heights[i+1];
    			heights[i+1] = heights[i];
    			heights[i] = tempInt;
    			numMoves++;
    		}
	    }
	}
	placein.close();
	
	if (numMoves < 0)
	{
		numMoves = 0;
	}
	
	ofstream placeout;
	placeout.open("outofplace.out");
	
	placeout << numMoves << endl;
	
	placeout.close();
	return 0;
}