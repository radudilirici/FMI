package arrays;

public class Ex1 {
    public static void main(String[] args) {

        byte[] bytes;
        bytes = new byte[5];
        bytes[0] = -128;
        bytes[4] = 127;
        for (byte b : bytes) {
            System.out.println(b);
        }
        System.out.println();

        short[] shortArray;
        boolean[] boolArrat = new boolean[4];

        int[] ints = new int[]{1, 2, -4, 10};
        for (int i : ints) {
            System.out.println(i);
        }
        System.out.println();

        int[] anotherInts = {0, 213, 532, 65};
        for (int i : anotherInts) {
            System.out.println(i);
        }
    }
}
