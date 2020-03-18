package basics;

import java.util.Scanner;

public class CitireNumar {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a letter");

        char letter = scanner.nextLine().charAt(0);

        switch (letter) {
            case 'a':
            case 'e':
                System.out.println("Vocala");
                break;
            default:
                break;
        }

    }
}
