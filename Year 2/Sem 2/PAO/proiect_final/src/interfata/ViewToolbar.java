package interfata;

import modele.Angajat;
import modele.Medic;
import modele.Pacient;
import modele.Programare;
import servicii.DbHandler;
import servicii.EvidentaAngajati;
import servicii.EvidentaPacienti;
import servicii.EvidentaProgramari;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class ViewToolbar extends JPanel implements ActionListener {

    private JButton butonAngajati, butonMedici, butonPacienti, butonProgramari;
    TypingListener typingListener;

    public ViewToolbar() {
        butonAngajati = new JButton("Angajati");
        butonAngajati.addActionListener(this);
        butonMedici = new JButton("Medici");
        butonMedici.addActionListener(this);
        butonPacienti = new JButton("Pacienti");
        butonPacienti.addActionListener(this);
        butonProgramari = new JButton("Programari");
        butonProgramari.addActionListener(this);

        setLayout(new FlowLayout(FlowLayout.LEFT));
        add(butonAngajati);
        add(butonMedici);
        add(butonPacienti);
        add(butonProgramari);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        JButton clicked = (JButton) e.getSource();
        if (typingListener == null) {
            return;
        }
        if (clicked == butonAngajati) {
            EvidentaAngajati angajati = EvidentaAngajati.getInstance();
            List<Angajat> dba = DbHandler.citesteAngajati();
            typingListener.textTyped("Angajati\n");
            for (Angajat a: dba) {
                angajati.adaugaAngajat(a);
                typingListener.textTyped(a.toString() + "\n");
            }
            typingListener.textTyped("\n");
        } else if (clicked == butonMedici) {
            EvidentaAngajati angajati = EvidentaAngajati.getInstance();
            typingListener.textTyped("Medici\n");
            List<Medic> dbm = DbHandler.citesteMedici();
            for (Medic m: dbm) {
                angajati.adaugaAngajat(m);
                typingListener.textTyped(m.toString() + "\n");
            }
            typingListener.textTyped("\n");
        } else if (clicked == butonPacienti) {
            EvidentaPacienti pacienti = EvidentaPacienti.getInstance();
            typingListener.textTyped("Pacienti\n");
            List<Pacient> dbp = DbHandler.citestePacienti();
            for (Pacient p: dbp) {
                pacienti.adaugaPacient(p);
                typingListener.textTyped(p.toString() + "\n");
            }
            typingListener.textTyped("\n");
        } else if (clicked == butonProgramari) {
            EvidentaProgramari programari = EvidentaProgramari.getInstance();
            typingListener.textTyped("Programari\n");
            List<Programare> dbpr = DbHandler.citesteProgramari();
            for (Programare pr: dbpr) {
                programari.adaugaProgramare(pr);
                typingListener.textTyped(pr.toString() + "\n");
            }
            typingListener.textTyped("\n");
        }
    }

    public TypingListener getTypingListener() {
        return typingListener;
    }

    public void setTypingListener(TypingListener typingListener) {
        this.typingListener = typingListener;
    }
}
