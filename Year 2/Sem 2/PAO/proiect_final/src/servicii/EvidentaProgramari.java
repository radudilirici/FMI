package servicii;

import modele.Medic;
import modele.Pacient;
import modele.Programare;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.Date;
import java.util.List;

import static servicii.CSVHandler.citesteCSV;

public final class EvidentaProgramari {
    // clasa Singleton pentru ca vrem sa avem toate programarile in acelasi loc
    private static final EvidentaProgramari INSTANCE;
    private static List<Programare> programari;

    static {
        INSTANCE = new EvidentaProgramari();
        programari = new ArrayList<>();
    }

    private EvidentaProgramari() {}

    public static EvidentaProgramari getInstance() {
        return INSTANCE;
    }

    public void adaugaProgramare(Programare programare) {
        try {
            programari.add(programare);
            programari.sort(Comparator.comparing(Programare::getData));
        }
        catch (NullPointerException e) {
            System.out.println(e);
        }
    }

    public void adaugaProgramariFisier(String path) {
        List<String[]> csv = citesteCSV(path);
        for (String[] p: csv) {
            if (p.length != 3) {
                continue;
            }
            this.adaugaProgramare(new Programare(p[0], p[1], p[2]));
        }
    }

    public void stergeProgramare(Programare programare) {
        try {
            if (programari.remove(programare)) {
                System.out.println("Stergere " + programare);
            } else {
                System.out.println("Programarea nu exista");
            }
        }
        catch (NullPointerException e) {
            System.out.println(e);
        }
    }

    public void stergeProgramariInainteDe(Date data) {
        try {
            if (programari.size() == 0) {
                return;
            }
            while (programari.get(0).comparaData(data) > 0) {
                Programare p = programari.get(0);
                programari.remove(0);
                System.out.println("Stergere " + p);
            }
        }
        catch (NullPointerException e) {
            System.out.println(e);
        }
    }

    public void stergeProgramariInainteDe(String data) {
        try {
            if (programari.size() == 0) {
                return;
            }
            while (programari.get(0).comparaData(data) < 0) {
                Programare p = programari.get(0);
                programari.remove(0);
                System.out.println("Stergere " + p);
            }
        }
        catch (NullPointerException e) {
            System.out.println(e);
        }
    }

    public Programare[] programariMedic(Medic medic) {
        List<Programare> lProgramari = new ArrayList<>();
        for (Programare p: programari) {
            if (medic.equals(p.getMedic())) {
                lProgramari.add(p);
            }
        }
        return lProgramari.toArray(new Programare[0]);
    }

    public Programare[] programariPacient(Pacient pacient) {
        List<Programare> lProgramari = new ArrayList<>();
        for (Programare p: programari) {
            if (pacient.equals(p.getPacient())) {
                lProgramari.add(p);
            }
        }
        return lProgramari.toArray(new Programare[0]);
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder();
        for (Programare a: programari) {
            s.append(a.toString()).append("\n");
        }
        return s.toString();
    }
}
