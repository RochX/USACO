/*
 ID: 
 PROG: milk2
 LANG: C++
 */
//NAME          :   
//GROUP         :   Krypton
//LAST MODIFIED :   26 December 2017
//PROBLEM ID    :   USACO Milking Cows
//DESCRIPTION   :   Finds the longest time interval where at least one cow was milked and the longest time interval where no cows were milked.
//SOURCES/HELP  :   
#include <fstream>
#include <iostream>
#include <math.h>
#include <iterator>
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
	//declare variables
	int numFarmers, numTimeStamps, milkTime = 0, idleTime = 0, tempInt, loopAmount, fixedTimeStampsSize, milkStart, milkEnd;
	float numDifferences, tempFloat;
	
	//open input file
	ifstream milk2in;
	milk2in.open("milk2.in");
	
	//read in amount of farmers
	milk2in >> numFarmers;
	
	//declare and initialize variables for start/stop times
	numTimeStamps = numFarmers*2;
	numDifferences = numTimeStamps-1;
	int timeStamps[numTimeStamps], idleDifferences[numTimeStamps-1], tempList[numFarmers], sorted[numTimeStamps], milkTimeStamps[numTimeStamps+2];
	
	//reads in the time stamps
	for (int i = 0; i < numTimeStamps; i++)
	{
		milk2in >> timeStamps[i];
	}
	
	//rearranges farmers by ascending starting time
	for (int i = 0; i < numFarmers; i++)
	{
		tempList[i] = timeStamps[i*2];
	}
	sort(tempList, tempList + numFarmers);
	for (int i = 0; i < numFarmers; i++)
	{
		sorted[i*2] = tempList[i];
		for (int j = 0; j < numFarmers; j++)
		{
			if (sorted[i*2] == timeStamps[j*2])
			{
				sorted[i*2+1] = timeStamps[j*2+1];
				break;
			}
		}
	}
	
	//puts sorted list into list that is used
	for (int i = 0; i < numTimeStamps; i++)
	{
		timeStamps[i] = sorted[i];
		milkTimeStamps[i] = sorted[i];
	}
	
	//adds two -1s to the end of the list so the next computation doesn't read garbage values
	milkTimeStamps[numTimeStamps] = -1;
	milkTimeStamps[numTimeStamps+1] = -1;
	
	//finds longest milk times
	for (int i = 0; i < numTimeStamps; i += 2)
	{
		//initialize start and end points
		milkStart = milkTimeStamps[i];
		milkEnd = milkTimeStamps[i+1];
		
		//loop for the remaining amount of farmers
		for (int j = i; j < numTimeStamps; j += 2)
		{
			//check if the start point of the next farmer is between the current start and end points
			if (milkStart <= milkTimeStamps[j+2] and milkTimeStamps[j+2] <= milkEnd)
			{
				//set new end point
				milkEnd = max(milkEnd, milkTimeStamps[j+3]);
			}
			else
			{
				//exit loop
				break;
			}
		}
		
		//find longest milking time
		milkTime = max(milkTime, milkEnd-milkStart);
	}
	
	//finds differences for idle time
	for (int i = 0; i < numDifferences; i++)
	{
		idleDifferences[i] = (timeStamps[i]-timeStamps[i+1])*-1;
	}
	
	//eliminates certain differences for idle time computation
	for (int i = 0; i < numTimeStamps; i += 2)
	{
		for (int j = 0; j < numTimeStamps; j += 2)
		{
			//checks if the first number in the pair is between the numbers of the next pair
			if (timeStamps[j] <= timeStamps[i] and timeStamps[i] <= timeStamps[j+1] and i != j)
			{
				//checks if the second number in the pair is between the numbers of the next pair
				if(timeStamps[j] <= timeStamps[i+1] and timeStamps[i+1] <= timeStamps[j+1])
				{
					idleDifferences[i+1] = 0;
				}
			}
		}
	}
	
	//finds longest idle times 
	loopAmount = floor(numDifferences/2);
	for (int i = 0; i < loopAmount; i++)
	{
		idleTime = max(idleTime, idleDifferences[i*2+1]);
	}
	
	//close input file
	milk2in.close();
	
	//open output file
	ofstream milk2out;
	milk2out.open("milk2.out");
	
	//output
	milk2out << milkTime << " " << idleTime << endl;
	
	//close output file
	milk2out.close();
	
	//exit program
	return 0;
}
			