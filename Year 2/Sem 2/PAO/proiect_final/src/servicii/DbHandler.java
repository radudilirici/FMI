package servicii;

import com.sun.istack.internal.NotNull;
import modele.Angajat;
import modele.Medic;
import modele.Pacient;
import modele.Programare;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DbHandler {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String USERNAME = "root";
    private static final String PASSWORD = "root";
    private static  Connection connection;

    public static boolean connect() {
        try {
            connection = DriverManager.getConnection(DB_URL, USERNAME, PASSWORD);
        } catch (SQLException e) {
            System.out.println("Couldn't connect to database " + e.getMessage());
            return false;
        }
        System.out.println("Connected to database");
        return true;
    }

    private static Statement executaQuery(String query) {
        boolean isResultSet = false;
        Statement stmt = null;

        try {
            stmt = connection.createStatement();
            isResultSet = stmt.execute(query);
            if (isResultSet) {
                CSVHandler.logCSV("", query);
                return stmt;
            }
        } catch (SQLException e ) {
            System.out.println(e.getMessage());
            return null;
        }
        return null;
    }

    public static List<Angajat> citesteAngajati() {

        Statement stmt = null;
        ResultSet rslt = null;
        String query = "select * from angajati;";
        List<Angajat> angajati = new ArrayList<>();

        stmt = executaQuery(query);
        if (stmt != null) {
            try {
                rslt = stmt.getResultSet();
                while (rslt.next()) {
                    String cnp = rslt.getString("cnp");
                    String nume = rslt.getString("nume");
                    String prenume = rslt.getString("prenume");
                    String profesie = rslt.getString("profesie");
                    String program = rslt.getString("program");
                    String[] programList;
                    if (program != null) {
                        programList = program.split(",");
                    } else {
                        programList = new String[]{"", "", "", "", ""};
                    }

                    angajati.add(new Angajat(cnp, nume, prenume, profesie, programList));
                }
                stmt.close();
            } catch (SQLException e) {
                System.out.println(e.getMessage());
                return null;
            }
        }
        return angajati;
    }

    public static void adaugaAngajat(@NotNull Angajat angajat) {

        String query = "insert into angajati (cnp,nume,prenume,profesie,program) values ('" +
                angajat.getCNP() + "','" +
                angajat.getNume() + "','" +
                angajat.getPrenume() + "','" +
                angajat.getProfesie() + "','" +
                angajat.getProgramString() + "');";

        executaQuery(query);
    }

    public static void actualizeazaAngajat(@NotNull Angajat angajat) {

        String query = "update angajati set " +
                "nume = '" + angajat.getNume() +
                "', prenume = '" + angajat.getPrenume() +
                "', profesie = '" + angajat.getProfesie() +
                "', program = '" + angajat.getProgramString() +
                "' where (cnp = '" + angajat.getCNP() + "');";

        executaQuery(query);
    }

    public static void stergeAngajat(@NotNull String CNP) {
        String query = "delete from angajati where (cnp = '" + CNP + "');";
        executaQuery(query);
    }

    public static List<Medic> citesteMedici() {

        Statement stmt = null;
        ResultSet rslt = null;
        String query = "select * from medici;";
        List<Medic> medici = new ArrayList<>();

        stmt = executaQuery(query);
        if (stmt != null) {
            try {
                rslt = stmt.getResultSet();
                while (rslt.next()) {
                    String cnp = rslt.getString("cnp");
                    String nume = rslt.getString("nume");
                    String prenume = rslt.getString("prenume");
                    String specializare = rslt.getString("specializare");
                    String program = rslt.getString("program");
                    String[] programList;
                    if (program != null) {
                        programList = program.split(",");
                    } else {
                        programList = new String[]{"", "", "", "", ""};
                    }

                    medici.add(new Medic(cnp, nume, prenume, specializare, programList));
                }
                stmt.close();
            } catch (SQLException e) {
                System.out.println(e.getMessage());
                return null;
            }
        }
        return medici;
    }

    public static void adaugaMedic(@NotNull Medic medic) {

        String query = "insert into medici (cnp,nume,prenume,specializare,program) values ('" +
                medic.getCNP() + "'," + "'" +
                medic.getNume() + "'," + "'" +
                medic.getPrenume() + "'," + "'" +
                medic.getSpecializare() + "'," + "'" +
                medic.getProgramString() + "');";

        executaQuery(query);
    }

    public static void actualizeazaMedic(@NotNull Medic medic) {

        String query = "update medici set " +
                "nume = '" + medic.getNume() +
                "', prenume = '" + medic.getPrenume() +
                "', specializare = '" + medic.getSpecializare() +
                "', program = '" + medic.getProgramString() +
                "' where (cnp = '" + medic.getCNP() + "');";

        executaQuery(query);
    }

    public static void stergeMedic(@NotNull String CNP) {
        String query = "delete from medici where (cnp = '" + CNP + "');";
        executaQuery(query);
    }

    public static List<Pacient> citestePacienti() {

        Statement stmt = null;
        ResultSet rslt = null;
        String query = "select * from pacienti;";
        List<Pacient> pacienti = new ArrayList<>();

        stmt = executaQuery(query);
        if (stmt != null) {
            try {
                rslt = stmt.getResultSet();
                while (rslt.next()) {
                    String cnp = rslt.getString("cnp");
                    String nume = rslt.getString("nume");
                    String prenume = rslt.getString("prenume");

                    pacienti.add(new Pacient(cnp, nume, prenume));
                }
                stmt.close();
            } catch (SQLException e) {
                System.out.println(e.getMessage());
                return null;
            }
        }
        return pacienti;
    }

    public static void adaugaPacient(@NotNull Pacient pacient) {

        String query = "insert into pacienti (cnp,nume,prenume) values ('" +
                pacient.getCNP() + "'," + "'" +
                pacient.getNume() + "'," + "'" +
                pacient.getPrenume() + "');";

        executaQuery(query);
    }

    public static void actualizeazaPacient(@NotNull Pacient pacient) {

        String query = "update pacienti set " +
                "nume = '" + pacient.getNume() +
                "', prenume = '" + pacient.getPrenume() +
                "' where (cnp = '" + pacient.getCNP() + "');";

        executaQuery(query);
    }

    public static void stergePacient(@NotNull String CNP) {
        String query = "delete from pacienti where (cnp = '" + CNP + "');";
        executaQuery(query);
    }

    public static List<Programare> citesteProgramari() {

        Statement stmt = null;
        ResultSet rslt = null;
        String query = "select * from programari;";
        List<Programare> programari = new ArrayList<>();

        stmt = executaQuery(query);
        if (stmt != null) {
            try {
                rslt = stmt.getResultSet();
                while (rslt.next()) {
                    String cnp_m = rslt.getString("cnp_medic");
                    String cnp_p = rslt.getString("cnp_pacient");
                    String data = rslt.getString("data");

                    programari.add(new Programare(cnp_m, cnp_p, data));
                }
                stmt.close();
            } catch (SQLException e) {
                System.out.println(e.getMessage());
                return null;
            }
        }
        return programari;
    }

    public static void adaugaProgramare(@NotNull Programare programare) {

        String query = "insert into programari (cnp_medic,cnp_pacient,data) values ('" +
                programare.getMedic().getCNP() + "'," + "'" +
                programare.getPacient().getCNP() + "'," + "'" +
                programare.getDataFormated() + "');";

        executaQuery(query);
    }

    public static void stergeProgramare(@NotNull Programare programare) {
        String query = "delete from programari where " +
                "(cnp_medic = '" + programare.getMedic().getCNP() +
                "') and (cnp_pacient = '" + programare.getPacient().getCNP() +
                "') and (data = '" + programare.getDataFormated() + "');";
        System.out.println(query);
        executaQuery(query);
    }

    public static void incarcaDate() {

        EvidentaAngajati angajati = EvidentaAngajati.getInstance();
        List<Angajat> dba = DbHandler.citesteAngajati();
        for (Angajat a: dba) {
            angajati.adaugaAngajat(a);
        }

        List<Medic> dbm = DbHandler.citesteMedici();
        for (Medic m: dbm) {
            angajati.adaugaAngajat(m);
        }

        EvidentaPacienti pacienti = EvidentaPacienti.getInstance();
        List<Pacient> dbp = DbHandler.citestePacienti();
        for (Pacient p: dbp) {
            pacienti.adaugaPacient(p);
        }

        EvidentaProgramari programari = EvidentaProgramari.getInstance();
        List<Programare> dbpr = DbHandler.citesteProgramari();
        for (Programare pr: dbpr) {
            programari.adaugaProgramare(pr);
        }
    }
}
