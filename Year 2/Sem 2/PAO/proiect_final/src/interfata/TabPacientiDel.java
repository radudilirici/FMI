package interfata;

import servicii.DbHandler;
import servicii.EvidentaPacienti;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class TabPacientiDel extends JPanel implements ActionListener {

    private JTextField cnp;
    JButton deleteButton;

    public TabPacientiDel() {

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
        EvidentaPacienti ep = EvidentaPacienti.getInstance();

        JButton clicked = (JButton) e.getSource();
        if (clicked == deleteButton) {
            DbHandler.stergePacient(cnp.getText());
            ep.stergePacient(cnp.getText());
        }
    }
}
