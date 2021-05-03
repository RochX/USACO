//NAME:		Xavier Silva
//Group:	Binary
//PROGRAM:	USACO Round 3 Teleportation
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;
//minimum function
int min(int x, int y)
{
  if (x < y)
  {
    return x;
  }
  else
  {
    return y;
  }
}

//main function
int main() {
	//input
	ifstream fin;
	fin.open("teleport.in");
	
	//declare variables
	int start, end, t1, t2, defaultDistance;
	
	//input
	fin >> start >> end >> t1 >> t2;
	//cout << start << " " << end << " " << t1 << " " << t2 << endl;
	
	//distance when teleporter isn't used
	defaultDistance = abs(start - end);
	//cout << defaultDistance << endl;
	
	//distance from start to both points of teleporter
	int startT1 = abs(start - t1);
	int startT2 = abs(start - t2);
	cout << startT1 << " " << startT2 << endl;
	
	//distance from end to both points of teleporter
	int endT1 = abs(end - t1);
	int endT2 = abs(end - t2);
	cout << endT1 << " " << endT2 << endl;
	
	//check if point 1 of the teleporter (T1) should be used
	bool useT1 = true;
	if (startT1 > startT2)
	{
		useT1 = false;
	}
	
	//declare variable
	int totalDistance = 0;
	
	//find total travel distance based on which point is being used
	if (useT1)
	{
		totalDistance += startT1 + endT2;
	}
	else
	{
		totalDistance += startT2 + endT1;
	}
	cout << totalDistance << endl;
	
	//find minimum distance
	int finalOut = min(totalDistance, defaultDistance);
	
	//output
	ofstream fout;
	fout.open("teleport.out");
	fout << finalOut << endl;
	fout.close();
	fin.close();
	return 0;
}