package JAVA.T13;

import java.awt.event.MouseEvent;

public class MyRectFactory  extends ShapeFactory{
    private MyRect r=null;
    public MyRectFactory(JMyPanel pnl) {
        super(pnl);
    }

    @Override
    public void mouseClicked(MouseEvent e) {

    }

    @Override
    public void mousePressed(MouseEvent e) {
        r=new MyRect();
        r.setLeftTop(e.getPoint());
        r.setRightBottom(e.getPoint());
        pnl.producing(r);
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        pnl.produced(r);
        r=null;
    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseExited(MouseEvent e) {

    }

    @Override
    public void mouseDragged(MouseEvent e) {
        r.setRightBottom(e.getPoint());
        pnl.producing(r);
    }

    @Override
    public void mouseMoved(MouseEvent e) {

    }
}
