package JAVA.TEMP;

class Cat implements Comparable<Cat> {
    int id;
    int age;

    public Cat(int id, int age) {
        this.id = id;
        this.age = age;
    }

    @Override
    public int compareTo(Cat o) {
        return this.age - o.age;
    }

    @Override
    public String toString() {
        return "Cat{" +
                "id=" + id +
                ", age=" + age +
                '}';
    }
}

class CleverSorter<T extends Comparable<T>> {
    public void sort(T[] data) {
        for (int i = 0; i < data.length - 1; i++) {
            for (int j = 0; j < data.length - 1 - i; j++) {
                if (data[j].compareTo(data[j + 1]) > 0) {
                    T temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }
}

public class shiyan_4_3 {
    public static void main(String[] args) {
        Integer[] data = {11, 3, 25, 8, 9, 36, 13, 29, 10, 50};
        CleverSorter<Integer> cs = new CleverSorter<>();
        cs.sort(data);
        for (Integer i : data) System.out.println(i);

        Cat[] cats = new Cat[10];
        cats[0] = new Cat(11, 50);
        cats[1] = new Cat(3, 10);
        cats[2] = new Cat(25, 29);
        cats[3] = new Cat(8, 13);
        cats[4] = new Cat(9, 36);
        cats[5] = new Cat(36, 9);
        cats[6] = new Cat(13, 8);
        cats[7] = new Cat(29, 25);
        cats[8] = new Cat(10, 3);
        cats[9] = new Cat(50, 11);
        CleverSorter<Cat> cs2 = new CleverSorter<>();
        cs2.sort(cats);
        for (Cat c : cats) System.out.println(c);
    }
}
