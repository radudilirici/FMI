package strings;

public class Main {

    static String membruClasa;

    public static void main(String[] args) {

        System.out.println(membruClasa); // val default pt String e null

        String s1 = "";
        String s2 = "abc"; // string pool
        System.out.println(s2);
        s2.toUpperCase(); // imutabilitate, valoarea referentiata de s2 nu se modifica
        System.out.println(s2); //abc
        s2 = s2.toUpperCase(); // "ABC" -se creeaza un nou obiect String in String pool, referentiat de s2
        System.out.println(s2); // ABC

        String s3 = "cde";
        String s4 = new String("cde"); //alocare explicita de memorie pe heap
        String s5 = "cde"; // referinta catre acelasi obiect "cde" din String pool
        System.out.println(s3 == s4); //false , referinte diferite catre obiecte diferite
        System.out.println(s4 == s5); //false
        System.out.println(s3 == s5); // true
        System.out.println(s3.equals(s4)); // true -> comparare continut
        s4 = s4.intern(); // trecere explicita in String pool
        System.out.println(s3 == s4); //true
        System.out.println(s3 == s5); // true


        String adresa = s1 + s2 + s3 + s4.toUpperCase() + s5.length(); // utilizare ineficienta a memoriei
        StringBuilder sb = new StringBuilder(adresa);
        sb.append(1234); // se returneaza aceeasi instanta de stringbuilder
        System.out.println("string builder: " + sb);

        String s6 = adresa + sb; // concatenare String si StringBuilder
        System.out.println("s6 = " + s6);

        StringBuffer sbf = new StringBuffer(adresa); // conversie de la string la stringbuffer
        StringBuffer sbf1 = new StringBuffer(sb); // conversie de la stringbuilder la stringbuffer
        StringBuilder sb1 = new StringBuilder(sbf); // conversie de la stringbuffer la stringbuilder


    }

}