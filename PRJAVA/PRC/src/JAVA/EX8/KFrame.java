package EX8;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

public class KFrame extends JFrame
{

    private JMenuBar menuBar = makeMenuBar();
    private KPanel panel = new KPanel();

    public KFrame()
    {
        setTitle("画图");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(500,500);
        setLocationRelativeTo(null);

        add(menuBar,BorderLayout.NORTH);
        add(panel);

        setVisible(true);
    }


    private JMenuBar makeMenuBar()
    {
        JMenuBar menuBar = new JMenuBar();
        JMenu drawMenu = new JMenu("画图");
        JMenuItem drawRect = new JMenuItem("矩形");
        JMenuItem drawCircle = new JMenuItem("圆");
        JMenuItem drawBrokenLine = new JMenuItem("折线");
        JMenuItem drawCurve = new JMenuItem("曲线");
        JMenuItem drawClear = new JMenuItem("清空");
        JMenuItem drawSave = new JMenuItem("保存");

        drawMenu.add(drawRect);
        drawMenu.add(drawCircle);
        drawMenu.add(drawBrokenLine);
        drawMenu.add(drawCurve);
        drawMenu.add(drawClear);
        drawMenu.add(drawSave);
        menuBar.add(drawMenu);

        drawRect.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                panel.setGraph(KPanel.Graph.Rect);
            }
        });

        drawCircle.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                panel.setGraph(KPanel.Graph.Circle);
            }
        });

        drawBrokenLine.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                panel.setGraph(KPanel.Graph.BrokenLine);
            }
        });

        drawCurve.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                panel.setGraph(KPanel.Graph.Curve);
            }
        });

        drawClear.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                panel.clear();
            }
        });

        drawSave.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                try
                {
                    panel.saveImage();
                }
                catch (IOException ex)
                {
                    ex.printStackTrace();
                }
            }
        });

        return menuBar;
    }
}
