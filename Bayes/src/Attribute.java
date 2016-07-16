
public class Attribute {
	private int id;
	private int count;
	private String name;
	private String type;
	
	
	public Attribute(int id, String name, String type){
		this.id = id;
		this.name = name;
		this.type = type;
		this.count = 1;
	}
	
	public int getCount() {
		return count;
	}

	public void addCount(){
		this.count ++;
	}

	@Override
	public boolean equals(Object o) {
		// TODO Auto-generated method stub
		Attribute a = (Attribute)o;
		if(a.id == id && a.name.equals(name) && a.type.equals(type)){
			return true;
		}else{
			return false;
		}
	}
	
	
}
