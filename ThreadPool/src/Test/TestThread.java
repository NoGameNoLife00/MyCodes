package Test;

public class TestThread {
	public void execute(Object param){
		int maxCount = (int) param;
        for (int i = 0; i <= maxCount; i++){
            System.out.println(i);
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
	}
}
