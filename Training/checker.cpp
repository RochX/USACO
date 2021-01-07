/*
 ID: 
 PROG: checker
 LANG: C++14
*/ 
//NAME          :   
//GROUP         :   Binary
//LAST MODIFIED :   20 April 2018
//PROBLEM ID    :   USACO Checker
//DESCRIPTION   :   Given a number N, solve the queens problem on an N x N board where the first three solutions and the total are printed
//SOURCES/HELP  :   USACO hints
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
//declare variables
int boardSize;
const int MAX_SIZE = 13;
//index = column, value = row
int checkerPos[MAX_SIZE];
//1 = can't place, 0 = can place
bool avaiablePos[MAX_SIZE][MAX_SIZE];
vector <string> solutions;

//check whether a piece can be placed
bool validPos(int row,int col)
{
  //check if the column is occupied
  if (checkerPos[col] != -1)
  {
    return false;
  }
  
  //declare variables
  int i = row; 
  int j = col;
  
  //check the left diagonal
  for (; i >= 0 and j >= 0; --i, --j)
  {
    if (avaiablePos[i][j])
    {
      return false;
    }
  }
  
  //reset variables
  i = row; 
  j = col;
  
  //check the right diagonal
  for (; i >= 0 and j < boardSize; --i, ++j)
  {
    if (avaiablePos[i][j])
    {
      return false;
    }
  }
  
  //if all conditions met then place a piece
  return true;
}

//search function
int search(int row)
{
  if (row == boardSize)
  {
    //declare variables
    string temp = "";
    string tempReverse = "";
    
    //make solutions as a string using ASCII characters and values
    for (int i = 0; i < boardSize; ++i)
    {
      temp += static_cast<char>(checkerPos[i]+65);
      tempReverse += static_cast<char>(checkerPos[boardSize-1-i]+65);
      if (i != boardSize-1)
      {
        temp += " ";
        tempReverse += " ";
      }
    }
    
    //add solution to the vector
    solutions.push_back(temp);
    
    //add the reverse of the string if it is not in the middle
    if (temp[boardSize-1] != 'A')
    {
      solutions.push_back(tempReverse);
    }
    
    //exit
    return 0;
  }
  
  //check whether the row is not zero
  bool rowNotZero = true;
  if (row == 0)
  {
    rowNotZero = false;
  }
  
  //loop through all of the columns
  for (int col = boardSize-1; col >= 0; --col)
  {
    //check if a column is occupied
    //also only place half of them if the row is zero to use symmetry to generate all of the solutions
    if (validPos(row,col) and (rowNotZero or col >= boardSize/2))
    {
      //place a piece
      checkerPos[col] = row;
      avaiablePos[row][col] = 1;
      search(row+1);
      
      //remove the placed piece
      avaiablePos[row][col] = 0;
      checkerPos[col] = -1;
    }
  }
}

//main function
int main() 
{
  //open files
  ifstream fin ("checker.in");
  ofstream fout ("checker.out");
  
  //input size
  fin >> boardSize;
  
  //reserve space the vector
  solutions.reserve(74000);
  
  //initialize the position list
  for (int i = 0; i < MAX_SIZE; ++i)
  {
    checkerPos[i] = -1;
  }
  
  //find all solutions
  search(0);
  
  //sort the list
  sort(solutions.begin(), solutions.end());
  
  //output solutions
  for (int i = 0; i < 3; ++i)
  {
    string temp = solutions[i];
    for (int j = 0; j < temp.size(); ++j)
    {
      if (temp[j] != ' ')
      {
        fout << int(temp[j])-64;
      }
      else
      {
        fout << ' ';
      }
    }
    fout << endl;
  }
  
  //output number of solutions
  fout << solutions.size() << endl;
  
  //exit program
  return 0;
}