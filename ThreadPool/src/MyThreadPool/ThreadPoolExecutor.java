package MyThreadPool;

import java.lang.reflect.InvocationTargetException;
import java.util.Date;
import java.util.LinkedList;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.SynchronousQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.ReentrantLock;

/**
 * Created by Administrator on 2016/3/31.
 */
public class ThreadPoolExecutor  {
    private enum Strategy {
        SYNCHRONOUS_QUEUE, // 直接提交策略， maximumPoolSize失效
        LINKED_BLOCKING_QUEUE,  // 无界队列策略maximumPoolSize失效
        ARRAY_BLOCKING_QUEUE    // 有界队列策略
    };


    private boolean isShowMessage = true;

    private int currPoolSize;
    private int corePoolSize;
    private int maximumPoolSize;
    private long keepAliveTime;
    private Strategy strategy;
    BlockingQueue<Task> workQueue;
    private LinkedList<WorkerThread> workThreads;
    private Object newWorkStart; // 信号量
    private ReentrantLock mainLock = new ReentrantLock();

    private int taskCount = 0;
    private AtomicInteger completeTaskCount = new AtomicInteger();
    private int workIndex = 0; // 工作线程编号
    private int getIdleThreadPollTime=50;//获取空闲线程轮询间隔时间,可配置 ms


    private boolean allowCoreThreadTimeOut = false;

    public ThreadPoolExecutor(int corePoolSize, int maximumPoolSize,
                              long keepAliveTime, TimeUnit timeUnit, BlockingQueue<Task> workQueue) throws IllegalArgumentException {
        if (corePoolSize < 0 || maximumPoolSize <= 0 || maximumPoolSize < corePoolSize || keepAliveTime < 0){
            throw new IllegalArgumentException();
        }
        if (workQueue == null){
            throw new NullPointerException();
        }

        this.corePoolSize = corePoolSize;
        this.maximumPoolSize = maximumPoolSize;
        this.keepAliveTime = timeUnit.toMillis(keepAliveTime);
        this.workQueue = workQueue;
        workThreads = new LinkedList<WorkerThread>();
        newWorkStart = new Object();
        currPoolSize = 0;
        if (workQueue.getClass() == SynchronousQueue.class){
            strategy = Strategy.SYNCHRONOUS_QUEUE;
        } else if (workQueue.getClass() == LinkedBlockingQueue.class){
            strategy = Strategy.LINKED_BLOCKING_QUEUE;
        } else if (workQueue.getClass() == ArrayBlockingQueue.class){
            strategy = Strategy.ARRAY_BLOCKING_QUEUE;
        }
    }

    public void shutdown(){
        for (WorkerThread worker : workThreads){
            worker.stopWorker();
        }
    }

    public void cleanOutTimeThread(){
    	if (keepAliveTime == 0){
    		return;
    	}
    	
        Date now = new Date();
        for (int i= 0; i < workThreads.size();){
            WorkerThread worker = workThreads.get(i);
            // 检测空闲线程的空闲时间
            if (worker.isWaiting()) {
                long dValue = now.getTime() - worker.getWaitingTime().getTime();
                // 空闲时间大于设定时间
                if (dValue > keepAliveTime) {
                    worker.stopWorker();
                    workThreads.remove(i);
                    continue;
                }
            }
            i++;
        }
    }

    // 移除任务队列中的任务，如果存在
    public boolean Remove(Task command){
        boolean removed = workQueue.remove(command);
        return removed;
    }

    private void executeBySynchronousQueue(Task command) throws InterruptedException{
        boolean success = workQueue.offer(command);
        while (!success){
            WorkerThread worker = new WorkerThread(++workIndex);
            worker.start();
            currPoolSize++;
            mainLock.lock();
            workThreads.add(worker);
            mainLock.unlock();
            synchronized (newWorkStart){
                success = workQueue.offer(command, 1, TimeUnit.MILLISECONDS);
            }
        }
        if (success){
            taskCount++;
        }
    }

    private void executeByLinkedBlockQueue(Task command) throws InterruptedException{
        boolean hasWaiting = false;
        for (WorkerThread worker : workThreads){
            // 当前线程池内有空闲线程
            if (worker.isWaiting()){
                hasWaiting = true;
                break;
            }
        }
        // 当线程池中工作线程没有空闲，且线程数小于核心线程数时
        if (!hasWaiting && currPoolSize < corePoolSize){
            WorkerThread w = new WorkerThread(++workIndex);
            w.start();
            currPoolSize++;
            mainLock.lock();
            workThreads.add(w);
            mainLock.unlock();
        }
        boolean success = workQueue.offer(command, 1, TimeUnit.MILLISECONDS);
        if (success){
            taskCount++;
        }
    }

