/*
 ID: 
 PROG: sprime
 LANG: C++
 */
//NAME          :   
//GROUP         :   Binary
//LAST MODIFIED :   13 March 2018
//PROBLEM ID    :   USACO Superprime Rib
//DESCRIPTION   :   Given a length for a set of numbers, find all of the superprime numbers that are the given length
//SOURCES/HELP  :   
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
using namespace std;

//check if a number is prime
bool checkPrime(int num)
{
  //if the number is 1 or 0 say its not prime
  if (num == 1)
  {
    return false;
  }
  
  //check if the number is prime by checking if every number is not divisible by it
  bool isPrime = true;
  for (int i = 2; i*i <= num; ++i)
  {
    if (num % i == 0)
    {
      return false;
    }
  }
  //return true or false based on if the number is prime
  if(isPrime)
  {
    return true;
  }
  return false;
}

//declare variables
int length;
const int MAX_LENGTH = 8;
int powersOf10[MAX_LENGTH+1] = {1,10,100,1000,10000,100000,1000000,10000000,100000000};

//check if a number is superprime
bool superPrimeChecker(int num)
{
  //declare variable
  int tempInt;
  
  //check if each spot cut is prime starting going left to right
  for (int i = length; i != 0; --i)
  {
    tempInt = num/powersOf10[i-1];
    if(!checkPrime(tempInt))
    {
      return false;
    }
  }
  return true;
}

//main function
int main() 
{
  //input
  ifstream fin;
  fin.open("sprime.in");
  fin >> length;
  fin.close();
  
  //open output file
  ofstream fout;
  fout.open("sprime.out");
  
  //set range
  int start = powersOf10[length-1], end = powersOf10[length];
  
  //test cout
  cout << start << " " << end << endl;
  
  //main loop
  for (int num = start+1; num < end; num += 2)
  {
    //stops checking the number if the first digit isn't a 1, 3, 7, or 9
    int firstDigit = num % 10;
    if (firstDigit == 1 or firstDigit == 3 or firstDigit == 7 or firstDigit == 9)
    {
      //check if a number is superprime and output it if it is
      if(superPrimeChecker(num))
      {
        fout << num << endl;
      }
    }
    
  }
  
  //close output
  fout.close();
  
  //exit program
  return 0;
}