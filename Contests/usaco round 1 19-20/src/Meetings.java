//Xavier Silva
//DM
//USACO 19-20 Round 1
//P2 Meetings
import java.io.*;
import java.util.*;
public class Meetings {
    //global vars
    static final double TIME = 0.5, TOL = 0.0001, MAX = Math.pow(10,9);
    static int loc, currB = 0, total = 0, meetings = 0;

    //main
    public static void main(String[] args) throws IOException
    {
        //vars, objects, and input
        BufferedReader in = new BufferedReader(new FileReader("meetings.in"));
        //Scanner scan = new Scanner(new File("meetings.in"));
        PrintWriter out = new PrintWriter(new FileWriter("meetings.out"));
        String[] inp = in.readLine().split("\\s+");
        int numCow = Integer.parseInt(inp[0]);
        loc = Integer.parseInt(inp[1]);
        ArrayList<Cow> cows = new ArrayList<>();

        //input the properties of cows
        for (int i = 0; i < numCow; i++) {
            inp = in.readLine().split("\\s+");
            int w = Integer.parseInt(inp[0]);
            int p = Integer.parseInt(inp[1]);
            int v = Integer.parseInt(inp[2]);
            total += w;
            cows.add(new Cow(w,p,v));
        }

        //sort the cows by position
        cows.sort(new Comparator<Cow>() {
            @Override
            public int compare(Cow o1, Cow o2) {
                return Double.compare(o1.pos,o2.pos);
            }
        });

        //update cows positions until 50% or greater of the weights are in the barns
        while (currB < total/2.0)
            update(cows);

        //output
        out.println(meetings);

        //exit
        in.close();
        //scan.close();
        out.close();
    }

    //update the positions
    public static void update(ArrayList<Cow> cows)
    {
        //find how much we can "fast forward" through time
        //do this by finding the minimum distance between any two objects (cows and barn)
        int fastForward = 1;
        double minDistance = cows.get(0).pos, currDistance;
        Cow c1, c2;
        for (int i = 0; i < cows.size()-1; i++)
        {
            c1 = cows.get(i);
            c2 = cows.get(i+1);
            currDistance = Math.abs(c2.pos - c1.pos);
            //do not change minDistance if: cows are chasing, or occupy same space with opposing velocities
            boolean chasing = c1.vel/c2.vel > 0;
            boolean samePosOpVel = currDistance < TOL && c1.vel < 0 && c2.vel > 0;
            if (!(chasing || samePosOpVel)) {
                minDistance = Math.min(minDistance, currDistance);
            }
        }
        minDistance = Math.min(minDistance, loc-cows.get(cows.size()-1).pos);

        //be sure the fastForward var isn't 0
        fastForward = (int) minDistance;
        if (fastForward < 1)
            fastForward = 1;


        //change positions
        for (Cow cow : cows)
        {
            cow.pos += cow.vel*TIME*fastForward;
        }

        //check for equal (bounce)
        for (int i = 0; i < cows.size()-1; i++)
        {
            Cow curr1 = cows.get(i);
            Cow curr2 = cows.get(i+1);
            if (!curr1.done && !curr2.done && Math.abs(curr1.pos-curr2.pos) < TOL)
            {
                curr1.vel *= -1;
                curr2.vel *= -1;
                meetings++;
            }
        }

        //check for farm
        for (int i = 0; i < cows.size(); i++)
        {
            Cow cow = cows.get(i);
            //is cow in a barn
            if (inBarn(cow))
            {
                //if so add its weight and remove it from list
                currB += cow.weight;
                cows.remove(i);
                i--;
            }
        }
    }

    //see if cow is in barn
    public static boolean inBarn(Cow cow)
    {
        return Math.abs(cow.pos-loc) < TOL || Math.abs(cow.pos-0) < TOL;
    }
}

//cow class
class Cow
{
    int weight, vel;
    double pos;
    boolean done;

    public Cow(int w, double p, int v)
    {
        weight = w;
        pos = p;
        vel = v;
        done = false;
    }
}
