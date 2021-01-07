/*
 ID: 
 PROG: combo
 LANG: C++
 */
//NAME          :   
//GROUP         :   Krypton
//LAST MODIFIED :   31 December 2017
//PROBLEM ID    :   USACO Combination Lock
//DESCRIPTION   :   Finds which combinations will break a lock with 2 combos and a small tolerance for error
//SOURCES/HELP  :   
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	//declare variables
	const int NUM_COMBOS = 2, NUM_DIALS = 3, TOLERANCE = 2, COMBO_DISPLACEMENT = 1000, MAX_COMBOS = 500; 
	int numDigits = 5, dialRange, possibleCombos = 0;
		//3d array key: x-axis: lock (master and John), y-axis: dial, z-axis: possible digits for the dial
	int possibleDigits[NUM_COMBOS][NUM_DIALS][numDigits];
		//2d array key: x-axis: numbers for combo, y-axis: dial
	int combos[MAX_COMBOS][NUM_DIALS], lock[NUM_COMBOS][NUM_DIALS];
	
	//open input file
	ifstream comboIn;
	comboIn.open("combo.in");
	
	//input range of dials
	comboIn >> dialRange;
	
	//input the locks
	for (int i = 0; i < NUM_COMBOS; i++)
	{
		for (int j = 0; j < NUM_DIALS; j++)
		{
			comboIn >> lock[i][j];
		}
	}
	
	//generate all the possible digits for both combos
	for (int combo = 0; combo < NUM_COMBOS; combo++)
	{
		for (int dial = 0; dial < NUM_DIALS; dial++)
		{
			for (int digits = 0; digits < numDigits; digits++)
			{
				//generate digit based on the tolerance for the lock
				possibleDigits[combo][dial][digits] = TOLERANCE - digits + lock[combo][dial];
				
				//creates digits for wrap around case
				if (possibleDigits[combo][dial][digits] == 0)
				{
					possibleDigits[combo][dial][digits] = dialRange;
				}
				if (possibleDigits[combo][dial][digits] == -1)
				{
					possibleDigits[combo][dial][digits] = dialRange-1;
				}
				if (possibleDigits[combo][dial][digits] == dialRange+1)
				{
					possibleDigits[combo][dial][digits] = 1;
				}
				if (possibleDigits[combo][dial][digits] == dialRange+2)
				{
					possibleDigits[combo][dial][digits] = 2;
				}
			}
		}
	}
	
	//create all possible combinations
	int counter = 0;
	for (int combo = 0; combo < NUM_COMBOS; combo++)
	{
		for (int digitsOne = 0; digitsOne < numDigits; digitsOne++)
		{
			for (int digitsTwo = 0; digitsTwo < numDigits; digitsTwo++)
			{
				for (int digitsThree = 0; digitsThree < numDigits; digitsThree++)
				{
					//create a combination
					combos[counter][0] = possibleDigits[combo][0][digitsOne];
					combos[counter][1] = possibleDigits[combo][1][digitsTwo];
					combos[counter][2] = possibleDigits[combo][2][digitsThree];
					
					//increment counter
					counter++;
				}
			}
		}
	}
	
	//check for duplicates
	int duplicates = 0;
	bool checkDuplicate;
	for (int i = 0; i < counter; i++)
	{
		for (int j = i+1; j < counter; j++)
		{
			checkDuplicate = false;
			
			//loop for all dials
			for (int k = 0; k < NUM_DIALS; k++)
			{
				//check if the dials are the same
				if (combos[i][k] == combos[j][k])
				{
					checkDuplicate = true;
				}
				else
				{
					//break out of the loop
					checkDuplicate = false;
					k += NUM_DIALS;
				}
			}
			if (checkDuplicate)
			{
				duplicates++;
			}
		}
	}
	
	//find the number of possible combos
	possibleCombos = counter - duplicates;
	
	//case for when the dial range is 5 or less
	if (dialRange <= numDigits)
	{
		possibleCombos = dialRange*dialRange*dialRange;
	}
	
	//close input file
	comboIn.close();
	
	//open input file
	ofstream comboOut;
	comboOut.open("combo.out");
	
	//output
	comboOut << possibleCombos << endl;
	
	//close input
	comboOut.close();
	
	//exit program
	return 0;
}
