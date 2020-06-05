package interfata;

import javax.swing.*;

public class ThirdTab extends JTabbedPane {

    TabAngajatiDel tabAngajati;
    TabMediciDel tabMedici;
    TabPacientiDel tabPacienti;
    TabProgramariDel tabProgramari;

    public ThirdTab() {
        tabAngajati = new TabAngajatiDel();
        tabMedici = new TabMediciDel();
        tabPacienti = new TabPacientiDel();
        tabProgramari = new TabProgramariDel();

        add("Angajati", tabAngajati);
        add("Medici", tabMedici);
        add("Pacienti", tabPacienti);
        add("Programari", tabProgramari);
    }
}
