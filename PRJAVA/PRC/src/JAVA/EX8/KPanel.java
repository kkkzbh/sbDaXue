package EX8;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

public class KPanel extends JPanel
{
    public enum Graph
    {
        Rect(1),
        Circle(2),
        BrokenLine(3),
        Curve(4);

        private final int value;

        Graph(int i)
        {
            value = i;
        }

        public int getValue()
        {
            return value;
        }

    }


    private ArrayList<KShape> shapes = new ArrayList<KShape>();
    private KShape shape = null;
    private PlotterAdaptor plo = new PlotterAdaptor();

    public KPanel()
    {
        plo.setPlotter(new RectPlotter(this));
        addMouseListener(plo);
        addMouseMotionListener(plo);

        setBackground(Color.WHITE);
    }

    @Override
    public void paint(Graphics g)
    {
        //g.clearRect(0,0,this.getWidth(),this.getHeight());
        //g.setColor(Color.black);

        g.setColor(Color.white);
        g.fillRect(0, 0, getWidth(), getHeight());
        g.setColor(Color.black);

        if(!shapes.isEmpty())
        {
            for(KShape it : shapes)
            {
                it.draw(g);
            }
        }
        if(shape!=null)
        {
            shape.draw(g);
        }
    }


    public void processing(KShape shape)
    {
        this.shape = shape;
        repaint();
    }

    public void processed(KShape shape)
    {
        shapes.add(shape);
        this.shape = null;
    }

    public void setGraph(Graph graph)
    {
        if(plo == null)
        {
            return;
        }
        switch(graph)
        {
            case Rect:
            {
                plo.setPlotter(new RectPlotter(this));
                break;
            }
            case Circle:
            {
                plo.setPlotter(new CirclePlotter(this));
                break;
            }
            case BrokenLine:
            {
                plo.setPlotter(new BrokenLinePlotter(this));
                break;
            }
            case Curve:
            {
                plo.setPlotter(new CurvePlotter(this));
                break;
            }
        }
    }

    public void clear()
    {
        shape = null;
        shapes.clear();
        repaint();
    }

    public void saveImage() throws IOException
    {
        BufferedImage image = new BufferedImage(getWidth(), getHeight(), BufferedImage.TYPE_INT_RGB);
        paint(image.getGraphics());
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setDialogTitle("保存");
        int userSelection = fileChooser.showSaveDialog(this);
        if (userSelection == JFileChooser.APPROVE_OPTION)
        {
            File fileToSave = fileChooser.getSelectedFile();
            ImageIO.write(image, "png", fileToSave);
        }
    }

}
