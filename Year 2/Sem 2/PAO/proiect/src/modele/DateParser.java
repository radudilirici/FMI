package modele;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class DateParser {
    private static final DateFormat dateFormat = new SimpleDateFormat("d M yyy HH:mm", Locale.ENGLISH);

    private DateParser() {};

    public static Date parseDate(String date) {
        try {
            return dateFormat.parse(date);
        }
        catch (ParseException e) {
            System.out.println("Format data incorect");
        }
        return null;
    }

    public static String formatDate(Date date) {
        return dateFormat.format(date);
    }
}
