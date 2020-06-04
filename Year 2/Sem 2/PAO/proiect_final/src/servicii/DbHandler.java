package servicii;

import com.sun.istack.internal.NotNull;
import modele.Angajat;
import modele.Medic;

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
                    String[] programList = program.split(",");

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
                angajat.getCNP() + "'," + "'" +
                angajat.getNume() + "'," + "'" +
                angajat.getPrenume() + "'," + "'" +
                angajat.getProfesie() + "'," + "'" +
                angajat.getProgramString() + "');";
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
                    String[] programList = program.split(",");

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
}
