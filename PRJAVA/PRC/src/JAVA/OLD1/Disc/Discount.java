package OLD1.Disc;

public abstract class Discount
{
    protected double d1,d2,d3,d4;
    protected Discount(double x1,double x2,double x3,double x4)
    {
        d1 = x1;
        d2 = x2;
        d3 = x3;
        d4 = x4;
    }
    public double getPrice(double money)
    {
        if(money <= 200) return d1 * money;
        else if(money <= 500) return d2 * money;
        else if(money <= 1000) return d3 * money;
        else return d4 * money;
    }
}

class DiscountNormal extends Discount
{
    DiscountNormal() {super(1,0.98,0.95,0.90);}
}

class DiscountIron extends Discount
{
    DiscountIron(){super(0.98,0.95,0.90,0.88);}
}

class DiscountBronze extends Discount
{
    DiscountBronze(){super(0.95,0.90,0.88,0.85);}
}

class DiscountSilver extends Discount
{
    DiscountSilver(){super(0.90,0.88,0.85,0.80);}
}

class DiscountGold extends Discount
{
    DiscountGold(){super(0.88,0.85,0.80,0.75);}
}

