//NAME:		Xavier Silva
//Group:	Binary
//PROGRAM:	USACO Round 3 Taming The Herd
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

int main() 
{
  //declare variable
  bool consistent1 = true;
  
  //input
  ifstream fin;
  fin.open("taming.in");
  
  //read in input
  int numDays;
  fin >> numDays;
  cout << numDays << endl;
  
  //declare variables
  int breakLog[numDays];
    //0 = no, 1 = yes, 2 = uncertain
  int breakOccur[numDays];
  
  //input log
  for (int i = 0; i < numDays; i++)
  {
    fin >> breakLog[i];
    cout << breakLog[i] << " ";
  }
  breakLog[0] = 0;
  cout << endl;
  
  //makes deductions based on data
  for (int i = 0; i < numDays; i++)
  {
    //check if log is known
    if (breakLog[i] > 0)
    {
      //check if not a break in
      if (breakLog[i-breakLog[i]] <= 0)
      {
        //set corresponding log point to a break in
        breakLog[i-breakLog[i]] = 0;
      }
      else
      {
        //not consistent otherwise
        consistent1 = false;
      }
    }
  }
  
  //test couts
  for (int i = 0; i < numDays; i++)
  {
    cout << breakLog[i] << " ";
  }
  cout << endl;
  
  //figures out what we know (was or was not a break in)
  for (int i = 0; i < numDays; i++)
  {
    if (breakLog[i] == 0)
    {
      breakOccur[i] = 1;
    }
    else if (breakLog[i] > 0)
    {
      breakOccur[i] = 0;
    }
    else
    {
      breakOccur[i] = 2;
    }
    cout << breakOccur[i] << " ";
  }
  cout << endl;
  
  //figures how many certain and uncertain break outs there are
  int certain = 0, uncertain = 0;
  for (int i = 0; i < numDays; i++)
  {
    if (breakOccur[i] == 1)
    {
      certain++;
    }
    if (breakOccur[i] == 2)
    {
      uncertain++;
    }
  }
  cout << certain << " " << uncertain << endl;
  int min = certain, max = certain + uncertain;
  
  //figures out if there is no events consistent
  bool consistent2 = true;
  for (int i = 0; i < numDays; i++)
  {
    if (breakOccur[i] == 2)
    {
      consistent2 = false;
    }
    else
    {
      consistent2 = true;
    }
  }
  cout << endl;
  
  //output
  ofstream fout;
  fout.open("taming.out");
  if (consistent1 and consistent2)
  {
    fout << min << " " << max << endl;
    cout << min << " " << max << endl;
  }
  else
  {
    fout << -1 << endl;
    cout << -1 << endl;
  }
  fout.close();
  fin.close();
  return 0;
}
