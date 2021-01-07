/*
 ID: 
 PROG: hamming
 LANG: C++14
*/ 
//NAME          :   
//GROUP         :   Binary
//LAST MODIFIED :   17 May 2018
//PROBLEM ID    :   USACO Hamming Codes
//DESCRIPTION   :   Given 3 numbers N, B, and D, find N numbers whose binary notation is B bits long differs by D bits from all of the other numbers
//SOURCES/HELP  :   https://www.geeksforgeeks.org/c-bitset-and-its-application/
#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
using namespace std;

int main() 
{
  //list of powers of 2 to speed up program
  const int POWS_OF_2[9] = {1,2,4,8,16,32,64,128,256};
  
  //declare variables
  int numCodes, numBits, distance, powOf2;
  vector <bitset<8> > binaryNums;
  bool valid;
  
  //open files
  ifstream fin ("hamming.in");
  ofstream fout ("hamming.out");
  
  //input
  fin >> numCodes >> numBits >> distance;
  
  //find the max number for the program
  powOf2 = POWS_OF_2[numBits];
  
  //generate all binary numbers
  for (int i = 0; i < powOf2; i++)
  {
    //convert number to binary string through bitset
    bitset<8> tempBitset(i);
    
    //put the number into a vector
    binaryNums.push_back(tempBitset);
  }
  
  //loop through start points
  for (int start = 0; start < powOf2; start++)
  {
    //declare vector in loop so it doesn't need to be cleared at end of loop
    vector<int> sequence;
    
    //set the first number of sequence
    sequence.push_back(start);
    
    //add values to the sequence
    for (int i = start+1; i < powOf2; i++)
    {
      //assume the number is valid
      valid = true;

      //check to see if the current number is at least the given hamming distance from the other numbers
      for (int j = 0; j < sequence.size(); j++)
      {
        //convert number in the sequence to a binary string
        bitset<8> temp(sequence[j]);
        
        //check for distance using xor of two binary strings and checking how many bits differ
        if (!((binaryNums[i] ^ temp).count() >= distance))
        {
          //if too close then exit checking loop
          valid = false;
          break;
        }
      }
      
      //if the number is valid then add it to the sequence
      if (valid)
      {
        sequence.push_back(i);
      }
      
      //if enough numbers have been found then output
      if (sequence.size() >= numCodes)
      {
        //loop through the codes
        for (int i = 0; i < numCodes; i++)
        {
          //output the number
          fout << sequence[i];
          
          //output a new line every 10 numbers
          if (i % 10 == 9)
          {
            fout << endl;
          }
          //prevent an extra space from being added
          else if (i != numCodes-1)
          {
            fout << " ";
          }
          //add last new line
          else
          {
            fout << endl;
          }
        }
        //exit program
        return 0;
      }
    }
  }
}