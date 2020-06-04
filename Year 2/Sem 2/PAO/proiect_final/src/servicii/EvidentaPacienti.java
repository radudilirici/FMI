package servicii;

import modele.Pacient;

import java.util.ArrayList;
import java.util.List;

import static servicii.CSVHandler.citesteCSV;

public class EvidentaPacienti {

    private static final EvidentaPacienti INSTANCE;
    private static List<Pacient> pacienti;

    static {
        INSTANCE = new EvidentaPacienti();
        pacienti = new ArrayList<>();
    }

    private EvidentaPacienti() {}

    public static EvidentaPacienti getInstance() {
        return INSTANCE;
    }

    public void adaugaPacient(Pacient Pacient) {
        try {
            pacienti.add(Pacient);
        }
        catch (NullPointerException e) {
            System.out.println(e);
        }
    }

    public void adaugaPacientiFisier(String path) {
        List<String[]> csv = citesteCSV(path);
        for (String[] p: csv) {
            if (p.length != 3) {
                continue;
            }
            this.adaugaPacient(new Pacient(p[0], p[1], p[2]));
        }
    }

    public void stergePacient(Pacient Pacient) {
        try {
            if (!pacienti.remove(Pacient)) {
                System.out.println("Pacientul nu exista");
            }
        }
        catch (NullPointerException e) {
            System.out.println(e);
        }
    }

    public Pacient getPacient(String CNP) {
        for (Pacient a: pacienti) {
            if (a.getCNP().equals(CNP)) {
                return a;
            }
        }
        System.out.println("Pacientul nu exista");
        return null;
    }

    public Pacient getPacient(String nume, String prenume) {
        for (Pacient a: pacienti) {
            if (a.getNume().equals(nume) && a.getPrenume().equals(prenume)) {
                return a;
            }
        }
        System.out.println("Pacientul nu exista");
        return null;
    }

    public Pacient getPacient(Pacient Pacient) {
        for (modele.Pacient a: pacienti) {
            if (a.equals(Pacient)) {
                return a;
            }
        }
        System.out.println("Pacientul nu exista");
        return null;
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder();
        for (Pacient a: pacienti) {
            s.append(a.toString()).append("\n");
        }
        return s.toString();
    }
}
