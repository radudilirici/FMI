package modele;

public class Program {

    private String programLuni;
    private String programMarti;
    private String programMiercuri;
    private String programJoi;
    private String programVineri;

    public Program(String programLuni, String programMarti, String programMiercuri, String programJoi, String programVineri) {
        this.programLuni = programLuni;
        this.programMarti = programMarti;
        this.programMiercuri = programMiercuri;
        this.programJoi = programJoi;
        this.programVineri = programVineri;
    }

    public Program(String[] program) {
        if (program.length != 5) {
            System.out.println("Argument incorect");
            return;
        }
        this.programLuni = program[0];
        this.programMarti = program[1];
        this.programMiercuri = program[2];
        this.programJoi = program[3];
        this.programVineri = program[4];
    }

    public Program(Program program) {
        this.programLuni = program.getProgramLuni();
        this.programMarti = program.getProgramMarti();
        this.programMiercuri = program.getProgramMiercuri();
        this.programJoi = program.getProgramJoi();
        this.programVineri = program.getProgramVineri();
    }

    public void setProgram(String programLuni, String programMarti, String programMiercuri, String programJoi, String programVineri) {
        this.programLuni = programLuni;
        this.programMarti = programMarti;
        this.programMiercuri = programMiercuri;
        this.programJoi = programJoi;
        this.programVineri = programVineri;
    }

    public void setProgram(String[] program) {
        if (program.length != 5) {
            System.out.println("Argument incorect");
            return;
        }
        this.programLuni = program[0];
        this.programMarti = program[1];
        this.programMiercuri = program[2];
        this.programJoi = program[3];
        this.programVineri = program[4];
    }

    public void setProgram(Program program) {
        this.programLuni = program.getProgramLuni();
        this.programMarti = program.getProgramMarti();
        this.programMiercuri = program.getProgramMiercuri();
        this.programJoi = program.getProgramJoi();
        this.programVineri = program.getProgramVineri();
    }

    public void setProgramLuni(String programLuni) {
        this.programLuni = programLuni;
    }

    public void setProgramMarti(String programMarti) {
        this.programMarti = programMarti;
    }

    public void setProgramMiercuri(String programMiercuri) {
        this.programMiercuri = programMiercuri;
    }

    public void setProgramJoi(String programJoi) {
        this.programJoi = programJoi;
    }

    public void setProgramVineri(String programVineri) {
        this.programVineri = programVineri;
    }

    public String[] getProgram() {
        return new String[]{programLuni, programMarti, programMiercuri, programJoi, programVineri};
    }

    public String getProgramLuni() {
        return programLuni;
    }

    public String getProgramMarti() {
        return programMarti;
    }

    public String getProgramMiercuri() {
        return programMiercuri;
    }

    public String getProgramJoi() {
        return programJoi;
    }

    public String getProgramVineri() {
        return programVineri;
    }

    @Override
    public String toString() {
        return "program: {" +
                "luni: " + programLuni +
                ", marti: " + programMarti +
                ", miercuri: " + programMiercuri +
                ", joi: " + programJoi +
                ", vineri: " + programVineri + "}";
    }
}
