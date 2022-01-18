/*
ID: xavierw1
PROG: stamps
LANG: JAVA
 */
import java.io.*;
import java.util.*;
public class stamps
{
    public static void main(String[] args) throws FileNotFoundException
    {
        //setup
        Scanner in = new Scanner(new File("stamps.in"));
        PrintWriter out = new PrintWriter("stamps.out");
        int k = in.nextInt();
        int n = in.nextInt();
        int[] stamps = new int[n];
        int maxStampValue = -1;

        //input and get our max stamp value
        for (int i = 0; i < n; i++)
        {
            stamps[i] = in.nextInt();
            maxStampValue = Math.max(maxStampValue, stamps[i]);
        }


        //stores what postage can be made
            //index = postage value
            //int at index = number of stamps needed to reach this postage value
        int[] postage = new int[maxStampValue * k + 2]; //we cannot make postage for maxStampValue * k + 1 since we only have k stamps
        Arrays.fill(postage, Integer.MAX_VALUE); //value of Integer.MAX_VALUE --> not assigned --> no combination that works
        postage[0] = 0; //trivial case; no stamps needed for zero postage

        //find the rest of the valid postage by adding each stamp value to each postage which hasn't used the maximum number of stamps
        int currentNumUsed;
        for (int postVal = 0; postVal < postage.length; postVal++)
        {
            for (int stamp : stamps)
            {

                currentNumUsed = postage[postVal];
                if (currentNumUsed < k) //is it possible to add more stamps from this postage value?
                {
                    //if so add our new stamp
                    assignPostage(postage, postVal+stamp, currentNumUsed+1);
                }
            }
        }
        //we should have gotten all valid postage values after this point

        //now loop to find the first invalid postage value (postage[i] == Integer.MAX_VALUE)
        for (int i = 0; i < postage.length; i++)
        {
            if (postage[i] == Integer.MAX_VALUE)
            {
                //therefore all of the previous ones were valid and so we can make postage from values 1 thru i-1,
                    //which is what the problem asks for
                out.println(i-1);
                break;
            }
        }

        //exit properly
        in.close();
        out.close();
    }

    //adds our new stamp the way we want to
    public static void assignPostage(int[] postage, int index, int newVal)
    {
        //we want to take the minimum value
            //this equates to using the least number of stamps possible to this postage value
        postage[index] = Math.min(postage[index], newVal);
    }
}
