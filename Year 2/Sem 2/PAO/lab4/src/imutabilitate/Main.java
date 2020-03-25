package imutabilitate;

public class Main {

    public static void main(String[] args) {

        Adresa domiciliu = new Adresa("Timisoara", "4A");
        Persoana persoana = new Persoana(1, "Teo", domiciliu);

        // String este clasa imutabila, deci numele nu se modifica
        System.out.println(persoana.getNume().toUpperCase());
        System.out.println(persoana);

        /*
        incercare alterare valoare membru (clasa mutabila) prin modificarea valorilor
        instantei date ca parametru la instantiere clasei imutabile
         */
        String stradaUppercase = domiciliu.getStrada().toUpperCase();
        domiciliu.setStrada(stradaUppercase);
        System.out.println(persoana);

        // incercare alterare continut prin intermediul get-erului
        Adresa adresaDomiciliu = persoana.getAdresa();
        String strada = adresaDomiciliu.getStrada();
        adresaDomiciliu.setStrada(strada.toUpperCase());
        System.out.println(persoana);
    }
}