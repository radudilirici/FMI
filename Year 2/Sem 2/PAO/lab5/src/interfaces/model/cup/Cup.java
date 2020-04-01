package interfaces.model.cup;

import interfaces.Washable;

public class Cup implements Washable {

    double volume;
    String color;

    public int getLevelOfFragility() {
        return Washable.FRAGILE;
    }

    @Override
    public void wash() {
        System.out.println("washing a cup");
    }
}
