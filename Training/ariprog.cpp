/*
 ID: 
 PROG: ariprog
 LANG: C++
*/
//NAME          :   
//GROUP         :   Binary
//LAST MODIFIED :   6 March 2018
//PROBLEM ID    :   USACO Arithmetic Progressions
//DESCRIPTION   :   Given a length N and a range M, find all of the sequences of length N in the set of bisquares within range M with a common difference.
//SOURCES/HELP  :   https://en.wikipedia.org/wiki/Binary_search_algorithm
#include <algorithm>
#include <fstream>
#include <iostream>
#include <math.h>
using namespace std;

//main function
int main() 
{
	//declare variables
	const int MAX_SEQUENCES = 10000;
	int tempNumPermutations = 40000;
	int finalNumPermutations;
	int tempBiSquare[tempNumPermutations];
	int range, progLength, counter = 0, duplicates = 0;
	
	//input
	ifstream fin;
	fin.open("ariprog.in");
	fin >> progLength >> range;
	fin.close();
	
	//loop to generate all bisquares (i^2+j^2)
	for (int i = 0; i <= range; ++i) 
	{
		int iTimesI = i * i;
		for (int j = i; j <= range; ++j) 
		{
			//generate bisquare
			tempBiSquare[counter] = iTimesI + j * j;

			//increment counter
			counter++;
		}
	}

	//find number of bisquares including duplicates
	tempNumPermutations = counter;

	//sort into ascending order
	sort(tempBiSquare, tempBiSquare + counter);

	//check for duplicates
	for (int i = 0; i < tempNumPermutations; i++) 
	{
		//checks if the current bisquare has already been made a duplicate
		if (tempBiSquare[i] >= 0) 
		{
			for (int j = i + 1; j < tempNumPermutations; j++) 
			{
				//makes numbers negative that are duplicates and increments number of duplicates
				if (tempBiSquare[i] == tempBiSquare[j]) 
				{
					tempBiSquare[j] *= -1;
					duplicates++;
				}
			}
		}
	}

	//final number of bisquares
	finalNumPermutations = counter - duplicates;
	
	//declare variable
	int finalBiSquare[finalNumPermutations];

	//subtract duplicates
	counter = 0;
	for (int i = 0; i < tempNumPermutations; i++) 
	{
		if (tempBiSquare[i] >= 0) 
		{
			finalBiSquare[counter] = tempBiSquare[i];
			counter++;
		}
	}

	//reset variable
	counter = 0;

	//declare variables
	bool isBiSquare, sequenceGood;
	int difference, tempSequence[progLength], firstElements[MAX_SEQUENCES];
	int differences[MAX_SEQUENCES], indices[finalNumPermutations];
		//max comparisons needed for binary search
	int maxComparisions = ceil(log2(finalNumPermutations));
	
	//find sequences
	for (int i = 0; i < finalNumPermutations; ++i) 
	{
		indices[i] = i;
		//set start point
		tempSequence[0] = finalBiSquare[i];
		for (int j = i + 1; j < finalNumPermutations; ++j) 
		{
			//set second term
			tempSequence[1] = finalBiSquare[j];

			//find difference between first and second term
			difference = tempSequence[1] - tempSequence[0];
			
			//break early if last term is greater than the last bisquare
			if (tempSequence[0]+difference*(progLength-1) > finalBiSquare[finalNumPermutations - 1])
			{
				break;
			}
      
			//find the supposed next N-2 terms
			for (int k = 2; k < progLength; ++k) 
			{
				tempSequence[k] = tempSequence[k - 1] + difference;
			}

			//do not check if the last term is greater than the largest bisquare
			if (!(tempSequence[progLength - 1] > finalBiSquare[finalNumPermutations - 1]))
			{
				//check if the other terms are bisquares
				sequenceGood = true;
				for (int h = 2; h < progLength; ++h) 
				{
					//declare variables
					int low = 0, high = finalNumPermutations - 1, mid;
					
					//checks if the hth term is a bisquare through a binary search
					for (int i = 0; i < maxComparisions; ++i) 
					{
						//find the average of low and high
						mid = (low + high) >> 1;
						
						//checks if the number is the number that is being searched for
						if (finalBiSquare[mid] == tempSequence[h]) 
						{
							isBiSquare = true;
							break;
						} 
						//case when the number is bigger than the middle number
						else if (tempSequence[h] > finalBiSquare[mid]) 
						{
							low = mid + 1;
						} 
						//case when the number is smaller than the middle number
						else 
						{
							high = mid - 1;
						}
						
						//check if the number is not the middle number
						if (finalBiSquare[mid] != tempSequence[h])
						{
						  isBiSquare = false;
						}
					}

					//exits checking if hth term is not a bisquare
					if (!isBiSquare) 
					{
						sequenceGood = false;
						break;
					}
				}
			} 
			else 
			{
				//break when last term is greater than the largest bisquare
				break;
			}
			
			//add first element and the difference into lists if sequence contains all bisquares
			if (sequenceGood) 
			{
				firstElements[counter] = tempSequence[0];
				differences[counter] = difference;
				counter++;
			}
		}
	}

	//sort lists through a bubble sort
	int tempInt;
	bool notSorted = true;
	//sort if the list is not sorted and the list size is greater than 1
	while (notSorted and counter > 1) 
	{
		//assume the list is sorted
		notSorted = false;
		
		//loop through the list
		for (int i = 0; i < counter - 1; ++i) 
		{
			//swap if the current term is greater than the next term
			if (differences[i] > differences[i + 1]) 
			{
				//the list is not sorted
				notSorted = true;
				
				//swap
				tempInt = differences[i + 1];
				differences[i + 1] = differences[i];
				differences[i] = tempInt;
				
				//swap (used to keep corresponding values together)
				tempInt = indices[i + 1];
				indices[i + 1] = indices[i];
				indices[i] = tempInt;
			}
		}
	}
	
	//output
	ofstream fout;
	fout.open("ariprog.out");
	//condition to check if there is any sequences at all
	if (differences[0] >= 1) 
	{
		for (int i = 0; i < counter; ++i) 
		{
			fout << firstElements[indices[i]] << " " << differences[i] << endl;
		}
	} 
	else 
	{
		fout << "NONE" << endl;
	}
	fout.close();
	
	//exit program
	return 0;
}