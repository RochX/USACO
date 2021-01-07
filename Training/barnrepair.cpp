/*
 ID: 
 PROG: barn1
 LANG: C++
 */
//NAME          :   
//GROUP         :   Krypton
//LAST MODIFIED :   31 December 2017
//PROBLEM ID    :   USACO Barn Repair
//DESCRIPTION   :   Finds the lowest number of stalls that need to be covered with a set amount of boards
//SOURCES/HELP  :   
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

//function that returns the bigger number
int max(int x, int y)
{
    if (x <= y)
    {
        return y;
    }
    else
    {
        return x;
    }
}

//main program
int main()
{
	//declare and initialize variables
	int maxBoards, numStalls, numCows, stallsCovered = 0;
	bool equal = false;
	
	//open input file
	ifstream barnin;
	barnin.open("barn1.in");
	
	//read in input
	barnin >> maxBoards >> numStalls >> numCows;
	
	//case for when there are more boards than cows
	if (maxBoards > numCows)
	{
		maxBoards = numCows;
		equal = true;
	}
	
	//finish declaring and initializing variables
	int numDifferences = numCows-1, numLargestDifferences = maxBoards-1, boardPointSize = maxBoards*2;
	int occupiedStalls[numCows], stallDifferences[numDifferences], tempList[numDifferences];
	int largestDifferences[numLargestDifferences], boardPoints[boardPointSize];
	
	//read in occupied stall numbers and sort by ascending order
	for (int i = 0; i < numCows; i++)
	{
		barnin >> occupiedStalls[i];
	}
	sort(occupiedStalls, occupiedStalls + numCows);
	
	//finds the differences between each stall number
	for (int i = 0; i < numDifferences; i++)
	{
		stallDifferences[i] = occupiedStalls[i+1] - occupiedStalls[i];
		tempList[i] = stallDifferences[i];
	}
	
	//sorts temporary list by ascending order
	sort(tempList, tempList + numDifferences);
	
	//finds the largest differences
	for (int i = 0; i < numLargestDifferences; i++)
	{
		largestDifferences[i] = tempList[numDifferences-i-1];
	}
	
	//finds which occupied stall numbers correspond with the largest differences
	int counter = 0, maxCounter = numLargestDifferences;
	for (int i = 0; i < numDifferences and counter < maxCounter; i++)
	{
		//checks for corresponding differences and whether it has already been checked
		if (stallDifferences[i] == largestDifferences[counter] and stallDifferences[i] != -1)
		{
			//sets the points
			boardPoints[counter*2] = occupiedStalls[i];
			boardPoints[counter*2+1] = occupiedStalls[i+1];
			
			//makes sure the difference isn't checked again
			stallDifferences[i] = -1;
			
			//resets and increments
			i = 0;
			counter++;
		}
	}
	
	//adds the first and last occupied stall to the point list
	boardPoints[boardPointSize-2] = occupiedStalls[0];
	boardPoints[boardPointSize-1] = occupiedStalls[numCows-1];
	
	//sorts into ascending order
	sort(boardPoints, boardPoints + boardPointSize);
	
	//adds up the differences to find the amount of stalls covered
	for (int i = 0; i < boardPointSize; i += 2)
	{
		stallsCovered += boardPoints[i+1] - boardPoints[i];
	}
	stallsCovered += maxBoards;
	
	//case for when there are more boards than cows
	if (equal)
	{
		stallsCovered = numCows;
	}
	
	//close input file
	barnin.close();
	
	//open output file
	ofstream barnout;
	barnout.open("barn1.out");
	
	//send output
	barnout << stallsCovered << endl;
	
	//close output file
	barnout.close();
	
	//exit program
	return 0;
}