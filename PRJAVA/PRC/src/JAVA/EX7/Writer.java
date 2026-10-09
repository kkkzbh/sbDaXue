package EX7;

import java.util.concurrent.locks.ReentrantReadWriteLock;
import java.util.Random;

public class Writer implements Runnable
{
    private final Var var;
    private final int data;   //要写的
    private final ReentrantReadWriteLock lock;

    public Writer(Var var, int data, ReentrantReadWriteLock lock)
    {
        this.var = var;
        this.data = data;
        this.lock = lock;
    }

    public void run()
    {
        lock.writeLock().lock();
        var.write(data);
        System.out.println(Thread.currentThread().getName() + " write : " + data);
        try
        {
            Thread.sleep(new Random().nextInt(300,1200));
        }
        catch(InterruptedException _){}
        lock.writeLock().unlock();
    }
}
