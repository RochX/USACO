/*
 ID: 
 PROG: holstein
 LANG: C++14
*/ 
//NAME          :   
//GROUP         :   APCS
//LAST MODIFIED :   2 October 2018
//PROBLEM ID    :   USACO Healthy Holsteins
//DESCRIPTION   :   Given a list of vitamins and scoops of feed containing some amount of each vitamin, find the minimum amount of feed needed to feed a cow
//SOURCES/HELP  :   
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#include <bitset>
using namespace std;

//declare variables
const int MAX_VITA = 25;
const int MAX_FEEDS = 15;
int numVita, numFeeds, vitaReqs[MAX_VITA];
  //row = feed, cols = vitamins
int feeds[MAX_FEEDS][MAX_VITA];

//function declaration
bool checkSolution(bitset<MAX_FEEDS>);
int min(int,int);

int main() 
{
  //declare variables
  vector <bitset<MAX_FEEDS> > works;
  int lowestBits = 16;
  int counter = 0;

  //open files
  ifstream fin ("holstein.in");
  ofstream fout ("holstein.out");
  
  //input data
  fin >> numVita;
  for (int i = 0; i < numVita; ++i)
  {
    fin >> vitaReqs[i];
  }
  fin >> numFeeds;
  for (int i = 0; i < numFeeds; ++i)
  {
    for (int j = 0; j < numVita; ++j)
    {
      fin >> feeds[i][j];
    }
  }

  //loop through all potential solutions
  for (int i = 1; i < pow(2, numFeeds); i++)
  {
    //set bitset to represent which feeds are used
    bitset<MAX_FEEDS> solution = i;

    //check the solution
    if (checkSolution(solution))
    {
      //add solution to list of ones that work and find the lowest number of feeds needed
      lowestBits = min(lowestBits, solution.count());
      works.push_back(solution);
    }
  }

  //output
  for (int i = 0; i < works.size(); i++)
  {
    //finds the first solution that has the least number of feeds in it
    if (works[i].count() == lowestBits)
    {
      //set a bitset of the final solution
      bitset<MAX_FEEDS> solution = works[i];

      //output number of feeds needed
      fout << lowestBits << " ";

      //loop to output which feeds are used
      for (int j = 0; j < numFeeds; j++)
      {
        //if solution was used
        if (solution[j] == 1)
        {
          //output feed number
          fout << j+1;

          //figure out spacing
          if (counter == lowestBits-1)
          {
            fout << endl;
            break;
          }
          else
          {
            fout << " ";
          }
          counter++;
        }
        
      }
      //exit loop
      break;
    }
  }
  
  //exit program
  return 0;
}

//returns the smallest number
int min(int x, int y) {return (x<y)?x:y;}

//check if a solution is valid
bool checkSolution(bitset<MAX_FEEDS> solution)
{
  //declare variable to store solution
  int tempSolution[MAX_VITA] = {};

  //loop through all feeds
  for (int i = 0; i < numFeeds; i++)
  {
    //set bitset to check if requirements are met
    bitset<MAX_VITA> check = 0;
    //check if this combination uses this feed
    if(solution[i] == 1)
    {
      //loop through all vitamins
      for (int j = 0; j < numVita; j++)
      {
        //add solution to the temporary solution
        tempSolution[j] += feeds[i][j];

        //check if requirements are met
        if (tempSolution[j] >= vitaReqs[j])
        {
          //if so then set that requirement bit to 1
          check[j] = 1;
        }
      }

      //check if all requirements are met
      if (check.count() == numVita)
      {
        return true;
      }
    }
  }

  return false;
}