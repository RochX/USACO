/*
 ID: 
 PROG: castle
 LANG: C++14
 */
//NAME          :   
//GROUP         :   Binary
//LAST MODIFIED :   15 May 2018
//PROBLEM ID    :   USACO The Castle
//DESCRIPTION   :   Given a list of integers that determine where walls are in a M x N castle, find the wall that can be removed in order to make largest room.
//SOURCES/HELP  :
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX_WIDTH = 51;
const int MAX_HEIGHT = 51;
//height, col
string castle[MAX_HEIGHT][MAX_WIDTH];
int rooms[MAX_HEIGHT][MAX_WIDTH];
bool visited[MAX_HEIGHT][MAX_WIDTH];
int marker = 1;

int tempH, tempW;

string baseConverter(int, int);
void fillRooms(int, int);
bool isConnected(int, int, int, int);

//function for test //couts
void outputRoomConfig()
{
    //cout << "Room Config:\n";
    for (int i = 0; i < tempH; i++)
    {
        for (int j = 0; j < tempW; j++)
        {
            //cout << rooms[i][j] << "    ";
        }
        //cout << endl;
    }
    //cout << endl;
}

//notes
//wall code: SENW (starting south, read counterclockwise)

int main()
{
    //declare variables
    int width, height, temp, numRooms, largestRoom = 0, largestAfterRemove = 0;
    int removedX, removedY, tempRemoved;
    char removedDirection;
    
    //open files
    ifstream fin ("castle.in");
    ofstream fout ("castle.out");
    
    //input
    fin >> width >> height;
    
    //temp vars for test //couts
    tempH = height;
    tempW = width;
    
    //input castle arrangement and convert it to binary
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            fin >> temp;
            castle[i][j] = baseConverter(temp,2);
            //cout << castle[i][j] << " ";
        }
        //cout << endl;
    }
    //cout << endl;
    
    //test //couts
    outputRoomConfig();
    
    //find rooms
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //check if the room hasn't already been found in a room
            if (!visited[i][j])
            {
                //call function to fill the room with a value
                fillRooms(i, j);
                
                //increment the value to put in the rooms
                marker++;
                
                //test //couts
                outputRoomConfig();
            }
        }
    }
    
    //find sizes of rooms
    numRooms = marker-1;
    int sizes[marker-1] = {};
    
    //loop through castle rooms to find size of rooms based on the marker placed
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sizes[rooms[i][j]-1]++;
        }
    }
    
    //find the largest room size
    //cout << "Sizes: ";
    for (int i = 0; i < marker-1; i++)
    {
        if (largestRoom < sizes[i])
        {
            largestRoom = sizes[i];
        }
        //cout << sizes[i] << " ";
    }
    //cout << endl;
    
    vector<int> largestRemoves;
    vector<int> removedXs;
    vector<int> removedYs;
    vector<char> removedDirections;
    
    
    //find largest size after one wall is removed
    //for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
    {
        //for (int i = 0; i < height; i++)
        //for (int j = 0; j < width; j++)
        for (int i = height; i--;)
        {
            //check breaking a wall to the north
            //do not check if room north is part of same room
            if (rooms[i][j] != rooms[i-1][j] and i-1 >= 0)
            {
                
                tempRemoved = sizes[rooms[i][j]-1]+sizes[rooms[i-1][j]-1];
                //cout << i << " " << j << " " << tempRemoved << endl;
                largestRemoves.push_back(tempRemoved);
                removedYs.push_back(i);
                removedXs.push_back(j);
                removedDirections.push_back('N');
                
                if (largestAfterRemove < tempRemoved)
                {
                    largestAfterRemove = tempRemoved;
                    removedY = i;
                    removedX = j;
                    removedDirection = 'N';
                }
            }
            
            //check breaking a wall to the east
            //do not check if room east is part of same room
            if (rooms[i][j] != rooms[i][j+1] and j+1 < width)
            {
                
                tempRemoved = sizes[rooms[i][j]-1]+sizes[rooms[i][j+1]-1];
                
                //cout << i << " " << j << " " << tempRemoved << endl;
                largestRemoves.push_back(tempRemoved);
                removedYs.push_back(i);
                removedXs.push_back(j);
                removedDirections.push_back('E');
                if (largestAfterRemove < tempRemoved)
                {
                    largestAfterRemove = tempRemoved;
                    removedY = i;
                    removedX = j;
                    removedDirection = 'E';
                }
            }
        }
    }
    //cout << largestRemoves.size() << endl;
    
    
    
    //output
    fout << numRooms << endl << largestRoom << endl << largestAfterRemove << endl;
    fout << removedY+1 << " " << removedX+1 << " " << removedDirection << endl;
    
    //exit program
    return 0;
}

