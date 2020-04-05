public abstract class Persoana {

    private String CNP;
    private String nume, prenume;

    public Persoana(String CNP, String nume, String prenume) {
        this.CNP = CNP;
        this.nume = nume;
        this.prenume = prenume;
    }

    public String getCNP() {
        return CNP;
    }

    public String getNume() {
        return nume;
    }

    public String getPrenume() {
        return prenume;
    }

    @Override
    public String toString() {
        return "CNP: " + this.CNP +
                ", nume: " + this.nume +
                ", prenume: " + this.prenume;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Persoana) {
            Persoana p = (Persoana) obj;
            return this.CNP.equals(p.getCNP());
        } else {
            return false;
        }
    }
}
