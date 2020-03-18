package ex1;

public class Milka extends CandyBox {

    private float radius, height;

    public Milka() {
        super();
    }
    public Milka(String flavor, String origin, float radius, float height) {
        super(flavor, origin);
        this.radius = radius;
        this.height = height;
    }

    void printMilkaDim() {
        System.out.println("radius: " + this.radius +
                           ", height: " + this.height);
    }

    @Override
    float getVolume() {
        return (float) (Math.PI * radius * radius * height);
    }

    @Override
    public String toString() {
        return "The " + this.getClass().getSimpleName() + " candy with " +
                super.toString() +
                " has the volume: " + this.getVolume();
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Milka) {
            Milka box = (Milka) obj;
            return super.equals(obj) && this.radius == box.radius && this.height == box.height;
        } else {
            return false;
        }
    }
}
