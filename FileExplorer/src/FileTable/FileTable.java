package FileTable;

import java.awt.Dimension;
import java.io.File;
import java.util.Comparator;

import javax.swing.JTable;
import javax.swing.table.TableModel;

/**
 * Created by Administrator on 2016/3/29.
 */
public class FileTable extends JTable {
    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public FileTable(){
        this.setDefaultRenderer(Object.class, new FileTableCellRenderer());
        this.setAutoCreateRowSorter(true);
        this.getTableHeader().setReorderingAllowed(false);
        this.setShowHorizontalLines(false);
        this.setShowVerticalLines(false);
        setIntercellSpacing(new Dimension(0,0)); //修改单元格间隔，因此也将影响网格线的粗细。
        setRowMargin(0);//设置相邻两行单元格的距离
    }

    public static final Comparator<File> FILE_COMPARATOR= new Comparator<File>() {
        @Override
        public int compare(File f1, File f2) {
            if (f1.isDirectory()){
                if (f2.isDirectory()){
                    return f1.getName().compareToIgnoreCase(f2.getName());
                } else {
                    return -1;
                }
            } else {
                if (!f2.isDirectory()){
                    return f1.getName().compareToIgnoreCase(f2.getName());
                } else {
                    return 1;
                }
            }
        }
    };

    @Override
    public void setModel(TableModel dataModel) {
        super.setModel(dataModel);

    }
}
