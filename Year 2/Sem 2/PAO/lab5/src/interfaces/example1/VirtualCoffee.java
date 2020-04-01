package interfaces.example1;

import interfaces.model.cup.CoffeeCup;
import interfaces.model.cup.Cup;
import interfaces.model.cup.TeaCup;

public class VirtualCoffee {

    public static void prepareCup(Cup cup){
        cup.wash();
    }

    public static void main(String[] args) {

        Cup cup = new Cup();
        prepareCup(cup);

        // dynamic polymorphism
        Cup coffeeCup = new CoffeeCup();
        prepareCup(coffeeCup);

        // dynamic polymorphism
        Cup teaCup = new TeaCup();
        prepareCup(teaCup);
    }


}
