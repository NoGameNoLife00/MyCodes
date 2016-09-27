package FileTree;

import java.awt.Rectangle;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.File;

import javax.swing.JTree;
import javax.swing.event.TreeExpansionEvent;
import javax.swing.event.TreeWillExpandListener;
import javax.swing.filechooser.FileSystemView;
import javax.swing.tree.ExpandVetoException;
import javax.swing.tree.TreePath;

/**
 * Created by Administrator on 2016/3/29.
 */
public class FileTree extends JTree {
	private static final long serialVersionUID = 1L;
	public TreePath mouseInPath;
    static protected FileSystemView fileSystemView = FileSystemView.getFileSystemView();
    public FileTree() {
        setRootVisible(false);
        addTreeWillExpandListener(new TreeWillExpandListener(){
            @Override
            public void treeWillExpand(TreeExpansionEvent event) throws ExpandVetoException {
                FileTreeNode fileNode = (FileTreeNode)event.getPath().getLastPathComponent();
                if (!fileNode.isInit()){
                    File[] files;
                    if(fileNode.isDummyRoot()) {
                        files = fileSystemView.getRoots();
                    } else {
                        files = fileSystemView.getFiles(fileNode.getFile(), false);
                    }

                    for (int i = 0; i < files.length; i++){
                        if (files[i].isDirectory())
                        {
                            FileTreeNode childFileNode = new FileTreeNode(files[i]);
                            fileNode.add(childFileNode);
                        }
                    }
                }
                fileNode.setInit(true);
            }

            @Override
            public void treeWillCollapse(TreeExpansionEvent event) throws ExpandVetoException {

            }
        });

        addMouseMotionListener(new MouseAdapter() {
            @Override
            public void mouseMoved(MouseEvent e) {
                TreePath path = getPathForLocation(e.getX(), e.getY());
                if (path != null) {
                    if (mouseInPath != null) {
                        Rectangle oldRect = getPathBounds(mouseInPath);
                        mouseInPath = path;
                        repaint(getPathBounds(path).union(oldRect));
                    } else {
                        mouseInPath = path;
                    }
                } else if (mouseInPath != null) {
                    Rectangle oldRect =getPathBounds(mouseInPath);
                    mouseInPath = null;
                    repaint(oldRect);
                }
            }
        });
    }
}
