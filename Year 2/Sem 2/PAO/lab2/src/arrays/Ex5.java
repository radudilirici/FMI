package arrays;

import java.util.Arrays;

public class Ex5 {

    public static void main(String[] args) {

        int[] ints = {2, 5, 7, 0, 22, 55, -234, 77};
        System.out.println(Arrays.binarySearch(ints, 55));  // s-a nimerit ca returneaza bine
                                                                 // el crede ca e sortat si asa si opereaza pe el
        System.out.println(Arrays.binarySearch(ints, -234));  // pe asta nu il mai gaseste
        System.out.println(Arrays.binarySearch(ints, 555));  // returneaza -9 pt ca ar trebuin sa fie pe pozitia 9
        Arrays.sort(ints);
        System.out.println(Arrays.toString(ints));
        System.out.println(Arrays.binarySearch(ints, 77));
    }
}
