public class Angajat extends Persoana{

    private String profesie;
    private Program program;

    public Angajat(String CNP, String nume, String prenume, String profesie, Program program) {
        super(CNP, nume, prenume);
        this.profesie = profesie;
        this.program = new Program(program);
    }

    public Angajat(String CNP, String nume, String prenume, String profesie, String[] program) {
        super(CNP, nume, prenume);
        this.profesie = profesie;
        this.program = new Program(program);
    }

    public Angajat(String CNP, String nume, String prenume, String profesie, String programLuni, String programMarti, String programMiercuri, String programJoi, String programVineri) {
        super(CNP, nume, prenume);
        this.profesie = profesie;
        this.program = new Program(programLuni, programMarti, programMiercuri, programJoi, programVineri);
    }

    public void setProfesie(String profesie) {
        this.profesie = profesie;
    }

    public void setProgram(String[] program) {
        this.program.setProgram(program);
    }

    public void setProgramLuni(String programLuni) {
        this.program.setProgramLuni(programLuni);
    }

    public void setProgramMarti(String programMarti) {
        this.program.setProgramLuni(programMarti);
    }

    public void setProgramMiercuri(String programMiercuri) {
        this.program.setProgramLuni(programMiercuri);
    }

    public void setProgramJoi(String programJoi) {
        this.program.setProgramLuni(programJoi);
    }

    public void setProgramVineri(String programVineri) {
        this.program.setProgramLuni(programVineri);
    }

    public String getProfesie() {
        return profesie;
    }

    public Program getProgram() {
        return program;
    }

    @Override
    public String toString() {
        return super.toString() +
                ", profesie: " + this.profesie +
                ", " + this.program;
    }
}
