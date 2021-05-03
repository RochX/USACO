#include <fstream>
#include <iostream>
#include <math.h>
#include <iterator>
#include <algorithm>
using namespace std;

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

int main()
{
	int size, maxTime = 0;
	ifstream lifein;
	lifein.open("lifeguards.in");
	
	lifein >> size;
	
	int tempTimeShifts[size*2], startTimes[size], timeShifts[size*2], indexList[size], tempList[size*2];
	
	
	
	for (int i = 0; i < size*2; i++)
	{
		lifein >> tempTimeShifts[i];
	}
	
	//sorts into ascending order with corresponding points
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
	
	for (int i = 0; i < size*2; i++)
	{
		cout << timeShifts[i] << " ";
	}
	
	for (int i = 0; i < size; i++)
	{
		indexList[i] = i*2+1;
	}
	
	int tempInt;
	for (int i = 0; i < size; i++)
	{
		for (int a = 0; a < size*2; a++)
		{
			tempList[a] = -1;
		}
		indexList[i-1] *= -1;
		indexList[i] *= -1;
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
		
		for (int j = 1; j < size*2; j++)
		{
			if (tempList[j] >= 0 and tempList[j-1] >= 0)
			{
				tempInt += tempList[j]-tempList[j-1];
				cout << tempList[j] << " " << tempList[j-1] << endl;
			}
		}
		maxTime = max(maxTime, tempInt);
	}
	
	lifein.close();
	
	ofstream lifeout;
	lifeout.open("lifeguards.out");
	
	lifeout << maxTime << endl;
	
	lifeout.close();
	
	return 0;
}