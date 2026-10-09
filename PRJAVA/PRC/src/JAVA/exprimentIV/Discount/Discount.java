package exprimentIV.Discount;

public interface Discount
{
    default public String getInfor(double price)
    {
        double np = getPrice(price);
        PresentCampaign pc = selectPresentCampaign(price);
        return String.format("原价%.2f,打折后%.2f,给您使用%s包装,赠您一件精美饰品%s",
                price,np,pc.getBox(),pc.getOrnament());
    }
    public double getPrice(double price);
    PresentCampaign selectPresentCampaign(double price);
}