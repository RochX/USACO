/*
ID: xavierw1
PROG: concom
LANG: JAVA
 */
//NAME          : Xavier Silva
//GROUP         : AdvCS
//LAST MODIFIED : 1-21-20
//PROBLEM ID    : USACO Controlling Companies
//DESCRIPTION   : Figure out which companies other companies control
//SOURCES/HELP  :
import java.io.*;
import java.util.*;

public class concom {
    static final int MAX_COMP = 100;
    public static void main(String[] args) throws IOException
    {
        //variables and objects
        Scanner in = new Scanner(new File("concom.in"));
        PrintWriter out = new PrintWriter(new FileWriter("concom.out"));
        int numInputs = in.nextInt();
        int[][] percents = new int[MAX_COMP][MAX_COMP];
        boolean[][] controls = new boolean[MAX_COMP][MAX_COMP];
        ArrayList<String> outputs = new ArrayList<>();

        //input
        for (int i = 0; i < numInputs; i++)
        {
            int compA = in.nextInt()-1, compB = in.nextInt()-1, per = in.nextInt();
            percents[compA][compB] = per;

            //set initial state
            if (per > 50 && compA != compB)
            {
                controls[compA][compB] = true;
                outputs.add((compA+1) + " " + (compB+1));
            }
        }

        //loop a bunch to make it work
        for (int a = 0; a < MAX_COMP; a++)
        {
            boolean loop = false;

            //loop through every company
            for (int i = 0; i < MAX_COMP; i++)
            {
                //loop through every company
                for (int j = 0; j < MAX_COMP; j++)
                {
                    //if a company doesn't control another and isn't itself see if company i controls company j
                    if (!controls[i][j] && i != j)
                    {
                        //keep track of the total
                        int total = percents[i][j];

                        //look at the other companies i controls
                        for (int k = 0; k < MAX_COMP; k++)
                        {
                            //if i controls company k add the amount that k controls j to the total
                            if (controls[i][k])
                            {
                                total += percents[k][j];
                            }
                        }

                        //check if the total is over 50
                        if (total > 50)
                        {
                            //if so add it
                            controls[i][j] = true;
                            outputs.add((i + 1) + " " + (j + 1));
                        }

                        loop = true;
                    }
                }
            }

            //exit loop if no updates happened
            if (!loop)
                break;
        }

        //sort the outputs
        outputs.sort(new Comparator<String>() {
            @Override
            public int compare(String o1, String o2) {
                int i1, i2;
                i1 = Integer.parseInt(o1.substring(0,o1.indexOf(' ')));
                i2 = Integer.parseInt(o2.substring(0,o2.indexOf(' ')));
                if (i1 == i2)
                {
                    i1 = Integer.parseInt(o1.substring(o1.lastIndexOf(' ')+1));
                    i2 = Integer.parseInt(o2.substring(o2.lastIndexOf(' ')+1));
                }
                return Integer.compare(i1,i2);
            }
        });

        //output and exit
        for (int i = 0; i < outputs.size(); i++)
        {
            out.println(outputs.get(i));
        }
        out.close();
        in.close();
    }
}
