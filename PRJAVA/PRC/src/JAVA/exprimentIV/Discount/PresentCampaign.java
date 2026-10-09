package exprimentIV.Discount;

public abstract class PresentCampaign
{
    public final String Box;
    public final String Ornament;

    public PresentCampaign(String Box, String Ornament)
    {
        this.Box = Box;
        this.Ornament = Ornament;
    }
    public String getBox()
    {
        return Box;
    }
    public String getOrnament()
    {
        return Ornament;
    }
}

class Exclusive extends PresentCampaign
{
    public Exclusive()
    {
        super("精致纸盒", "精美发夹");
    }
}

class Delicacy extends PresentCampaign
{
    public Delicacy()
    {
        super("定制PVC盒","时尚墨镜");
    }
}

class Gorgeous extends PresentCampaign
{
    public Gorgeous()
    {
        super("豪华木盒","珍珠手链");
    }
}

class Luxury extends PresentCampaign
{
    public Luxury()
    {
        super("紫檀木盒","珍珠项链");
    }
}