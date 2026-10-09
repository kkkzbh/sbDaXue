package EX6.RandomGGG;

import javax.swing.*;
import java.awt.*;
import java.util.Random;

public class RandomGGG
{
    private JFrame frame = new JFrame("随机数序列，查找重复值");
    private JLabel lenLabel = new JLabel("长度");
    private JTextField lenField = new JTextField(15);
    private JLabel rangeLabel = new JLabel("范围");
    private JTextField rangeField = new JTextField(15);
    private JButton b1 = new JButton("生成");
    private JButton b2 = new JButton("查找重复值");
    private Box box = Box.createHorizontalBox();

    private JPanel CntPanel = new JPanel(new GridLayout(5,0));

    private Random rand = new Random();

    private JTextField[] TextArray;

    public RandomGGG()
    {
        frame.setBounds(100, 100, 450, 300);
        frame.setPreferredSize(new Dimension(600, 500));
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        rand.setSeed(System.currentTimeMillis());

        b1.addActionListener(e ->
        {
            int len = Integer.parseInt(lenField.getText());
            int range = Integer.parseInt(rangeField.getText()) + 1;
            TextArray = new JTextField[len];
            CntPanel.removeAll();
            for(int i = 0; i < len; i++)
            {
                TextArray[i] = new JTextField();
                TextArray[i].setText(rand.nextInt(1,range) + "");
                CntPanel.add(TextArray[i]);
            }
            frame.revalidate();
        });

        b2.addActionListener(e ->
        {
            int len = Integer.parseInt(lenField.getText());
            int range = Integer.parseInt(rangeField.getText()) + 1;
            int[] bucket = new int[range];
            for(int i = 0; i != len; i++)
            {
                ++bucket[Integer.parseInt(TextArray[i].getText())];
            }
            for(int i = 0; i != len; i++)
            {
                if(bucket[Integer.parseInt(TextArray[i].getText())] > 1)
                {
                    TextArray[i].setBackground(Color.orange);
                }
            }
            frame.revalidate();
        });

        box.add(lenLabel);
        box.add(lenField);
        box.add(rangeLabel);
        box.add(rangeField);
        box.add(b1);
        box.add(b2);
        frame.add(box,BorderLayout.NORTH);

        frame.add(CntPanel);


        frame.pack();
        frame.setVisible(true);
    }

}
