package interfata;

import javax.swing.*;

public class MainFrame extends JFrame {

    FirstTab firstTab;
    SecondTab secondTab;

    JTabbedPane tabbedPane = new JTabbedPane();

    public MainFrame() {
        super("Gestionare baza de date");

        firstTab = new FirstTab();
        secondTab = new SecondTab();

        tabbedPane.add("Citire date", firstTab);
        tabbedPane.add("Adaugare date", secondTab);

        add(tabbedPane);

        setSize(1000, 500);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        setVisible(true);
    }
}
