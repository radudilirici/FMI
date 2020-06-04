package interfata;

import servicii.DbHandler;

public class App {

    public static void main(String[] args) {

        MainFrame mainFrame = new MainFrame();
        DbHandler.connect();
        DbHandler.incarcaDate();
    }
}
