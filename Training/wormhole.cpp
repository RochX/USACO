/*
 ID: 
 PROG: wormhole
 LANG: C++
 */
//NAME          :   
//GROUP         :   Krypton
//LAST MODIFIED :   30 January 2018
//PROBLEM ID    :   USACO Wormholes
//DESCRIPTION   :   Finds how many different pairing of wormholes cause an infinite loop to be formed
//SOURCES/HELP  :   Brian Dean ( http://www.usaco.org/current/data/sol_wormhole.html )
#include <iostream>
#include <fstream>
using namespace std;

//declare variables
const int MAX_WORMHOLES = 12;
int numWormholes, to_right[MAX_WORMHOLES+1], partner[MAX_WORMHOLES+1];

//check for a cycle
bool checkCycle()
{
	//test all possible start points
    for (int start = 1; start <= numWormholes; start++)
    {
		//start point is a wormhole
        int position = start;
		
		//try to go through all wormholes
        for (int k = 0; k < numWormholes; k++)
        {
			//if there is no wormhole to the right, then it locks itself at 0
            position = to_right[partner[position]];
        }
		//statement for when an infinite cycle occurs
        if (position != 0)
        {
            return true;
        }
    }
    return false;
}

//solve function
int solve()
{
    //check for unpaired wormholes
    int i, total = 0;
    for (i = 1; i <= numWormholes; i++)
    {
		//exits when first unpaired wormhole is found
        if (partner[i] == 0)
        {
            break;
        }
    }
	
    //check if all wormholes are paired (base case)
    if (i > numWormholes)
    {
		//return 1 if an infinite cycle exists otherwise 0
        if (checkCycle())
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    
    //try pairing the first unpaired wormhole with all other wormholes (recursion case)
    for (int j = i+1; j <= numWormholes; j++)
    {
        //check if the wormhole is unpaired
        if (partner[j] == 0)
        {
            //first unpaired wormhole is paired
            partner[i] = j;
            //the current unpaired wormhole is paired
            partner[j] = i;
            
			//add total
            total += solve();
            //reset pairs
            partner[i] = partner [j] = 0;
        }
    }
	//return the number of current pairing with infinite cycles
	return total;
}

//main program
int main()
{
    //declare variables
    int X[MAX_WORMHOLES+1], Y[MAX_WORMHOLES+1];
	ifstream wormholeIn;
	wormholeIn.open("wormhole.in");
	
    //input
	wormholeIn >> numWormholes;
	for (int i = 1; i <= numWormholes; i++)
	{
        wormholeIn >> X[i] >> Y[i];
	}
	
	//close input
    wormholeIn.close();
    
    //find which wormholes are to the right
	for (int i = 1; i <= numWormholes; i++)
	{
        for (int j = 1; j <= numWormholes; j++)
        {
            //check if a wormhole is to the right and is the same vertically
            if (X[j] > X[i] and Y[i] == Y[j])
            {
                //check if the current wormhole is closer than the one currently or there's none currently to the right
                if (to_right[i] == 0 or X[j] - X[i] < X[to_right[i]] - X[i])
                {
                    to_right[i] = j;
                }
            }
        }
	}
	
	
	//output
	ofstream wormholeOut;
	wormholeOut.open("wormhole.out");
    wormholeOut << solve() << endl;
	wormholeOut.close();
	
	//exit program
	return 0;
}
