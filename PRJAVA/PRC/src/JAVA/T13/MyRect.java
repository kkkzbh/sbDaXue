package JAVA.T13;

import java.awt.*;

public class MyRect extends MyShape{
    private int x1,y1,x2,y2;
    public void setLeftTop(Point point){
        this.x1=point.x;
        this.y1=point.y;
    }
    public void setRightBottom(Point point){
        this.x2=point.x;
        this.y2=point.y;
    }

    public void draw(Graphics g) {
        g.drawRect(x1,y1,x2-x1,y2-y1);
    }
}
