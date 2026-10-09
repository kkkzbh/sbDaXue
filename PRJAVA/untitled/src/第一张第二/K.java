package 第一张第二;

import java.awt.*;
import java.awt.event.*;
import java.util.Arrays;
import java.util.Comparator;
import javax.swing.*;

class Text implements Comparable<Text>, Comparator<Text>
{
    @Override   // compareTo --> Comparable
    public int compareTo(Text o)
    {
        return Double.compare(1.1,1.10000000000000000000000000000000000000000000000000000000000000000000000000001);
    }

    @Override   // compare --> Comparator
    public int compare(Text o1, Text o2)
    {
        return 0;
    }
}

public class K extends JFrame implements ActionListener
{
    private JLabel l1,l2;
    private JTextField in,out;
    private JButton b1,b2;

    public K()
    {
        super("信息输入");
        setBounds(100,100,250,200);
        setLayout(new FlowLayout(FlowLayout.LEFT));
        l1 = new JLabel("请输入一个字符串，输入完毕后按回车");
        in = new JTextField(20);
        l2 = new JLabel("输入的信息是:");
        out = new JTextField(20);
        b1 = new JButton("重新输入");
        b2 = new JButton("退出");

        JPanel pb = new JPanel();
        pb.setLayout(new FlowLayout());
        pb.add(b1);
        pb.add(b2);

        in.addActionListener(this);
        b1.addActionListener(this);
        b2.addActionListener(this);

        Container c = getContentPane();
        c.add(l1);
        c.add(in);
        c.add(l2);
        c.add(out);
        c.add(pb);

        setVisible(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
    }

    public void actionPerformed(ActionEvent e)
    {
        if(e.getSource() == in)
        {
            out.setText(in.getText());
            in.setText("");
        }
        else if(e.getSource() == b1)
        {
            out.setText("");
        }
        else if(e.getSource() == b2)
        {
            System.exit(0);
        }
    }

    public static void main(String[] args)
    {
        K k = new K();
        double d = Double.parseDouble("1.1");
        int[] a = new int[10];
        Arrays.sort(a);
    }
}
