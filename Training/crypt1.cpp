/*
 ID: 
 PROG: crypt1
 LANG: C++
 */
//NAME          :   
//GROUP         :   Krypton
//LAST MODIFIED :   28 December 2017
//PROBLEM ID    :   USACO Prime Cryptarithm
//DESCRIPTION   :   Finds the number of possible solution to a cryptarithm given a certain set of digits
//SOURCES/HELP  :   
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

//user defined function to find the length of an int
int intLength(int number)
{
	int len = 0;
	while (number > 0)
	{
		number /= 10;
		len++;
	}
	return len;
}

//main program
int main()
{
	//declare variables
	const int PARTIAL_LENGTH = 3, PRODUCT_LENGTH = 4, TOTAL_LENGTH = 2*PARTIAL_LENGTH+PRODUCT_LENGTH;
	int numDigits, solutions = 0, partialOne = 0, partialTwo = 0, product = 0, digitsToCheck[TOTAL_LENGTH];
	long int tempInt;
	bool validDigits;
	
	//open input file
	ifstream cryptin;
	cryptin.open("crypt1.in");
	
	//read in how many digits
	cryptin >> numDigits;
	
	//read in digits to a list
	int digits[numDigits];
	for (int i = 0; i < numDigits; i++)
	{
		cryptin >> digits[i];
	}
	
	//close input file
	cryptin.close();
	
	//loops for every possible number combination
	for (int f = 0; f < numDigits; f++)
	{
		for (int s = 0; s < numDigits; s++)
		{
			for (int t = 0; t < numDigits; t++)
			{
				for (int fo = 0; fo < numDigits; fo++)
				{
					for (int fi = 0; fi < numDigits; fi++)
					{
						//reset variable
						validDigits = true;
						
						//finds the partials and the product
						partialOne = (100*digits[f]+10*digits[s]+1*digits[t])*digits[fo];
						partialTwo = (100*digits[f]+10*digits[s]+1*digits[t])*digits[fi];
						product = partialOne+partialTwo*10;
						
						//checks if the lengths are correct 
						if (intLength(partialOne) == PARTIAL_LENGTH and intLength(partialTwo) == PARTIAL_LENGTH and intLength(product) == PRODUCT_LENGTH)
						{
							//puts the partials into one number where the digits remain the same
							tempInt = partialTwo*pow(10, PARTIAL_LENGTH)+partialOne;
							
							//puts number into array
							for (int i = 0; i < TOTAL_LENGTH; i++)
							{
								if (i == PARTIAL_LENGTH*2)
								{
									tempInt = product;
								}
								digitsToCheck[i] = tempInt % 10;
								tempInt /= 10;
								
							}
							
							//sets all correct digits to -1
							for (int i = 0; i < TOTAL_LENGTH; i++)
							{
								for (int j = 0; j < numDigits; j++)
								{
									if (digitsToCheck[i] == digits[j])
									{
										digitsToCheck[i] = -1;
									}
								}
							}
							
							//checks if any digit is not -1
							for (int i = 0; i < TOTAL_LENGTH; i++)
							{
								if (digitsToCheck[i] != -1)
								{
									validDigits = false;
								}
							}
							
							if (validDigits)
							{
								solutions++;
							}
						}
					}
				}
			}
		}
	}
	
	//open output file
	ofstream cryptout;
	cryptout.open("crypt1.out");
	
	//send output
	cryptout << solutions << endl;
	
	//close output file
	cryptout.close();
	
	//exit program
	return 0;
}