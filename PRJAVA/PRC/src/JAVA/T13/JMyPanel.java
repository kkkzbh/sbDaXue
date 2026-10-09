package JAVA.T13;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class JMyPanel extends JPanel {
    public static final int Rect=0;
    public static final int Curv=1;
    private Mylistener l;
    private ArrayList<MyShape> shapes=new ArrayList<>();
    private MyShape shape=null;
    @Override
    public void paint(Graphics g) {
        g.clearRect(0,0,this.getWidth(),this.getHeight());
        if(!shapes.isEmpty()){
            for(MyShape ms:shapes)ms.draw(g);
        }
        if(shape!=null)shape.draw(g);
    }

    public JMyPanel() {
        l=new Mylistener();
        this.addMouseListener(l);
        this.addMouseMotionListener(l);
        l.setFactory(new MyRectFactory(this));
    }

    public void producing(MyShape shape) {
        this.shape=shape;
        this.repaint();
    }
    public void produced(MyShape shape){
        this.shape=null;
        shapes.add(shape);
//        this.repaint();

    }

    public void setAction(int action) {
        if(l==null)return;
        switch (action){
            case Curv:l.setFactory(new MyCurvFactory(this));break;
            case Rect:l.setFactory(new MyRectFactory(this));break;
        }
    }

    public void clearScreen() {
        shape=null;
        shapes.clear();
        this.repaint();
    }
}
