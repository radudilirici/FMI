import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class EvidentaAngajati {

    private static final EvidentaAngajati INSTANCE = new EvidentaAngajati();
    private static List<Angajat> angajati;

    public EvidentaAngajati() {
        angajati = new ArrayList<Angajat>();
    }

    public static EvidentaAngajati getInstance() {
        return INSTANCE;
    }

    public void adaugaAngajat(Angajat angajat) {
        try {
            angajati.add(angajat);
        }
        catch (NullPointerException e) {
            System.out.println(e);
        }
    }

    public void stergeAngajat(Angajat angajat) {
        try {
            if (!angajati.remove(angajat)) {
                System.out.println("Angajatul nu exista");
            }
        }
        catch (NullPointerException e) {
            System.out.println(e);
        }
    }

    public Angajat getAngajat(String CNP) {
        for (Angajat a: angajati) {
            if (a.getCNP().equals(CNP)) {
                return a;
            }
        }
        System.out.println("Nu exista angajatul");
        return null;
    }

    public Angajat getAngajat(String nume, String prenume) {
        for (Angajat a: angajati) {
            if (a.getNume().equals(nume) && a.getPrenume().equals(prenume)) {
                return a;
            }
        }
        System.out.println("Nu exista angajatul");
        return null;
    }

    public Angajat getAngajat(Angajat angajat) {
        for (Angajat a: angajati) {
            if (a.equals(angajat)) {
                return a;
            }
        }
        System.out.println("Nu exista angajatul");
        return null;
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder();
        for (Angajat a: angajati) {
            s.append(a.toString()).append("\n");
        }
        return s.toString();
//        return Arrays.toString(angajati.toArray(new Angajat[0]));
    }
}
