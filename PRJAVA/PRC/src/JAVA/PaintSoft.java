package JAVA;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.border.BevelBorder;

class SoftExa{
	public static void main(String[] args) {
		new PaintSoft();
	}
}

/*
 * �ҵ����岼���ǽ���������Ϊ�߲��֣�Ȼ������һ����ѡ����壬ѡ��Ҫ����ͼ��
 * �м��ǻ���壬�������ﻭͼ�������������ͱ�����水ť������һ����������
 * ���߹ؼ����ڵ������ȡ�㣬Ȼ�󽫵����ӣ����߹ؼ������϶������µ㣬������
 * �����ߣ���ô�Ϳ���һ�����ߣ�Բ�;��ιؼ����ڻ�ȡ�϶�����ȡ�������㣬Բ
 * ע��뾶�����ã�����ע�ⳤ��ߡ�������㷨����Ϊ������״�Ķ����Լ��ӹ�����
 */
public class PaintSoft extends JFrame implements ItemListener{
	int count=0;
	JRadioButton[] radioItem;
	Shape currentShape;
	JButton[] button;
	DrawPanel drawPanel=new DrawPanel();
	public PaintSoft()
	{
		this.setTitle("³�ٺ�Ļ�ͼ����");
		this.setSize(650,550);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.setLocationRelativeTo(null);
		//ͼ��ѡ�� ��ѡ
		this.add(addRadio(),BorderLayout.NORTH);
		//�ӻ����
		drawPanel.setBackground(Color.WHITE);
		this.add(drawPanel,BorderLayout.CENTER);
		//�Ӱ�ť��� ��
		this.add(addButton(),BorderLayout.SOUTH);
		this.setVisible(true);
	}
	
	public JPanel addButton()//��Ӱ�ť  ���� ����
	{
		button=new JButton[2];
		button[0]=new JButton("����");
		button[1]=new JButton("�������");
		
		JPanel buttonPanel=new JPanel();
		buttonPanel.setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
		for(int i=0;i<button.length;i++)
		{
			button[i].setFont(new Font("����",Font.CENTER_BASELINE,15));
			button[i].addActionListener(new ActionListener() {

				@Override
				public void actionPerformed(ActionEvent e) {
					// TODO Auto-generated method stub
					if(e.getSource()==button[0])
						drawPanel.clearPanel();
					else {
						  exitPaint();
					}
				}

				private void exitPaint() {//���滭ͼ
					BufferedImage im=new BufferedImage(drawPanel.getWidth(),drawPanel.getHeight(),BufferedImage.TYPE_4BYTE_ABGR);
					  Graphics g=im.getGraphics();
//					  g.drawRect(100,,2000,2000);
					  drawPanel.paint(g);
					  File out=new File("D:\\java����ҵͼƬ.png");
					  try {//������ʾ��
						ImageIO.write(im,"png",out);
						JOptionPane.showMessageDialog(null, "����ɹ���", "��ʾ", JOptionPane.QUESTION_MESSAGE);
					} catch (IOException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
						JOptionPane.showMessageDialog(null, "����ʧ�ܣ�", "��ʾ", JOptionPane.QUESTION_MESSAGE);
					}
				}
				
			});
			buttonPanel.add(button[i]);
		}
		
		return buttonPanel;
	}
	
	private JPanel addRadio() {//��ѡ��
		radioItem=new JRadioButton[4];
		radioItem[0]=new JRadioButton("����");
		radioItem[1]=new JRadioButton("����");
		radioItem[2]=new JRadioButton("����");
		radioItem[3]=new JRadioButton("Բ��");
		//��ѡ��ťʹ�� ���  ��ѡ  ��ť��
		JPanel groupPanel=new JPanel();
		groupPanel.setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
		ButtonGroup group=new ButtonGroup();
		for(int i=0;i<radioItem.length;i++)
		{
			radioItem[i].setFont(new Font("����",Font.CENTER_BASELINE,15));
			groupPanel.add(radioItem[i]);
			group.add(radioItem[i]);
			radioItem[i].addItemListener(this);
		}
		return groupPanel;
	}
	@Override
	public void itemStateChanged(ItemEvent e) {
		// TODO Auto-generated method stub
		if(e.getSource()==radioItem[0])
			drawPanel.setAction(DrawPanel.BrokenLine);
		else if(e.getSource()==radioItem[1])
			drawPanel.setAction(DrawPanel.Curv);
		else if(e.getSource()==radioItem[2])
			drawPanel.setAction(DrawPanel.Retangle);
		else if(e.getSource()==radioItem[3])
			drawPanel.setAction(DrawPanel.Circle);
	}
}

