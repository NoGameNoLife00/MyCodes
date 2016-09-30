package MyThreadPool;

import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.SynchronousQueue;
import java.util.concurrent.TimeUnit;


public class Executors {
    public static ThreadPoolExecutor newFixedThreadPool(int nThreads) {
        return new ThreadPoolExecutor(nThreads, nThreads,
                1000L, TimeUnit.MILLISECONDS,
                new LinkedBlockingQueue<Task>());
    }

    public static ThreadPoolExecutor newSingleThreadExecutor() {
        return (new ThreadPoolExecutor(1, 1,
                        1000L, TimeUnit.MILLISECONDS,
                        new LinkedBlockingQueue<Task>()));
    }

    public static ThreadPoolExecutor newCachedThreadPool() {
        return new ThreadPoolExecutor(0, Integer.MAX_VALUE,
                1L, TimeUnit.SECONDS,
                new SynchronousQueue<Task>());
    }

}
