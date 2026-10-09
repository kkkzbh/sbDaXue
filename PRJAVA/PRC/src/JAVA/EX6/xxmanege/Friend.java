package EX6.xxmanege;

import java.util.Vector;

public class Friend
{
    private String name;
    private String sex;
    private String phone;
    private String relation;

    public Friend(String name, String sex, String phone, String relation)
    {
        this.name = name;
        this.sex = sex;
        this.phone = phone;
        this.relation = relation;
    }

    public Friend(String name, String sex, String phone)
    {
        this.name = name;
        this.sex = sex;
        this.phone = phone;
    }

    public Friend(String name, String sex)
    {
        this.name = name;
        this.sex = sex;
    }

    public Friend(String name)
    {
        this.name = name;
    }

    public String getSex()
    {
        return sex;
    }

    public String getName()
    {
        return name;
    }

    public String getPhone()
    {
        return phone;
    }

    public String getRelation()
    {
        return relation;
    }

    public void setName(String name)
    {
        this.name = name;
    }

    public void setSex(String sex)
    {
        this.sex = sex;
    }

    public void setPhone(String phone)
    {
        this.phone = phone;
    }

    public void setRelation(String relation)
    {
        this.relation = relation;
    }

    public Vector<String> message()
    {
        Vector<String> mes = new Vector<>();
        mes.add(name);
        mes.add(sex);
        mes.add(phone);
        mes.add(relation);
        return mes;
    }

}
