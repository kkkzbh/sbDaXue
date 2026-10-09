package OLD1;


public class RMB
{
    private static String[] place = {"","","拾","佰","仟","万","拾","佰","扦","亿","十亿",};
    private static String[] num = {"零","壹","贰","叁","肆","伍","陆","柒","捌","玖"};
    private static String[] minu = {"","分","角"};
    private static int find_point(String str)
    {
        int point_place;    //寻找数字中的.
        for(point_place = 0; point_place < str.length() - 1;++point_place) if(str.charAt(point_place) == '.') break;
        return point_place;
    }
    private static int small_first(String str,int point_place)
    {
        int beg_small;  //忽略前导0时的记录小数开始的位置
        for(beg_small = point_place + 1; beg_small < str.length() && str.charAt(beg_small) == '0';++beg_small);
        return beg_small;
    }
    static class Int   //实在用不了指针 我真没办法了
    {
        public int digit_count;  //记录整数的位数
        Int(int x) { digit_count = x;}
    }
    private static int next_zero(String str, int p, int point_place, Int digit,StringBuilder ans)
    {
        int tmp = p;
        while(str.charAt(p) == '0' && p != point_place )
        {
            if(place[digit.digit_count].equals("万") || place[digit.digit_count].equals("亿")) ans.append(place[digit.digit_count]);
            ++p;
            --digit.digit_count;
        }
        return p == tmp ? p : p == point_place ? p : p - 1;
    }
    private static void p_interger(String str,int point_place,StringBuilder ans)
    {
        Int digit = new Int(point_place);   //1000000
        for(int i = 0; i != point_place;i = next_zero(str,++i,point_place,digit,ans))   //排除连续0
        {
            String pre = num[str.charAt(i) - '0'];
            String back = place[digit.digit_count--];
            if(!(pre.equals("壹") && back.equals("拾")) || !ans.isEmpty()) ans.append(pre);
            if(!pre.equals("零") || back.equals("万") || back.equals("亿")) ans.append(back);
        }
    }
    private static void p_small(String str,int beg_small,StringBuilder ans)
    {
        for(int small_count = str.length() - beg_small;small_count != 0;--small_count)
            ans.append(num[str.charAt(beg_small++) - '0']).append(minu[small_count]);
    }
    public static String toString(double x)
    {
        String str = Double.toString(x);
        StringBuilder ans = new StringBuilder();
        int point_place = find_point(str);
        int beg_small = small_first(str,point_place);   //拿到小数的开始位置
        int small_count = str.length() - beg_small;   //记录小数位数
        p_interger(str,point_place,ans); ans.append("元");
        if(small_count == 0) ans.append("整");
        else p_small(str,beg_small,ans);

        return ans.toString();
    }

    //    public static String toString(double x)
//    {
//        String[] place = {"","","拾","佰","仟","万","拾","佰","扦","亿","十亿",};
//        String[] num = {"零","壹","贰","叁","肆","伍","陆","柒","捌","玖"};
//        String[] minu = {"","分","角"};
//        String str = Double.toString(x);
//        int dig = 0;        //小数点前 数字的个数
//        int dec = 0;        //小数点位置的尾后指针
//        int flag = 1;       //作用如下
//        for(int i = 0; i < str.length();++i)
//        {
//            if(str.charAt(i) == '.')
//            {
//                flag = 0;
//                dec = i + 1;
//            }
//            if(flag == 1) ++dig;
//        }
//        int fg = dec;
//        while(fg < str.length() && str.charAt(fg) == '0') fg++; //忽略小数点前导0
//        int d = str.length() - fg;  //计算实际小数位数
//        int isTwoNum = 0;
//        if(dig == 2) isTwoNum = 1;  //特判是否是两位数
//        StringBuilder ans = new StringBuilder();
//        String last = "";
//
//        for(int i = 0; i < dec - 1;++i) //对于整数部分
//        {
//            if(!last.equals("零") || !num[str.charAt(i) - '0'].equals("零"))
//            {
//                if(isTwoNum != 1 || !num[str.charAt(i) - '0'].equals("壹") )    //特判二位数
//                    if(i != dec - 2 || !num[str.charAt(i) - '0'].equals("零"))   //特判最后一位零
//                        ans.append(num[str.charAt(i) - '0']);   //拼接主词
//            }
//            if(!num[str.charAt(i) - '0'].equals("零"))
//            {
//                ans.append(place[dig--]);   //拼接谓词
//            }
//            else --dig;
//            last = num[str.charAt(i) - '0'];    //标记last的num
//        }
//        ans.append("元");    //添元
//        if(d == 0) ans.append("整"); //考虑小数点后的处理
//        else
//        {
//            while(d != 0)
//            {
//                ans.append(num[str.charAt(fg++) - '0']);
//                ans.append(minu[d--]);
//            }
//        }
//        return ans.toString();
//    }


}
