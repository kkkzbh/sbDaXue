

class Parent {
    int parentVar = 10; // 默认访问权限的成员变量
}

class Child extends Parent {
    void accessParentVar() {
        // 尝试访问父类的默认访问权限变量
        System.out.println(parentVar); // 编译错误：parentVar cannot be resolved or is not a field
    }
}

public class Main {

    public static void main(String[] args) {
        final int val;
        val = 10;
        System.out.println(val);
        System.out.println("Hella word");
    }
}
