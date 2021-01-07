/*
 ID: 
 PROG: pprime
 LANG: C++11
 */
//NAME          :   
//GROUP         :   Binary
//LAST MODIFIED :   13 March 2018
//PROBLEM ID    :   USACO Prime Palindromes
//DESCRIPTION   :   Given a range of numbers, find all of the numbers that are prime and are a palindrome
//SOURCES/HELP  :   , https://brilliant.org/wiki/prime-numbers/
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

//check if a number is prime
bool checkPrimeBruteForce(int num)
{
  //if the number is 1 or 0 say its not prime
  if (num == 1 or num == 0)
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

//vector of the numbers to check
vector<int> palindromes;

//generate palindromes
void generatePalindromes()
{
  //save some memory for the numbers to check
  palindromes.reserve(5000);
  
  //generate 1 digit palindromes
  for (int i = 1; i < 10; i++)
  {
    palindromes.push_back(i);
  }
  
  //put 11 into the palindromes list (the only even numbered digit prime palindrome)
  palindromes.push_back(11);
  
  //generate 3 digit palindromes
  for (int d1 = 1; d1 < 10; d1 += 2)
  {
    for (int d2 = 0; d2 < 10; ++d2)
    {
      palindromes.push_back(d1*100+d2*10+d1);
    }
  }
  
  //generate 5 digit palindromes
  for (int d1 = 1; d1 < 10; d1 += 2)
  {
    for (int d2 = 0; d2 < 10; ++d2)
    {
      for (int d3 = 0; d3 < 10; ++d3)
      {
        palindromes.push_back(d1*10000+d2*1000+d3*100+d2*10+d1);
      }
    }
  }
  
  //generate 7 digit palindromes
  for (int d1 = 1; d1 < 10; d1 += 2)
  {
    for (int d2 = 0; d2 < 10; ++d2)
    {
      for (int d3 = 0; d3 < 10; ++d3)
      {
        for (int d4 = 0; d4 < 10; ++d4)
        {
          palindromes.push_back(d1*1000000+d2*100000+d3*10000+d4*1000+d3*100+d2*10+d1);
        }
      }
    }
  }
}

//main function
int main() 
{
  //declare variables
  int start, end;
  
  //input
  ifstream fin;
  fin.open("pprime.in");
  fin >> start >> end;
  fin.close();
  
  //open output file
  ofstream fout;
  fout.open("pprime.out");
  
  //make the start number odd if its not odd
  if(start % 2 == 0)
  {
    start++;
  }
  
  //generate the palindromes
  generatePalindromes();
  
  for (int i = 0; i < palindromes.size(); ++i)
  {
    //exit if the palindrome is largest than the range
    if (palindromes[i] > end)
    {
      break;
    }
    
    //output if the palindrome is both prime and within the range
    if (checkPrimeBruteForce(palindromes[i]) and start <= palindromes[i] and palindromes[i] <= end)
    {
      fout << palindromes[i] << endl;
    }
  }
  
  //close output file
  fout.close();
  
  //exit program
  return 0;
}