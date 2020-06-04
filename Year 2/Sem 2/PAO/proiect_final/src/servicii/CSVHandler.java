package servicii;

import com.sun.istack.internal.NotNull;
import modele.DateParser;

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.List;

public class CSVHandler {

    private static String LOGPATH = "src/date/logs.csv";

    private CSVHandler() {}

    public static List<String[]> citesteCSV(String path) {
        String aux = "";
        String splitBy = ",";
        List<String[]> csv = new ArrayList<>();
        try {
            BufferedReader br = new BufferedReader(new FileReader(path));
            while ((aux = br.readLine()) != null) {
                String[] line = aux.split(splitBy);
                csv.add(line);
                logCSV("r", path);
            }
        }
        catch (IOException e) {
            System.out.println(e);
        }
        return csv;
    }

    public static void scrieCsv(String path, @NotNull String[] args) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < args.length - 1; i++) {
            sb.append(args[i]).append(",");
        }
        sb.append(args[args.length - 1]);

        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter(path, true));
            writer.write(sb.toString());
            writer.newLine();
            writer.close();
            logCSV("w", path);
        }
        catch (IOException e) {
            System.out.println(e);
        }
    }

    private static void logCSV(String mode, String file) {
        /**
         * 'mode' trebuie sa fie 'r' sau 'w'
         */
        StringBuilder sb = new StringBuilder();
        if (mode.equals("r")) {
            mode = "read from ";
        } else if (mode.equals("w")) {
            mode = "write in ";
        } else {
            return;
        }
        sb.append(mode).append(file).append(",").append(DateParser.formatDate(new Date()));
        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter(LOGPATH, true));
            writer.write(sb.toString());
            writer.newLine();
            writer.close();
        }
        catch (IOException e) {
            System.out.println(e);
        }
    }
}
