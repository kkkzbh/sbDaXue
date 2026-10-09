package JAVA.T13;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

public abstract class ShapeFactory implements MouseMotionListener, MouseListener {
    protected JMyPanel pnl=null;

    public ShapeFactory(JMyPanel pnl) {
        this.pnl = pnl;
    }

    public abstract void mouseClicked(MouseEvent e) ;
    public abstract void mousePressed(MouseEvent e) ;
    public abstract void mouseReleased(MouseEvent e) ;
    public abstract void mouseEntered(MouseEvent e) ;
    public abstract void mouseExited(MouseEvent e) ;
    public abstract void mouseDragged(MouseEvent e) ;
    public abstract void mouseMoved(MouseEvent e) ;
}
