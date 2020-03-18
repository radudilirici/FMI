package ex1;

public class Lindt extends CandyBox {

    private float length, width, height;

    public Lindt() {
        super();
    }
    public Lindt(String flavor, String origin, float length, float width, float height) {
        super(flavor, origin);
        this.length = length;
        this.width = width;
        this.height = height;
    }

    void printLindtDim() {
        System.out.println("length: " + this.length +
                           ", width:" + this.width +
                           ", height: " + this.height);
    }

    @Override
    float getVolume() {
        return length * width * height;
    }

    @Override
    public String toString() {
        return "The " + this.getClass().getSimpleName() + " candy with " +
                super.toString() +
                " has the volume: " + this.getVolume();
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Lindt) {
            Lindt box = (Lindt) obj;
            return super.equals(obj) && this.length == box.length && this.width == box.width && this.height == box.height;
        } else {
            return false;
        }
    }
}
