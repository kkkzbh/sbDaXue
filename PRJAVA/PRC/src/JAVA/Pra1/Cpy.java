package JAVA.Pra1;

import java.awt.*;
import java.awt.event.*;

public class Cpy extends Frame implements ActionListener
{
    private TextField cpy_text,clear_text;
    private Button cpy_but,clear_but;

    Cpy()
    {
        super("CopyDemo");
        setBounds(400,250,300,100);
        setLayout(new FlowLayout());
        cpy_text = new TextField(10);
        clear_text = new TextField(10);
        setFont(new Font("宋体", Font.PLAIN, 12));
        cpy_but = new Button("复制");
        clear_but = new Button("清空");
        add(cpy_text);
        add(cpy_but);
        add(clear_text);
        add(clear_but);
        cpy_but.addActionListener(this);
        clear_but.addActionListener(this);
        addWindowListener(new Close());
        setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent event)
    {
        if(event.getSource() == cpy_but)
        {
            String text = cpy_text.getText();
            clear_text.setText(text);
        }
        else if(event.getSource() == clear_but)
        {
            clear_text.setText("");
            cpy_text.setText("");
        }
    }
}

class Close implements WindowListener
{

    @Override
    public void windowOpened(WindowEvent e){}

    @Override
    public void windowClosing(WindowEvent e)
    {
        System.exit(0);
    }

    @Override
    public void windowClosed(WindowEvent e){}

    @Override
    public void windowIconified(WindowEvent e){}

    @Override
    public void windowDeiconified(WindowEvent e){}

    @Override
    public void windowActivated(WindowEvent e){}

    @Override
    public void windowDeactivated(WindowEvent e){}
}

class Main
{
    public static void main(String[] args)
    {
        new Cpy();
    }
}