

package exprimentIV.Sorter;

import java.util.Comparator;
import java.util.Random;

public class Sorter<T extends Comparable<? super T>>
{
    private static final Random rdm = new Random();
    private static final int Cutoff = 10000;
    private Comparer cmp;
    private Comparator<T> comp;

    public Sorter(){}
    public Sorter(Comparer cmp)
    {
        this.cmp = cmp;
    }
    public Sorter(Comparator<T> comp)
    {
        this.comp = comp;
    }
    public void reset(Comparer cmp)
    {
        this.cmp = cmp;
    }
    public void reset(Comparator<T> comp)
    {
        this.comp = comp;
    }
    public void clear()
    {
        cmp = null;
        comp = null;
    }
    public void sort(Object[] a)
    {
        if(a == null)
            throw new IllegalArgumentException(); //空指针 或者错传排序数据 抛出不合法参数异常
        if(cmp == null) //如果没有设置cmp 默认调用quickSort
            quickSort(a,0,a.length);
        else
        {
            cmp.compare(a[0], a[1]); //这里进行一次空比较 如果说Object不是当前Sorter支持的cmp类型 则截止排序
            quickSort(a, 0, a.length, cmp);
        }
    }

    public void insertSort(Object[] a)
    {
        if (a == null)
            throw new IllegalArgumentException();
        if (cmp == null)
            insertSort(a, 0, a.length);
        else
        {
            cmp.compare(a[0], a[1]);
            insertSort(a, 0, a.length, cmp);
        }
    }

    public void sort(T[] a)
    {
        if(a == null)
            throw new IllegalArgumentException();
        if(comp == null)
            quickSort(a,0,a.length);
        else
            quickSort(a,0,a.length,comp);
    }


    private static Object midea3(Object[] a, int left, int right)
    {                           //取三者中位数 并直接分好 最左最右的数
        int mid = ((left + right--) >> 1);
        if(((Comparable)a[mid]).compareTo(a[left]) < 0)
            swap(a, left, mid);
        if(((Comparable)a[mid]).compareTo(a[right]) > 0)
            swap(a, right, mid);
        swap(a,mid,right - 1);  //把mid值 放到右边界的左边 纯个人习惯
        return a[right - 1];
    }

    public static void swap(Object[] a,int x,int y)
    {
        Object tmp = a[x];
        a[x] = a[y];
        a[y] = tmp;
    }

    private static void selectSort(Object[] a,int l,int r,Comparer cmp)
    {
        for(int i = l; i < r - 1;++i)
        {
            int v = i;
            for(int j = i + 1; j != r;++j) if(cmp.compare(a[j],a[v]) < 0) v = j;
            swap(a,i,v);
        }
    }

    private static void insertSort(Object[] a,int left,int right) //左闭右开
    {
        assert left < right;    //断言这个区间是一定存在的5
        if(right - left == 1) return;   //排除1个元素的情况
        for(int l = left + 1; l != right; l++)  //枚举待插入元素 从第二个元素开始插入
        {
            Object val = a[l];
            int j;
            for(j = l; j > left && ((Comparable)val).compareTo(a[j - 1]) < 0; j--) //计算插入点
                a[j] = a[j - 1];
            a[j] = val;
        }
    }

    private static void insertSort(Object[] a,int l,int r,Comparer cmp)
    {
        for(int i = l; i != r;++i)
        {
            int pos = i;
            Object val = a[i];
            while(pos > l && cmp.compare(a[pos - 1],val) > 0)
            {
                a[pos] = a[pos - 1];
                --pos;
            }
            a[pos] = val;
        }
    }

    private static <T> void insertSort(T[] a,int l,int r,Comparator<T> cmp)
    {
        for(int i = l; i != r;++i)
        {
            int pos = i;
            T val = a[i];
            while(pos > l && cmp.compare(a[pos - 1],val) > 0)
            {
                a[pos] = a[pos - 1];
                --pos;
            }
            a[pos] = val;
        }
    }

    private static void quickSort(Object[] a,int left,int right)
    {
        if(right - left + 1 > Cutoff)
        {
            Object pivot = midea3(a,left,right); //切分点
            int l = left;
            int r = right - 1;
            while(l < r)
            {
                while(((Comparable)pivot).compareTo(a[++l]) > 0){} //寻找不对劲点
                while(((Comparable)pivot).compareTo(a[--r]) < 0){}
                if(l < r)
                    swap(a,l,r);
            }
            swap(a,l,right - 1);
            quickSort(a,left,l);
            quickSort(a,l,right);
        }
        else
            insertSort(a,left,right);
    }

    private static void quickSort(Object[] a,int left,int right,Comparer cmp)
    {
        if(right - left + 1 > Cutoff)
        {
            swap(a,rdm.nextInt(left,right),right - 1);
            int l = left - 1;
            int r = right - 1;
            while(l < r)
            {
                while(l < right && cmp.compare(a[++l],a[right - 1]) < 0);
                while(r >= left && cmp.compare(a[--r],a[right - 1]) > 0);
                if(l < r)
                    swap(a,l,r);
            }
            swap(a,l,right - 1);
            quickSort(a,left,l,cmp);
            quickSort(a,l,right,cmp);
        }
        else
            insertSort(a,left,right,cmp);
    }

    private static <T> void quickSort(T[] a, int left, int right, Comparator<T> cmp)
    {
        if(right - left + 1 > Cutoff)
        {
            swap(a,rdm.nextInt(left,right),right - 1);
            int l = left - 1;
            int r = right - 1;
            while(l < r)
            {
                while(l < right && cmp.compare(a[++l],a[right - 1]) < 0);
                while(r >= left && cmp.compare(a[--r],a[right - 1]) > 0);
                if(l < r)
                    swap(a,l,r);
            }
            swap(a,l,right - 1);
            quickSort(a,left,l,cmp);
            quickSort(a,l,right,cmp);
        }
        else
            insertSort(a,left,right,cmp);
    }

}
