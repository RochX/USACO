import java.io.*;
import java.util.*;
public class exercise {
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(new File("exercise.in"));
        PrintWriter out = new PrintWriter(new FileWriter("exercise.out"));

        int n = in.nextInt(), m = in.nextInt();
        int sum = 0;

        //assume k could potentially be n^2 at most
        //factor pair of K: K = f1 * f2 and f1 >= f2
        for (int k = 0; k < n*n; k++) {
            //check all of the factor pairs of K, check if K <= N or if f1 + f2 <= N and f1 % f2 != 0
            if (k <= n) {
                sum = (sum + k) % m;
                System.out.println(k);
            }
            else {
                for (int f1 = 1; f1 * f1 <= k; f1++) {
                    if (k % f1 == 0) {
                        int f2 = k / f1;
                        if (f1 + f2 <= n && modGreater(f1, f2) != 0 && (f1 % 2 == 1 || f2 % 2 == 1)) {
                            sum = (sum + k) % m;
                            System.out.println(k);
                            break;
                        }
                    }
                }
            }
        }

        out.println(sum);


        in.close();
        out.close();
    }

    public static int modGreater(int a, int b) {
        if (a > b)
            return a % b;
        else
            return b % a;
    }
}
