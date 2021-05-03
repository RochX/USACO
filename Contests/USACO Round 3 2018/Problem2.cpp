//NAME:		Xavier Silva
//Group:	Binary
//PROGRAM:	USACO Round 3 Hoofball
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

//declare variables
const int MAX_N = 100;
const int MAX_DISTANCE = 1000;
int distances[MAX_N];
int numCows;
string templateString;

//solves cases
int solve(string held, int currentHolder, int ballsGiven)
{
  //throws ball based on cow ball it is first given to
  ballsGiven++;
  for (int i = numCows-1; --i;)
  {
    //finds distances to the 2 closest cows and shows that this cow has held the ball
    held[currentHolder] = '1';
    int distFront = abs(distances[currentHolder] - distances[currentHolder+1]);
    int distBack = abs(distances[currentHolder] - distances[currentHolder-1]);
    
    //first and last cows
    if (currentHolder == 0)
    {
      distBack += MAX_DISTANCE;
    }
    if(currentHolder == numCows-1)
    {
      distFront += MAX_DISTANCE;
    }
    //cout << currentHolder << "  " << distFront << " " << distBack << endl;
    
    //finds who to throw it to
    if (distFront < distBack)
    {
      currentHolder++;
    }
    else
    {
      currentHolder--;
    }
  }
  //cout << held << " " << currentHolder << " " << ballsGiven << endl;;
  
  //checks if all are TRUE
  bool allHad = true;
  for (int i = numCows; --i;)
  {
    if (held[i-1] == '0')
    {
      allHad = false;
      break;
    }
  }
  
  //case for when all are true
  if (allHad)
  {
    return ballsGiven;
  }
  //case for when all are not true
  //finds new currentHolder
  int solutions[numCows], counter = 0;
  for (int i = 0; i < numCows; i++)
  {
    if (held[i] == '0')
    {
      solutions[counter] = solve(held, i, ballsGiven);
      counter++;
    }
  }
  //finds best solution
  if(!allHad)
  {
    int min = solutions[0];
    for (int i = 1; i < counter; i++)
    {
      if (min > solutions[i])
      {
        min = solutions[i];
      }
    }
    return min;
  }
  else
  {
    return ballsGiven;
  }
}

//function to set up initial cases
int search(string temp)
{
  //set up initial cases and send them to solve
  int solutions[numCows];
  for (int i = 0; i < numCows; i++)
  {
    solutions[i] = solve(temp, i, 0);
    //cout << solutions[i] << " ";
  }
  //cout << endl;
  
  //find best solution
  int min = solutions[0];
  for (int i = 1; i < numCows; i++)
  {
    if (min > solutions[i])
    {
      min = solutions[i];
    }
  }
  return min;
}


int main() 
{
  //input
  ifstream fin;
  fin.open("hoofball.in");
  fin >> numCows;
  
  //input distances (sorted into ascending order) and create template
  for (int i = numCows; --i;)
  {
    fin >> distances[i-1];
    templateString += '0';
  }
  sort(distances, distances + numCows);
  
  //test couts
  for (int i = 0; i < numCows; i++)
  {
    cout << distances[i] << " ";
  }
  cout << endl << templateString << endl;
  
  //get final solution
  int finalSolution = search(templateString);
  
  //output
  ofstream fout;
  fout.open("hoofball.out");
  //cout << finalSolution << endl;
  fout << finalSolution << endl;
  fout.close();
  fin.close();
  return 0;
}