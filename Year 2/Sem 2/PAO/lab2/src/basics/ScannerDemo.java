package basics;

import java.util.Scanner;

public class ScannerDemo {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your name");

        String name = scanner.nextLine();
        scanner.close();  // close the resource
        System.out.println("My name is " + name);
    }
}
