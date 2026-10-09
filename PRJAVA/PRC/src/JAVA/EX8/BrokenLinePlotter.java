package EX8;

import java.awt.event.MouseEvent;

public class BrokenLinePlotter extends Plotter
{
    private KBrokenLine bl = null;

    public BrokenLinePlotter(KPanel p)
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
        bl = new KBrokenLine();
        bl.setStart(e.getPoint());
    }

    @Override
    public void mouseReleased(MouseEvent e)
    {
        p.processed(bl);
        bl = null;
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
        bl.setEnd(e.getPoint());
        p.processing(bl);
    }

    @Override
    public void mouseMoved(MouseEvent e)
    {

    }
}
