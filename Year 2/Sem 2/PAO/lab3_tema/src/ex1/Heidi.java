package ex1;

public class Heidi extends CandyBox{

    private float length;

    public Heidi() {
        super();
    }
    public Heidi(String flavor, String origin, float length) {
        super(flavor, origin);
        this.length = length;
    }

    void printHeidiDim() {
        System.out.println("length: " + this.length);
    }

    @Override
    float getVolume() {
        return length * length * length;
    }

    @Override
    public String toString() {
        return "The " + this.getClass().getSimpleName() + " candy with " +
                super.toString() +
                " has the volume: " + this.getVolume();
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Heidi) {
            Heidi box = (Heidi) obj;
            return super.equals(obj) && this.length == box.length;
        } else {
            return false;
        }
    }
}
