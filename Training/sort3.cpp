/*
 ID: 
 PROG: sort3
 LANG: C++14
*/ 
//NAME          :   
//GROUP         :   Binary
//LAST MODIFIED :   24 April 2018
//PROBLEM ID    :   USACO Sort3
//DESCRIPTION   :   Given a list of size N with 3 different values, find how many swaps are needed to sort it into ascending order
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
  //open files
  ifstream fin ("sort3.in");
  ofstream fout ("sort3.out");
  
  //declare and input variables
  int sortSize, numDigits[3] = {0,0,0}, numSwaps = 0;
  fin >> sortSize;
  int sortList[sortSize], correctList[sortSize];
  
  //input list and find how many of each number there are
  for (int i = 0; i < sortSize; ++i)
  {
    fin >> sortList[i];
    switch(sortList[i])
    {
      case 1: numDigits[0]++;
        break;
      case 2: numDigits[1]++;
        break;
      case 3: numDigits[2]++;
        break;
    }
  }
  
  //swap 1s
  for (int i = 0; i < numDigits[0]; i++)
  {
    //swap starting from the front if its 2
    if (sortList[i] == 2)
    {
      for (int j = numDigits[0]; j < sortSize; j++)
      {
        if (sortList[j] == 1)
        {
          //swap
          int temp = sortList[j];
          sortList[j] = sortList[i];
          sortList[i] = temp;
          numSwaps++;
          break;
        }
      }
    }
    //swap starting from the back if its 3
    if (sortList[i] == 3)
    {
      for (int j = sortSize-1; j >= numDigits[0]; j--)
      {
        if (sortList[j] == 1)
        {
          //swap
          int temp = sortList[j];
          sortList[j] = sortList[i];
          sortList[i] = temp;
          numSwaps++;
          break;
        }
      }
    }
  }
  
  //swap 2s
  for (int i = numDigits[0]; i < numDigits[0]+numDigits[1]; i++)
  {
    //swap starting from the back if its 3
    if (sortList[i] == 3)
    {
      for (int j = sortSize-1; j >= numDigits[1]; j--)
      {
        if (sortList[j] == 2)
        {
          //swap
          int temp = sortList[j];
          sortList[j] = sortList[i];
          sortList[i] = temp;
          numSwaps++;
          break;
        }
      }
    }
  }
  
  //output
  fout << numSwaps << endl;
  
  //exit program
  return 0;
}