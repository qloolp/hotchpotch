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
		
		this.setFileFilter(new FileNameExtensionFilter("Txt File","txt"));                      //����ʽɸѡ
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
		if(!jta.getText().equals(history))     //��鵱ǰ�ļ��Ƿ����
			Save();  
		history = null;
		jta.setText(null);
		MyNotepad.isANewFile = true;
	}
	
	public void Open() throws 
IOException
	{
		if(!jta.getText().equals(history))     //��鵱ǰ�ļ��Ƿ����
			Save();  		
		
		this.setSelectedFile(new File(this.getCurrentDirectory(),"*.txt"));
		this.setDialogTitle("Open");
		this.showOpenDialog(null);
		
		path = this.getSelectedFile();
		
		BufferedReader br = new BufferedReader(new FileReader(path));
		StringBuffer sb = new StringBuffer();
		String oneLine;
		while((oneLine=br.readLine())!=null)         //�ļ��������ж���
			sb.append(oneLine+'\n');
		br.close();
		
		history = sb.toString();                   //��������history
		
		jta.setText(history);
		
		MyNotepad.isANewFile = false;
	}
	
	public void Save() throws IOException
	{
		if(MyNotepad.isANewFile)                      //���½��ļ�
		{			
			SaveAs();
		}
		else
		{
		                                           	//ֱ��д�ļ�
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
		
		this.showSaveDialog(null);                   //�ļ�����Ի���
	   
		path = this.getSelectedFile();
		
		path = new File(path.getParentFile(),path.getName());
		
		MyNotepad.isANewFile = false;   
		
		                                             //д�ļ�
    	BufferedWriter bw = new BufferedWriter(new FileWriter(path));

		history = jta.getText();
		bw.write(history);
    	bw.close();
	}


}
