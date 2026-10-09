package OLD1.Disc;

import java.util.Random;

public class Sort
{
    private final Comparer cmp;
    public Sort(Comparer cp){ cmp = cp;}
    private static int cnt = 0;
    private Object[] a;
    private static final Random rdm = new Random();
    private void swap(int l,int r)
    {
        Object tmp = a[l];
        a[l] = a[r];
        a[r] = tmp;
    }
    private void insertSort(int l,int r)
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
    private void selectSort(int l,int r)
    {
        for(int i = l; i < r - 1;++i)
        {
            int v = i;
            for(int j = i + 1; j != r;++j) if(cmp.compare(a[j],a[v]) < 0) v = j;
            swap(i,v);
        }
    }
    private int SA(int l,int r)
    {
        int sa = rdm.nextInt(l,r);
        int left = l - 1,right = r - 1;
        swap(right,sa);
        int pivot = right;
        while(left < right)
        {
            while (left != r && cmp.compare(a[++left], a[pivot]) < 0);
            while (right > l && cmp.compare(a[pivot], a[--right]) < 0);
            if (left < right) swap(left,right);
        }
        swap(left,pivot);
        return left;
    }
    private void quick_sort(int l,int r)
    {
        if(r - l >= cnt)
        {
            int border = SA(l,r);
            quick_sort(l,border);
            quick_sort(border + 1,r);
        }
        else
        {
            boolean k = rdm.nextBoolean();
            if(k) insertSort(l,r);
            else selectSort(l,r);
        }
    }
    public void sort(Object[] arr)
    {
        if(arr == null || !cmp.isRight(arr[0])) throw new IllegalArgumentException();
        cnt = arr.length / 4 + 1;
        a = arr;
        quick_sort(0,arr.length);
    }
    public void selectSort(Object[] arr)
    {
        if(arr == null || !cmp.isRight(arr[0])) throw new IllegalArgumentException();
        a = arr;
        selectSort(0,arr.length);
    }
    public void insertSort(Object[] arr)
    {
        if(arr == null || !cmp.isRight(arr[0])) throw new IllegalArgumentException();
        a = arr;
        insertSort(0,arr.length);
    }
}

