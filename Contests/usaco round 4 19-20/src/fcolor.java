import java.io.*;
import java.util.*;
public class fcolor {
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(new File("fcolor.in"));
        PrintWriter out = new PrintWriter(new FileWriter("fcolor.out"));

        int n = in.nextInt(), m = in.nextInt();

        int[] color = new int[n];
        int[] colorPairings = new int[n];
        Arrays.fill(colorPairings, -1);
        ArrayList<ArrayList<Integer>> pointsTo = new ArrayList<>();
        ArrayList<ArrayList<Integer>> pointsFrom = new ArrayList<>();


        for (int i = 0; i < n; i++) {
            color[i] = i;
            pointsTo.add(new ArrayList<>());
            pointsFrom.add(new ArrayList<>());
        }

        int start, end;
        for (int i = 0; i < m; i++) {
            start = in.nextInt()-1;
            end = in.nextInt()-1;

            pointsTo.get(start).add(end);
            pointsFrom.get(end).add(start);
        }

        Queue<Integer> toCheck = new LinkedList<>();
        //look at when two or more point to the same point
        for (int i = 0; i < n; i++) {
            ArrayList<Integer> curr = pointsFrom.get(i);
            int pointColor = color[i];
            if (curr.size() >= 2) {
                //update the colors of each of the individual points
                int minColor = minColor(curr, color);
                for (int j = 0; j < curr.size(); j++) {
                    color[curr.get(j)] = minColor;
                    toCheck.add(curr.get(j));
                }
                colorPairings[pointColor] = minColor;
            }
        }
        
        //loop through all points already done, look at what color its previous points point to, assign its color based on the color pairing
        boolean[] done = new boolean[n];
        while (toCheck.size() > 0) {
            int currPoint = toCheck.remove();

            if (done[currPoint])
                continue;

            done[currPoint] = true;
            ArrayList<Integer> curr = pointsFrom.get(currPoint);

            for (int point : curr) {
                color[point] = colorPairings[color[currPoint]];
                toCheck.add(point);
            }
        }

        for (int i = 0; i < color.length; i++) {
            out.println(color[i]+1);
        }

        in.close();
        out.close();
    }

    public static int minColor(ArrayList<Integer> arr, int[] color) {
        int min = color.length;
        for (int a : arr) {
            if (color[a] < min)
                min = color[a];
        }
        return min;
    }
}
