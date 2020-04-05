import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class EvidentaPacienti {

    private static final EvidentaPacienti INSTANCE = new EvidentaPacienti();
    private static List<Pacient> pacienti;

    public EvidentaPacienti() {
        pacienti = new ArrayList<Pacient>();
    }

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
        System.out.println("Nu exista Pacientul");
        return null;
    }

    public Pacient getPacient(String nume, String prenume) {
        for (Pacient a: pacienti) {
            if (a.getNume().equals(nume) && a.getPrenume().equals(prenume)) {
                return a;
            }
        }
        System.out.println("Nu exista Pacientul");
        return null;
    }

    public Pacient getPacient(Pacient Pacient) {
        for (Pacient a: pacienti) {
            if (a.equals(Pacient)) {
                return a;
            }
        }
        System.out.println("Nu exista Pacientul");
        return null;
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder();
        for (Pacient a: pacienti) {
            s.append(a.toString()).append("\n");
        }
        return s.toString();
//        return Arrays.toString(pacienti.toArray(new Pacient[0]));
    }
}
