package modele;

import servicii.EvidentaAngajati;
import servicii.EvidentaPacienti;

import java.util.Date;

public class Programare {

    private Medic medic;
    private Pacient pacient;
    private Date data;

    public Programare(Medic medic, Pacient pacient, Date data) {
        this.medic = medic;
        this.pacient = pacient;
        this.data = data;
    }

    public Programare(Medic medic, Pacient pacient, String data) {
        this.medic = medic;
        this.pacient = pacient;
        this.data = DateParser.parseDate(data);
    }

    public Programare(String cnpMedic, String cnpPacient, String data) {
        EvidentaAngajati angajati = EvidentaAngajati.getInstance();
        EvidentaPacienti pacienti = EvidentaPacienti.getInstance();
        Medic medic = (Medic) angajati.getAngajat(cnpMedic);
        Pacient pacient = pacienti.getPacient(cnpPacient);
        this.medic = medic;
        this.pacient = pacient;
        this.data = DateParser.parseDate(data);
    }

    public Programare(Programare programare) {
        this.medic = programare.getMedic();
        this.pacient = programare.getPacient();
        this.data = programare.getData();
    }

    public Medic getMedic() {
        return medic;
    }

    public Pacient getPacient() {
        return pacient;
    }

    public Date getData() {
        return data;
    }

    public int comparaData(Date data) {
        return this.data.compareTo(data);
    }

    public int comparaData(String data) {
        Date dataAux = null;
        dataAux = DateParser.parseDate(data);
        if (dataAux == null) {
            return 0;
        }
        return this.data.compareTo(dataAux);
    }

    @Override
    public String toString() {
        return "programare: {" +
                "medic: " + this.medic.getPrenume() + " " + this.medic.getNume() +
                ", pacient: " + this.pacient.getPrenume() + " " + this.pacient.getNume() +
                ", data: " + DateParser.formatDate(this.data) + "}";
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Programare) {
            Programare p = (Programare) obj;
            return this.medic.equals(p.getMedic()) && this.pacient.equals(p.getPacient()) && this.data.equals(p.getData());
        } else {
            return false;
        }
    }
}
