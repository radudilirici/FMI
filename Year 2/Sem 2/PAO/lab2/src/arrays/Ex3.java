package arrays;

import java.util.Arrays;

public class Ex3 {

    public static void main(String[] args) {

        int[] ints = {321, 54, -34};
        int[] intsCopy;
        intsCopy = ints.clone();
        System.out.println(Arrays.toString(intsCopy));

        int[] anotherCopy = new int[5];
        System.arraycopy(ints, 0, anotherCopy, 0, ints.length);  // anotherCopy trebie sa fie initializat
        System.out.println(Arrays.toString(anotherCopy));
    }
}
