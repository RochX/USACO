//NAME:		Xavier Silva
//Group:	Binary
//PROGRAM:	USACO Round 2 Lifeguards
#include <fstream>
#include <iostream>
#include <math.h>
#include <iterator>
#include <algorithm>
using namespace std;

//max function
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

//main function
int main()
{
	//declare variables
	int size, maxTime = 0;
	
	//input size
	ifstream lifein;
	lifein.open("lifeguards.in");
	lifein >> size;
	
	//declare variables
	int tempTimeShifts[size*2], startTimes[size], timeShifts[size*2], indexList[size], tempList[size*2];
	
	
	//input times
	for (int i = 0; i < size*2; i++)
	{
		lifein >> tempTimeShifts[i];
	}
	
	//sorts times into ascending order with corresponding points
	for (int i = 0; i < size; i++)
	{
		startTimes[i] = tempTimeShifts[i*2];
		cout << startTimes[i] << " ";
	}
	cout << endl;
	sort(startTimes, startTimes + size);
	for (int i = 0; i < size; i++)
	{
		cout << startTimes[i] << endl;
		timeShifts[i*2] = startTimes[i];
		for (int j = 0; j < size; j++)
		{
			if (timeShifts[i*2] == tempTimeShifts[j*2])
			{
				timeShifts[i*2+1] = tempTimeShifts[j*2+1];
				break;
			}
		}
	}
	
	//test couts
	for (int i = 0; i < size*2; i++)
	{
		cout << timeShifts[i] << " ";
	}
	
	//create a list of index values
	for (int i = 0; i < size; i++)
	{
		indexList[i] = i*2+1;
	}
	
	//declare variables
	int start, end, counter;
	
	//loop for all possible lifeguards fired
	for (int i = 0; i < size; i++)
	{
		//create a temporary list
		for (int a = 0; a < size*2; a++)
		{
			tempList[a] = -1;
		}
		
		//set index values to negative if the life guard is being fired and reset the previous one
		indexList[i-1] *= -1;
		indexList[i] *= -1;
		
		//create new list without the fired lifeguard
		for (int j = 0; j < size; j++)
		{
			//cout << "indexList = " << indexList[j]-1 << endl;
			if (indexList[j]-1 >= 0)
			{
				//c//out << "test" << timeShifts[indexList[j]-1] << endl;
				tempList[j*2] = timeShifts[indexList[j]-1];
				tempList[j*2+1] = timeShifts[indexList[j]-1+1];
			}
		}
		
		//test couts
		for (int a = 0; a < size*2; a++)
		{
			cout << tempList[a] << " ";
		}
		cout << endl;
		
		//calculate max time covered
			//Post Contest Note: After the contest I realized I calculated the wrong thing for this problem
		for (int k = 0; k < size*2; k += 2)
		{
			//set start and end points
			start = tempList[k];
			end = tempList[k+1];
			
			//loop for the rest of the times
			for (int h = k; h < size*2; h += 2)
			{
				//check if the start point of the next lifeguard is contained in the current start and end points
				if (start <= tempList[h+2] and tempList[h+2] <= end)
				{
					//set the end point to be the biggest number
					end = max(end, tempList[h+3]);
				}
				else
				{
					//exit loop
					break;
				}
			}
			//test couts
			cout << end << " - " << start << " = " << end-start << endl;
			
			//set the longest time
			maxTime = max(maxTime, end-start);
		}
	}
	
	//close input
	lifein.close();
	
	//output
	ofstream lifeout;
	lifeout.open("lifeguards.out");
	lifeout << maxTime+1 << endl;
	lifeout.close();
	
	//exit program
	return 0;
}