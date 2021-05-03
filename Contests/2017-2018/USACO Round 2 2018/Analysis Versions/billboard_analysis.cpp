//NAME:		Xavier Silva
//Group:	Binary
//PROGRAM:	USACO Round 2 Blocked Billboard II
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;

int main()
{
	//declare variables
	int area, CF[2*2], LM[4*2], containedPoints[8];
	
	//input
	ifstream billin;
	billin.open("billboard.in");
	for (int i = 0; i < 4; i++)
	{
		billin >> LM[i];
	}
	//find the other points of the lawnmower rectangle
	LM[4] = LM[0];
	LM[5] = LM[3];
	LM[6] = LM[2];
	LM[7] = LM[1];
	
	//input
	for (int i = 0; i < 4; i++)
	{
		billin >> CF[i];
	}
	
	//fill array of contained points with impossible value
	for (int i = 0; i < 8; i++)
	{
		containedPoints[i] = 1001;
	}
	
	//close input
	billin.close();
	
	//find all points contained in the rectangle
	for (int i = 0; i < 4; i++)
	{
		if (CF[3] >= LM[i*2+1] and LM[i*2+1] >= CF[1] and CF[2] >= LM[i*2] and LM[i*2] >= CF[0])
		{
			containedPoints[i*2] = LM[i*2];
			containedPoints[i*2+1] = LM[i*2+1];
		}
	}
	
	//check if there are no points of lawnmower billboard are contained by the cow feed billboard
	bool noPoints = false;
	for (int i = 0; i < 8; i++)
	{
		if (containedPoints[i] != 1001)
		{
			noPoints = false;
			break;
		}
		else
		{
			noPoints = true;
		}
	}
	
	//check if all points of lawnmower billboard are contained by the cow feed billboard
	bool allPoints = false;
	for (int i = 0; i < 8; i++)
	{
		if (containedPoints[i] != 1001)
		{
			allPoints = false;
			break;
		}
		else
		{
			allPoints = true;
		}
	}
	
	//check if one points of lawnmower billboard is contained by the cow feed billboard
	bool onePoint = false;
	int counter;
	for (int i = 0; i < 8; i++)
	{
		if (containedPoints[i] == 1001)
		{
			counter++;
		}
	}
	
	
	//check for 0 or 1 points
	if (onePoint or noPoints)
	{
		//calculate area of lawnmower billboard
		area = abs((LM[3]-LM[1])*(LM[2]-LM[0]));
	}
	//check for all points
	else if (allPoints)
	{
		//set area to 0
		area = 0;
	}
	//2 points contained
	else
	{
		//declare variables
		int point1[2], point2[2];
		bool nextPoint = false;
		
		//finds the two points and puts them into lists
		for (int i = 0; i < 4; i++)
		{
			if (containedPoints[i*2] != 1001)
			{
				if (nextPoint)
				{
					point2[0] = containedPoints[i];
					point2[1] = containedPoints[i+1];
				}
				else
				{
					point1[0] = containedPoints[i];
					point1[1] = containedPoints[i+1];
					nextPoint = true;
				}
			}
		}
		
		//change coordinates for when x is the same
		if (point1[0] == point2[0])
		{
			if (CF[2] >= point1[0])
			{
				point1[0] = CF[0];
				point2[0] = CF[0];
			}
			else
			{
				point1[0] = CF[2];
				point2[0] = CF[2];
			}
			LM[0] = point1[0];
			LM[4] = point1[0];
		}
		
		//change coordinates for when y is the same
		if (point1[1] == point2[1])
		{
			if (CF[3] <= point1[1])
			{
				point1[1] = CF[3];
				point2[1] = CF[3];
			}
			else
			{
				point1[1] = CF[1];
				point2[1] = CF[1];
			}
			LM[3] = point1[1];
			LM[7] = point1[1];
		}
		
		//calculate area using the new points
		area = abs((LM[3]-LM[1])*(LM[2]-LM[0]));
		
	}
	
	//output
	ofstream billout;
	billout.open("billboard.out");
	billout << area << endl;
	billout.close();
	
	//exit program
	return 0;
}
