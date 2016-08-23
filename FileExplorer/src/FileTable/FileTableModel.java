package FileTable;

import java.io.File;

import javax.swing.filechooser.FileSystemView;
import javax.swing.table.DefaultTableModel;

/**
 * Created by Administrator on 2016/3/29.
 */
public class FileTableModel extends DefaultTableModel {

	private static final long serialVersionUID = 1L;
	private static String[] tableHeader = {"名称", "修改日期", "类型", "大小"};
    private FileSystemView fileSystemView = FileSystemView.getFileSystemView();
    public FileTableModel(Object[][] objects){
        super(objects, tableHeader);
    }

    @Override
    public boolean isCellEditable(int row, int column) {
        return false;
    }


    @Override
    public Object getValueAt(int row, int column) {
        File file = (File) super.getValueAt(row, column);
        if (column == 0){
            return file;
        } else if (column == 1){
            return file.lastModified();
        } else if (column == 2) {
            return fileSystemView.getSystemTypeDescription(file);
        } else if (column == 3){
            return file.length();
        }
        return super.getValueAt(row, column);
    }
}
