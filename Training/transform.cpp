/*
 ID: 
 PROG: transform
 LANG: C++
 */
//NAME          :    
//GROUP         :   Krypton
//LAST MODIFIED :   24 December 2017
//PROBLEM ID    :   USACO Transformations
//DESCRIPTION   :   Figures out which transformation an N x N tile arrangement has gone through.
//SOURCES/HELP  :   
#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
using namespace std;

//declare global variables
int squareSize;

//user defined function to rotate any square
string transform90(string square)
{
	//declare and initialize variables
    string rotated = "", tempPart = "", tempSquare = square;
	
	//loop for each column 
    for (int i = 0; i < squareSize; i++)
    {
		//loop for each row
        for (int j = 0; j < squareSize; j++)
		{
			//adds tile of current current column and row to temporary variable
			tempPart += tempSquare[j*squareSize+i];
		}
		//reverses the tiles of the column
		reverse(tempPart.begin(), tempPart.end());
		
		//adds the rotated column to the transformed square
		rotated += tempPart;
		
		//reset temporary variable
		tempPart = "";
    }
	
	//return transformed square
	return rotated;
}

//user defined function to reflect any square
string transformHorizontal(string square)
{
	//declare and initialize variables
	string reflected = "", tempPart = "";
	
	//loop for each row
    for (int i = 0; i < squareSize; i++)
    {
		//loop for each column
        for (int j = 0; j < squareSize; j++)
		{
			//adds tile of current current column and row to temporary variable
			tempPart += square[j+i*squareSize];
		}
		
		//reverses the tiles of the column
		reverse(tempPart.begin(), tempPart.end());
		
		//adds the reflected row to the transformed square
		reflected += tempPart;
		
		//reset temporary variable
		tempPart = "";
    }
	
	//return transformed square
	return reflected;
}

//main function
int main()
{
	//declare variables
	const int NUM_POSSIBLITIES = 11;
	int transformationValue;
    string squarePre, squarePost, tempString;
	
	//open input file
	ifstream transformin;
	transformin.open("transform.in");
	
	//read in the size
	transformin >> squareSize;
	
	//create list to store all transformations possible
		/*list of transformations in the array
			0 = 90 Rotation (1)
			1 = 180 Rotation (2)
			2 = 270 Rotation (3)
			3 = Horizontal (4)
			4 = Horizontal + 90 Rotation (5)
			5 = Horizontal + 180 Rotation (5)
			6 = Horizontal + 270 Rotation (5)
			7 = 90 Rotation + Horizontal (5)
			8 = 180 Rotation + Horizontal (5)
			9 = 270 Rotation + Horizontal (5)
			10 = No transformation (6)
		*/
	string squareTransformed[NUM_POSSIBLITIES];
	
	//read in pre transform square
	for (int i = 0; i < squareSize; i++)
	{
        transformin >> tempString;
        squarePre += tempString;
        tempString = "";
	}
	
	//read in post transform square
    for (int i = 0; i < squareSize; i++)
    {
        transformin >> tempString;
        squarePost += tempString;
		tempString = "";
    }
	
	//close input file
	transformin.close();
	
	//finds all rotation only possibilities
	for (int i = 0; i < 3; i++)
	{
		//set temporary variable to the pre transform square
		tempString = squarePre;
		
		//rotate the square for multiple of 90
		for (int j = 0; j < i+1; j++)
		{
			//call function to rotate itself
			tempString = transform90(tempString);
		}
		
		//put transformation into list
		squareTransformed[i] = tempString;
	}
	
	//finds horizontal reflection possibility
		//set temporary variable to the pre transform square
		tempString = squarePre;
	
		//call function to reflect itself
		tempString = transformHorizontal(tempString);
		
		//put transformation into list
		squareTransformed[3] = tempString;
	
	//finds horizontal then rotation possibilities
	for (int i = 0; i < 3; i++)
	{
		//set temporary variable to the pre transform square
		tempString = squarePre;
		
		//call function to reflect itself
		tempString = transformHorizontal(tempString);
		
		//rotate the square for multiple of 90
		for (int j = 0; j < i+1; j++)
		{
			//call function to rotate itself
			tempString = transform90(tempString);
		}
		
		//put transformation into list
		squareTransformed[i+4] = tempString;
	}
	
	//finds rotation then horizontal possibilities
	for (int i = 0; i < 3; i++)
	{
		//set temporary variable to the pre transform square
		tempString = squarePre;
		
		//rotate the square for multiple of 90
		for (int j = 0; j < i+1; j++)
		{
			tempString = transform90(tempString);
		}
		
		//call function to reflect itself
		tempString = transformHorizontal(tempString);
		
		//put transformation into list
		squareTransformed[i+7] = tempString;
	}
	
	//finds no change possibility
	squareTransformed[10] = squarePre;
	
	//compares all possible transformations with the actual transformation
	for (int i = 0; i < NUM_POSSIBLITIES; i++)
	{
		//checks for equality
		if (squareTransformed[i] == squarePost)
		{
			switch (i)
			{
				//case for 90 degree rotation
				case 0: 
					transformationValue = 1;
					break;
					
				//case for 180 degree rotation
				case 1: 
					transformationValue = 2;
					break;
					
				//case for 270 degree rotation
				case 2: 
					transformationValue = 3;
					break;
					
				//case for horizontal reflection
				case 3: 
					transformationValue = 4;
					break;
				
				//cases for combination of reflection and rotation
				case 4: case 5: case 6: case 7: case 8: case 9:
					transformationValue = 5;
					break;
					
				//case for no transformation
				case 10:
					transformationValue = 6;
					break;
			}
			
			//end loop
			break;
		}
		else
		{
			//case if the transformation is invalid
			transformationValue = 7;
		}
	}
	
	//open output file
	ofstream transformout;
	transformout.open("transform.out");
	
	//send output
	transformout << transformationValue << endl;
	
	//close output file
	transformout.close();
	
	//exit program
	return 0;
}
