import java.io.*;
import java.util.*;
public class haircut {
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(new File("haircut.in"));
        PrintWriter out = new PrintWriter(new FileWriter("haircut.out"));


        int n = in.nextInt();
        long[] orig = new long[n];
        long[] prevHair, currHair;
        boolean[] prevChanged = new boolean[n], currChanged;
        long[] inversions = new long[n];

        for (int i = 0; i < n; i++) {
            orig[i] = in.nextLong();
        }
        //Arrays.fill(hair[0], 0); <-- this happens anyway
        Arrays.fill(prevChanged, true);
        inversions[0] = 0;
        out.println(inversions[0]);
        prevHair = new long[n];

        for (int len = 1; len < n; len++) {
            currChanged = new boolean[n];

            currHair = new long[n];
            //currHair = trim(orig, len);

            int totalChanged = 0;
            int answerChange = 0;
            for (int i = 0; i < n; i++) {
                //trim
                if (orig[i] > len)
                    currHair[i] = len;
                else
                    currHair[i] = orig[i];

                //previous number not changed
                if (prevHair[i] == currHair[i])
                    currChanged[i] = false;
                else {
                    currChanged[i] = true;
                    totalChanged++;
                }

                if (prevChanged[i] && !currChanged[i]) {
                    answerChange += totalChanged;
                }
            }
            inversions[len] = inversions[len-1] + answerChange;
            out.println(inversions[len]);

            prevHair = currHair;
            prevChanged = currChanged;
        }


        in.close();
        out.close();
    }
}
