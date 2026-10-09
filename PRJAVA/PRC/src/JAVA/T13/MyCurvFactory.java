package JAVA.T13;

import java.awt.event.MouseEvent;

public class MyCurvFactory extends ShapeFactory{
    private MyCurv curv = null;
    public MyCurvFactory(JMyPanel pnl) {
        super(pnl);
    }

    @Override
    public void mouseClicked(MouseEvent e) {

    }

    @Override
    public void mousePressed(MouseEvent e) {
        curv=new MyCurv();
        curv.addPoint(e.getPoint());
        pnl.producing(curv);
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        pnl.produced(curv);
        curv=null;
    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseExited(MouseEvent e) {

    }

    @Override
    public void mouseDragged(MouseEvent e) {
        curv.addPoint(e.getPoint());
        pnl.producing(curv);
    }

    @Override
    public void mouseMoved(MouseEvent e) {

    }
}
