/*
 ID: 
 PROG: milk
 LANG: C++
 */
//NAME          :   
//GROUP         :   Binary
//LAST MODIFIED :   14 May 2018
//PROBLEM ID    :   USACO Mixing Milk
//DESCRIPTION   :   Finds the lowest price that Merry Milk Makers can buy from a set of farmers
//SOURCES/HELP  :   
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() 
{
  //declare variables
  int amountNeeded, numFarmers, temp, totalPrice = 0;
  bool notSorted = true;
  
  //open files
  ifstream fin ("milk.in");
  ofstream fout ("milk.out");
  
  //input
  fin >> amountNeeded >> numFarmers;
  
  //declare variable
  int priceThenAmount[numFarmers][2];
  
  //input the lists
  for (int i = 0; i < numFarmers; ++i)
  {
    fin >> priceThenAmount[i][0] >> priceThenAmount[i][1];
  }
  
  //sort the 2d array through bubble sort
  do
  {
    //assume the array is sorted
    notSorted = false;
    
    //loop through the farmers to sort
    for (int i = 0; i < numFarmers-1; ++i)
    {
      //check if the current price is greater than the next price
      if (priceThenAmount[i][0] > priceThenAmount[i+1][0])
      {
        //say the array is not sorted
        notSorted = true;
        
        //swap
        temp = priceThenAmount[i][0];
        priceThenAmount[i][0] = priceThenAmount[i+1][0];
        priceThenAmount[i+1][0] = temp;
        
        //swap
        temp = priceThenAmount[i][1];
        priceThenAmount[i][1] = priceThenAmount[i+1][1];
        priceThenAmount[i+1][1] = temp;
      }
    }
  } while (notSorted);
  
  //buy milk
  for (int i = 0; i < numFarmers; ++i)
  {
    //assume everything is bought
    totalPrice += priceThenAmount[i][0]*priceThenAmount[i][1];
    amountNeeded -= priceThenAmount[i][1];
    
    //break if equal
    if (amountNeeded == 0)
    {
      break;
    }
    //if too much is bought then subtract until the prices are equal
    else if (amountNeeded < 0)
    {
      while (amountNeeded < 0)
      {
        totalPrice -= priceThenAmount[i][0];
        amountNeeded += 1;
      }
      break;
    }
  }
  
  //output
  fout << totalPrice << endl;
  
  //exit program
  return 0;
  
}