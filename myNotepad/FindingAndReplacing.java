package myNotepad;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JRadioButton;
import javax.swing.JTextArea;
import javax.swing.JTextField;

public class FindingAndReplacing extends JDialog implements ActionListener
{
	private JTextArea jta;
	private JLabel jlfind = new JLabel("Find what:");
	private JLabel jlreplace = new JLabel("Replace with:");
	private JTextField jtffind = new JTextField(10);
	private JTextField jtfreplace = new JTextField(10);
	private JButton jbfind = new JButton("Find Next");
	private JButton jbreplace = new JButton("Replace");
	private JButton jbreplaceAll = new JButton("Replace All");
	private JButton jbcancel = new JButton("Cancel");
	private JRadioButton jbMatchCase = new JRadioButton("Match case",false);
	
	private int start=0;
	private int end;
	private int length;
	private String text;
	private String findText;
	private String replaceText;
	public FindingAndReplacing(JFrame owner, JTextArea jta)
	{
		super(owner,"FindAndReplace",true);
		this.jta = jta;
		jlfind.setBounds(10,10,100,20);		
		jtffind.setBounds(120,10,90,20);	
		jbfind.setBounds(220,10,100,20);
		
		jlreplace.setBounds(10,40,100,20);
		jtfreplace.setBounds(120,40,90,20);
		jbreplace.setBounds(220,40,100,20);
		jbreplaceAll.setBounds(220,70,100,20);
		
		jbcancel.setBounds(220,120,100,20);
		
		
		
		this.setLayout(null);
		add(jlfind);
		add(jtffind);
		add(jbfind);

		jbfind.addActionListener(this);
		jbreplace.addActionListener(this);
		jbreplaceAll.addActionListener(this);
		jbcancel.addActionListener(this);
		
		
		
		
		this.addWindowListener(new WindowAdapter(){
			public void windClosing(WindowEvent e){
				FindingAndReplacing.this.dispose();
			}
		});
	}
	
	public void showfind()
	{
		
		jbMatchCase.setBounds(10,60,100,20);
		add(jbMatchCase);
		this.setTitle("Find");
		this.setBounds(450,250,350,150);
		this.setVisible(true);
	}
	
	public int find()
	{

		text = jta.getText();
		findText = jtffind.getText();
		
		if(!jbMatchCase.isSelected())
		{
			text = text.toUpperCase();
			findText = findText.toUpperCase();
		}
		
		length = findText.length();
		end = text.length();

		if(start<=end)
		{
			start = text.indexOf(findText,start);
			if(start>=0)
			{
				jta.setSelectionStart(start);
				jta.setSelectionEnd(start+length);
				start += length;
				return start-length;
			}
		}
		jta.setSelectionStart(text.length());
		jta.setSelectionEnd(text.length());		
		return -1;
	}
	
	
	public void showreplace()
	{
		
		this.setTitle("Replace");
		add(jlreplace);
		add(jtfreplace);
		add(jbreplace);
		add(jbreplaceAll);
		add(jbcancel);
		jbMatchCase.setBounds(10,120,100,20);
		add(jbMatchCase);
		this.setBounds(450,250,350,200);
		this.setVisible(true);		
	}

	public int replace(Boolean replaceAll)
	{
		int index;
		replaceText = jtfreplace.getText();
		while(replaceAll)
		{
			start = 0;
			index = find();
			if(index>=0)
			{
				jta.replaceRange(replaceText, jta.getSelectionStart(), jta.getSelectionEnd());
	//			System.out.println(replaceText);
			//	System.out.println(x);
			}
			else
				return index;
		}
		
		while(!replaceAll)
		{
			start = 0;
			System.out.println(" 准备替换，statr:"+jta.getSelectionStart()+"    end"+jta.getSelectionEnd());
			if(jta.getSelectionEnd()>jta.getSelectionStart())
				jta.replaceRange(replaceText, jta.getSelectionStart(), jta.getSelectionEnd());
			
			find();
	//		System.out.println("back:  end"+jta.getSelectionEnd()+"statr:"+jta.getSelectionStart());
			System.out.println(" 下一个，statr:"+jta.getSelectionStart()+"    end"+jta.getSelectionEnd());
			return jta.getSelectionStart();
		}
        return -1;
	}
	
	
	
	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		if(e.getSource() == jbfind)
		{
			find();
		}
		if(e.getSource() == jbreplace)
		{
			replace(false);
		}
		if(e.getSource() == jbreplaceAll)
		{
			replace(true);
		}
		
	}
	
	
}
