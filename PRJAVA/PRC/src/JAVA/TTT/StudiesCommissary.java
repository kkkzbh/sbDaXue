package JAVA.TTT;

public class StudiesCommissary extends Student
{

    public StudiesCommissary(String no, String name, String yuwen, String mathematiccs)
    {
        super(no, name, yuwen, mathematiccs);
    }

    public StudiesCommissary(String no, String name, String yuwen)
    {
        super(no, name, yuwen);
    }

    public StudiesCommissary(String no, String name)
    {
        super(no, name);
    }

    public StudiesCommissary(String no)
    {
        super(no);
    }

    public StudiesCommissary()
    {
    }

    @Override
    public String toString()
    {
        return "学委,学号:" + super.getNo() + " 姓名" + super.getName() + " 语文" + super.getYuwen() + " 数学" + super.getMathematiccs();
    }
}
