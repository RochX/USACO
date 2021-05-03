import java.io.*;
import java.util.*;

public class tester {
    public static void main(String[] args) throws IOException {
        PrintWriter tester = new PrintWriter(new FileWriter("haircut.in"));

        Random rand = new Random();
        int number = 100000;

        tester.println(number);

        for (int i = 0; i < number; i++) {
            tester.print(rand.nextInt(number) + " ");
        }
        tester.println();

        tester.close();
    }
}
