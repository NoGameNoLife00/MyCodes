package FileTree;

import java.io.File;

import javax.swing.Icon;
import javax.swing.filechooser.FileSystemView;
import javax.swing.tree.DefaultMutableTreeNode;

/**
 * Created by Administrator on 2016/3/29.
 */
public class FileTreeNode extends DefaultMutableTreeNode {
 
	private static final long serialVersionUID = 1L;


	static FileSystemView fileSystemView = FileSystemView.getFileSystemView();


    private boolean isInit;
    private boolean isDummyRoot;
    private String fileName;
    private Icon fileIcon;

    public File getFile() {
        return file;
    }

    private File file;

    public FileTreeNode(File file){
        this(file, false, true);
    }
    public FileTreeNode(File file, boolean isDummyRoot){
        this(file,isDummyRoot, true);
    }
    public FileTreeNode(File file, boolean isDummyRoot, boolean allowsChildren){
        super(file, allowsChildren);
        this.file = file;
        this.fileName = fileSystemView.getSystemDisplayName(file);
        this.fileIcon = fileSystemView.getSystemIcon(file);
        this.isDummyRoot = isDummyRoot;
    }

    public boolean isInit() {
        return isInit;
    }

    public void setInit(boolean init) {
        isInit = init;
    }

    public boolean isDummyRoot() {
        return isDummyRoot;
    }

    public void setDummyRoot(boolean dummyRoot) {
        isDummyRoot = dummyRoot;
    }

    public String getFileName() {
        return fileName;
    }

    public void setFileName(String fileName) {
        this.fileName = fileName;
    }

    public Icon getFileIcon() {
        return fileIcon;
    }

    public void setFileIcon(Icon fileIcon) {
        this.fileIcon = fileIcon;
    }
}
