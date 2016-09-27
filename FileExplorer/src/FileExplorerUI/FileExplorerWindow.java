package FileExplorerUI;

import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.util.Collections;
import java.util.Comparator;
import java.util.Stack;
import java.util.Vector;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTextField;
import javax.swing.JTree;
import javax.swing.ScrollPaneLayout;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.filechooser.FileSystemView;
import javax.swing.table.TableRowSorter;
import javax.swing.tree.DefaultTreeModel;

import FileTable.FileTable;
import FileTable.FileTableModel;
import FileTree.FileTree;
import FileTree.FileTreeCellRenderer;
import FileTree.FileTreeNode;

/**
 * Created by Administrator on 2016/3/28.
 */
public class FileExplorerWindow extends JFrame {

	private static final long serialVersionUID = 1L;
	private JPanel pnlTop;
    private JPanel pnlLeft;
    private JPanel pnlRight;
    private JSplitPane spBottom;
    private JTextField tfDir;
    private FileTreeNode fileTreeRoot;
    private FileTree trFileTree;
    private FileTable tbFile;
    private Stack<File> stackFile;
    private JButton btnBack;
    File[] fileRoots;
    Object[][] initFileData;
    JScrollPane spTable;
    FileSystemView fileSystemView = FileSystemView.getFileSystemView();
    private void initData(){
        stackFile = new Stack<File>();
        fileRoots = fileSystemView.getRoots();
        fileTreeRoot = new FileTreeNode(fileRoots[0], true);
        File[] files = fileSystemView.getFiles(fileRoots[0], false);
        for (int i = 0; i < files.length; i++) {
            if (files[i].isDirectory())
            {
                FileTreeNode childNode = new FileTreeNode(files[i], false);
                fileTreeRoot.add(childNode);
            }
        }

        File[] libFiles = fileSystemView.getFiles(files[3], false);
        initFileData = new Object[libFiles.length][4];
        for (int i=0; i < libFiles.length; i++){
            for (int j = 0; j < 4; j++){
                initFileData[i][j] = files[i];
            }
        }
    }

