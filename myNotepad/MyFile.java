package myNotepad;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import javax.swing.JFileChooser;
import javax.swing.JTextArea;
import javax.swing.filechooser.FileNameExtensionFilter;

public class MyFile extends JFileChooser{

	private JTextArea jta;
	private String history;
	private File path;

	
	
	public MyFile(JTextArea jta)
	{
         
		this.jta = jta;
		history = new String("");
		
		this.setFileFilter(new FileNameExtensionFilter("Txt File","txt"));                      //按格式筛选
	}


	public File getPath()
	{
		return path;
	}
	
	
	public File getDefaultPath()
	{

		File defaultPath = this.getCurrentDirectory();
		defaultPath = new File(defaultPath,"*.txt");
		return defaultPath;
	}
	
	
	
	
	
	
	public void New() throws IOException
	{
		if(!jta.getText().equals(history))     //检查当前文件是否更改
			Save();  
		history = null;
		jta.setText(null);
		MyNotepad.isANewFile = true;
	}
	
	public void Open() throws 
IOException
	{
		if(!jta.getText().equals(history))     //检查当前文件是否更改
			Save();  		
		
		this.setSelectedFile(new File(this.getCurrentDirectory(),"*.txt"));
		this.setDialogTitle("Open");
		this.showOpenDialog(null);
		
		path = this.getSelectedFile();
		
		BufferedReader br = new BufferedReader(new FileReader(path));
		StringBuffer sb = new StringBuffer();
		String oneLine;
		while((oneLine=br.readLine())!=null)         //文件内容逐行读入
			sb.append(oneLine+'\n');
		br.close();
		
		history = sb.toString();                   //重新设置history
		
		jta.setText(history);
		
		MyNotepad.isANewFile = false;
	}
	
	public void Save() throws IOException
	{
		if(MyNotepad.isANewFile)                      //是新建文件
		{			
			SaveAs();
		}
		else
		{
		                                           	//直接写文件
			BufferedWriter bw = new BufferedWriter(new FileWriter(path));
			history = jta.getText();
			bw.write(history);
			bw.close();
		}

	}
	
	public void SaveAs() throws IOException
	{
		
		this.setDialogTitle("Save As");	
		
		this.setSelectedFile(this.getDefaultPath());
		
		this.showSaveDialog(null);                   //文件保存对话框
	   
		path = this.getSelectedFile();
		
		path = new File(path.getParentFile(),path.getName());
		
		MyNotepad.isANewFile = false;   
		
		                                             //写文件
    	BufferedWriter bw = new BufferedWriter(new FileWriter(path));

		history = jta.getText();
		bw.write(history);
    	bw.close();
	}


}
