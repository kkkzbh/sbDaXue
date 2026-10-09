package JAVA.T13;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

public class Mylistener implements MouseListener,MouseMotionListener{
    private ShapeFactory f=null;
    public void setFactory(ShapeFactory f){
        this.f=f;
    }
    @Override
    public void mouseClicked(MouseEvent e) {
        if(f!=null)f.mouseClicked(e);
    }

    @Override
    public void mousePressed(MouseEvent e) {
        if(f!=null)f.mousePressed(e);
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        if(f!=null)f.mouseReleased(e);
    }

    @Override
    public void mouseEntered(MouseEvent e) {
        if(f!=null)f.mouseEntered(e);
    }

    @Override
    public void mouseExited(MouseEvent e) {
        if(f!=null)f.mouseExited(e);
    }

    @Override
    public void mouseDragged(MouseEvent e) {
        if(f!=null)f.mouseDragged(e);
    }

    @Override
    public void mouseMoved(MouseEvent e) {
        if(f!=null)f.mouseMoved(e);
    }
}
