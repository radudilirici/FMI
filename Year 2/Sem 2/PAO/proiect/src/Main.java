import modele.*;
import servicii.*;

import java.util.Arrays;

public class Main {
    public static void main(String[] args) {

        // angajati
        EvidentaAngajati angajati = EvidentaAngajati.getInstance();
        angajati.adaugaAngajatiFisier("src/date/medici.csv", true);
        angajati.adaugaAngajatiFisier("src/date/angajati.csv", false);

        System.out.println("Angajati");
        System.out.println(angajati);

        Medic medic1 = (Medic) angajati.getAngajat("cnp1");
        Medic medic2 = (Medic) angajati.getAngajat("cnp2");

        System.out.println("Medic2:");
        System.out.println(medic2);
        System.out.println(angajati.getAngajat("cnp2").getProgram() + "\n");

        // pacienti
        EvidentaPacienti pacienti = EvidentaPacienti.getInstance();
        pacienti.adaugaPacientiFisier("src/date/pacienti.csv");

        Pacient pacient1 = pacienti.getPacient("cnp4");
        Pacient pacient2 = pacienti.getPacient("cnp5");

        // programari
        EvidentaProgramari programari = EvidentaProgramari.getInstance();
        programari.adaugaProgramariFisier("src/date/programari.csv");

        System.out.println("Programari:");
        System.out.println(programari);  // sunt sortate in functie de data
        System.out.println("Programari medic 1:");
        System.out.println(Arrays.toString(programari.programariMedic(medic1)) + "\n");
        System.out.println("Programari pacient 1:");
        System.out.println(Arrays.toString(programari.programariPacient(pacient1)) + "\n");

        programari.stergeProgramare(new Programare(medic1, pacient1, "10 5 2020 13:00"));  // programare inexistenta
        programari.stergeProgramare(new Programare(medic2, pacient2, "13 5 2020 17:00"));
        programari.stergeProgramariInainteDe("12 5 2020 17:00");

        System.out.println("Programari dupa stergeri:");
        System.out.println(programari);

        // write
        CSVHandler.scrieCsv("src/date/out.csv", new String[]{medic1.getNume(), medic1.getPrenume()});
        CSVHandler.scrieCsv("src/date/out.csv", new String[]{pacient1.getNume(), pacient1.getPrenume()});

    }
}