class DrawPanel extends  JPanel
{
	public static final int BrokenLine=0;//����ģʽ����
	public static final int Curv=1;//����
	public static final int Retangle=2;//����
	public static final int Circle=3;//Բ
	private ArrayList<Shape> shapes=new ArrayList<>();
	private Shape shape=null;
	private MyListener listener;
	
	public DrawPanel()
	{
		listener=new MyListener();
		this.addMouseListener(listener);
		this.addMouseMotionListener(listener);
		listener.setFactory(new RetangleFactory(this));//Ĭ�ϻ�����
	}
	
	public void paint(Graphics g) {
        g.clearRect(0,0,this.getWidth(),this.getHeight());
        if(!shapes.isEmpty()){
            for(Shape ms:shapes)
            	ms.draw(g);
        }
        if(shape!=null)
        	shape.draw(g);//��Ӧ�Ļ�����
    }
	
	public void producing(Shape shape) {
        this.shape=shape;
        this.repaint();
    }
    public void produced(Shape shape){
        this.shape=null;
        shapes.add(shape);
//        this.repaint();
    }
    
    public void setAction(int action)
    {
    	if(listener==null)
    		return;
    	switch(action) {
    	case(BrokenLine):
    		listener.setFactory(new BrokenLineFactory(this));
    	     break;
    	case(Curv):
    		listener.setFactory(new CurvFactory(this));
    	    break;
    	case(Retangle):
    		listener.setFactory(new RetangleFactory(this));
    	    break;
    	case(Circle):
    		listener.setFactory(new CircleFactory(this));
    		break;
    	}
    }
    
    public void clearPanel()//����
    {
    	shape=null;
    	shapes.clear();
    	this.repaint();
    }
	
}

class MyListener implements MouseListener,MouseMotionListener{
	private ShapeFactory current=null;

	public void setFactory(ShapeFactory f){
		current=f;
    }
	@Override
	public void mouseDragged(MouseEvent e) {
		// TODO Auto-generated method stub
		if(current!=null)
			current.mouseDragged(e);
	}

	@Override
	public void mouseMoved(MouseEvent e) {
		// TODO Auto-generated method stub
		if(current!=null)
			current.mouseMoved(e);
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		if(current!=null)
			current.mouseClicked(e);
	}

	@Override
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub
		if(current!=null)
			current.mousePressed(e);
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		if(current!=null)
			current.mouseReleased(e);
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		if(current!=null)
			current.mouseEntered(e);
	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		if(current!=null)
			current.mouseExited(e);
	}
	
}

/*
 * ͳһע��һ�����⣬�Ǿ��ǻ��ʵ���ɫ��������ʵ���ɫ��draw���ú��ˣ�
 * ��ô�������ʱ�����Ǻ�ɫ�ģ�������ɫҪС�Ĳ����Ǻ�ɫ
 */
abstract class Shape{
	public abstract void draw(Graphics g);
}
abstract class ShapeFactory implements MouseListener,MouseMotionListener{
	protected DrawPanel drawPanel;
	public ShapeFactory(DrawPanel panel)
	{
		drawPanel=panel;
	}
	public abstract void mouseClicked(MouseEvent e) ;
    public abstract void mousePressed(MouseEvent e) ;
    public abstract void mouseReleased(MouseEvent e) ;
    public abstract void mouseEntered(MouseEvent e) ;
    public abstract void mouseExited(MouseEvent e) ;
    public abstract void mouseDragged(MouseEvent e) ;
    public abstract void mouseMoved(MouseEvent e) ;
}

//����
class BrokenLine extends Shape
{
	ArrayList<Point> points;//�����
	
	public BrokenLine()
	{
		points=new ArrayList<>();
	}