    private void executeByArrayBlockingQueue(Task command) throws InterruptedException{
        boolean hasWaiting = false;
        boolean success = false;
        for (WorkerThread worker : workThreads){
            // 当前线程池内有空闲线程
            if (worker.isWaiting()){
                hasWaiting =true;
                break;
            }
        }

        // 当线程池中工作线程没有空闲，且线程数小于核心线程数时
        if (!hasWaiting && currPoolSize < corePoolSize){
            // 创建线程加入线程池
            WorkerThread w = new WorkerThread(++workIndex);
            w.start();
            currPoolSize++;
            mainLock.lock();
            workThreads.add(w);
            mainLock.unlock();
            success = workQueue.offer(command, 1, TimeUnit.MILLISECONDS);
            if (success){
                taskCount++;
            }
            return;
        }

        success = workQueue.offer(command, 1, TimeUnit.MILLISECONDS);
        // 工作队列已经满的时候,却当前线程数小于最大线程数，则继续创建线程
        if (!success && currPoolSize < maximumPoolSize){
            // 创建线程加入线程池
            WorkerThread w = new WorkerThread(++workIndex);
            w.start();
            currPoolSize++;
            workThreads.add(w);
            success = workQueue.offer(command, 1, TimeUnit.MILLISECONDS);
            return;
        } else if (!success) {
            // 工作线程，和当前线程数都达到最大数量时，报错
            System.out.println("can't execute new task");
        }

        if (success){
            taskCount++;
        }

        // 当前线程数大于核心线程数或允许清理核心线程时，清理超时线程
        if (allowCoreThreadTimeOut || (currPoolSize > corePoolSize)){
            cleanOutTimeThread();
        }
    }

    public void execute(Task command) throws InterruptedException {
        if (strategy == Strategy.SYNCHRONOUS_QUEUE){
            executeBySynchronousQueue(command);
        } else if (strategy == Strategy.LINKED_BLOCKING_QUEUE){
            executeByLinkedBlockQueue(command);
        } else if (strategy == Strategy.ARRAY_BLOCKING_QUEUE){
            executeByArrayBlockingQueue(command);
        }
    }

    private class WorkerThread extends Thread {
        private int index = -1;
        private boolean isRunning = true;
        private boolean isWaiting = false;
        
        public WorkerThread(int index){
            this.index = index;
        }
        
        
        public void stopWorker(){
            isRunning = false;
        }
        public boolean isWaiting(){
            return this.isWaiting;
        }

        public Date getWaitingTime() {
            return waitingTime;
        }

        private Date waitingTime;

        public void run(){
            if (isShowMessage){
                System.out.println("worker("+index+") is start");
            }
            synchronized (newWorkStart){
                newWorkStart.notify();
            }

            while (isRunning){
                Task task = null;
                // 使用直接提交策略
                if(strategy == Strategy.SYNCHRONOUS_QUEUE){
                    try {
                        task = (Task) workQueue.poll(getIdleThreadPollTime, TimeUnit.MILLISECONDS);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }

                } else if (strategy == Strategy.LINKED_BLOCKING_QUEUE){
                    // 无界队列策略
                    synchronized (workQueue){
                        // 取出任务
                        if (isRunning){
                            try {
                                task = (Task) workQueue.poll(getIdleThreadPollTime, TimeUnit.MILLISECONDS);
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                            }
                        }
                    }
                } else if (strategy == Strategy.ARRAY_BLOCKING_QUEUE){
                    // 有界队列策略
                    try {
                        task = (Task) workQueue.poll(getIdleThreadPollTime, TimeUnit.MILLISECONDS);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }

                }

                if (task != null){
                    isWaiting = false;
                    if (isShowMessage){
                        System.out.println("Worker("+index+") is run: " + task.toString());
                    }
                    
                    try {
						task.getMethod().invoke(task.getExecute(), task.getParameters());
					} catch (IllegalAccessException e) {
						e.printStackTrace();
					} catch (IllegalArgumentException e) {
						e.printStackTrace();
					} catch (InvocationTargetException e) {
						e.printStackTrace();
					}
                    
                    completeTaskCount.getAndIncrement();
                    if (isShowMessage)
                    {
                        System.out.println("Worker("+index+") is stop: " + task.toString());
                    }
                    isWaiting =true;
                    waitingTime = new Date();
                    task = null;
                }
                
                // 线程空闲， 检测超时线程
                mainLock.lock();
                cleanOutTimeThread();
                mainLock.unlock();
            }

            if (isShowMessage){
                System.out.println("Worker("+index+") is over");
            }
        }
    }

    public boolean isShowMessage() {
        return isShowMessage;
    }

    public void setShowMessage(boolean showMessage) {
        isShowMessage = showMessage;
    }

    public int getCorePoolSize() {
        return corePoolSize;
    }

    public void setCorePoolSize(int corePoolSize) {
        this.corePoolSize = corePoolSize;
    }

    public int getMaximumPoolSize() {
        return maximumPoolSize;
    }

    public void setMaximumPoolSize(int maximumPoolSize) {
        this.maximumPoolSize = maximumPoolSize;
    }

    public long getKeepAliveTime(TimeUnit unit){
        return unit.convert(keepAliveTime, TimeUnit.NANOSECONDS);
    }

    public void setKeepAliveTime(long time, TimeUnit unit) {
        if (time < 0)
            throw new IllegalArgumentException();
        if (time == 0 && isAllowCoreThreadTimeOut())
            throw new IllegalArgumentException("Core threads must have nonzero keep alive times");
        long keepAliveTime = unit.toNanos(time);
        this.keepAliveTime = keepAliveTime;
    }

    public boolean isAllowCoreThreadTimeOut() {
        return allowCoreThreadTimeOut;
    }

    public void setAllowCoreThreadTimeOut(boolean allowCoreThreadTimeOut) {
        this.allowCoreThreadTimeOut = allowCoreThreadTimeOut;
    }

    public int getPoolSize() {
        return currPoolSize;
    }

    public int getTaskCount() {
        return taskCount;
    }

    public int getCompleteTaskCount() {
        return completeTaskCount.get();
    }

}
