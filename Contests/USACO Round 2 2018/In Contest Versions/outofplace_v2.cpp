//NAME:		Xavier Silva
//Group:	Binary
//PROGRAM:	USACO Round 2 Out of Place
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
	//declare variables
	int size, numMoves = 0, tempInt;
	
	//input
	ifstream placein;
	placein.open("outofplace.in");
	placein >> size;
	
	//declare variables
	int tempList[size+2];
	
	//set beginning and end of list to impossible values
	tempList[0] = 0;
	tempList[size+1] = 1000001;
	
	//input
	for (int i = 0; i < size; i++)
	{
		placein >> tempList[i+1];
	}
	
	//initialize variable
	tempInt = size+2;
	
	//find duplicates in the list
	for (int i = 0; i < size+2; i++)
	{
	    for (int j = i+1; j < size+2; j++)
	    {
	        if (tempList[i] == tempList[j])
	        {
	            tempList[i] *= -1;
	            size--;
	        }
	    }
	}
	//test cout
	cout << size << endl;
	
	//declare variables
	int heights[size+2], counter = 0, correctHeights[size+2];
	
	//create new list without duplicates
	for (int i = 0; i < tempInt; i++)
	{
	    //cout << tempList[i] << endl;
	    if (tempList[i] >= 0)
	    {
	        heights[counter] = tempList[i];
	        cout << heights[counter] << " ";
	        counter++;
	    }
	}
	cout << endl;
	
	//create a template of the end result
	for (int i = 0; i < size+2; i++)
	{
		correctHeights[i] = heights[i];
		cout << correctHeights[i] << " ";
	}
	sort(correctHeights, correctHeights + size+2);
	
	//loops to swap 
	for (int i = 1; i < size+1; i++)
	{
	    for (int j = 1; j < size+1; j++)
	    {
			//height is greater than the next height
    		if (heights[i-1] > heights[i])
    		{
    			tempInt = heights[i-1];
    			heights[i-1] = heights[i];
    			heights[i] = tempInt;
    			i--;
    			numMoves++;
    		}
			//next height is less than the current height
    		else if (heights[i+1] < heights[i])
    		{
    			tempInt = heights[i+1];
    			heights[i+1] = heights[i];
    			heights[i] = tempInt;
    			numMoves++;
    		}
			
			//test couts
    		for (int i = 0; i < size+2; i++)
    	    {
    	    	cout << heights[i] << " ";
    	    }
    	    cout << endl;
	    }
	}
	
	//close input
	placein.close();
	//numMoves--;
	
	cout << numMoves << endl;
	
	//fall back case
	if (numMoves < 0)
	{
	    cout << "test";
		numMoves = 0;
	}
	
	//output
	ofstream placeout;
	placeout.open("outofplace.out");
	placeout << numMoves << endl;
	placeout.close();
	
	//exit program
	return 0;
}