package JAVA.T13;


import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MyJFrame extends JFrame {
    JMyPanel panel = new JMyPanel();
    public MyJFrame() {
        this.setTitle("画图");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setSize(500, 500);
        this.setLocationRelativeTo(null);
        this.add(mainMenu(),BorderLayout.NORTH);
        this.add(panel, BorderLayout.CENTER);
        this.setVisible(true);
    }

    private JMenuBar mainMenu() {
        JMenuBar menuBar = new JMenuBar();
        JMenu menuDraw=new JMenu("画图");
        menuDraw.setMnemonic('D');
        JMenuItem menuDrawRect=new JMenuItem("画矩形");
        menuDraw.add(menuDrawRect);
        JMenuItem menuDrawCurv=new JMenuItem("画曲线");
        menuDraw.add(menuDrawCurv);
        JMenuItem menuClear=new JMenuItem("清屏幕");
        menuDraw.add(menuClear);
        menuBar.add(menuDraw);
        menuDrawRect.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                panel.setAction(JMyPanel.Rect);
            }
        });
        menuDrawCurv.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                panel.setAction(JMyPanel.Curv);
            }
        });
        menuClear.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                panel.clearScreen();
            }
        });
        return menuBar;
    }
}
