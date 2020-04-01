package interfaces.model.vehicle;

import interfaces.Washable;

public class Car implements Washable {

    @Override
    public void wash() {
        System.out.println("washing a car");
    }
}
