import java.io.*;
import java.util.*;
public class haircutBruteForce {
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(new File("haircut.in"));
        PrintWriter out = new PrintWriter(new FileWriter("haircut.out"));


        int n = in.nextInt();
        int[] orig = new int[n];

        for (int i = 0; i < n; i++) {
            orig[i] = in.nextInt();
        }

        for (int len = 0; len < n; len++) {
            int[] arr = Arrays.copyOf(orig, n);
            out.println(inversions(arr, len));
        }




        in.close();
        out.close();
    }

    public static int inversions (int[] arr, int len) {
        int total = 0;
        for (int i = 0; i < arr.length; i++) {
            //trim
            if (arr[i] > len)
                arr[i] = len;
            for (int j = i+1; j < arr.length; j++) {
                //trim
                if (arr[j] > len)
                    arr[j] = len;

                //check for inversion
                if (arr[i] > arr[j])
                    total++;
            }
        }

        return total;
    }
}
