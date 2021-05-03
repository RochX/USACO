#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int main() 
{
  ifstream fin ("tttt.in");
  
  string board = "";
  char temp;
  for (int i = 0; i < 9; ++i)
  {
    fin >> temp;
    board += temp;
  }
  cout << board << endl;;
  
  int individuals = 0;
  int teams = 0;
  
  vector <string> toCheck;
  
  string tempString;
  
  //columns
  for (int i = 0; i < 3; ++i)
  {
    tempString = board[i];
    tempString += board[i+3];
    tempString += board[i+6];
    toCheck.push_back(tempString);
  }
  
  //rows
  for (int i = 0; i <= 6; i += 3)
  {
    tempString = board[i];
    tempString += board[i+1];
    tempString += board[i+2];
    toCheck.push_back(tempString);
  }
  
  cout << endl;
  cout << board[2] << board[4] << board[6] << endl;
  
  //diagonals
  tempString = board[0];
  tempString += board[4];
  tempString += board[8];
  toCheck.push_back(tempString);
  
  tempString = board[2];
  tempString += board[4];
  tempString += board[6];
  toCheck.push_back(tempString);
  
  cout << toCheck[0] << endl << endl;
  
  cout << "Test\n";
  for (int i = 0; i < toCheck.size(); ++i)
  {
    cout << toCheck[i] << " ";
  }
  cout << endl;
  tempString = "";
  
  vector <string> finalToCheck;
  
  //delete duplicates
  for (int i = 0; i < toCheck.size(); ++i)
  {
    bool add = true;
    for (int j = 0; j < finalToCheck.size(); ++j)
    {
      if (toCheck[i] == finalToCheck[j])
      {
        add = false;
      }
    }
    if (add or finalToCheck.size() == 0)
    {
      finalToCheck.push_back(toCheck[i]);
    }
  }
  
  const int MAX_PLAYERS = 26;
  bool teamsWin[MAX_PLAYERS];
  for (int i = 0; i < MAX_PLAYERS; ++i)
  {
    teamsWin[i] = false;
  }
  
  cout << "checking\n";
  for (int j = 0; j < finalToCheck.size(); ++j)
  {
    cout << finalToCheck[j] << endl;
    tempString = finalToCheck[j];
    
    //teams
    if (tempString[0] == tempString[1] xor tempString[0] == tempString[2] xor tempString[1] == tempString[2])
    {
      //check if the group of 3 isn't one cow
      if (!(tempString[0] == tempString[1] and tempString[0] == tempString[2]))
      {
        teams++;
      }
    }
    
    //individuals
    if (tempString[0] == tempString[1] and tempString[0] == tempString[2])
    {
      individuals++;
    }
  }
  
  ofstream fout ("tttt.out");
  fout << individuals << endl << teams << endl;
  
  return 0;
  
}