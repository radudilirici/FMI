package interfata;

import javax.swing.*;
import java.awt.*;

public class SecondTab extends JTabbedPane {

    TabAngajati tabAngajati;
    TabMedici tabMedici;
    TabPacienti tabPacienti;
    TabProgramari tabProgramari;

    public SecondTab() {
        tabAngajati = new TabAngajati();
        tabMedici = new TabMedici();
        tabPacienti = new TabPacienti();
        tabProgramari = new TabProgramari();

        add("Adaugare angajati", tabAngajati);
        add("Adaugare medici", tabMedici);
        add("Adaugare pacienti", tabPacienti);
        add("Adaugare programari", tabProgramari);
    }
}
