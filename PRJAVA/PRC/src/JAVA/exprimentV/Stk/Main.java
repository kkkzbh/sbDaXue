package exprimentV.Stk;

import exprimentIV.Sorter.Cat;
import exprimentV.Stk.FullStackException;
import java.util.ArrayList;
import java.util.EmptyStackException;
import java.util.LinkedList;
import java.util.Random;
import exprimentV.Stk.*;

public class Main
{
    public static void main(String[] args)
    {
        Stack<Cat> cats = new Stack<Cat>(10);
        Random rand = new Random();
        for (int i = 0; i < 100; i++) {
            boolean op=rand.nextInt(5)<=2;
            try {
                if (op) cats.push(new Cat("miao" + i));
                else cats.pop();
            }
            catch (EmptyStackException e) {
                System.out.println("栈已空，不能出栈");
                break;
            }
            catch(FullStackException e){
                System.out.println("栈已满，不能再入栈");
                break;
            }
        }
    }
}