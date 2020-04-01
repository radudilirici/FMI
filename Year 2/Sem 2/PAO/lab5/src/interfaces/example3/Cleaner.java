package interfaces.example3;

public class Cleaner {

    // when forcing a relation between different object models
    public static void clean(WashableObject washableObject) {
        washableObject.wash();
    }


    public static void main(String[] args) {
        Dog dog = new Dog();
        clean(dog);

        Window window = new Window();
        clean(window);

        Car car = new Car();
        clean(car);

        Cup cup = new CoffeeCup();
        clean(cup);

        String unknownType = "unknown type";
//        clean(unknownType); // does not compile, not a interfaces.example2.WashableObject

    }
}
