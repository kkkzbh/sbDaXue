package EX8;

import java.awt.event.MouseEvent;

public class CurvePlotter extends Plotter
{

    private KCurve curve = null;

    public CurvePlotter(KPanel p)
    {
        super(p);
    }

    @Override
    public void mouseClicked(MouseEvent e)
    {

    }

    @Override
    public void mousePressed(MouseEvent e)
    {
        curve = new KCurve();
        curve.addPoint(e.getPoint());
    }

    @Override
    public void mouseReleased(MouseEvent e)
    {
        p.processed(curve);
        curve = null;
    }

    @Override
    public void mouseEntered(MouseEvent e)
    {

    }

    @Override
    public void mouseExited(MouseEvent e)
    {

    }

    @Override
    public void mouseDragged(MouseEvent e)
    {
        curve.addPoint(e.getPoint());
        p.processing(curve);
    }

    @Override
    public void mouseMoved(MouseEvent e)
    {

    }
}
