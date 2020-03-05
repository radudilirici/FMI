package basics;

public class Operators {
    public static void main(String[] args) {
        boolean b1 = true;
        boolean b2 = (b1 = false);
        System.out.println(b2);  // nu e true mereu...

        int i = 0;
        while (b1 = false) {  // nu ruleaza la infinit... expresia returneaza ce a atribuit
            System.out.println("...");
            i++;
            if (i > 10) {
                break;
            }
        }
    }
}
