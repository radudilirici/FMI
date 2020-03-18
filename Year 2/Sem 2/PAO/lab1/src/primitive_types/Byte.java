package primitive_types;

public class Byte {
    static byte defaultValue;

    public static void main(String[] args) {
        // byte -> 8 bits   de la -128 la 127
        byte b1 = -128;  // trebuie neaparat initializate variabilele locale
        System.out.println(--b1);

        byte b2 = (byte)12_345;  // daca nu fac conversie explicita nu compileaza
        System.out.println(b2);  // _ nu face nimic in numere. e doar ca sa ma ajute pe mine

        System.out.println(defaultValue);  // valoarea default e 0
    }
}
