/*
 ID: 
 PROG: skidesign
 LANG: C++
 */
//NAME          :   
//GROUP         :   Krypton
//LAST MODIFIED :   27 December 2017
//PROBLEM ID    :   USACO Ski Course Design
//DESCRIPTION   :   Finds the minimum price that Farmer John must spend in order to put all of his hills within a range of 17
//SOURCES/HELP  :   
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

//function that returns the smaller number
int min(int x, int y)
{
    if (x >= y)
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
	const int TAX_DIFFERENCE = 17, MAX_HEIGHT = 100, MAX_HILLS = 1000, MAX_COST = MAX_HILLS/2*(MAX_HEIGHT*MAX_HEIGHT);
	int numHills, biggest, smallest, start, end, tempCost = 0, price, ;
		//the initial is one more than the max cost for any hill arrangement with the given parameters
		//this number is used so the minimum function always has 2 arguments
	int cost = MAX_COST+1;
	bool noneInRange;
	
	//open input file
	ifstream skidesignin;
	skidesignin.open("skidesign.in");
	
	//read in number of hills
	skidesignin >> numHills;
	
	//declare variable
	int heights[numHills];
	
	//reads in heights and sort them into ascending order
	for (int i = 0; i < numHills; i++)
	{
		skidesignin >> heights[i];
	}
	sort(heights, heights + numHills);
	
	//close input file
	skidesignin.close();
	
	//find the smallest and largest heights
	smallest = heights[0];
	biggest = heights[numHills-1];
	
	//tests all ranges possible for costs and finds the lowest cost
	for (int i = smallest; i+17 <= biggest; i++)
	{
		//declares the start and end points
		start = i;
		end = i + 17;
		
		//resets variables
		tempCost = 0;
		noneInRange = true;
		
		//finds cost of changing heights
		for (int i = numHills; i--;)
		{
			//resets variable
			price = 0;
			
			//adds price to temporary variable if the height is lower than the start point or higher than the end point
			if (heights[i] < start)
			{
				price = (start - heights[i])*(start - heights[i]);
				tempCost += price;
				noneInRange = false;
			}
			else if (heights[i] > end)
			{
				price = (heights[i] - end)*(heights[i] - end);
				tempCost += price;
				noneInRange = false;
			}
		}
		
		//case for when all numbers are within the range
		if (noneInRange)
		{
			tempCost = 5000001;
		}
		cost = min(cost, tempCost);
	}
	
	//case for when all heights are within 17 of each other
	if (cost == MAX_COST+1)
	{
		cost = 0;
	}
	
	//open output file
	ofstream skidesignout;
	skidesignout.open("skidesign.out");
	
	//send output
	skidesignout << cost << endl;
	
	//close output file
	skidesignout.close();
	
	//exit program
	return 0;
}