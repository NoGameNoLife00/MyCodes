package FileExplorerUI;

import javax.swing.*;

/**
 * Created by Administrator on 2016/3/28.
 */
public class Main {
    public static void main(String args[]){
        setLookAndFeel();

        final JFrame f=new FileExplorerWindow();
        f.setVisible(true);

    }
    public static void setLookAndFeel() {
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
