package EX6.Set;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Objects;

public class Set extends JFrame
{

    private DefaultListModel<String> S1Model = new DefaultListModel<>();
    private JList<String> Set1 = new JList<>(S1Model);
    private JScrollPane sc1 = new JScrollPane(Set1);
    private JLabel l1 = new JLabel("整数");
    private JTextField input1 = new JTextField(10);
    private JButton b1 = new JButton("添加");
    private JPanel p1 = new JPanel(new BorderLayout());
    private JPanel pl = new JPanel(new BorderLayout());

    private String[] operators = { "+","-","*" };
    private JComboBox<String> operator = new JComboBox<>(operators);
    private JPanel opePanel = new JPanel(new BorderLayout());

    private DefaultListModel<String> S2Model = new DefaultListModel<>();
    private JList<String> Set2 = new JList<>(S2Model);
    private JScrollPane sc2 = new JScrollPane(Set2);
    private JLabel l2 = new JLabel("整数");
    private JTextField input2 = new JTextField(10);
    private JButton b2 = new JButton("添加");
    private JPanel p2 = new JPanel(new BorderLayout());
    private JPanel pr = new JPanel(new BorderLayout());

    private JButton equals = new JButton("=");
    private Box equBox = Box.createVerticalBox();

    private DefaultListModel<String> S3Model = new DefaultListModel<>();
    private JList<String> Set3 = new JList<>(S3Model);
    private JScrollPane sc3 = new JScrollPane(Set3);

    private Box box3 = Box.createHorizontalBox();

    public Set()
    {
        setTitle("集合运算");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setBounds(100, 100, 450, 300);
        setPreferredSize(new Dimension( 600, 200));

        sc1.setPreferredSize(new Dimension(200, 100));
        sc2.setPreferredSize(new Dimension(200, 100));
        sc3.setPreferredSize(new Dimension(150, 120));

        p1.add(l1,BorderLayout.WEST);
        p1.add(input1);
        p1.add(b1,BorderLayout.EAST);


        pl.add(sc1);
        pl.add(p1, BorderLayout.SOUTH);


        p2.add(l2,BorderLayout.WEST);
        p2.add(input2);
        p2.add(b2,BorderLayout.EAST);


        pr.add(sc2);
        pr.add(p2, BorderLayout.SOUTH);

        box3.add(Box.createHorizontalStrut(5));
        box3.add(pl);
        box3.add(Box.createHorizontalStrut(5));

        opePanel.add(operator, BorderLayout.NORTH);
        box3.add(opePanel);
        box3.add(Box.createHorizontalStrut(5));

        box3.add(pr);
        box3.add(Box.createHorizontalStrut(5));

        equBox.add(Box.createVerticalGlue());
        equBox.add(equals);
        equBox.add(Box.createVerticalGlue());
        box3.add(equBox);
        box3.add(Box.createHorizontalStrut(5));

        box3.add(sc3);
        box3.add(Box.createHorizontalStrut(5));


        b1.addActionListener(e ->
        {
            String s = input1.getText();
            if(!S1Model.contains(s))
                S1Model.addElement(input1.getText());
        });

        b2.addActionListener(e ->
        {
            String s = input2.getText();
            if(!S2Model.contains(s))
                S2Model.addElement(input2.getText());
        });

        equals.addActionListener(e ->
        {
           if(Objects.equals(operator.getSelectedItem(), "+"))
           {
               ArrayList<String> s1 = new ArrayList<>();
               for(int i = 0; i < S1Model.size(); i++)
               {
                   s1.add(S1Model.get(i));
               }
               ArrayList<String> s2 = new ArrayList<>();
               for(int i = 0; i < S2Model.size(); i++)
               {
                   s2.add(S2Model.get(i));
               }
               S3Model.removeAllElements();
                for(String s : s1)
                    if(!S3Model.contains(s))
                        S3Model.addElement(s);
                for(String s : s2)
                    if(!S3Model.contains(s))
                        S3Model.addElement(s);
           }
           else if(Objects.equals(operator.getSelectedItem(), "-"))
           {
               ArrayList<String> s1 = new ArrayList<>();
               for(int i = 0; i < S1Model.size(); i++)
               {
                   s1.add(S1Model.get(i));
               }
               ArrayList<String> s2 = new ArrayList<>();
               for(int i = 0; i < S2Model.size(); i++)
               {
                   s2.add(S2Model.get(i));
               }
               HashSet<String> set = new HashSet<>(s2);

               S3Model.removeAllElements();
               for(String s : s1)
               {
                   if(!set.contains(s) && !S3Model.contains(s))
                       S3Model.addElement(s);
               }
           }
           else
           {
               ArrayList<String> s1 = new ArrayList<>();
               for(int i = 0; i < S1Model.size(); i++)
               {
                   s1.add(S1Model.get(i));
               }
               ArrayList<String> s2 = new ArrayList<>();
               for(int i = 0; i < S2Model.size(); i++)
               {
                   s2.add(S2Model.get(i));
               }
               HashSet<String> set = new HashSet<>(s2);

               S3Model.removeAllElements();
               for(String s : s1)
               {
                   if(set.contains(s) && !S3Model.contains(s))
                       S3Model.addElement(s);
               }
           }
        });

        add(box3);
        pack();
        setLocationRelativeTo(null);
        setVisible(true);
    }
}

class Main
{
    public static void main(String[] args)
    {
        new Set();
    }
}