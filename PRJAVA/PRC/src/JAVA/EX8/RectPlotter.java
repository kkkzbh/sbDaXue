package EX8;

import java.awt.event.MouseEvent;

public class RectPlotter extends Plotter
{

    private KRect rect = null;

    RectPlotter(KPanel p)
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
        p.processing(rect = new KRect(e.getPoint(),e.getPoint()));
    }

    @Override
    public void mouseReleased(MouseEvent e)
    {
        p.processed(rect);
        rect = null;
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
        rect.setEnd(e.getPoint());
        p.processing(rect);
    }

    @Override
    public void mouseMoved(MouseEvent e)
    {

    }
}
