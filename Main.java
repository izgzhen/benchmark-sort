import java.util.Arrays;
import java.util.Random;
import java.security.SecureRandom;

enum Algo {
    ARRAYS_SORT
}

public class Main {
    public static void main(String[] args) {
        String algoOpt = args[0];
        Algo algo = null;
        if (algoOpt.equals("arrays-sort")) {
            algo = Algo.ARRAYS_SORT;
        } else {
            System.err.println("Invalid algo_opt: " + algoOpt);
            System.exit(-1);
        }
        int interval = Integer.valueOf(args[1]);
        int maxN = Integer.valueOf(args[2]);
        Random rd = new SecureRandom();
        for (int n = interval; n < maxN; n += interval) {
            int[] arr = new int[n];
            for (int i = 0; i < arr.length; i++) {
                arr[i] = rd.nextInt(Integer.MAX_VALUE);
            }

            long start_ns = System.nanoTime();
            switch (algo) {
                case ARRAYS_SORT:
                    Arrays.sort(arr);
                    break;
                default:
                    System.err.println("Sort not implemented: " + algo);
                    System.exit(-1);
            }
            System.out.println(n + " " + (System.nanoTime() - start_ns) / 1000.0);

            // sanity check
            for (int i = 0; i < arr.length - 1; i++) {
                assert(arr[i] <= arr[i+1]);
            }
        }
    }
}