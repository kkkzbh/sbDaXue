package JAVA.Joseph;

public class Person
{
    private int id;
    private Person left;
    private Person right;

    public Person(int id)
    {
        this.id = id;
    }
    public boolean numberOff(int v)
    {
        if(v == 0) return false;
        return true;
    }
    public void die()
    {
        System.out.println(getId() + "离开了");
        this.left.together(this.right);
    }
    public void together(Person p)
    {
        this.right = p;
        p.left = this;
    }
    public Person next()
    {
        return this.right;
    }
    public int getId()
    {
        return id;
    }
}
