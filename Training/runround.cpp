/*
 ID: 
 PROG: runround
 LANG: C++14
*/ 
//NAME          :   
//GROUP         :   APCS
//LAST MODIFIED :   4 October 2018
//PROBLEM ID    :   USACO Runaround Numbers
//DESCRIPTION   :   Given a number find the next number that is a runaround number.
//SOURCES/HELP  :   
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <bitset>
#include <sstream>
using namespace std;

//declare function
bool checkRunRound(string);

//main function
int main() 
{
  //declare variables
  unsigned long int start, currentNum;
  string num;

  //open files
  ifstream fin ("runround.in");
  ofstream fout ("runround.out");

  //input
  fin >> start;
  currentNum = start+1;

  //declare string stream
  stringstream ss;

  //loop until a runaround number is found
  while (true)
  {
    //convert an integer into a string
    ss << currentNum;
    num = ss.str();
    ss.str("");

    //move to next number
    currentNum++;

    //exit loop if number is a runaround number
    if (checkRunRound(num))
    {
      break;
    }
  }

  //output
  fout << num << endl;

  //exit program
  return 0;
}

//check if a number is a runaround number
bool checkRunRound(string check)
{
  //declare variables
  const int MAX_LEN = 9;
  int length = check.length(), index = 0;
  bitset <MAX_LEN> isRunRound;

  //check for duplicate digits or for zero and return false if either are present
  for (int i = 0; i < length; i++)
  {
    for (int j = i+1; j < length; j++)
    {
      if (check[i] == check[j] or check[j] == '0')
      {
        return false;
      }
    }
  }

  //check if a number is runaround by doing the cycle
  for (int i = 0; i < length; i++)
  {
    //find where the current digit goes to
    index = (check[index]-48+index)%length;

    //check if the digit has already been visited
    if (isRunRound[index] == 1)
    {
      return false;
    }

    //say that this digit has been visited
    isRunRound[index] = 1;
  }

  //number is runaround otherwise
  return true;
}