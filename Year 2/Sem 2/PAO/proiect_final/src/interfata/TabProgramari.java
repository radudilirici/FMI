package interfata;

import modele.Programare;
import servicii.DbHandler;
import servicii.EvidentaProgramari;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class TabProgramari extends JPanel implements ActionListener {

    private JTextField cnp_m, cnp_p, data;

    public TabProgramari() {

        JPanel cnp_mPanel, cnp_pPanel, dataPanel;
        JButton buton;

        setLayout(new FlowLayout(FlowLayout.CENTER));

        cnp_mPanel = new JPanel();
        cnp_mPanel.setLayout(new FlowLayout(FlowLayout.LEFT));
        cnp_mPanel.add(new JLabel("CNP medic"));
        cnp_m = new JTextField(10);
        cnp_mPanel.add(cnp_m);
        add(cnp_mPanel);

        cnp_pPanel = new JPanel();
        cnp_pPanel.setLayout(new FlowLayout(FlowLayout.LEFT));
        cnp_pPanel.add(new JLabel("CNP pacient"));
        cnp_p = new JTextField(10);
        cnp_pPanel.add(cnp_p);
        add(cnp_pPanel);

        dataPanel = new JPanel();
        dataPanel.setLayout(new FlowLayout(FlowLayout.LEFT));
        dataPanel.add(new JLabel("Data"));
        data = new JTextField(20);
        dataPanel.add(data);
        add(dataPanel);

        buton = new JButton("Adauga");
        add(buton);
        buton.addActionListener(this);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Programare programare = new Programare(cnp_m.getText(), cnp_p.getText(), data.getText());
        DbHandler.adaugaProgramare(programare);
        EvidentaProgramari epr = EvidentaProgramari.getInstance();
        epr.adaugaProgramare(programare);
    }
}
