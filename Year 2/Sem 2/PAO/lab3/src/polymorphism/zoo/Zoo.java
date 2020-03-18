package polymorphism.zoo;

public class Zoo {

    {
        // bloc de initializare
        // se apeleaza inaintea constructorului
        // nrMaxAnimale = 5;
    }
    static {
    }

    private final int nrMaxAnimale;
    Animal[] animaleZoo;
    private int indexCurent;

    public Zoo(int nrMaxAnimale) {
        if(nrMaxAnimale > 0) {
            this.nrMaxAnimale = nrMaxAnimale;
            this.animaleZoo = new Animal[nrMaxAnimale];
        } else {
            throw new RuntimeException("Nu ati introdus intreg pozitiv");
        }
    }

    public void adaugaAnimal(Animal animal) {
        if(indexCurent < animaleZoo.length) {
            animaleZoo[indexCurent] = animal;
            System.out.println("Adaugat animal " + animal.getClass().getSimpleName() + " la pozitia " + indexCurent++);
            // getClass imi da tot arborele pana la clasa
        }
    }
}
