package Test;

import java.lang.reflect.Method;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.TimeUnit;

import MyThreadPool.Executors;
import MyThreadPool.Task;
import MyThreadPool.ThreadPoolExecutor;

/**
 * Created by Administrator on 2016/3/30.
 */
public class MainTest {
	
    public static void  main(String[] args){
//        ThreadPoolTest1();
//        ThreadPoolTest2();
        ThreadPoolTest3();
    }

    private static void ThreadPoolTest1(){
        ThreadPoolExecutor pool = Executors.newCachedThreadPool();
        Method method = null;
		try {
			method = TestThread.class.getMethod("execute", Object.class);
		} catch (NoSuchMethodException e1) {
			e1.printStackTrace();
		} catch (SecurityException e1) {
			e1.printStackTrace();
		}
        Task task1 = new Task(new TestThread(), method,  5);
        try {
            for (int i = 0; i < 5; i++){
                pool.execute(task1);
                Thread.sleep(1000);
            }
            Thread.sleep(10000);
            pool.execute(task1);
            pool.shutdown();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

    }

    private static void ThreadPoolTest2(){
    	ThreadPoolExecutor pool = Executors.newFixedThreadPool(3);
        Method method = null;
		try {
			method = TestThread.class.getMethod("execute", Object.class);
		} catch (NoSuchMethodException e1) {
			e1.printStackTrace();
		} catch (SecurityException e1) {
			e1.printStackTrace();
		}
        Task task1 = new Task(new TestThread(), method,  5);
        try {
            for (int i = 0; i < 5; i++){
                pool.execute(task1);
                Thread.sleep(1000);
            }
            Thread.sleep(10000);
            pool.execute(task1);
            pool.shutdown();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private static void ThreadPoolTest3(){
    	ThreadPoolExecutor pool = new ThreadPoolExecutor(2, 3, 5, TimeUnit.SECONDS, new ArrayBlockingQueue<Task>(2));
        Method method = null;
		try {
			method = TestThread.class.getMethod("execute", Object.class);
		} catch (NoSuchMethodException e1) {
			e1.printStackTrace();
		} catch (SecurityException e1) {
			e1.printStackTrace();
		}
        Task task1 = new Task(new TestThread(), method,  5);
        try {
            for (int i = 0; i<10; i++){
                pool.execute(task1);
            }
            Thread.sleep(15000);
            pool.execute(task1);
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
    
    
}

