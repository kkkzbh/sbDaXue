package EXEX;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;

public class Draw extends JFrame {
    private JPanel drawingPanel;
    private int startX, startY, endX, endY;
    private Shape currentShape;
    private String currentTool;

    public Draw() {
        setTitle("Smooth Drawing App");
        setSize(800, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        drawingPanel = new JPanel() {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                Graphics2D g2d = (Graphics2D) g;
                g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
                if (currentShape != null) {
                    currentShape.draw(g2d);
                }
            }
        };
        drawingPanel.setBackground(Color.WHITE);
        drawingPanel.addMouseListener(new MouseAdapter() {
            public void mousePressed(MouseEvent e) {
                startX = e.getX();
                startY = e.getY();
            }

            public void mouseReleased(MouseEvent e) {
                endX = e.getX();
                endY = e.getY();
                if (currentTool != null) {
                    if (currentTool.equals("Rectangle")) {
                        currentShape = new RectangleShape(startX, startY, endX, endY);
                    } else if (currentTool.equals("Circle")) {
                        currentShape = new CircleShape(startX, startY, endX, endY);
                    }
                    repaint();
                }
            }
        });
        drawingPanel.addMouseMotionListener(new MouseMotionAdapter() {
            public void mouseDragged(MouseEvent e) {
                endX = e.getX();
                endY = e.getY();
                if (currentTool != null) {
                    if (currentTool.equals("Rectangle")) {
                        currentShape = new RectangleShape(startX, startY, endX, endY);
                    } else if (currentTool.equals("Circle")) {
                        currentShape = new CircleShape(startX, startY, endX, endY);
                    }
                    repaint();
                }
            }
        });

        JToolBar toolBar = new JToolBar();
        String[] tools = {"Rectangle", "Circle"};
        for (String tool : tools) {
            JButton button = new JButton(tool);
            button.addActionListener(new ToolButtonListener(tool));
            toolBar.add(button);
        }

        JButton saveButton = new JButton("Save");
        saveButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                saveImage();
            }
        });
        toolBar.add(saveButton);

        getContentPane().add(toolBar, BorderLayout.NORTH);
        getContentPane().add(drawingPanel, BorderLayout.CENTER);
    }

    private class ToolButtonListener implements ActionListener {
        private String tool;

        public ToolButtonListener(String tool) {
            this.tool = tool;
        }

        public void actionPerformed(ActionEvent e) {
            currentTool = tool;
        }
    }

    private void saveImage() {
        BufferedImage image = new BufferedImage(drawingPanel.getWidth(), drawingPanel.getHeight(), BufferedImage.TYPE_INT_ARGB);
        Graphics2D g2d = image.createGraphics();
        drawingPanel.paint(g2d);
        g2d.dispose();

        File file = new File("drawing.png");
        try {
            ImageIO.write(image, "png", file);
            System.out.println("Image saved as: " + file.getAbsolutePath());
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private abstract class Shape {
        public abstract void draw(Graphics2D g);
    }

    private class RectangleShape extends Shape {
        private int x1, y1, x2, y2;

        public RectangleShape(int x1, int y1, int x2, int y2) {
            this.x1 = x1;
            this.y1 = y1;
            this.x2 = x2;
            this.y2 = y2;
        }

        public void draw(Graphics2D g) {
            g.setColor(Color.BLACK);
            g.drawRect(Math.min(x1, x2), Math.min(y1, y2), Math.abs(x2 - x1), Math.abs(y2 - y1));
        }
    }

    private class CircleShape extends Shape {
        private int x1, y1, x2, y2;

        public CircleShape(int x1, int y1, int x2, int y2) {
            this.x1 = x1;
            this.y1 = y1;
            this.x2 = x2;
            this.y2 = y2;
        }

        public void draw(Graphics2D g) {
            g.setColor(Color.BLACK);
            int radius = (int) Math.sqrt(Math.pow(x2 - x1, 2) + Math.pow(y2 - y1, 2));
            g.drawOval(x1 - radius, y1 - radius, 2 * radius, 2 * radius);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new Draw().setVisible(true);
            }
        });
    }
}
