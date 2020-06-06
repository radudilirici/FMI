package interfata;

import javax.swing.*;

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

        add("Angajati", tabAngajati);
        add("Medici", tabMedici);
        add("Pacienti", tabPacienti);
        add("Programari", tabProgramari);
    }
}
