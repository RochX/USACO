/*
 ID: 
 PROG: dualpal
 LANG: C++
 */
//NAME          :   
//GROUP         :   Krypton
//LAST MODIFIED :   24 December 2017
//PROBLEM ID    :   USACO Dual Palindromes
//DESCRIPTION   :   Finds all numbers greater than a certain number S that are palindromes in 2 or more in the number bases 2-10
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

//function to check if a string is a palindrome
bool checkPal(string number)
{
	//declare and initialize variables
		//find length of number
	int squareLength = number.length();
		//assumes number is not a palindrome
	bool isPal = false;
		//temporary variable for converted number
	string tempString = number;
		
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
	
	//checks if the number's length is one
	if (squareLength == 1)
	{
		isPal = true;
	}
	return isPal;
}

//main function
int main() 
{
	//declare variables
	int startNumber, amountOfNumbers, numBases, currentNum;
	bool isPal;
	
	//open input file
	ifstream dualpalin;
	dualpalin.open("dualpal.in");
	
	//read in amount of numbers needed and the starting number
	dualpalin >> amountOfNumbers >> startNumber;
	
	//close input file
	dualpalin.close();
	
	//open output file
	ofstream dualpalout;
	dualpalout.open("dualpal.out");
	
	//initializes the first number to check
	currentNum = startNumber + 1;
	
	//initialize counter variable for loop
	int counter = 0;
	
	//loops to get the correct amount of numbers
	while (counter < amountOfNumbers)
	{
		//initialize how many bases each number is a palindrome in
		numBases = 0;
		
		//loops for bases 2-10
		for (int j = 2; j <= 10; j++)
		{
			//exits loops if the number is palindromic in 2 or more bases
			if (numBases >= 2)
			{
				break;
			}
			
			//calls functions and increments the palindromic base counter if the converted number is a palindrome
			isPal = checkPal(baseConverter(currentNum, j));
			if (isPal)
			{
				numBases++;
			}
		}
		
		//checks if the number is a dual palindrome
		if (numBases >= 2)
		{
			//outputs number
			dualpalout << currentNum << endl;
			
			//increments the counter for the amount of numbers
			counter++;
		}
		
		//advances to next number
		currentNum++;
	}
	
	//close output file
	dualpalout.close();
	
	//exit program
	return 0;
}