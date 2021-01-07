/*
 ID: 
 PROG: lamps
 LANG: C++14
*/ 
//NAME          :   
//GROUP         :   APCS
//LAST MODIFIED :   15 November 2018
//PROBLEM ID    :   USACO Party Lamps
//DESCRIPTION   :   Given a 4 types of buttons, find how many ways there are to make a configuration given which lamps should be on or off and how many buton presses are allowed.
//SOURCES/HELP  :   
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <bitset>
#include <sstream>
using namespace std;

//function declaration
string base10Convert(int,int);
string applyButtons(string, string);
string button(string, int);

int main() 
{
  //file IO
  ifstream fin ("lamps.in");
  ofstream fout ("lamps.out");

  //variable declaration
  const int MAX_LAMPS = 100;
  bool onLamps[MAX_LAMPS] = {}, offLamps[MAX_LAMPS] = {};
  int numLamps, numPresses, input;
  string initial = "", tempConfig, key = "";
  vector<string> instruction;

  //input
  fin >> numLamps >> numPresses;
  
  
  //input on lamps
  while (true)
  {
    fin >> input;
    if (input == -1) 
      break;
    onLamps[input-1] = true;
  }

  //input off lamps
  while (true)
  {
    fin >> input;
    if (input == -1) 
      break;
    offLamps[input-1] = true;
  }

  //set the initial string and creates the key string
  for (int i = 0; i < numLamps; i++)
  {
    initial += "1";
    if (onLamps[i])
    {
      key += "1";
    }
    else if (offLamps[i])
    {
      key += "0";
    }
    else
    {
      key += "*";
    }
  }
  
  //finds working press combos
  for (int i = 0; i < 30; i++)
  {
    //create a press configuration
    tempConfig = base10Convert(i, 4);

    //exit if the number of buttons to be pressed is greater than the number given
    if (tempConfig.length() > numPresses)
      break;

    //add leading zeroes
    while (tempConfig.length() < numPresses)
      tempConfig = "0" + tempConfig;
    
    //apply the button combination
    string result = applyButtons(initial, tempConfig);

    //see if the current button combination equals a previous one
    bool isPart = false;
    for (int i = 0; i < instruction.size(); i++)
    {
      string applied = applyButtons(initial, instruction[i]);
      if (result == applied)
      {
        isPart = true;
        break;
      }
    }

    //if it isn't equal to a previous one add it to list
    if (!isPart)
    {
      instruction.push_back(tempConfig);
    }
  }

  //add the reduced lamp combinations and check if they meet the requirements
  vector<string> valid;
  for (int i = 0; i < instruction.size(); i++)
  {
    //apply the combination
    tempConfig = applyButtons(initial, instruction[i]);

    //check if a config fits the requirements
    bool good = true;
    for (int j = 0; j < tempConfig.length(); j++)
    {
      if (key[j] != '*' and tempConfig[j] != key[j])
      {
        good = false;
      }
    }

    //config is good then add it to the list
    if (good)
    {
      valid.push_back(tempConfig);
    }
  }
  //case when there are no valid outputs
  if (valid.size() == 0)
    fout << "IMPOSSIBLE\n";
  else
  {
    //sort and output
    sort(valid.begin(), valid.end());
    for (int i = 0; i < valid.size(); i++)
    {
      fout << valid[i] << endl;
    }
  }
}

//base 10 to base converter
string base10Convert(int dec, int base)
{
  string result = "", symbol = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  while (dec > 0)
  {
    result = symbol[dec%base] + result;
    dec /= base;
  }
  return result;
}

//do a button
string button(string config, int buttonNum)
{
  switch(buttonNum)
  {
    //flip all
    case 0:
      for (int i = 0; i < config.length(); i++)
      {
        config[i] = (config[i] == '0') ? '1' : '0';
      }
      break;
    //flip evens
    case 1:
      for (int i = 0; i < config.length(); i += 2)
      {
        config[i] = (config[i] == '0') ? '1' : '0';
      }
      break;
    //flip odds
    case 2:
      for (int i = 1; i < config.length(); i += 2)
      {
        config[i] = (config[i] == '0') ? '1' : '0';
      }
      break;
    //flip every 3rd
    case 3:
      for (int i = 0; i < config.length(); i += 3)
      {
        config[i] = (config[i] == '0') ? '1' : '0';
      }
      break;
  }
  return config;
}

//do the entire button combination
string applyButtons(string config, string buttonPresses)
{
  int toPress;
  for (int i = 0; i < buttonPresses.size(); i++)
  {
    toPress = buttonPresses[i]-48;
    config = button(config, toPress);
  }
  return config;
}