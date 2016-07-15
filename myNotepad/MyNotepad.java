package myNotepad;

import java.awt.Color;
import java.awt.FileDialog;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.io.IOException;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JFrame; 
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JRadioButtonMenuItem;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

public class MyNotepad extends JFrame implements ActionListener{

	public Boolean isSaved = false;
	public Boolean HaveOpenedFile = false;
	public static Boolean isANewFile = true;
	
	private JTextArea jta = new JTextArea();
	
	private JScrollPane jsp = new JScrollPane(jta); 
	
	private JPanel jp = new JPanel();
	
	private JMenuBar jmb = new JMenuBar();
	
	private FindingAndReplacing findAndReplace = new FindingAndReplacing(this,jta);
	
	private MyFile myFile = new MyFile(jta);
	
	private JFontChooser fontChooser = new JFontChooser(jta);
	
	
	private JMenu jm[] = {new JMenu("File"), new JMenu("Edit"), new JMenu("Format"), 
	new JMenu("Help")};

	private JMenuItem jmiFile[] = { new JMenuItem("New"), new JMenuItem("Open"), new JMenuItem("Save"), new JMenuItem("Save As")}; 
	
	private JMenuItem jmiEdit[] = { new JMenuItem("Undo"), new JMenuItem("Cut"), new JMenuItem("Copy"), new JMenuItem("Paste"),
			new JMenuItem("Delete"), new JMenuItem("Find"), new JMenuItem("Replace")};

	private JMenuItem jmiFormat[] = {new JRadioButtonMenuItem("Word Wrap",true), new JMenuItem("Font…")};
	
	
	public MyNotepad()
	{
		jp.setLayout(new GridLayout(1, 3));         //设置JPanel的布局管理器
		
		jp.add(jsp);                 //将JScorrPane添加到JPanel中
	
		jta.setLineWrap(true);            //设置JTextArea为自动换行
		
		jta.setEditable(true);
		
		jta.setSelectedTextColor(Color.WHITE);           //设置选择字体颜色
		jta.setSelectionColor(Color.blue);                    //设置选择部分的背景色
		

		
		
		
		
		jmb.add(jm[0]);
		for(int i=0; i<jmiFile.length; i++)
		{
			jm[0].add(jmiFile[i]);
			jmiFile[i].addActionListener(this);
		}
		
		jmb.add(jm[1]);
		for(int i=0; i<jmiEdit.length; i++)
		{
			jm[1].add(jmiEdit[i]);
			jmiEdit[i].addActionListener(this);
		}
		
		jmb.add(jm[2]);
		for(int i=0; i<jmiFormat.length; i++)
		{
			jm[2].add(jmiFormat[i]);
			jmiFormat[i].addActionListener(this);
		}
			

		this.setJMenuBar(jmb);
		
		this.add(jp);
		
		this.setTitle("MyNotepad-Untitled");
		
		this.setBounds(300,100,600,600);
		
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		
		
		this.addWindowListener(new WindowAdapter(){
        @Override
        public void windowClosing(WindowEvent e) {
        	try {
				myFile.Save();
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
        }  
	});
		
		
		
		
		
		
		this.setVisible(true);
	}
	

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		new MyNotepad();
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub

		//File
		for(int i=0; i<jmiFile.length; i++)
		{
			if(e.getSource() == jmiFile[i])
			{
				switch(i)
				{
				case 0:
					try {
						myFile.New();
						this.setTitle("MyNotepad/Untitled.txt");
					} catch (IOException e2) {
						// TODO Auto-generated catch block
						e2.printStackTrace();
					}
					break;
				case 1:

					try {
						myFile.Open();
						File path = myFile.getPath();
						String fileName = path.getName();
						this.setTitle("MyNotepad/"+fileName);						
					} catch (IOException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					break;
				case 2:

					try {
						myFile.Save();
						File path = myFile.getPath();
						String fileName = path.getName();
						this.setTitle("MyNotepad/"+fileName);	
					} catch (IOException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					break;
				case 3:
					try {
						myFile.SaveAs();
						File path = myFile.getPath();
						String fileName = path.getName();
						this.setTitle("MyNotepad/"+fileName);								
					} catch (IOException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					break;				
				}
			}
		}
		//Edit
		for(int i=0; i<jmiEdit.length; i++)
		{
			if(e.getSource()==jmiEdit[i])
			{
				switch(i)
				{
				case 0:
					jta.setText(null);
					jta.append("Undo");
					break;
				case 1:
					jta.cut();
					break;
				case 2:
					jta.copy();
					break;
				case 3:
					jta.paste();
					break;
				case 4:
					jta.setText(null);
					jta.append("Delete");
				case 5:
					findAndReplace.showfind();
					break;
				case 6:
					findAndReplace.showreplace();
					break;			
				}
			}
		}
		//Format
		if(e.getSource() == jmiFormat[0])
		{
			if(jmiFormat[0].isSelected())
				jta.setLineWrap(true);
			else
				jta.setLineWrap(false);
			
		}else if(e.getSource() == jmiFormat[1])
		{
		//	jta.setText(null);
		//	jta.append("Font");
			fontChooser.show(this);
			
			
		}
	}

}




