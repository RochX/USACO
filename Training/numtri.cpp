/*
 ID: 
 PROG: numtri
 LANG: C++
 */
//NAME          :   
//GROUP         :   Binary
//LAST MODIFIED :   14 March 2018
//PROBLEM ID    :   USACO Number Triangles
//DESCRIPTION   :   Given a triangle of number of R rows, find the largest sum by traversing the triangle from the top to the bottom.
//SOURCES/HELP  :   
#include <iostream>
#include <fstream>
using namespace std;
//returns the larger of two numbers
int max(int x, int y)
{
  if (x > y)
  {
    return x;
  }
  else
  {
    return y;
  }
}
//main function
int main() 
{
  //declare variable
  int numRows;
  
  //input row number
  ifstream fin ("numtri.in");
  fin >> numRows;
  
  //input triangle
  int triangle[numRows][numRows];
  for (int row = 0; row < numRows; ++row)
  {
    for (int col = 0; col < row+1; ++col)
    {
      fin >> triangle[row][col];
    }
  }
  //close input file
  fin.close();
  
  //find the best path by working from the bottom up
  for (int row = numRows-2; row >= 0; --row)
  {
    for (int col = 0; col < row+1; ++col)
    {
      //adds the largest number a number can progress to
      triangle[row][col] += max(triangle[row+1][col], triangle[row+1][col+1]);
    }
  }
  //output
  ofstream fout ("numtri.out");
  fout << triangle[0][0] << endl;
  fout.close();
  
  //exit program
  return 0;
}