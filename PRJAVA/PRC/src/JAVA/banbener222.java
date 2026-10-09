package JAVA;//只能保存

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

public class banbener222 extends JFrame {
    private Shape currentShape; // 当前绘制的图形
    private Color currentColor = Color.BLACK; // 当前绘制的颜色
    private int startX, startY; // 起始坐标
    private int endX, endY; // 结束坐标
    public banbener222() {
        setTitle("Resizable Drawing App");
        setSize(800, 600);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        JPanel drawingPanel = new JPanel() {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                Graphics2D g2d = (Graphics2D) g;
                if (currentShape != null) {
                    g2d.setColor(currentColor);
             //       g2d.draw(currentShape);
                }
            }
        };

        drawingPanel.addMouseListener(new MouseAdapter() {
            public void mousePressed(MouseEvent e) {
                startX = e.getX();
                startY = e.getY();
                endX = startX;
                endY = startY;
            }

            public void mouseReleased(MouseEvent e) {
                if (currentShape != null) {
                    currentShape = null;
                    repaint();
                }
            }
        });
        drawingPanel.addMouseMotionListener(new MouseMotionAdapter() {
            public void mouseDragged(MouseEvent e) {
                endX = e.getX();
                endY = e.getY();
                if (currentShape != null) {
//                    if (currentShape instanceof Rectangle2D) {
//                        ((Rectangle2D) currentShape).setFrameFromDiagonal(startX, startY, endX, endY);
//                    } else if (currentShape instanceof Ellipse2D) {
//                        ((Ellipse2D) currentShape).setFrameFromDiagonal(startX, startY, endX, endY);
//                    }
                    repaint();
                }
            }
        });
        JMenuBar menuBar = new JMenuBar();
        JMenu fileMenu = new JMenu("File");
        JMenuItem saveItem = new JMenuItem("Save");

        saveItem.addActionListener(e -> {
            try {
                saveImage(drawingPanel);
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        });
        fileMenu.add(saveItem);
        menuBar.add(fileMenu);
        setJMenuBar(menuBar);

        getContentPane().add(drawingPanel);
    }

    private void saveImage(Component component) throws IOException {
        BufferedImage image = new BufferedImage(component.getWidth(), component.getHeight(), BufferedImage.TYPE_INT_RGB);
        component.paint(image.getGraphics());
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setDialogTitle("Save Image");
        int userSelection = fileChooser.showSaveDialog(this);
        if (userSelection == JFileChooser.APPROVE_OPTION) {
            File fileToSave = fileChooser.getSelectedFile();
            ImageIO.write(image, "png", fileToSave);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            banbener222 app = new banbener222();
            app.setVisible(true);
        });
    }
}