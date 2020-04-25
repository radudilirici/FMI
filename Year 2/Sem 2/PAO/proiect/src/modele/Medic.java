package modele;

public class Medic extends Angajat {

    private String specializare;

    public Medic(String CNP, String nume, String prenume, String specializare, Program program) {
        super(CNP, nume, prenume, "medic", program);
        this.specializare = specializare;
    }

    public Medic(String CNP, String nume, String prenume, String specializare, String[] program) {
        super(CNP, nume, prenume, "medic", program);
        this.specializare = specializare;
    }

    public Medic(String CNP, String nume, String prenume, String specializare, String programLuni, String programMarti, String programMiercuri, String programJoi, String programVineri) {
        super(CNP, nume, prenume, "medic", programLuni, programMarti, programMiercuri, programJoi, programVineri);
        this.specializare = specializare;
    }

    @Override
    public String toString() {
        return super.toString() +
                ", specializare: " + this.specializare;
    }
}
