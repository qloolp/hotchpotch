package myNotepad;

import java.awt.BorderLayout;
import java.awt.Dialog;
import java.awt.Font;
import java.awt.Frame;
import java.awt.GraphicsEnvironment;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

public class JFontChooser extends JPanel implements ActionListener ,ListSelectionListener{
	
	private JTextArea jta;
	JDialog dialog;
	
	private Font historyFont;           //以前字体
	
	private String currFont;
	private int currStyle;
	private int currSize;
	
	private JLabel jlbFont;              //字体
	private JLabel jlbStyle;             //字形
	private JLabel jlbSize;              //尺寸
	private JTextField jtfFont;
	private JTextField jtfStyle;
	private JTextField jtfSize;
	private JButton ok = new JButton("Ok");
	private JButton cancel = new JButton("Cancel");
                                                                              //获得当前设备可使用字体
	private String[] availabelFonts = GraphicsEnvironment.getLocalGraphicsEnvironment().getAvailableFontFamilyNames();
	private String[] availabelStyle= {"Regular","Italic","Bold","Bold Italic"};
    private String[] availabelSize = {"8","9","11","12","14","16","18","20","22","24","26","28","36","48","72"};
	
	
	private JList jlFont = new JList(availabelFonts);
	private JList jlStyle = new JList(availabelStyle);
	private JList jlSize = new JList(availabelSize);
	private JScrollPane jspFont = new JScrollPane(jlFont);
	private JScrollPane jspStyle = new JScrollPane(jlStyle);
	private JScrollPane jspSize = new JScrollPane(jlSize);

	private JPanel jpExample;           //效果显示
	private JLabel jlExample;
	
	
	
	public JFontChooser(JTextArea jta)
	{
		this.jta = jta;
		
		historyFont = jta.getFont();        //获得当前文本区所使用字体
		
		currFont = historyFont.getFontName();
		currStyle = historyFont.getStyle();
		currSize = historyFont.getSize();
		
			
		this.setLayout(null);
		ok.addActionListener(this);
		cancel.addActionListener(this);		
        this.add(ok);
        ok.setBounds(10, 240, 60, 20);
        this.add(cancel);
        cancel.setBounds(80, 240, 60, 20);
        
        
		jlbFont = new JLabel("Font");
		jlbFont.setBounds(12, 10, 30, 20);
		this.add(jlbFont);
		
		
		jtfFont = new JTextField(historyFont.getName());
		jtfFont.setBounds(10, 30, 155, 20);
		jtfFont.setEditable(false);
		this.add(jtfFont);

		
		jlFont.addListSelectionListener(this);
		jlFont.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);      //设置为单选
		jspFont.setBounds(10,50,155,100);
		this.add(jspFont);
		
		jlbStyle = new JLabel("Style");
		jlbStyle.setBounds(175, 10, 30, 20);
		this.add(jlbStyle);
		
		
		String temp = new String();
		switch(historyFont.getStyle())
		{
		case Font.PLAIN :
			temp = "Regular";
			break;
		case Font.ITALIC:
			currStyle = Font.ITALIC;
			temp = "Italic";
			break;
		case Font.BOLD:
			temp = "Bold";
			break;
		case Font.BOLD|Font.ITALIC:
			temp = "Bold Italic";
		}
		
		jtfStyle = new JTextField(temp);
		jtfStyle.setBounds(175, 30, 130, 20);
		jtfStyle.setEditable(false);
		this.add(jtfStyle);

		
		jlStyle.addListSelectionListener(this);
		jlStyle.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		jspStyle.setBounds(175, 50, 130, 100);
		this.add(jspStyle);
		
		
		jlbSize = new JLabel("Size");
		jlbSize.setBounds(320, 10, 30, 20);
		this.add(jlbSize);
		
		
        jtfSize = new JTextField(Integer.toString(historyFont.getSize()));
        jtfSize.setBounds(320, 30, 60, 20);
        jtfSize.setEditable(false);
        this.add(jtfSize);
        
       
        jlSize.addListSelectionListener(this);
        jlSize.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        jspSize.setBounds(320, 50, 60, 100);
        this.add(jspSize);
        
        jpExample = new JPanel();
        jlExample = new JLabel("示例abcABC");
        jpExample.setBorder(javax.swing.BorderFactory.createTitledBorder("示例"));
        this.add(jpExample);
        jpExample.setBounds(150, 170, 230, 100);
        jpExample.setLayout(new BorderLayout());
        jpExample.add(jlExample);
        
        
        
	}
    public void show(JFrame parent)
    {
    	dialog = new JDialog(parent,"FontChooser",true);
    	dialog.add(this);
    	dialog.setSize(400, 310);
    	dialog.setResizable(true);
        dialog.addWindowListener(new WindowAdapter() {

            @Override
            public void windowClosing(WindowEvent e) {
                dialog.removeAll();
                dialog.dispose();
                dialog = null;
            }   	
    });
        
       dialog.setVisible(true); 
    }
        

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		if(e.getSource() == ok)
		{
			jta.setFont(new Font(currFont,currStyle,currSize));
			dialog.dispose();
			dialog = null;
		}else if(e.getSource() == cancel)
		{
			jta.setFont(historyFont);
			dialog.dispose();
			dialog = null;
		}
	}


	@Override
	public void valueChanged(ListSelectionEvent e) {
		// TODO Auto-generated method stub
		if(e.getSource() == jlFont)
		{
			currFont = (String)jlFont.getSelectedValue();
			jtfFont.setText(currFont);
			jlExample.setFont(new Font(currFont,currStyle,currSize));
		}else if(e.getSource() == jlStyle)
		{
			switch((String)jlStyle.getSelectedValue())
			{
			case "Regular" :
				currStyle = Font.PLAIN;
				break;
			case "Italic":
				currStyle = Font.ITALIC;
				break;
			case "Bold":
				currStyle = Font.BOLD;
				break;
			case "Bold Italic":
				currStyle = Font.BOLD|Font.ITALIC;
			}
			jtfStyle.setText((String)jlStyle.getSelectedValue());
			jlExample.setFont(new Font(currFont,currStyle,currSize));
		}else if(e.getSource() == jlSize)
		{
			currSize = Integer.parseInt((String)jlSize.getSelectedValue());
			jtfSize.setText(Integer.toString(currSize));
			jlExample.setFont(new Font(currFont,currStyle,currSize));
		}
	}
	
}
