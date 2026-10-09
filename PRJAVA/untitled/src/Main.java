

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

void main()
{
    Thread th = new Thread(new Runnable()
    {
        @Override
        public void run()
        {
            for(int i=0;i<10;i++)
            {
                System.out.println(Thread.currentThread().getName());
            }
        }
    });
    th.start();
    JButton b = new JButton("Click Me");
    b.addActionListener(new ActionListener()
    {

        @Override
        public void actionPerformed(ActionEvent e)
        {
            System.out.println(e.getActionCommand());
        }
    });
    JFrame f = new JFrame();
    Container C = f.getContentPane();

}