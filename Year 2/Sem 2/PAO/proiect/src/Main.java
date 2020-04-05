import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        Program program1 = new Program("9-17", "12-20", "9-17", "12-20", "liber");
        Medic medic1 = new Medic("cnp1", "Dumitru", "Anca", "pediatrie", program1);
        Medic medic2 = new Medic("cnp2", "Dobranici", "Andrei", "dermatologie", "liber","9-17", "12-20", "9-17", "12-20");
        medic2.setProgramLuni("12-14");
        Angajat ingrijitor = new Angajat("cnp5", "Matei", "Alex", "ingrigitor", "7-9, 15-16", "7-9, 15-16", "7-9, 15-16", "7-9, 15-16", "7-9, 15-16");

        EvidentaAngajati angajati = EvidentaAngajati.getInstance();
        angajati.adaugaAngajat(medic1);
        angajati.adaugaAngajat(medic2);
        angajati.adaugaAngajat(ingrijitor);

        System.out.println("Angajati");
        System.out.println(angajati);

        System.out.println("Medic2:");
        System.out.println(medic2);
        System.out.println(angajati.getAngajat("cnp2").getProgram() + "\n");

        Pacient pacient1 = new Pacient("cnp3", "Dinescu", "Mihai");
        Pacient pacient2 = new Pacient("cnp4", "Voinea", "Vlad");

        EvidentaProgramari programari = EvidentaProgramari.getInstance();
        programari.adaugaProgramare(new Programare(medic1, pacient2, "12 5 2020, 15:00"));
        programari.adaugaProgramare(new Programare(medic2, pacient1, "13 5 2020, 13:00"));
        programari.adaugaProgramare(new Programare(medic1, pacient1, "11 5 2020, 11:00"));
        programari.adaugaProgramare(new Programare(medic2, pacient2, "15 5 2020, 17:00"));

        System.out.println("Programari:");
        System.out.println(programari);  // sunt sortate in functie de data
        System.out.println("Programari medic 1:");
        System.out.println(Arrays.toString(programari.programariMedic(medic1)) + "\n");
        System.out.println("Programari pacient 1:");
        System.out.println(Arrays.toString(programari.programariPacient(pacient1)) + "\n");

        programari.stergeProgramare(new Programare(medic1, pacient1, "10 5 2020, 13:00"));  // programare inexistenta
        programari.stergeProgramare(new Programare(medic2, pacient1, "13 5 2020, 13:00"));
        programari.stergeProgramariInainteDe("12 5 2020, 17:00");

        System.out.println("Programari dupa stergeri:");
        System.out.println(programari);

    }
}
