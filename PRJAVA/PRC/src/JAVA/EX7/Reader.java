package EX7;

import java.util.concurrent.locks.ReentrantReadWriteLock;
import java.util.Random;

public class Reader implements Runnable
{
    private final Var var;
    private final ReentrantReadWriteLock lock;

    public Reader(Var var, ReentrantReadWriteLock lock)
    {
        this.var = var;
        this.lock = lock;
    }

    public void run()
    {
        lock.readLock().lock();
        System.out.println(Thread.currentThread().getName() + ": Reading : " + var.read());
        try
        {
            Thread.sleep(new Random().nextInt(800,1600));
        }
        catch(InterruptedException _){}
        lock.readLock().unlock();
    }
}
