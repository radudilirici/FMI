package interfata;

import servicii.DbHandler;
import servicii.EvidentaAngajati;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class TabMediciDel extends JPanel implements ActionListener {

    private JTextField cnp;
    JButton deleteButton;

    public TabMediciDel() {

        JPanel cnpPanel;

        setLayout(new FlowLayout(FlowLayout.CENTER));

        cnpPanel = new JPanel();
        cnpPanel.setLayout(new FlowLayout(FlowLayout.LEFT));
        cnpPanel.add(new JLabel("CNP"));
        cnp = new JTextField(10);
        cnpPanel.add(cnp);
        add(cnpPanel);

        deleteButton = new JButton("Sterge");
        add(deleteButton);
        deleteButton.addActionListener(this);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        EvidentaAngajati ea = EvidentaAngajati.getInstance();

        JButton clicked = (JButton) e.getSource();
        if (clicked == deleteButton) {
            DbHandler.stergeMedic(cnp.getText());
            ea.stergeAngajat(cnp.getText());
        }
    }
}
