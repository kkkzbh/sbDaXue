package exprimentIV.Discount;

public abstract class PersentageDiscount implements Discount
{
    protected double d1, d2, d3, d4;

    protected PersentageDiscount(double x1, double x2, double x3, double x4)
    {
        d1 = x1;
        d2 = x2;
        d3 = x3;
        d4 = x4;
    }

    public double getPrice(double money)
    {
        if (money <= 200) return d1 * money;
        else if (money <= 500) return d2 * money;
        else if (money <= 1000) return d3 * money;
        else return d4 * money;
    }

    int section1, section2, section3;

    public void setSection(int section1, int section2, int section3)
    {
        this.section1 = section1;
        this.section2 = section2;
        this.section3 = section3;
    }
    public PresentCampaign selectPresentCampaign(double price)
    {
        if(price < section1)
            return new Exclusive();
        else if(price < section2)
            return new Delicacy();
        else if(price < section3)
            return new Gorgeous();
        else
            return new Luxury();
    }
}

class DiscountNormal extends PersentageDiscount
{
    public DiscountNormal()
    {
        super(1,0.98,0.95,0.90);
        super.setSection(4000,10000,13000);
    }
}

class DiscountIron extends PersentageDiscount
{
    public DiscountIron()
    {
        super(0.98,0.95,0.90,0.88);
        super.setSection(3000,8000,11000);
    }
}

class DiscountBronze extends PersentageDiscount
{
    public DiscountBronze()
    {
        super(0.95,0.90,0.88,0.85);
        super.setSection(3000,7000,9000);
    }
}

class DiscountSilver extends PersentageDiscount
{
    public DiscountSilver()
    {
        super(0.90,0.88,0.85,0.80);
        super.setSection(2000,5000,7000);
    }
}

class DiscountGold extends PersentageDiscount
{
    public DiscountGold()
    {
        super(0.88,0.85,0.80,0.75);
        super.setSection(1000,3000,6000);
    }
}