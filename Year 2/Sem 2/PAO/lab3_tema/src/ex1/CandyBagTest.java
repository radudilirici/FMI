package ex1;

public class CandyBagTest {

    public static void main(String[] args) {

        Lindt lindt1 = new Lindt("Caramel", "Switzerland", 20, 10, 10);
        Lindt lindt2 = new Lindt("Caramel", "Switzerland", 15, 10, 15);
        Lindt lindt3 = new Lindt("Caramel", "Switzerland", 15, 10, 15);
        Lindt lindt4 = new Lindt("Caramel", "Switzerland", 15, 10, 15);
        Milka milka1 = new Milka("Hazelnut", "Switzerland", 10, 20);
        Heidi heidi1 = new Heidi("Oranges", "Romania", 15);

        CandyBag bag = new CandyBag(10);
        bag.addBox(lindt1);
        bag.addBox(lindt2);
        bag.addBox(lindt3);
        bag.addBox(milka1);
        bag.addBox(heidi1);
        bag.addBox(lindt4);

        System.out.println("");
        for (int i = 0; i < bag.boxes.length && bag.boxes[i] != null; i++) {
            System.out.println(bag.boxes[i]);
        }
    }
}
