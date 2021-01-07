/*
 ID: 
 PROG: milk3
 LANG: C++
*/
//NAME          :   
//GROUP         :   Binary
//LAST MODIFIED :   11 March 2018
//PROBLEM ID    :   USACO Mother's Milk
//DESCRIPTION   :   Given the capacities for three buckets and the fact that the last bucket starts as full, find the possible values for the last bucket when the first bucket is empty and after some amount of transfers
//SOURCES/HELP  :   
#include <algorithm>
#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

//declare variables
const int MAX_SOLUTIONS = 21, NUM_BUCKETS = 3;
int sizes[NUM_BUCKETS];
bool solutions[MAX_SOLUTIONS];
vector<int> milkCombos;

//pour bucket 'start' into bucket 'destination'
int* pour(int start, int destination, int buckets[])
{
  
  int amountStart = buckets[start], startSize = sizes[start];
  int amountDestination = buckets[destination], destinationSize = sizes[destination];
  //continue with pour only if the destination bucket is not full and the start bucket has milk
  if (amountDestination != destinationSize and amountStart != 0)
  {
    //find how much room is in the destination bucket
    int roomInDestination = destinationSize - amountDestination;
    
    //declare variable
    int amountToPour;
    
    //check if there is enough room in the destination bucket for all of the milk in the start bucket
    //figure out how much to pour from start bucket to destination bucket
    if (amountStart >= roomInDestination)
    {
      amountToPour = amountStart - (amountStart - roomInDestination);
    }
    else
    {
      amountToPour = amountStart;
    }
    
    //transfer milk
    amountDestination += amountToPour;
    amountStart -= amountToPour;
    
    //set values in the array given in the function argument
    buckets[start] = amountStart;
    buckets[destination] = amountDestination;
  }
  
  //return the list
  return buckets;
}

//checks and then solves a given milk combination
int solve(int startingBuckets[])
{
  //0 = A, 1 = B, 2 = C
  int buckets[NUM_BUCKETS];
  //transfer the function argument to an array in the function
  for (int i = 0; i < NUM_BUCKETS; i++)
  {
    buckets[i] = startingBuckets[i];
  }
  
  //check if A is empty
  if (buckets[0] == 0)
  {
    //check if the value of C has already been added
    if (!solutions[buckets[2]])
    {
      //if not then add it
      solutions[buckets[2]] = true;
    }
    else
    {
      //if so then stop recursion
      return 0;
    }
  }
  
  //create a int to store the current milk combination
  int milkCombination = buckets[0]*10000+buckets[1]*100+buckets[2];
  
  //check if this milk combination has been checked
  bool hasBeenChecked = false;
  for (int i = 0; i < milkCombos.size(); i++)
  {
    if (milkCombos[i] == milkCombination)
    {
      hasBeenChecked = true;
      break;
    }
  }
  
  //stop recursion if the current milk combination has been checked already
  if(hasBeenChecked)
  {
    return 0;
  }
  
  //add the milk combination to the vector
  milkCombos.push_back(milkCombination);
  
  //generate the next 6 possible milk permutations
  for (int i = 0; i < NUM_BUCKETS; i++)
  {
    for (int j = 0; j < NUM_BUCKETS; j++)
    {
      //reset the bucket list the pour function points to
      for (int k = 0; k < NUM_BUCKETS; k++)
      {
        buckets[k] = startingBuckets[k];
      }
      
      //solve next combination if a bucket isn't being poured into itself
      if (i != j)
      {
        solve(pour(i,j, buckets));
      }
    }
  }
}

//main function
int main() 
{
  //save some space for the combinations vector
  milkCombos.reserve(20);
  
  //input
  ifstream fin;
  fin.open("milk3.in");
  fin >> sizes[0] >> sizes[1] >> sizes[2];
  fin.close();
  
  //open output file
  ofstream fout;
  fout.open("milk3.out");
  
  //initial array for solution
  int buckets[NUM_BUCKETS] = {0, 0, sizes[2]};
  
  //solve
  solve(buckets);
  
  //send output
  string output = "";
  for (int i = 0; i < MAX_SOLUTIONS; i++)
  {
    //loops through bool array
    if(solutions[i])
    {
      stringstream ss;
      ss << i;
      string str = ss.str();
      output += str + " ";
    }
  }
  
  //cuts off last space
  if (output != "")
  {
    output.erase(output.length()-1, output.length());
  }
  fout << output << endl;
  fout.close();
  
  //exit program
  return 0;
}