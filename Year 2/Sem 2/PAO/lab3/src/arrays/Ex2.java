package arrays;

import java.util.Arrays;

public class Ex2 {

    public static void main(String[] args) {

        char[] chars = {'j', 'a', 'v', 'a', 'a'};
        for (char c : chars) {
            System.out.print(c);
        }
        System.out.println();
        System.out.println(chars);  // caz particular. in general imi scire tipul de date @ adresa
        System.out.println();

        int[] ints = {21, 34, 524, -12};
        System.out.println(Arrays.toString(ints));  // Ctrl + click pt documentatie
        System.out.println();

        int[][] intMatrix = new int[3][3];  // merge si int intMatrix[][], dar e bad practice
        intMatrix[0][1] = 1;
        for (int[] i : intMatrix) {
            for (int j : i) {
                System.out.print(j + " ");
            }
            System.out.println();
        }
        System.out.println();

        char[][] multiChars = {{'h', 'e', 'l', 'l', 'o'}, {'f', 'r', 'o', 'm'}, {'j', 'a', 'v', 'a'}};  // nr variabil de coloane
        for (char[] c : multiChars) {
            System.out.println(Arrays.toString(c));
        }
        System.out.println();

        int[][] multiInts = new int[3][];
        multiInts[0] = new int[2];
        multiInts[0][0] = 1;
        multiInts[0][1] = 2;
        multiInts[1] = new int[]{12, 24, 76};
        multiInts[2] = new int[4];
        displayArrayValues(multiInts);
        System.out.println();
    }

    private static void displayArrayValues(int[][] multiInts) {  // static ca sa nu fie nevoie sa cream o instanta
        for (int[] i :multiInts) {
            System.out.println(Arrays.toString(i));
        }
    }
}
