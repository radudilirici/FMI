import interfata.MainFrame;
import servicii.DbHandler;

/**
 * aplicatia de baza, cu interfata grafica
 */
public class App {

    public static void main(String[] args) {

        MainFrame mainFrame = new MainFrame();
        DbHandler.connect();
        DbHandler.incarcaDate();
    }
}
