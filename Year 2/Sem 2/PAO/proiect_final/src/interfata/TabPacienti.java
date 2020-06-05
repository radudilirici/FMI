package interfata;

import modele.Pacient;
import servicii.DbHandler;
import servicii.EvidentaPacienti;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class TabPacienti extends JPanel implements ActionListener {

    private JTextField cnp, nume, prenume;
    JButton addButton, updateButton;

    public TabPacienti() {

        JPanel cnpPanel, numePanel, prenumePanel;

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

        addButton = new JButton("Adauga");
        add(addButton);
        addButton.addActionListener(this);

        updateButton = new JButton("Actualizeaza");
        add(updateButton);
        updateButton.addActionListener(this);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Pacient pacient = new Pacient(cnp.getText(), nume.getText(), prenume.getText());
        EvidentaPacienti ep = EvidentaPacienti.getInstance();

        JButton clicked = (JButton) e.getSource();
        if (clicked == addButton) {
            DbHandler.adaugaPacient(pacient);
            ep.adaugaPacient(pacient);
        } else if (clicked == updateButton){
            DbHandler.actualizeazaPacient(pacient);
            ep.actualizeazaPacient(pacient);
        }
    }
}
