/*
 ID: 
 PROG: gift1
 LANG: C++
*/
//NAME          :   
//GROUP         :   Krypton
//LAST MODIFIED :   8 November 2017
//PROBLEM ID    :   USACO GreedyGiftGivers
//DESCRIPTION   :   Finds how much more money each person receives than they
//				:	give. 
//SOURCES/HELP  :   

#include <iostream>
#include <fstream>
using namespace std;

//main program
int main()
{
    //declare variables
    int numPeople, moneyToGiveTotal, numPeopleToGive;
    float moneyToGive, moneyMod;
    string nameTempGiver, nameTempToGive;
    
    //open file and read in input
    ifstream giftin;
    giftin.open("gift1.in");
    giftin >> numPeople;
    
    //declare variables with input variable
    string people[numPeople];
    string peopleToGive[numPeople];
    int peopleMoney[numPeople];
    
    //read in people names and put them into a list
    for (int j = 0; j < numPeople; j++)
    {
        giftin >> people[j];
    }
    
    //set people's money to 0
    for (int i = 0; i < numPeople; i++)
    {
        peopleMoney[i] = 0;
    }
    
    //main part that loops program
    for (int a = numPeople; a--;)
    {
        //reads in who is giving money
        giftin >> nameTempGiver;
        
        //loop the next part for the amount of people
        for (int j = numPeople; j--;)
        {
            //checks to see where the giver is in the list
            if (nameTempGiver == people[j])
            {
                //reads in how much money to give and how many people to divide it among
                giftin >> moneyToGiveTotal >> numPeopleToGive;
                
                //checks if person is giving to no one so program doesn't divide by 0
                if (numPeopleToGive != 0)
                {
                    moneyMod = moneyToGiveTotal % numPeopleToGive;
                }
                else
                {
                    moneyMod = 0;
                }
                
                //calculates how much money giver is giving to each person
                moneyToGive = (moneyToGiveTotal - moneyMod)/numPeopleToGive;
                
                //changes the amount of money the giver by adding remainder and subtracting the amount given
                peopleMoney[j] += moneyMod - moneyToGiveTotal;
                
                //loops to give all money to the amount of people receiving it
                for (int i = numPeopleToGive; i--;)
                {
                    //reads in who is getting the money
                    giftin >> nameTempToGive;
                    
                    //loops to check find the receiver's spot in the money list
                    for (int k = numPeople; k--;)
                    {
                        //checks if the spot in the people list equals the receiver
                        if (nameTempToGive == people[k])
                        {
                            //adds the money given into their money spot in the money list
                            peopleMoney[k] += moneyToGive;
                        }
                    }
                }
            }
        }
    }
    
    //close input file
    giftin.close();
    
    //create output file
    ofstream giftout;
    giftout.open("gift1.out");
    
    //loops for amount of people
    for (int i = 0; i < numPeople; i++)
    {
        //outputs person's name and money with a space between them on one line
        giftout << people[i] << " " << peopleMoney[i] << endl;
    }
    
    //closes output file
    giftout.close();
    
    //exit program
    return 0;
    
}
