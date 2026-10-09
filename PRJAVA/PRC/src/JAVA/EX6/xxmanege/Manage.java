package EX6.xxmanege;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Vector;
import java.util.List;

import static java.lang.System.exit;

public class Manage extends JFrame
{

    /* ****************************************************************** /*
                Menu
    /* ****************************************************************** */

    private JMenuBar MenuBar = new JMenuBar();
    private JMenu funSec = new JMenu("功能选择");
    private JMenu find = new JMenu("查询");
    private JMenuItem ad = new JMenuItem("添加");
    private JMenuItem del = new JMenuItem("删除选中项");
    private JMenuItem browse = new JMenuItem("浏览电话簿");
    private JMenuItem exit = new JMenuItem("退出");
    private JMenuItem findName = new JMenuItem("按姓名查询");
    private JMenuItem findSex = new JMenuItem("按性别查询");
    private JMenuItem findPhone = new JMenuItem("按电话号码查询");
    private JMenuItem findRelation = new JMenuItem("按关系查询");
    {
        ad.addActionListener(new ActionListener()
        {

            @Override
            public void actionPerformed(ActionEvent e)
            {
                addButton.doClick();
            }
        });


        findName.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                findKey.setSelectedIndex(keyIndex.get("姓名"));
                findKeyText.getActionListeners()[0].actionPerformed(e);
            }
        });

        findSex.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                findKey.setSelectedIndex(keyIndex.get("性别"));
                findKeyText.getActionListeners()[0].actionPerformed(e);
            }
        });

        findPhone.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                findKey.setSelectedIndex(keyIndex.get("电话号码"));
                findKeyText.getActionListeners()[0].actionPerformed(e);
            }
        });

        findRelation.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                findKey.setSelectedIndex(keyIndex.get("关系"));
                findKeyText.getActionListeners()[0].actionPerformed(e);
            }
        });

        del.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                if(tableModel.getDataVector() == contains)
                {
                    int[] sec = table.getSelectedRows();
                    int del = 0;
                    for (int i : sec)
                    {
                        friendList.remove(i - del);
                        tableModel.removeRow(i - del);
                        ++del;
                    }
                }
                else
                {
                    int[] sec = table.getSelectedRows();
                    int del = 0;
                    for(int i : sec)
                    {
                        Vector v = findContains.elementAt(i - del);
                        int index = 0;
                        for (; index != contains.size(); ++index)
                        {
                            if (v.equals(contains.elementAt(index)))
                                break;
                        }
                        tableModel.removeRow(i - del);
                        friendList.remove(index);
                        contains.remove(index);
                        ++del;
                    }
                }
            }
        });

        browse.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                tableModel.setDataVector(contains,title);
            }
        });

        exit.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                exit(0);
            }
        });

        MenuBar.add(funSec);
        funSec.add(ad);
        funSec.add(del);
        funSec.add(find);
        funSec.add(browse);
        funSec.addSeparator();
        funSec.add(exit);
        find.add(findName);
        find.add(findSex);
        find.add(findPhone);
        find.add(findRelation);
    }


    /* ****************************************************************** /*
                Tool
    /* ****************************************************************** */

    JLabel findKeyLabel = new JLabel("查找关键字");
    String[] KeyList = { "姓名","性别","电话号码","关系" };
    HashMap<String,Integer> keyIndex = new HashMap<>();
    {
        keyIndex.put("姓名",0);
        keyIndex.put("性别",1);
        keyIndex.put("电话号码",2);
        keyIndex.put("关系",3);
    }
    JComboBox<String> findKey = new JComboBox<>(KeyList);
    JTextField findKeyText = new JTextField(8);
    Vector<Vector> findContains = new Vector<>();
    JToolBar toolBar = new JToolBar();
    {
        findKeyText.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                String key = findKeyText.getText();
                int index = findKey.getSelectedIndex();
                findContains.removeAllElements();
                for(Vector vs : contains)
                {
                    if(vs.elementAt(index).equals(key))
                        findContains.addElement(vs);
                }
                tableModel.setDataVector(findContains,title);
                tableModel.fireTableDataChanged();
            }
        });

        findKey.setMaximumSize(new Dimension(70, 30));
        findKeyText.setMaximumSize(new Dimension(140, 30));
        toolBar.add(findKeyLabel);
        toolBar.add(findKey);
        toolBar.add(findKeyText);
        toolBar.setPreferredSize(new Dimension(300,30));
        toolBar.setFloatable(false);
    }



    /* ****************************************************************** /*
                Table
    /* ****************************************************************** */

    ArrayList<Friend> friendList = new ArrayList<>();
    Vector<String> title = new Vector<>(List.of(KeyList));
    Vector<Vector> contains = new Vector<>();
    DefaultTableModel tableModel = new DefaultTableModel(contains,title);
    JTable table = new JTable(tableModel);
    JScrollPane tableSP = new JScrollPane(table);




    /* ****************************************************************** /*
                bottom
    /* ****************************************************************** */

    JLabel nameLabel = new JLabel("姓名");
    JTextField nameText = new JTextField(8);
    JLabel sexLabel = new JLabel("性别");
    JTextField sexText = new JTextField(8);
    JLabel phoneLabel = new JLabel("电话号码");
    JTextField phoneText = new JTextField(8);
    JLabel relationLabel = new JLabel("关系");
    JTextField relationText = new JTextField(8);
    JButton addButton = new JButton("添加");
    JPanel bottomPanel = new JPanel();
    {
        addButton.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                String name = nameText.getText();
                if(name.isEmpty())
                {
                    JOptionPane.showMessageDialog(Manage.this,"姓名不能为空!","提示",JOptionPane.ERROR_MESSAGE);
                }
                else
                {
                    String sex = sexText.getText();
                    String phone = phoneText.getText();
                    String relation = relationText.getText();
                    Friend people = new Friend(name, sex, phone, relation);
                    friendList.add(people);
                    tableModel.addRow(people.message());
                }
            }
        });


        bottomPanel.add(nameLabel);
        bottomPanel.add(nameText);
        bottomPanel.add(sexLabel);
        bottomPanel.add(sexText);
        bottomPanel.add(phoneLabel);
        bottomPanel.add(phoneText);
        bottomPanel.add(relationLabel);
        bottomPanel.add(relationText);
        bottomPanel.add(addButton);
    }



    /* ****************************************************************** /*
                dialog
    /* ****************************************************************** */

    /*
     *  also have other realize which in the region of bottom.
     */






    /* ****************************************************************** /*
                utility
    /* ****************************************************************** */

    public Manage()
    {
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setBounds(100, 100, 450, 300);
        setLocationRelativeTo(null);
        setPreferredSize(new Dimension(800, 600));


        setJMenuBar(MenuBar);
        getContentPane().add(toolBar,BorderLayout.NORTH);
        getContentPane().add(tableSP,BorderLayout.CENTER);
        getContentPane().add(bottomPanel,BorderLayout.SOUTH);


        pack();
        setVisible(true);
    }

}
