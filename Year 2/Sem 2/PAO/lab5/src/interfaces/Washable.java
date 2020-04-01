package interfaces;

public interface Washable {

    // public static final by default
    public static final int IMPERVIOUS = 0;
    static int RESISTANT = 1;
    final int FRAGILE = 2;
    public int EXPLOSIVE = 3;

    // public abstract by default
    void wash();

    // public
    default boolean needsWashing() {
        System.out.println("by default, wash everything");
        return true;
    }

}
