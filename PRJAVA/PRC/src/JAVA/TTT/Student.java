package JAVA.TTT;


public class Student
{
    private String no;
    private String name;
    private String yuwen;
    private String mathematiccs;

    public Student(String no, String name, String yuwen, String mathematiccs)
    {
        this.no = no;
        this.name = name;
        this.yuwen = yuwen;
        this.mathematiccs = mathematiccs;
    }

    public Student(String no, String name, String yuwen)
    {
        this.no = no;
        this.name = name;
        this.yuwen = yuwen;
    }

    public Student(String no, String name)
    {
        this.no = no;
        this.name = name;
    }

    public Student(String no)
    {
        this.no = no;
    }

    public Student()
    {

    }

    public String getNo()
    {
        return no;
    }
    public String getName()
    {
        return name;
    }
    public String getYuwen()
    {
        return yuwen;
    }
    public String getMathematiccs()
    {
        return mathematiccs;
    }

    public void setNo(String no)
    {
        this.no = no;
    }

    public void setName(String name)
    {
        this.name = name;
    }

    public void setYuwen(String yuwen)
    {
        this.yuwen = yuwen;
    }

    public void setMathematiccs(String mathematiccs)
    {
        this.mathematiccs = mathematiccs;
    }

    public String toString()
    {
        return "学号:" + no + " 姓名:" + name + " 语文" + yuwen + " 数学" + mathematiccs;
    }
}