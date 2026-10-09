package AWT;

import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
public class MyJFrame extends JFrame{
    JSpinner sp;
    JTextField tf1,tf2;
    public MyJFrame(String title)  {
        super(title);
        this.setSize(500, 400);
        this.setLayout(new FlowLayout());
        this.setLocationRelativeTo(null);
        this.addJTextField();

        SpinnerNumberModel sm=new SpinnerNumberModel();
        sp=new JSpinner(sm);
        sp.setPreferredSize(new Dimension(50,30));
        sp.addChangeListener(new ChangeListener() {

            @Override
            public void stateChanged(ChangeEvent arg0) {
                // TODO Auto-generated method stub
                tf2.setText((Integer)sp.getValue()+"");
            }});
        this.add(sp);

        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setVisible(true);
        // TODO Auto-generated constructor stub
    }
    private void addJTextField()
    {
        tf1=new JTextField(20);
        tf2=new JTextField(20);
        this.add(tf1);
        this.add(tf2);
        tf1.addCaretListener(new CaretListener() {

            @Override
            public void caretUpdate(CaretEvent arg0) {
                // TODO Auto-generated method stub
                tf2.setText(tf1.getText());
            }});
//		tf1.addActionListener(new ActionListener() {
//
//			@Override
//			public void actionPerformed(ActionEvent arg0) {
//				// TODO Auto-generated method stub
//				tf2.setText(tf1.getText());
//			}
//
//		});
    }
    public static void main(String[] args) {
        new MyJFrame("This is JFrame");
    }

}
