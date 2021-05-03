/*
ID: xavierw1
PROG: fracdec
LANG: JAVA
 */
//NAME          : Xavier Silva
//GROUP         : AdvCS
//LAST MODIFIED : 1-31-20
//PROBLEM ID    : USACO Fractions to Decimals
//DESCRIPTION   : Converts fractions to decimals with repeating decimals notated
//SOURCES/HELP  : https://en.wikipedia.org/wiki/Long_division
import java.io.*;
import java.util.*;
public class fracdec
{
    public static void main(String[] args) throws IOException
    {
        //vars and objects
        Scanner in = new Scanner(new File("fracdec.in"));
        PrintWriter out = new PrintWriter(new FileWriter("fracdec.out"));
        //input
        int num = in.nextInt(), den = in.nextInt();
        int lenRepeat = lenRepeat(den), intPart;
        ArrayList<Integer> remainders = new ArrayList<>(5000);
        StringBuilder res = new StringBuilder("");

        //get the integer part first
        intPart = num/den;

        //long division
        for (int i = 0; true; i++)
        {
            //add digits
            res.append(intPart);

            //gives us remainder and stores it
            num = num - (intPart * den);
            remainders.add(num);

            //if remainder is zero then exit loop
            if (num == 0)
                break;

            //check for repeating decimal
            if (i-lenRepeat >= 0 && remainders.get(i-lenRepeat).equals(remainders.get(i)))
            {
                //insert the parentheses and exit loop
                res.insert(res.length()-lenRepeat,"(");
                res.append(")");
                break;
            }

            //multiply by 10 and find new integer part
            num *= 10;
            intPart = num/den;

            //insert decimal point
            if (i == 0)
                res.append(".");
        }

        //add decimal if answer is an integer
        if (!res.toString().contains("."))
            res.append(".0");

        //output
        int lines = res.length() / 76;
        int i = 0;
        for (; i / 76 < lines; i += 76)
        {
            out.println(res.subSequence(i,i+76));
        }
        out.println(res.substring(i));

        //exit program
        out.close();
        in.close();
    }

    //finds how long the repeating decimal is (calculates it for 1/N but it is the same no matter the numerator)
    static int lenRepeat(int den)
    {
        //find a remainder far enough into the decimal
        int currRem = 1;
        for (int i = 0; i < den+1; i++)
        {
            currRem = (currRem * 10) % den;
        }

        //count how many remainders it takes for one to repeat
        int rem = currRem, count = 0;
        do
        {
            rem = (rem * 10) % den;
            count++;
        } while (currRem != rem);

        //return the count
        return count;
    }
}
