package JAVA.PetShop;

import java.util.Scanner;

public class Manage
{
    private static final Scanner in = new Scanner(System.in);
    private static final int defaultSize = 64;
    private static final int defaultAddTime = 2;

    private Cat[] Cats = new Cat[defaultSize];
    private int CatSize = 0;
    private int CatCap = defaultSize;
    private Dog[] Dogs = new Dog[defaultSize];
    private int DogSize = 0;
    private int DogCap = defaultSize;

    public Manage(){}

    private void pmenu()
    {
        System.out.println("1.添加狗");
        System.out.println("2.添加猫");
        System.out.println("3.记录喂食数据");
        System.out.println("4.统计");
        System.out.println("5.宠物数据信息");
        System.out.println("6.更新睡眠");
        System.out.println("0.退出");
    }

    public void menu()
    {
        System.out.print("请选择 :>");
        int select;
        do
        {
            pmenu();
            select = in.nextInt();
            switch (select)
            {
                case 1:
                {
                    M_addDog();
                    break;
                }
                case 2:
                {
                    M_addCat();
                    break;
                }
                case 3:
                {
                    account();
                    break;
                }
                case 4:
                {
                    statistics();
                    break;
                }
                case 5:
                {
                    petInformation();
                    break;
                }
                case 6:
                {
                    updateSleep();
                    break;
                }
                case 0: break;
                default:
                {
                    System.out.print("输入有误 待会请重新输入！\n");
                    in.nextLine();
                }
            }
        }while(select != 0);
    }





    private void petInformation()
    {
        for(int i = 0; i != CatSize;++i) System.out.println(Cats[i].characteristic());
        for(int i = 0; i != DogSize;++i) System.out.println(Dogs[i].characteristic());
        in.nextLine();
    }

    private void statistics()
    {
        for(int i = 0; i != CatSize;++i) System.out.println(Cats[i].statistics());
        for(int i = 0; i != DogSize;++i) System.out.println(Dogs[i].statistics());
        in.nextLine();
    }

    private void account()
    {
        int select;
        do
        {
            System.out.print("记录 猫(1) | 狗(2) | 返回(3)\n");
            select = in.nextInt();
            if (select == 1)
            {
                int index,eatCount;
                do
                {
                    System.out.print("index\t\t名字\t\t共吃鱼\n");
                    pCatsForAccount();
                    System.out.print("按格式输入 {a} {b} a 是小猫的index b 是吃的(单位 :两)数\n:> if a = 0 exit:<\n");
                    index = in.nextInt();
                    if(index == 0) break;
                    eatCount = in.nextInt();
                    if(index >= 1 && index <= CatSize)
                    {
                        Cats[index - 1].eat(eatCount);
                        System.out.print("记录成功！\n");
                        in.nextLine();
                    }
                    else
                    {
                        System.out.print("输入有误！ 重新输入\n");
                        in.nextLine();
                    }
                }while(true);
            }
            else if (select == 2)
            {
                int index,eatCount;
                do
                {
                    System.out.print("index\t\t名字\t\t共吃肉\n");
                    pDogsForAccount();
                    System.out.print("按格式输入 {a} {b} a 是小狗的index b 是吃的(单位 :两)数\n:> if a = 0 exit:<\n");
                    index = in.nextInt();
                    eatCount = in.nextInt();
                    if(index >= 1 && index <= DogSize)
                    {
                        Dogs[index - 1].eat(eatCount);
                        System.out.print("记录成功！\n");
                        in.nextLine();
                    }
                    else if(index != 0)
                    {
                        System.out.print("输入有误！ 重新输入\n");
                        in.nextLine();
                    }
                }while(index != 0);
            }
            else if(select != 3)
            {
                System.out.println("输入有误 重新输入\n");
            }
        }while(select != 3);
    }
    private void pCatsForAccount()
    {
        for(int i = 0; i != CatSize;++i)
        {
            System.out.print((i + 1) + "\t\t" + Cats[i].getName() + "\t\t" + Cats[i].getEatCount() + "\n");
        }
    }
    private void pDogsForAccount()
    {
        for(int i = 0; i != DogSize;++i)
        {
            System.out.print((i + 1) + "\t\t" + Dogs[i].getName() + "\t\t" + Dogs[i].getEatCount() + "\n");
        }
    }
    private void updateSleep()
    {
        for(int i = 0; i != CatSize;++i) Cats[i].sleep();
        for(int i = 0; i != DogSize;++i) Dogs[i].sleep();
    }
    private void addCat(String name,String color,int age)
    {
        if(CatSize == CatCap) reallocCat();
        Cats[CatSize++] = new Cat(name,color,age);
    }
    private void addDog(String name,String var,int weigh)
    {
        if(DogSize == DogCap) reallocDog();
        Dogs[DogSize++] = new Dog(name,var,weigh);
    }

    private void M_addDog()
    {
        String name,var;
        int weigh;
        System.out.print("请输入狗的名字 :>");
        name = in.next();
        System.out.print("请输入狗的品种 :>");
        var = in.next();
        System.out.print("请输入狗的体重 :>");
        weigh = in.nextInt();
        addDog(name,var,weigh);
        System.out.println("添加成功!");
        in.nextLine();
    }
    private void M_addCat()
    {
        String name,color;
        int age;
        System.out.print("请输入猫的名字 :>");
        name = in.next();
        System.out.print("请输入猫的毛色 :>");
        color = in.next();
        System.out.print("请输入猫的年龄 :>");
        age = in.nextInt();
        addCat(name,color,age);
        System.out.println("添加成功!");
        in.nextLine();
    }
    private void reallocCat()
    {
        Cat[] tmp = Cats;
        Cats = new Cat[CatCap * defaultAddTime];
        for(int i = 0; i != CatCap;++i) Cats[i] = tmp[i];
        CatCap *= defaultAddTime;
    }
    private void reallocDog()
    {
        Dog[] tmp = Dogs;
        Dogs = new Dog[DogCap * defaultAddTime];
        for(int i = 0; i != DogCap;++i) Dogs[i] = tmp[i];
        DogCap *= defaultAddTime;
    }
}