    private void createComponent(){
        pnlTop = new JPanel();
        pnlLeft = new JPanel();
        pnlRight = new JPanel();
        spBottom = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
        tfDir = new JTextField();
        trFileTree = new FileTree();
        tbFile = new FileTable();
        btnBack = new JButton("后退");
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

    private void updateTable(File file, Boolean isBack){
        String path = file.getAbsolutePath();
        if (path == null)
            return;
        tfDir.setText(path);
        File[] files = fileSystemView.getFiles(file, false);

        if (!isBack){
            stackFile.push(file);
        }
        Vector<File> vFile = new Vector<File>();
        for (int i = 0; i < files.length; i++){
            vFile.add(files[i]);
        }
        Collections.sort(vFile, FILE_COMPARATOR);

        Object[][] fileData;
        fileData = new Object[files.length][4];
        for (int i = 0; i < fileData.length; i++){
            for (int j = 0; j < 4; j++){
                fileData[i][j] = vFile.elementAt(i);
            }
        }

        FileTableModel model = new FileTableModel(fileData);
        tbFile.setModel(model);
        TableRowSorter sort = new TableRowSorter(model);
        sort.setComparator(0, FILE_COMPARATOR);
        tbFile.setRowSorter(sort);
        // 设置table 列宽
        tbFile.getColumnModel().getColumn(0).setPreferredWidth(200);
        tbFile.getColumnModel().getColumn(1).setPreferredWidth(120);
        tbFile.getColumnModel().getColumn(2).setPreferredWidth(100);
        tbFile.getColumnModel().getColumn(3).setPreferredWidth(50);
        spTable.getViewport().setBackground(Color.white);

    }

    private void AddComponentListener(){
        trFileTree.addTreeSelectionListener(new TreeSelectionListener(){
            @Override
            public void valueChanged(TreeSelectionEvent e) {
                JTree tree = (JTree)e.getSource();
                FileTreeNode selectNode = (FileTreeNode)tree.getLastSelectedPathComponent();
                if (selectNode != null){
                    File file = selectNode.getFile();
                    updateTable(file, false);
                }
            }
        });

        trFileTree.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                if (e.getClickCount() == 1)
                {
                    JTree tree = (JTree)e.getSource();
                    FileTreeNode selectNode = (FileTreeNode)tree.getLastSelectedPathComponent();
                    if (selectNode != null){
                        File file = selectNode.getFile();
                        updateTable(file, false);
                    }
                }
            }
        });

        tbFile.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                FileTable fileTable = (FileTable)e.getSource();
                int row = fileTable.rowAtPoint(e.getPoint());
                File file = (File) fileTable.getValueAt(row, 0);
                if (e.getClickCount() == 1){
//                	TreePath path =trFileTree.getSelectionPath();
//                	path.pathByAddingChild(new FileTreeNode(file));
//                	trFileTree.setSelectionPath(path);
                } else if (e.getClickCount() == 2){
                    updateTable(file, false);
                }
            }
        });

        btnBack.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (stackFile.size()>1)
                {
                    stackFile.pop();
                    updateTable(stackFile.peek(), true);
                }

            }
        });

    }

    private void initComponent(){
        initData();
        createComponent();
        AddComponentListener();

        spTable = new JScrollPane(tbFile);
        spTable.setBackground(Color.white);
        // 设置table 列宽

        DefaultTreeModel dfTreeModel = new DefaultTreeModel(fileTreeRoot) {
            @Override
            public boolean isLeaf(Object node) {
                FileTreeNode treeNode = (FileTreeNode) node;
                if (treeNode.isDummyRoot()){
                    return false;
                }
                return ((File)treeNode.getUserObject()).isFile();
            }
        };
        trFileTree.setModel(dfTreeModel);
        trFileTree.setCellRenderer(new FileTreeCellRenderer());
        trFileTree.setRootVisible(false);
        trFileTree.setSelectionRow(0);

        JScrollPane scroll = new JScrollPane(trFileTree);
        scroll.setLayout(new ScrollPaneLayout());
        scroll.getViewport().setBackground(Color.WHITE);
        pnlLeft.setLayout(new GridBagLayout());
        pnlLeft.add(scroll, new GridBagConstraints(0, 0, 1, 1, 1.0, 1.0, GridBagConstraints.EAST,
                GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));

        pnlRight.setLayout(new GridBagLayout());


        pnlRight.add(spTable,new GridBagConstraints(0, 0, 1, 1, 1.0, 1.0, GridBagConstraints.EAST,
                GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));

        pnlTop.setLayout(new GridBagLayout());
        pnlTop.add(btnBack, new GridBagConstraints(0, 0, 1, 1, 0.05, 1.0, GridBagConstraints.WEST,
                GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));

        pnlTop.add(tfDir,new GridBagConstraints(1, 0, 1, 1, 0.95, 1.0, GridBagConstraints.EAST,
                GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));

        spBottom.setLeftComponent(pnlLeft);
        spBottom.setRightComponent(pnlRight);
        pnlLeft.setMinimumSize(new Dimension(200,600));

        Container container = this.getContentPane();
        container.setLayout(new GridBagLayout());
        container.add(pnlTop, new GridBagConstraints(0, 0, 1, 1, 1.0, 0.05, GridBagConstraints.EAST,
                GridBagConstraints.BOTH, new Insets(2, 0, 0, 0), 0, 0));
        container.add(spBottom, new GridBagConstraints(0, 1, 1, 1, 1.0, 0.95, GridBagConstraints.EAST,
                GridBagConstraints.BOTH, new Insets(4, 2, 2, 2), 0, 0));
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        this.setBounds(screenSize.width/2 - 400, screenSize.height/2 - 300, 800, 600);
        this.setMinimumSize(new Dimension(800, 600));
    }

    public FileExplorerWindow(){
        super("文件浏览器");
        initComponent();
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosed(WindowEvent e) {
                super.windowClosed(e);
            }
        });
    }

}
