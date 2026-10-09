package exprimentIV.Discount;

public class Main
{
    public static void main(String[] args) {
        Discount d=new DiscountNormal();
        System.out.println("普通消费者");
        System.out.println(d.getInfor(2000));//输出2000元打折结果
        System.out.println(d.getInfor(5000));//输出5000元打折结果
        System.out.println(d.getInfor(8000));//输出8000元打折结果
        System.out.println(d.getInfor(12000));//输出12000元打折结果
        d=new DiscountIron();
        System.out.println("白铁VIP");
        System.out.println(d.getInfor(2000));//输出2000元打折结果
        System.out.println(d.getInfor(5000));//输出5000元打折结果
        System.out.println(d.getInfor(8000));//输出8000元打折结果
        System.out.println(d.getInfor(12000));//输出12000元打折结果
        d=new DiscountBronze();
        System.out.println("青铜VIP");
        System.out.println(d.getInfor(2000));//输出2000元打折结果
        System.out.println(d.getInfor(5000));//输出5000元打折结果
        System.out.println(d.getInfor(8000));//输出8000元打折结果
        System.out.println(d.getInfor(12000));//输出12000元打折结果
        d=new DiscountSilver();
        System.out.println("白银VIP");
        System.out.println(d.getInfor(2000));//输出2000元打折结果
        System.out.println(d.getInfor(5000));//输出5000元打折结果
        System.out.println(d.getInfor(8000));//输出8000元打折结果
        System.out.println(d.getInfor(12000));//输出12000元打折结果
        d=new DiscountGold();
        System.out.println("黄金VIP");
        System.out.println(d.getInfor(2000));//输出2000元打折结果
        System.out.println(d.getInfor(5000));//输出5000元打折结果
        System.out.println(d.getInfor(8000));//输出8000元打折结果
        System.out.println(d.getInfor(12000));//输出12000元打折结果
    }
}
