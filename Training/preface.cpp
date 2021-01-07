/*
 ID: 
 PROG: preface
 LANG: C++14
*/ 
//NAME          :   
//GROUP         :   APCS
//LAST MODIFIED :   8 October 2018
//PROBLEM ID    :   USACO Preface Numbering
//DESCRIPTION   :   Given a number N find how many times each of the roman numeral digits appear in the numbers 1-N.
//SOURCES/HELP  :   
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

//declare function
string numToRoman(int);

int main() 
{
  //open files
  ifstream fin ("preface.in");
  ofstream fout ("preface.out");

  //declare variables
    //I, V, X, L, C, D, M
  int romanNumerals[7] = {};
  int numPages, index;
  string romanNum;
  const string COMPARE = "IVXLCDM";

  //input
  fin >> numPages;

  //loop through all numbers 1-N
  for (int i = 1; i <= numPages; i++)
  {
    //convert the number into roman numeral form
    romanNum = numToRoman(i);

    //loop to add number of times each digit occurs
    for (int j = 0; j < romanNum.length(); j++)
    {
      for (index = 0; index < COMPARE.length(); index++)
      {
        if (romanNum[j] == COMPARE[index])
        {
          break;
        }
      }
      romanNumerals[index]++;
    }
  }

  //print out all letters that occur at least once
  for (int i = 0; i < COMPARE.length(); i++)
  {
    if (romanNumerals[i] != 0)
    {
      fout << COMPARE[i] << " " << romanNumerals[i] << endl;
    }
  }

  //exit program
  return 0;
}

//convert an int into its roman numeral equivalent
string numToRoman(int num)
{
  //declare variables
  string result = "";
  const int INDEX_1000S = 0, INDEX_100S = 1, INDEX_10S = 2, INDEX_1S = 3;
  int numValues[4] = {};

  //find how many of each digit there are
  numValues[INDEX_1000S] = num / 1000;
  num -= numValues[INDEX_1000S]*1000;
  numValues[INDEX_100S] = num / 100;
  num -= numValues[INDEX_100S]*100;
  numValues[INDEX_10S] = num / 10;
  num -= numValues[INDEX_10S]*10;
  numValues[INDEX_1S] = num;  
  
  //add thousands to the result
  for (int i = 0; i < numValues[INDEX_1000S]; i++)
  {
    result += 'M';
  }

  //add hundreds to the result based on how many there are
  if (numValues[INDEX_100S] == 9)
  {
    result += "CM";
  }
  else if (numValues[INDEX_100S] >= 5)
  {
    result += 'D';
    numValues[INDEX_100S] -= 5;
  }
  if (numValues[INDEX_100S] == 4)
  {
    result += "CD";
  }
  else if (numValues[INDEX_100S] <= 3)
  {
    for (int i = 0; i < numValues[INDEX_100S]; i++)
    {
      result += 'C';
    }
  }

  //add tens to the result based on how many there are
  if (numValues[INDEX_10S] == 9)
  {
    result += "XC";
  }
  else if (numValues[INDEX_10S] >= 5)
  {
    result += 'L';
    numValues[INDEX_10S] -= 5;
  }
  if (numValues[INDEX_10S]  == 4)
  {
    result += "XL";
  }
  else if (numValues[INDEX_10S] <= 3)
  {
    for (int i = 0; i < numValues[INDEX_10S]; i++)
    {
      result += 'X';
    }
  }

  //add ones to the result based on how many there are
  if (numValues[INDEX_1S] == 9)
  {
    result += "IX";
  }
  else if (numValues[INDEX_1S] >= 5)
  {
    result += 'V';
    numValues[INDEX_1S] -= 5;
  }
  if (numValues[INDEX_1S] == 4)
  {
    result += "IV";
  }
  else if (numValues[INDEX_1S] <= 3)
  {
    for (int i = 0; i < numValues[INDEX_1S]; i++)
    {
      result += 'I';
    }
  }

  //return the roman numeral number
  return result;
}