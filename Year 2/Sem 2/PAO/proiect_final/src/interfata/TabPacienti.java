package interfata;

import modele.Pacient;
import servicii.DbHandler;
import servicii.EvidentaPacienti;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class TabPacienti extends JPanel implements ActionListener {

    private JTextField cnp, nume, prenume, specializare, program;

    public TabPacienti() {

        JPanel cnpPanel, numePanel, prenumePanel;
        JButton buton;

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

        buton = new JButton("Adauga");
        add(buton);
        buton.addActionListener(this);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Pacient pacient = new Pacient(cnp.getText(), nume.getText(), prenume.getText());
        DbHandler.adaugaPacient(pacient);
        EvidentaPacienti ep = EvidentaPacienti.getInstance();
        ep.adaugaPacient(pacient);
    }
}