	public void draw(Graphics g) {
		
		for (Point point : points) {  
            g.fillOval(point.x - 2, point.y - 2, 4, 4); // ����СԲ���ʾ��  
        }  
		if(points.size()>=2)//������������
		{
			for(int i=0;i<points.size()-1;i++)
			{
				g.drawLine(points.get(i).x, points.get(i).y, points.get(i+1).x, points.get(i+1).y);
			}
		}
		
	}

}

class BrokenLineFactory extends ShapeFactory{
	private BrokenLine line=null;

	public BrokenLineFactory(DrawPanel panel) {
		super(panel);
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		if(line==null)//������Ĵ���������һ�Σ���ε�����ǵ�ǰ����ʵ������
			line=new BrokenLine();
		line.points.add(e.getPoint());
		drawPanel.producing(line);
	}

	@Override
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		if(line!=null)
		{
			line.points.add(e.getPoint());
			drawPanel.produced(line);//Ϊʲôproduced��ing����
		}
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseDragged(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseMoved(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	
}

class Curv extends Shape
{
	ArrayList<Point> points=new ArrayList<>();
	
	@Override
	public void draw(Graphics g) {
		// TODO Auto-generated method stub
		for(int i=1;i<points.size();i++)
		{
			g.drawLine(points.get(i-1).x,points.get(i-1).y,points.get(i).x,points.get(i).y);
		}
	}
	
}

class CurvFactory extends ShapeFactory
{
	private Curv curv=null;

	public CurvFactory(DrawPanel panel) {
		super(panel);
		// TODO Auto-generated constructor stub
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub
		curv=new Curv();//ÿһ���϶���궼���µ�����ʵ������
		curv.points.add(e.getPoint());
		drawPanel.producing(curv);
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		drawPanel.produced(curv);
		curv=null;
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseDragged(MouseEvent e) {
		// TODO Auto-generated method stub
		curv.points.add(e.getPoint());//�϶������ӵ�
		drawPanel.producing(curv);
	}

	@Override
	public void mouseMoved(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	
}

class Retangle extends Shape
{
    private Point leftTop,rightBottom;//���Ͻ� ���½�
	
	public void setLeftTop(Point point)
	{
		leftTop=point;
	}
	
	public void setRightBottom(Point point)
	{
		rightBottom=point;
	}
	
	public void draw(Graphics g)
	{
		g.drawRect(leftTop.x,leftTop.y, rightBottom.x-leftTop.x, rightBottom.y-leftTop.y);
	}
	
}
class RetangleFactory extends ShapeFactory
{
	private Retangle retangle=null;
	
	public RetangleFactory(DrawPanel panel) {
		super(panel);
	}
	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub
		retangle=new Retangle();
		retangle.setLeftTop(e.getPoint());
		retangle.setRightBottom(e.getPoint());
		drawPanel.producing(retangle);
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		drawPanel.produced(retangle);
		retangle=null;
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseDragged(MouseEvent e) {
		// TODO Auto-generated method stub
		retangle.setRightBottom(e.getPoint());
		drawPanel.producing(retangle);
	}

	@Override
	public void mouseMoved(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	
}

class Circle extends Shape
{
	private Point top;
	private int r;//�뾶
	
	public void setTopPoint(Point point)
	{
		top=point;
	}

	public void setRadius(int r)
	{
		this.r=r;
	}
	
	@Override
	public void draw(Graphics g) {
		// TODO Auto-generated method stub
		g.drawOval(top.x, top.y, 2*r, 2*r);
	}
}

class CircleFactory extends ShapeFactory
{
	private Circle circle=null;
	private Point tmp;//��Ҫ�����㣬���������һ����

	public CircleFactory(DrawPanel panel) {
		super(panel);
		// TODO Auto-generated constructor stub
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub
		circle=new Circle();
		tmp=e.getPoint();
		circle.setTopPoint(tmp);
		circle.setRadius(0);//�����ð뾶Ϊ0
		drawPanel.producing(circle);
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		drawPanel.produced(circle);
		circle=null;
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseDragged(MouseEvent e) {
		// TODO Auto-generated method stub
		int dx = e.getPoint().x - tmp.x;
        int dy = e.getPoint().y - tmp.y;
        int radius = (int) ((Math.sqrt(dx * dx + dy * dy)/2)); // ����뾶  ����֮�����
        circle.setRadius(radius);
		drawPanel.producing(circle);
	}

	@Override
	public void mouseMoved(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	
}