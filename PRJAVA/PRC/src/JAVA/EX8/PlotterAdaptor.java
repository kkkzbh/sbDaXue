package EX8;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

public class PlotterAdaptor implements MouseListener, MouseMotionListener
{
    private Plotter plo = null;

    PlotterAdaptor(){}

    PlotterAdaptor(Plotter plo)
    {
        setPlotter(plo);
    }

    public void setPlotter(Plotter plo)
    {
        this.plo = plo;
    }

    @Override
    public void mouseClicked(MouseEvent e)
    {
        if(plo != null)
        {
            plo.mouseClicked(e);
        }
    }

    @Override
    public void mousePressed(MouseEvent e)
    {
        if(plo != null)
        {
            plo.mousePressed(e);
        }
    }

    @Override
    public void mouseReleased(MouseEvent e)
    {
        if(plo != null)
        {
            plo.mouseReleased(e);
        }
    }

    @Override
    public void mouseEntered(MouseEvent e)
    {
        if(plo != null)
        {
            plo.mouseEntered(e);
        }
    }

    @Override
    public void mouseExited(MouseEvent e)
    {
        if(plo != null)
        {
            plo.mouseExited(e);
        }
    }

    @Override
    public void mouseDragged(MouseEvent e)
    {
        if(plo != null)
        {
            plo.mouseDragged(e);
        }
    }

    @Override
    public void mouseMoved(MouseEvent e)
    {
        if(plo != null)
        {
            plo.mouseMoved(e);
        }
    }
}
