package interfata;

import servicii.DbHandler;

import javax.swing.*;

public class MainFrame extends JFrame {

    FirstTab firstTab;
    JPanel secondTab;

    JTabbedPane tabbedPane = new JTabbedPane();

    public MainFrame() {
        super("App");

        firstTab = new FirstTab();
        secondTab = new JPanel();

        tabbedPane.add("Citire date", firstTab);
        tabbedPane.add("Adaugare date", secondTab);

        add(tabbedPane);

        setSize(1000, 500);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        setVisible(true);
    }
}
