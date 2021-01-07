/*
 ID: 
 PROG: palsquare
 LANG: C++
 */
//NAME          :   
//GROUP         :   Krypton
//LAST MODIFIED :   24 December 2017
//PROBLEM ID    :   USACO Palindromic Squares
//DESCRIPTION   :   Finds all base B numbers 1-300 base 10 that are palindromes.
//SOURCES/HELP  :   
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
using namespace std;

//user defined function to convert base 10 numbers to any base 2-36
string baseConverter(int num10, int base)
{
    //declare and initialize variables
    int digit, powerNum = 0;
    string numB = "";
        //constant list has all digits for bases 2-36
    const string BASE_DIGITS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int maxPower = 1;
    
    //loop to determine the first power greater than the base 10 number
    for (; maxPower <= num10; powerNum++)
    {
        maxPower = pow(base, powerNum);
    }
    
    //subtracts 1 from the exponent value of the first power greater than the base 10 number
    powerNum--;
    
    //loops while the exponent value is greater than 0
    while (powerNum > 0)
    {
        //decrements the power and exponent value
        maxPower /= base;
        powerNum--;
    
        //determines the highest integer multiple of the current highest power
        digit = floor(num10/maxPower);
        
        //subtracts the amount being added to the final number
        num10 -= maxPower*digit;
        
        //adds the digit to the number using the conversion list
        numB += BASE_DIGITS[digit];
        
    }
	//returns the converted number
    return numB;
}

//main function
int main()
{
	//declare variables
	const int INTS_RANGE = 300;
	int base, ints[INTS_RANGE], intSquared[INTS_RANGE], squareLength;
	string convertedInts[INTS_RANGE], convertedIntSquared[INTS_RANGE], tempString;
	bool isPal;
	
	//initializes lists with integers and their squares 1-300
	for (int i = 0; i < INTS_RANGE; i++)
	{
		ints[i] = i+1;
		intSquared[i] = (i+1)*(i+1);
	}
	
	//open input file
	ifstream palsquarein;
	palsquarein.open("palsquare.in");
	
	//read in the base
	palsquarein >> base;
	
	//close input file
	palsquarein.close();
	
	//converts all of the numbers to the desired base
	for (int i = 0; i < INTS_RANGE; i++)
	{
		convertedInts[i] = baseConverter(ints[i], base);
		convertedIntSquared[i] = baseConverter(intSquared[i], base);
	}
	
	//opens output file
	ofstream palsquareout;
	palsquareout.open("palsquare.out");
	
	//check for palindromes
	for (int i = 0; i < INTS_RANGE; i++)
	{
		//assumes square is not a palindrome
		isPal = false;
		
		//find length of converted square
		squareLength = convertedIntSquared[i].length();
		
		//temporary variable for converted number
		tempString = convertedIntSquared[i];
		
		//runs for the floor of length divided by 2 to check both ends at the same time
		for (int j = 0; j < floor(squareLength/2); j++)
		{
			//checks if the numbers opposite of each other in the number are equal
			if (tempString[j] == tempString[squareLength-j-1])
			{
				//says that it is a palindrome
				isPal = true;
			}
			else
			{
				//say that it is not a palindrome
				isPal = false;
				
				//exits loop
				break;
			}
		}
		
		//checks if the number is a palindrome or its length is one
		if (isPal or squareLength == 1)
		{
			//outputs the integer and its square in base B
			palsquareout << convertedInts[i] << " " << convertedIntSquared[i] << endl;
		}
	}
	//close output
	palsquareout.close();
	
	//exit program
	return 0;
}