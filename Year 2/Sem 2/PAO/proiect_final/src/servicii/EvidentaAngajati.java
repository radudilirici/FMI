package servicii;

import modele.Angajat;
import modele.Medic;

import java.util.ArrayList;
import java.util.List;

import static servicii.CSVHandler.citesteCSV;

public class EvidentaAngajati {

    private static final EvidentaAngajati INSTANCE;
    private static List<Angajat> angajati;

    static {
        INSTANCE = new EvidentaAngajati();
        angajati = new ArrayList<>();
    }

    private EvidentaAngajati() {}

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

    public void adaugaAngajatiFisier(String path, boolean medic) {
        List<String[]> csv = citesteCSV(path);
        for (String[] a: csv) {
            if (a.length != 9) {
                continue;
            }
            if (medic) {
                this.adaugaAngajat(new Medic(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]));
            } else {
                this.adaugaAngajat(new Angajat(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]));
            }

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
        System.out.println("Angajatul nu exista");
        return null;
    }

    public Angajat getAngajat(String nume, String prenume) {
        for (Angajat a: angajati) {
            if (a.getNume().equals(nume) && a.getPrenume().equals(prenume)) {
                return a;
            }
        }
        System.out.println("Angajatul nu exista");
        return null;
    }

    public Angajat getAngajat(Angajat angajat) {
        for (Angajat a: angajati) {
            if (a.equals(angajat)) {
                return a;
            }
        }
        System.out.println("Angajatul nu exista");
        return null;
    }

    public boolean existaAngajat(String CNP) {
        for (Angajat a: angajati) {
            if (a.getCNP().equals(CNP)) {
                return true;
            }
        }
        return false;
    }

    public void stergeAngajat(String CNP) {
        angajati.remove(getAngajat(CNP));
    }

    public void actualizeazaAngajat(Angajat angajat) {
        stergeAngajat(angajat.getCNP());
        adaugaAngajat(angajat);
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder();
        for (Angajat a: angajati) {
            s.append(a.toString()).append("\n");
        }
        return s.toString();
    }
}
