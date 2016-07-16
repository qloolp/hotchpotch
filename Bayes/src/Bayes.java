import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

class Bayes{
	
	private ArrayList<Attribute> data;
	private ArrayList<Attribute> ap;
	private int[] tp;     //unacc, acc, good, vgood
	
	public Bayes(){
		data = new ArrayList<>();
		ap = new ArrayList<>();
		tp = new int[4];
	}
	
	
	public void ReadFile() throws IOException{
		BufferedReader in = new BufferedReader(new FileReader(new File("learn.txt")));
		String temp;
		String[] line;
		int length;
		while((temp = in.readLine())!= null){
			line = temp.split(",");
			length = line.length-1;
			for(int i=0; i<length; i++){
				data.add(new Attribute(i, line[i], line[length]));
			}
			if(line[length].equals("unacc")){
				tp[0]++;
			}else if(line[length].equals("acc")){
				tp[1]++;
			}else if(line[length].equals("good")){
				tp[2]++;
			}else {
				tp[3]++;
			}
		}
		
	}

	public void computeCount(){
		int index;
		for (Attribute a : data) {
			index = ap.indexOf(a);
			if(index == -1){
				ap.add(a);
			}else{
				ap.get(index).addCount();
			}
		}
	}
	
	public int computeProbility(String t){
		String[] att = t.split(",");
		Attribute a;
		Attribute b;
		String re = null;
		int index;
		int type;//unacc, acc, good, vgood
		int length;
		double[] p={1.0,1.0,1.0,1.0};
		
		length = att.length-1;
		
		
		for(int i=0; i<length; i++){          //unacc
			a = new Attribute(i, att[i], "unacc");
			index = ap.indexOf(a);
			if(index == -1){
				p[0] *= (double)tp[3]/(double)(tp[0]+tp[1]+tp[2]+tp[3]);
				continue;
			}
			b = ap.get(index);

			p[0] *=  (double)b.getCount()/(double)tp[0];
		}
		
		for(int i=0; i<length; i++){          //acc
			a = new Attribute(i, att[i], "acc");
			index = ap.indexOf(a);
			if(index == -1){
				p[1] *= (double)tp[3]/(double)(tp[0]+tp[1]+tp[2]+tp[3]);
				continue;
			}
			b = ap.get(index);
			p[1] *=  (double)b.getCount()/(double)tp[1];
		}
		
		for(int i=0; i<length; i++){          //good
			a = new Attribute(i, att[i], "good");
			index = ap.indexOf(a);
			if(index == -1){
				p[2] *= (double)tp[3]/(double)(tp[0]+tp[1]+tp[2]+tp[3]);
				continue;
			}
			
			b = ap.get(index);
			p[2] *=  (double)b.getCount()/(double)tp[2];
		}
		
		
		for(int i=0; i<length; i++){          //vgood
			a = new Attribute(i, att[i], "vgood");
			index = ap.indexOf(a);
			if(index == -1){
				p[3] *= (double)tp[3]/(double)(tp[0]+tp[1]+tp[2]+tp[3]);
				continue;
			}
			b = ap.get(index);
			p[3] *=  (double)b.getCount()/(double)tp[3];
		}
		
		
		double max=-1;
		index = 0;
		
		for(int i=0; i<p.length; i++){
			if(max<p[i]){
				max = p[i];
				index = i;
			}
		}
		return index;
	}

	
	public void check() throws IOException{
		int sum=0;
		int right=0;
		int index;
		
		ReadFile();
		computeCount();
		ArrayList<String> type = new ArrayList<>();
		BufferedReader in = new BufferedReader(new FileReader(new File("test.txt")));
		String temp;
		String[] line;
		type.add("unacc");
		type.add("acc");
		type.add("good");
		type.add("vgood");
		while((temp = in.readLine())!=null){
			line = temp.split(",");
			index = type.indexOf(line[line.length-1]);
			sum++;
			if(index == computeProbility(temp)){
				right++;
			}
		}
		double p = (double)right/(double)sum;
		System.out.println("sum:"+sum+"\t\tright:"+right+"\t\tCorrect rate:"+p);
	}
	
	public  static void main(String[] arvgs) throws IOException{
		new Bayes().check();
	}
}