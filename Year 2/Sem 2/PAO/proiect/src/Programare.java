import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class Programare {

    private Medic medic;
    private Pacient pacient;
    private Date data;
    private static final DateFormat dateFormat = new SimpleDateFormat("d M yyyy, HH:mm", Locale.ENGLISH);

    public Programare(Medic medic, Pacient pacient, Date data) {
        this.medic = medic;
        this.pacient = pacient;
        this.data = data;
    }

    public Programare(Medic medic, Pacient pacient, String data) {
        this.medic = medic;
        this.pacient = pacient;
        try {
            this.data = dateFormat.parse(data);
        }
        catch (ParseException e) {
            System.out.println("Format data incorect");
        }
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
        try {
            dataAux = dateFormat.parse(data);
        }
        catch (ParseException e) {
            System.out.println("Format data incorect");
        }
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
                ", data: " + dateFormat.format(this.data) + "}";
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
