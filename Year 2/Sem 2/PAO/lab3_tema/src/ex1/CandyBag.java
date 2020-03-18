package ex1;

public class CandyBag {

    private final int noOfBoxes;

    CandyBox[] boxes;
    private int currentIndex;

    public CandyBag(int noOfBoxes) {
        if(noOfBoxes > 0) {
            this.noOfBoxes = noOfBoxes;
            this.boxes = new CandyBox[noOfBoxes];
        } else {
            throw new RuntimeException("Nu ati introdus un numar intreg pozitiv");
        }
    }

    public void addBox(CandyBox box) {
        if(this.currentIndex < this.boxes.length) {
            if (box instanceof Lindt) {
                int noOfDuplicates = 0;
                for (int i = 0; i < this.currentIndex; i++) {
                    if (box.equals(this.boxes[i])){
                        noOfDuplicates++;
                    }
                }
                if (noOfDuplicates > 0) {
                    System.out.println("The Lindt box already appears in the list " + noOfDuplicates + " times");
                } else {
                    System.out.println("The Lindt box doesn't appear in the list");
                }
            }
            this.boxes[currentIndex++] = box;
//            System.out.println("Added a box of " + box.getClass().getSimpleName() + " at position " + currentIndex++);
        }
    }
}
