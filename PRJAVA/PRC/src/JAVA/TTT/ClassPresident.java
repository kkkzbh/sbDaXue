package JAVA.TTT;

public class ClassPresident extends Student
{


    public ClassPresident(String no, String name, String yuwen, String mathematiccs)
    {
        super(no, name, yuwen, mathematiccs);
    }

    public ClassPresident(String no, String name, String yuwen)
    {
        super(no, name, yuwen);
    }

    public ClassPresident(String no, String name)
    {
        super(no, name);
    }

    public ClassPresident(String no)
    {
        super(no);
    }

    public ClassPresident()
    {
    }

    @Override
    public String toString()
    {
        return "班长,学号:" + super.getNo() + " 姓名" + super.getName() + " 语文" + super.getYuwen() + " 数学" + super.getMathematiccs();
    }
}
