package EX8;

import java.awt.*;
import java.awt.event.MouseEvent;

public class CirclePlotter extends Plotter
{
    private KCircle circle = null;

    public CirclePlotter(KPanel p)
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
        circle = new KCircle(e.getPoint());
    }

    @Override
    public void mouseReleased(MouseEvent e)
    {
        p.processed(circle);
        circle = null;
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
        Point p = e.getPoint();
        Point center = circle.getCenter();
        int r = (int)Math.sqrt((p.x - center.x) * (p.x - center.x) + (p.y - center.y) * (p.y - center.y));
        circle.setR(r);
        super.p.processing(circle);
    }

    @Override
    public void mouseMoved(MouseEvent e)
    {

    }
}
