/*
 ID: 
 PROG: frac1
 LANG: C++
*/ 
//NAME          :   
//GROUP         :   Binary
//LAST MODIFIED :   20 April 2018
//PROBLEM ID    :   USACO Ordered Fractions
//DESCRIPTION   :   Given a number N, find all of the simplified fractions with numerators 0-N and denominators 1-N sorted in ascending order.
//SOURCES/HELP  :   
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int main() 
{
  //open input and output files
  ifstream fin ("frac1.in");
  ofstream fout ("frac1.out");
  
  //input the range
  int range;
  fin >> range;
  
  //declare variables
  vector <float> numerator;
  vector <float> denominator;
  vector <float> decimal;
  int counter = 0;
  
  //generate all possible fractions within the range and calculate their decimal values
  for (int i = 0; i <= range; ++i)
  {
    for (int j = 1; j <= range; ++j)
    {
      if (i <= j)
      {
        numerator.push_back(i);
        denominator.push_back(j);
        decimal.push_back(numerator[counter]/denominator[counter]);
        ++counter;
      }
      
    }
  }
  
  //set the decimals of the fractions that are not simplified to be less than 0
  for (int i = 0; i < numerator.size(); ++i)
  {
    if (decimal[i] >= 0)
    {
      for (int j = i+1; j < numerator.size(); ++j)
      {
        if (decimal[j] == decimal[i])
        {
          decimal[j] *= -1;
          decimal[j]--;
        }
      }
    }
  }
  
  //declare variables
  vector <float> finalNumerator;
  vector <float> finalDenominator;
  vector <float> finalDecimal;
  
  //put all of the simplified fractions into vectors
  for (int i = 0; i < numerator.size(); ++i)
  {
    if (decimal[i] >= 0)
    {
      finalNumerator.push_back(numerator[i]);
      finalDenominator.push_back(denominator[i]);
      finalDecimal.push_back(decimal[i]);
    }
  }
  
  //make a copy of the decimal list and sort one of them
  vector <float> originalDecimal;
  for (int i = 0; i < finalDecimal.size(); ++i)
  {
    originalDecimal.push_back(finalDecimal[i]);
  }
  sort(finalDecimal.begin(), finalDecimal.end());
  
  //loop through the sorted list
  for (int i = 0; i < finalDecimal.size(); ++i)
  {
    //loop through the nonsorted list
    for (int j = 0; j < finalDecimal.size(); ++j)
    {
      //find the position of the nonsorted decimal in the sorted list
      if (finalDecimal[i] == originalDecimal[j])
      {
        //output the fraction that goes with the decimal
        fout << finalNumerator[j] << "/" << finalDenominator[j] << endl;
        break;
      }
    }
  }
  
  //exit program
  return 0;
}