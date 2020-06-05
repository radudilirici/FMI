package interfata;

import modele.Angajat;
import servicii.DbHandler;
import servicii.EvidentaAngajati;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class TabAngajati extends JPanel implements ActionListener {

    private JTextField cnp, nume, prenume, profesie, program;
    JButton addButton, updateButton;

    public TabAngajati() {

        JPanel cnpPanel, numePanel, prenumePanel, profesiePanel, programPanel;

        setLayout(new FlowLayout(FlowLayout.CENTER));

        cnpPanel = new JPanel();
        cnpPanel.setLayout(new FlowLayout(FlowLayout.LEFT));
        cnpPanel.add(new JLabel("CNP"));
        cnp = new JTextField(10);
        cnpPanel.add(cnp);
        add(cnpPanel);

        numePanel = new JPanel();
        numePanel.setLayout(new FlowLayout(FlowLayout.LEFT));
        numePanel.add(new JLabel("Nume"));
        nume = new JTextField(10);
        numePanel.add(nume);
        add(numePanel);

        prenumePanel = new JPanel();
        prenumePanel.setLayout(new FlowLayout(FlowLayout.LEFT));
        prenumePanel.add(new JLabel("Prenume"));
        prenume = new JTextField(13);
        prenumePanel.add(prenume);
        add(prenumePanel);

        profesiePanel = new JPanel();
        profesiePanel.setLayout(new FlowLayout(FlowLayout.LEFT));
        profesiePanel.add(new JLabel("Profesie"));
        profesie = new JTextField(10);
        profesiePanel.add(profesie);
        add(profesiePanel);

        programPanel = new JPanel();
        programPanel.setLayout(new FlowLayout(FlowLayout.LEFT));
        programPanel.add(new JLabel("Program"));
        program = new JTextField(30);
        programPanel.add(program);
        add(programPanel);

        addButton = new JButton("Adauga");
        add(addButton);
        addButton.addActionListener(this);

        updateButton = new JButton("Actualizeaza");
        add(updateButton);
        updateButton.addActionListener(this);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Angajat angajat = new Angajat(cnp.getText(), nume.getText(), prenume.getText(), profesie.getText(), program.getText().split(","));
        EvidentaAngajati ea = EvidentaAngajati.getInstance();

        JButton clicked = (JButton) e.getSource();
        if (clicked == addButton) {
            DbHandler.adaugaAngajat(angajat);
            ea.adaugaAngajat(angajat);
        } else if (clicked == updateButton) {
            DbHandler.actualizeazaAngajat(angajat);
            ea.actualizeazaAngajat(angajat);
        }
    }
}
