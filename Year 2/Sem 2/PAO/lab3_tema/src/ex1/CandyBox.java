package ex1;

public class CandyBox {

    private String flavor;
    private String origin;

    public CandyBox() {}
    public CandyBox(String flavor, String origin) {
        this.flavor = flavor;
        this.origin = origin;
    }

    float getVolume() {
        return 0;
    }

    @Override
    public String toString() {
        return "flavor: " + flavor +
                ", origin: " + origin;
    }

    @Override
    public boolean equals(Object obj) {
        // in clasa CandyBox, flavor si origin sunt singurele informatii disponibile
        // vom suprascrie metoda si in clasele extinse pentru a verifica si celelalte campuri
        if (obj instanceof CandyBox) {
            CandyBox box = (CandyBox) obj;
            return this.flavor.equals(box.flavor) && this.origin.equals(box.origin);
        } else {
            return false;
        }
    }
}
