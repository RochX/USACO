//Xavier Silva
//AdvCS
//USACO Round 3 19-20
//P2 Help Yourself
import java.io.*;
import java.util.*;
public class help
{
    public static void main(String[] args) throws IOException
    {
        Scanner in = new Scanner(new File("help.in"));
        PrintWriter out = new PrintWriter(new FileWriter("help.out"));

        int numSeg = in.nextInt();
        Seg[] segments = new Seg[numSeg];

        for (int i = 0; i < segments.length; i++)
        {
            segments[i] = new Seg(in.nextInt(),in.nextInt());
        }
        //System.out.println(Arrays.toString(segments));

        Arrays.sort(segments, new Comparator<Seg>() {
            @Override
            public int compare(Seg o1, Seg o2) {
                int startComp = Integer.compare(o1.left,o2.left);
                int endComp = Integer.compare(o1.right,o2.right);
                if (startComp == 0)
                    return endComp;
                else
                    return startComp;
            }
        });

        //brute force
        int complex = 0;
        for (int i = 1; i < Math.pow(2,numSeg); i++)
        {
            StringBuilder binary = new StringBuilder(Integer.toBinaryString(i));
            while (binary.length() < numSeg)
                binary.insert(0,0);

            ArrayList<Seg> list = new ArrayList<>();

            for (int j = 0; j < binary.length(); j++)
            {
                if (binary.charAt(j) == '1')
                {
                    if (list.size() == 0)
                        list.add(new Seg(segments[j].left,segments[j].right));
                    Seg curr = segments[j];
                    for (int k = 0; k < list.size(); k++)
                    {
                        Seg a = list.get(k);
                        boolean overlap = false;
                        if (curr.left <= a.left && a.left <= curr.right)
                        {
                            a.left = curr.left;
                            overlap = true;
                        }
                        if (curr.left <= a.right && a.right <= curr.right)
                        {
                            a.right = curr.right;
                            overlap = true;
                        }
                        if (a.left <= curr.left && curr.right <= a.right)
                        {
                            overlap = true;
                        }

                        if (!overlap && !list.contains(curr))
                            list.add(new Seg(curr.left,curr.right));
                    }
                }
            }

            complex += list.size();
            complex = complex % (int)(Math.pow(10,9) + 7);
        }

        out.println(complex);

        in.close();
        out.close();
    }
}

class Seg
{
    int left, right;

    public Seg(int l, int r)
    {
        left = l;
        right = r;
    }

    @Override
    public String toString() {
        return left + "-" + right;
    }

    public boolean equals(Seg s)
    {
        return toString().equals(s.toString());
    }
}