//direction keys (from original point):
/*0=south
 1=east
 2=north
 3=west
 */

//given a direction and two rooms, check if they are part of the same room
bool isConnected(int p1h, int p1w, int p2h, int p2w, int direction)
{
    //case for when any of the destination numbers are negative
    if (p2h < 0 or p2w < 0)
    {
        return 0;
    }
    
    
    //declare and initialize variables
    string room1 = castle[p1h][p1w];
    string room2 = castle[p2h][p2w];
    ////cout << room1 << " " << room2 << endl;
    
    //check if rooms are adjacent
    if (room1[direction] == '0' and room2[(direction+2)%4] == '0')
    {
        return 1;
    }
    
    //otherwise false
    return 0;
}

//fill the rooms with a certain marker to create bigger rooms
void fillRooms(int height, int width)
{
    //set room to visited
    visited[height][width] = true;
    
    //set the room to be a part of a larger room
    rooms[height][width] = marker;
    
    //check if an adjacent room is part of the same room and hasn't been visited yet
    //south
    ////cout << "south: " << castle[height][width] << " " << castle[height+1][width] << "; ";
    ////cout << !visited[height+1][width] << " " << isConnected(height, width, height+1, width, 0) << endl;
    if (!visited[height+1][width] and isConnected(height, width, height+1, width, 0))
    {
        fillRooms(height+1, width);
    }
    //east
    ////cout << "east: " << castle[height][width] << " " << castle[height][width+1] << "; ";
    ////cout << !visited[height][width+1] << " " << isConnected(height, width, height, width+1, 1) << endl;
    if (!visited[height][width+1] and isConnected(height, width, height, width+1, 1))
    {
        fillRooms(height, width+1);
    }
    //north
    ////cout << "north: " << castle[height][width] << " " << castle[height-1][width] << "; ";
    ////cout << !visited[height-1][width] << " " << isConnected(height, width, height-1, width, 2) << endl;
    if (!visited[height-1][width] and isConnected(height, width, height-1, width, 2))
    {
        fillRooms(height-1, width);
    }
    //west
    /*//cout << "west: " << castle[height][width] << " ";
     if (width-1 >= 0)
     {
     //cout << castle[height][width-1];
     }
     //cout << "; " << !visited[height][width-1] << " " << isConnected(height, width, height, width-1, 3) << endl;
     */
    if (!visited[height][width-1] and isConnected(height, width, height, width-1, 3))
    {
        fillRooms(height, width-1);
    }
}

//declare variable
const int LENGTH = 4;

//base converter for making binary numbers
string baseConverter(int num10, int base)
{
    //declare and initialize variables
    int digit, powerNum = 0;
    string numB = "";
    //constant list has all digits for bases 2-36
    const string BASE_DIGITS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int maxPower = 1;
    
    //loop to determine the first power greater than the base 10 number
    for (; maxPower <= num10; powerNum++)
    {
        maxPower = pow(base, powerNum);
    }
    
    //subtracts 1 from the exponent value of the first power greater than the base 10 number
    powerNum--;
    
    //loops while the exponent value is greater than 0
    while (powerNum > 0)
    {
        //decrements the power and exponent value
        maxPower /= base;
        powerNum--;
        
        //determines the highest integer multiple of the current highest power
        digit = floor(num10/maxPower);
        
        //subtracts the amount being added to the final number
        num10 -= maxPower*digit;
        
        //adds the digit to the number using the conversion list
        numB += BASE_DIGITS[digit];
        
    }
    
    //adds leading zeros if needed
    while (numB.length() < LENGTH)
    {
        numB = "0" + numB;
    }
    
    //returns the converted number
    return numB;
}
