/*
 ID: 
 PROG: friday
 LANG: JAVA
*/ 
//NAME          :   
//GROUP         :   APCS
//LAST MODIFIED :   12 October 2018
//PROBLEM ID    :   USACO Friday
//DESCRIPTION   :   Given an integer N, find how many of each day of the week lands a 13th over the next N years, starting on January 1, 1900 
//SOURCES/HELP  :   
import java.io.*;
import java.util.*;
class friday 
{
  public static void main(String[] args) throws IOException
  {
    //file input
    BufferedReader in = new BufferedReader(new FileReader("friday.in"));

    //file output
    PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("friday.out")));

    //declare variables
    final int DAYS_IN_WEEK = 7, START_YEAR = 1900, NUM_MONTHS = 12;
    final int[] MONTH_LENGTHS = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int numYears = Integer.parseInt(in.readLine()), currYear, dayOfWeek = 1, numDays;
    int[] days = new int[DAYS_IN_WEEK];
    boolean isLeapYear;

    //loop for the number of years needed
    for (int i = 0; i < numYears; i++)
    {
      //set which year is being looped through and if its a leap year
      currYear = START_YEAR+i;
      isLeapYear = (currYear % 4 == 0 && currYear % 100 != 0) || currYear % 400 == 0;

      //loop through each month of the year
      for (int k = 0; k < NUM_MONTHS; k++)
      {
        //set how many days are in the month
        numDays = MONTH_LENGTHS[k];
        
        //set the days to the correct amount if the month is feburary and if its a leap year
        if (isLeapYear && k == 1)
        {
          numDays = 29;
        }
        //loop through each day
        for (int j = 0; j < numDays; j++)
        {
          //if the day is a 13th then increment the count of how many 13s there are
          if (j == 13)
          {
            days[dayOfWeek]++;
          }

          //move to next day of the week
          dayOfWeek = (dayOfWeek+1) % DAYS_IN_WEEK;
        }
      }
    }

    //output
    for (int i = 0; i < DAYS_IN_WEEK-1; i++)
    {
      out.print(days[i] + " ");
    }
    out.println(days[DAYS_IN_WEEK-1]);

    //exit program
    in.close();
    out.close();
    return;
  }
}